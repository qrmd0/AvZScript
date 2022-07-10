/*
 * @Author: qrmd
 * @Date: 2022-06-20 18:43:47
 * @LastEditors: qrmd
 * @LastEditTime: 2022-06-21 11:25:17
 * @Description: FE二十四炮 全难度极限出怪运阵演示脚本
 * 使用方法：1、前往https://gitee.com/vector-wlc/AsmVsZombies，根据教程下载并安装好AsmVsZombies
 *          2、在Visul Studio Code中打开本脚本，右键点击编辑区空白处，在弹出菜单中选择“AvZ:Run Script”
 * 更多AvZ脚本尽在AvZScript公开脚本仓库：
 * 主库：https://github.com/qrmd0/AvZScript
 * 镜像库：https://gitee.com/qrmd/AvZScript
 * Copyright (c) 2022 by qrmd , All Rights Reserved.
 */

#include "avz.h"

using namespace AvZ;
// 自动在[row]行[col]列种植三叶草清除浓雾。结合TickRunner使用
void CleanFog(int row, int col);
TickRunner fog_cleaner;
// *** In Queue
// 留下一行领带僵尸或巨人僵尸，自动放置植物将其拖住以延长第20波收尾，适用于六行场地
void EndingTheRound();
// 自动在指定位置放置植物触发巨人僵尸举锤阻挡其前进。结合TickRunner使用
void BlockGargantuar(std::vector<Grid> pos);
TickRunner block_giga;
void Script()
{
    // 脚本在游戏主界面和选择植物界面生效
    OpenMultipleEffective('Q', MAIN_UI_OR_FIGHT_UI);
    // 全难度极限出怪：普僵、撑杆、橄榄、舞王、冰车、小丑、矿工、跳跳、小偷、扶梯、投篮、白眼、红眼、海豚
    SetZombies({ZOMBIE, POLE_VAULTING_ZOMBIE, FOOTBALL_ZOMBIE, DANCING_ZOMBIE, ZOMBONI, JACK_IN_THE_BOX_ZOMBIE, DIGGER_ZOMBIE, POGO_ZOMBIE, BUNGEE_ZOMBIE, LADDER_ZOMBIE, CATAPULT_ZOMBIE, GARGANTUAR, GIGA_GARGANTUAR, DOLPHIN_RIDER_ZOMBIE});
    // 选择植物：寒冰菇、模仿寒冰菇、毁灭菇、火爆辣椒、阳光菇、南瓜头、樱桃炸弹、小喷菇、花盆、胆小菇、三叶草
    SelectCards({ICE_SHROOM, M_ICE_SHROOM, DOOM_SHROOM, JALAPENO, SUN_SHROOM, PUMPKIN, CHERRY_BOMB, PUFF_SHROOM, FLOWER_POT, BLOVER});
    SetTime(-599, 1);
    // 填充炮列表
    pao_operator.resetPaoList({{1, 1}, {6, 1}, {1, 3}, {6, 3}, {1, 5}, {6, 5}, {1, 7}, {6, 7}, {2, 1}, {5, 1}, {2, 3}, {5, 3}, {2, 5}, {5, 5}, {2, 7}, {5, 7}, {3, 1}, {4, 1}, {3, 3}, {4, 3}, {3, 5}, {4, 5}, {3, 7}, {4, 7}});
    // 开始自动存冰
    ice_filler.start({{4, 9}});
    // 开始自动修补南瓜头
    plant_fixer.start(PUMPKIN, {{3, 9}, {4, 9}}, 1200);
    // 铲除临时植物
    Shovel({{1, 9}, {2, 9}, {5, 9}, {6, 9}});
    // 开始自动清除浓雾
    Shovel(3, 9);
    Card(BLOVER, 3, 9);
    SetTime(-300, 1);
    InsertOperation([=]() {
        fog_cleaner.pushFunc([]() {
            CleanFog(3, 9);
        });
    });
    // 主体节奏 P6-2I PPSSDD|PPDD|PPSSDD|PPDD|NA|I3PPI-DD 601|601|601|601|601|601 每波执行确定的操作，不考虑非旗帜波的刷新延迟
    // wave1 PPSSDD
    SetTime(295 - 373 - 3, 1);
    pao_operator.pao({{2, 8.8}, {5, 8.8}, {2, 8.8}, {5, 8.8}});
    SetTime(295 + 110 - 376, 1);
    pao_operator.pao({{1, 8.8}, {5, 8.8}});

    // wave2 PPDD
    SetTime(359 - 373, 2);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    SetTime(359 - 373 + 107, 2);
    pao_operator.pao({{1, 7.7}, {5, 7.7}});

    // wave3 PPSSDD
    SetTime(295 - 373 - 3, 3);
    pao_operator.pao({{2, 8.8}, {5, 8.8}, {2, 8.8}, {5, 8.8}});
    SetTime(295 + 110 - 376, 3);
    pao_operator.pao({{1, 8.8}, {5, 8.8}});

    // wave4 PPDD
    SetTime(359 - 373, 4);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    SetTime(359 - 373 + 107, 4);
    pao_operator.pao({{1, 7.7}, {5, 7.7}});

    // wave5 NA
    SetTime(0, 5);
    fog_cleaner.pause();
    SetTime(295 - 100, 5);
    Card(DOOM_SHROOM, 2, 9);
    Card(JALAPENO, 6, 9);
    SetTime(295 - 1 + 105 - 420, 5);
    fog_cleaner.pause();
    Card(M_ICE_SHROOM, 3, 9);
    SetPlantActiveTime(ICE_SHROOM, 420);

    // wave6 I3PPIDD
    SetTime(359 - 373, 6);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    SetTime(359 + 110 - 373, 6);
    pao_operator.pao({{1, 7.7}, {5, 7.7}});
    SetTime(359 - 100, 6);
    Card(ICE_SHROOM, 3, 9);
    SetPlantActiveTime(ICE_SHROOM, 100);
    SetTime(359 + 1, 6);
    fog_cleaner.goOn();

    // wave7 PPSSDD
    SetTime(268 - 373 - 3, 7);
    pao_operator.pao({{2, 8.8}, {5, 8.8}, {2, 8.8}, {5, 8.8}});
    SetTime(268 + 110 - 376, 7);
    pao_operator.pao({{1, 8.8}, {5, 8.8}});

    // wave8 PPDD
    SetTime(359 - 373, 8);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    SetTime(359 - 373 + 107, 8);
    pao_operator.pao({{1, 7.7}, {5, 7.7}});

    // wave9 PPSSDD-PP
    SetTime(295 - 373 - 3, 9);
    pao_operator.pao({{2, 8.8}, {5, 8.8}, {2, 8.8}, {5, 8.8}});
    SetTime(295 + 110 - 376, 9);
    pao_operator.pao({{1, 8.8}, {5, 8.8}});
    SetTime(295 + 601 - 376, 9);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});

    // wave10 PPDD
    SetTime(359 - 373, 10);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    SetTime(359 - 373 + 107, 10);
    pao_operator.pao({{1, 7.7}, {5, 7.7}});
    SetTime(359, 10);
    Card(PUFF_SHROOM, 3, 9);

    // wave11 PPSSDD
    SetTime(295 - 373 - 3, 11);
    pao_operator.pao({{2, 8.8}, {5, 8.8}, {2, 8.8}, {5, 8.8}});
    SetTime(295 + 110 - 376, 11);
    pao_operator.pao({{1, 8.8}, {5, 8.8}});

    // wave12 PPDD
    SetTime(359 - 373, 12);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    SetTime(359 - 373 + 107, 12);
    pao_operator.pao({{1, 7.7}, {5, 7.7}});

    // wave13 PPSSDD
    SetTime(295 - 373 - 3, 13);
    pao_operator.pao({{2, 8.8}, {5, 8.8}, {2, 8.8}, {5, 8.8}});
    SetTime(295 + 110 - 376, 13);
    pao_operator.pao({{1, 8.8}, {5, 8.8}});

    // wave14 PPDD
    SetTime(359 - 373, 14);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    SetTime(359 - 373 + 107, 14);
    pao_operator.pao({{1, 7.7}, {5, 7.7}});

    // wave15 NA
    SetTime(295 - 100, 15);
    Card(DOOM_SHROOM, 5, 9);
    Card(JALAPENO, 1, 9);
    SetTime(295 - 1 + 105 - 420, 15);
    fog_cleaner.pause();
    Card(M_ICE_SHROOM, 3, 9);
    SetPlantActiveTime(ICE_SHROOM, 420);

    // wave16 I3PPIDD
    SetTime(359 - 373, 16);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    SetTime(359 + 110 - 373, 16);
    pao_operator.pao({{1, 7.7}, {5, 7.7}});
    SetTime(359 - 100, 16);
    Card(ICE_SHROOM, 3, 9);
    SetPlantActiveTime(ICE_SHROOM, 100);
    SetTime(359 + 1, 16);
    fog_cleaner.goOn();

    // wave17 PPSSDD
    SetTime(268 - 373 - 3, 17);
    pao_operator.pao({{2, 8.8}, {5, 8.8}, {2, 8.8}, {5, 8.8}});
    SetTime(268 + 110 - 376, 17);
    pao_operator.pao({{1, 8.8}, {5, 8.8}});

    // wave18 PPDD
    SetTime(0, 18);
    plant_fixer.pause();
    SetTime(359 - 373, 18);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    SetTime(359 - 373 + 107, 18);
    pao_operator.pao({{1, 7.7}, {5, 7.7}});

    // wave19 PPSSDD-PP
    SetTime(295 - 373 - 3, 19);
    pao_operator.pao({{2, 8.8}, {5, 8.8}, {2, 8.8}, {5, 8.8}});
    SetTime(295 + 110 - 376, 19);
    pao_operator.pao({{1, 8.8}, {5, 8.8}});
    SetTime(1068 - 376, 19);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});

    // wave20 PPSSAD-PP
    // 炮消珊瑚
    SetTime(223 - 373, 20);
    pao_operator.pao(4, 7.5875);
    SetTime(0, 20);
    Card(PUFF_SHROOM, 3, 9);
    SetTime(295 - 373 - 3, 20);
    pao_operator.pao({{2, 8.8}, {5, 8.8}, {2, 8.8}, {5, 8.8}});
    SetTime(295 + 110 - 100, 20);
    Card(CHERRY_BOMB, 1, 9);
    SetTime(295 + 110 - 376, 20);
    pao_operator.pao(5, 8.8);
    SetTime(814 - 373, 20);
    EndingTheRound();
    SetTime(1500, 20);
    Card(ICE_SHROOM, {{1, 9}, {6, 9}});
    SetTime(850, 20);
    plant_fixer.goOn();
}
void CleanFog(int row, int col)
{
    // 浓雾未蔓延至可见区域的最小倒计时
    const int min_countdown_invisible_fog = 1556;
    // 三叶草生效时长
    const int time_blover_activate = 100;
    // 浓雾蔓延倒计时
    int countdown_fog = ReadMemory<int>(0x6A9EC0, 0x768, 0x5D4);
    auto seeds = GetMainObject()->seedArray();
    int index_blover = GetSeedIndex(BLOVER);
    if (countdown_fog - time_blover_activate < min_countdown_invisible_fog && seeds[index_blover].isUsable()) {
        if (GetPlantIndex(row, col) > 0) {
            ShovelNotInQueue(row, col);
        }
        CardNotInQueue(index_blover + 1, row, col);
    }
}
void BlockGargantuar(std::vector<Grid> pos)
{
    for (Grid each : pos) {
        auto zombies = GetMainObject()->zombieArray();
        auto seeds = GetMainObject()->seedArray();
        std::vector<int> indices_seed = {GetSeedIndex(PUFF_SHROOM), GetSeedIndex(FLOWER_POT), GetSeedIndex(SCAREDY_SHROOM), GetSeedIndex(SUN_SHROOM)};
        for (int index = 0; index < GetMainObject()->zombieTotal(); ++index) {
            if (!zombies[index].isDead() && !zombies[index].isDisappeared() && (zombies[index].type() == GARGANTUAR || zombies[index].type() == GIGA_GARGANTUAR) && zombies[index].row() + 1 == each.row && (zombies[index].abscissa() <= 40 + (each.col - 1) * 80 + 50 + 1 && zombies[index].abscissa() >= 40 + (each.col - 1) * 80 - 5)) {
                for (int index_seed : indices_seed) {
                    if (index_seed >= 0) {
                        if (seeds[index_seed].isUsable() && (GetPlantIndex(each.row, each.col) < 0 && GetPlantIndex(each.row, each.col, FLOWER_POT) < 0)) {
                            CardNotInQueue(index_seed + 1, each.row, each.col);
                            break;
                        }
                    }
                }
            }
        }
    }
}
void EndingTheRound()
{
    InsertOperation([=]() {
        std::vector<int> number_of_zombie_in_the_row(5, 0);
        std::vector<int> number_of_giga_in_the_row(5, 0);
        auto zombies = GetMainObject()->zombieArray();
        for (int index = 0; index < GetMainObject()->zombieTotal(); ++index) {
            if (!zombies[index].isDead() && !zombies[index].isDisappeared()) {
                if (zombies[index].type() == ZOMBIE || zombies[index].type() == CONEHEAD_ZOMBIE || zombies[index].type() == BUCKETHEAD_ZOMBIE || zombies[index].type() == SCREEN_DOOR_ZOMBIE) {
                    number_of_zombie_in_the_row[zombies[index].row()] += 1;
                }
                if (zombies[index].type() == GIGA_GARGANTUAR) {
                    number_of_giga_in_the_row[zombies[index].row()] += 1;
                }
            }
        }
        if (number_of_giga_in_the_row[1 - 1] == 0 && number_of_giga_in_the_row[6 - 1] == 0) {
            if (number_of_zombie_in_the_row[1 - 1] > 0) {
                SetTime(1068 - 376, 20);
                pao_operator.recoverPao({{3, 9}, {5, 9}});
                SetTime(850, 20);
                Card(PUMPKIN, 1, 9);
            } else if (number_of_zombie_in_the_row[6 - 1] > 0) {
                SetTime(1068 - 376, 20);
                pao_operator.recoverPao({{2, 9}, {4, 9}});
                SetTime(850, 20);
                Card(PUMPKIN, 6, 9);
            } else if (number_of_zombie_in_the_row[3 - 1] > 0) {
                SetTime(1068 - 376, 20);
                pao_operator.recoverPao({{1, 9}, {4, 9}});
            } else if (number_of_zombie_in_the_row[4 - 1] > 0) {
                SetTime(1068 - 376, 20);
                pao_operator.recoverPao({{2, 9}, {6, 9}});
            }
        } else if (number_of_giga_in_the_row[1 - 1] > 0) {
            SetTime(1068 - 376, 20);
            pao_operator.recoverPao({{3, 9}, {5, 9}});
            block_giga.pushFunc([=]() {
                BlockGargantuar({{1, 9}});
            });
        } else if (number_of_giga_in_the_row[6 - 1] > 0) {
            SetTime(1068 - 376, 20);
            pao_operator.recoverPao({{2, 9}, {4, 9}});
            block_giga.pushFunc([=]() {
                BlockGargantuar({{6, 9}});
            });
        } else {
            SetTime(1068 - 376, 20);
            pao_operator.recoverPao({{2, 9}, {5, 9}});
            return;
        }
        SetTime(3500 - 373, 20);
        pao_operator.recoverPao({{2, 9}, {5, 9}});
    });
}