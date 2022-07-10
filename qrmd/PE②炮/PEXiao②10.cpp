/*
 * @Author: qrmd
 * @Date: 2022-06-23 12:06:34
 * @LastEditors: qrmd
 * @LastEditTime: 2022-06-28 11:45:35
 * @Description:PE②炮 全难度极限出怪运阵演示脚本
 * 使用方法：1、前往https://gitee.com/vector-wlc/AsmVsZombies，根据教程下载并安装好AsmVsZombies
 *          2、前往游戏存档文件夹C:/ProgramData/PopCap Games/PlantsVsZombies/userdata，备份原游戏存档，然后用脚本配套的存档文件替换同名文件
 *          3、在Visul Studio Code中打开本脚本，右键点击编辑区空白处，在弹出菜单中选择“AvZ:Run Script”
 * 来自AvZScript公开脚本仓库：
 * 主库：https://github.com/qrmd0/AvZScript
 * 镜像库：https://gitee.com/qrmd/AvZScript
 * Copyright (c) 2022 by qrmd, All Rights Reserved.
 */

#include "avz.h"
using namespace AvZ;
// 留下一行领带僵尸或巨人僵尸，自动放置植物将其拖住以延长第[wave]波收尾，适用于六行场地
void EndingTheWave(int wave);
// 如果[wave]波上半场刷出的僵尸总血量较高，返回2，否则返回5。用于6行场地的智能樱桃消延迟
int GetRowHaveHigherZombieHp(int wave);
// 自动在指定位置放置植物触发巨人僵尸举锤阻挡其前进。结合TickRunner使用
void BlockGargantuar(std::vector<Grid> pos);
TickRunner block_giga;
void Script()
{
    // 脚本在游戏主界面和选择植物界面生效
    OpenMultipleEffective('Q', MAIN_UI_OR_FIGHT_UI);
    // 全难度极限出怪：普僵、撑杆、橄榄、舞王、冰车、小丑、矿工、跳跳、小偷、扶梯、投篮、白眼、红眼、海豚
    SetZombies({ZOMBIE, POLE_VAULTING_ZOMBIE, FOOTBALL_ZOMBIE, DANCING_ZOMBIE, ZOMBONI, JACK_IN_THE_BOX_ZOMBIE, DIGGER_ZOMBIE, POGO_ZOMBIE, BUNGEE_ZOMBIE, LADDER_ZOMBIE, CATAPULT_ZOMBIE, GARGANTUAR, GIGA_GARGANTUAR, DOLPHIN_RIDER_ZOMBIE});
    // 选择植物：咖啡豆、寒冰菇、模仿寒冰菇、睡莲叶、毁灭菇、樱桃炸弹、高坚果、土豆地雷、寒冰射手、小喷菇
    SelectCards({COFFEE_BEAN, ICE_SHROOM, M_ICE_SHROOM, LILY_PAD, DOOM_SHROOM, CHERRY_BOMB, TALL_NUT, POTATO_MINE, SNOW_PEA, PUFF_SHROOM});
    SetTime(-599, 1);
    // 填充炮列表
    pao_operator.resetPaoList({{1, 2}, {6, 1}, {1, 4}, {6, 3}, {2, 1}, {5, 2}, {2, 5}, {6, 5}, {3, 4}, {4, 3}});
    // 开始自动存冰
    ice_filler.start({{3, 6}, {4, 6}, {5, 6}, {5, 5}, {5, 4}});
    // 开始自动修补高坚果
    plant_fixer.start(TALL_NUT, {{3, 7}, {4, 7}}, 1200);
    // 铲除与种植临时植物
    Card(LILY_PAD, 3, 7);
    SetTime(-599 + 751, 1);
    Card(LILY_PAD, 4, 7);
    SetTime(-599 + 751 * 2, 1);
    Card(LILY_PAD, 3, 3);
    Card(DOOM_SHROOM, 3, 3);
    // 主体节奏 ch4u I-PPdd|IPP-PPDD 1627|1848 每波执行确定的操作，不考虑非旗帜波的刷新延迟

    // wave1 PPDD 首代
    SetTime(359 - 373, 1);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    SetTime(359 + 110 - 376, 1);
    pao_operator.pao({{1, 7.7}, {5, 7.7}});
    SetTime(12 + 601 - 298, 1);
    ice_filler.coffee();

    // wave2 I-PPdd
    SetTime(1627 - 200 - 373, 2);
    pao_operator.pao({{1, 8.8}, {5, 8.8}});
    SetTime(1627 - 200 + 349 - 373, 2);
    pao_operator.pao({{1, 2.5}, {5, 2.5}});
    SetTime(12 + 1627 - 298, 2);
    ice_filler.coffee();

    // wave3 IPP-PPDD
    SetTime(452 - 373, 3);
    pao_operator.pao({{2, 7.4}, {5, 7.4}});
    SetTime(1848 - 200 - 373, 3);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    SetTime(1848 - 200 + 221 - 373, 3);
    pao_operator.pao({{1, 7.3}, {5, 7.3}});
    SetTime(12 + 1848 - 298, 3);
    ice_filler.coffee();

    // wave4 I-PPdd
    SetTime(1627 - 200 - 373, 4);
    pao_operator.pao({{1, 8.8}, {5, 8.8}});
    SetTime(1627 - 200 + 349 - 373, 4);
    pao_operator.pao({{1, 2.5}, {5, 2.5}});
    SetTime(12 + 1627 - 298, 4);
    ice_filler.coffee();

    // wave5 IPP-PPDD
    SetTime(452 - 373, 5);
    pao_operator.pao({{2, 7.4}, {5, 7.4}});
    SetTime(1848 - 200 - 373, 5);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    SetTime(1848 - 200 + 221 - 373, 5);
    pao_operator.pao({{1, 7.3}, {5, 7.3}});
    SetTime(12 + 1848 - 298, 5);
    ice_filler.coffee();

    // wave6 I-PPdd
    SetTime(1627 - 200 - 373, 6);
    pao_operator.pao({{1, 8.8}, {5, 8.8}});
    SetTime(1627 - 200 + 349 - 373, 6);
    pao_operator.pao({{1, 2.5}, {5, 2.5}});
    SetTime(12 + 1627 - 298, 6);
    ice_filler.coffee();

    // wave7 IPP-PPDD
    SetTime(452 - 373, 7);
    pao_operator.pao({{2, 7.4}, {5, 7.4}});
    SetTime(1848 - 200 - 373, 7);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    SetTime(1848 - 200 + 221 - 373, 7);
    pao_operator.pao({{1, 7.3}, {5, 7.3}});
    SetTime(12 + 1848 - 298, 7);
    ice_filler.coffee();

    // wave8 I-PPdd
    SetTime(1627 - 200 - 373, 8);
    pao_operator.pao({{1, 8.8}, {5, 8.8}});
    SetTime(1627 - 200 + 349 - 373, 8);
    pao_operator.pao({{1, 2.5}, {5, 2.5}});
    SetTime(12 + 1627 - 298, 8);
    ice_filler.coffee();

    // wave9 IN-PPDDDD-PP
    SetTime(969 - 298, 9);
    Card(COFFEE_BEAN, 3, 3);
    SetTime(4500 + 5001, 9);
    Card(LILY_PAD, 3, 2);
    Card(DOOM_SHROOM, 3, 2);
    SetTime(1848 - 200 + 9 - 212 - 373, 9);
    pao_operator.pao({{2, 8.475}, {5, 8.475}});
    SetTime(1848 - 200 + 9 - 373, 9);
    pao_operator.pao({{1, 8.475}, {5, 8.475}});
    SetTime(1848 - 200 + 9 - 373 + 224, 9);
    pao_operator.pao({{1, 8.8}, {5, 8.8}});
    SetTime(1848 - 200 + 9 + 224 + 10, 9);
    EndingTheWave(9);

    // wave10 PPAdd
    SetTime(341 - 376, 10);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    SetTime(374, 10);
    Card(SNOW_PEA, 1, 9);
    Card(PUFF_SHROOM, 6, 9);
    SetTime(445, 10);
    Shovel({{1, 9}, {6, 9}});
    // 智能樱桃消中场延迟
    InsertTimeOperation(341 - 3 - 100, 10, [=]() {
        SetTime(341 - 3 - 100, 10);
        Card(CHERRY_BOMB, GetRowHaveHigherZombieHp(10), 9);
    });
    SetTime(341 - 3 + 258 - 373, 10);
    pao_operator.pao({{2, 2.5}, {5, 2.5}});
    SetTime(12 + 601 - 298, 10);
    ice_filler.coffee();

    // wave11 IPP-PPDD
    SetTime(452 - 373, 11);
    pao_operator.pao({{2, 7.4}, {5, 7.4}});
    SetTime(1848 - 200 - 373, 11);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    SetTime(1848 - 200 + 221 - 373, 11);
    pao_operator.pao({{1, 7.3}, {5, 7.3}});
    SetTime(12 + 1848 - 298, 11);
    ice_filler.coffee();

    // wave12 I-PPdd
    SetTime(1627 - 200 - 373, 12);
    pao_operator.pao({{1, 8.8}, {5, 8.8}});
    SetTime(1627 - 200 + 349 - 373, 12);
    pao_operator.pao({{1, 2.5}, {5, 2.5}});
    SetTime(12 + 1627 - 298, 12);
    ice_filler.coffee();

    // wave13 IPP-PPDD
    SetTime(452 - 373, 13);
    pao_operator.pao({{2, 7.4}, {5, 7.4}});
    SetTime(1848 - 200 - 373, 13);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    SetTime(1848 - 200 + 221 - 373, 13);
    pao_operator.pao({{1, 7.3}, {5, 7.3}});
    SetTime(12 + 1848 - 298, 13);
    ice_filler.coffee();

    // wave14 I-PPdd
    SetTime(1627 - 200 - 373, 14);
    pao_operator.pao({{1, 8.8}, {5, 8.8}});
    SetTime(1627 - 200 + 349 - 373, 14);
    pao_operator.pao({{1, 2.5}, {5, 2.5}});
    SetTime(12 + 1627 - 298, 14);
    ice_filler.coffee();

    // wave15 IPP-PPDD
    SetTime(452 - 373, 15);
    pao_operator.pao({{2, 7.4}, {5, 7.4}});
    SetTime(1848 - 200 - 373, 15);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    SetTime(1848 - 200 + 221 - 373, 15);
    pao_operator.pao({{1, 7.3}, {5, 7.3}});
    SetTime(12 + 1848 - 298, 15);
    ice_filler.coffee();

    // wave16 I-PPdd
    SetTime(1627 - 200 - 373, 16);
    pao_operator.pao({{1, 8.8}, {5, 8.8}});
    SetTime(1627 - 200 + 349 - 373, 16);
    pao_operator.pao({{1, 2.5}, {5, 2.5}});
    SetTime(12 + 1627 - 298, 16);
    ice_filler.coffee();

    // wave17 IPP-PPDD
    SetTime(452 - 373, 17);
    pao_operator.pao({{2, 7.4}, {5, 7.4}});
    SetTime(1848 - 200 - 373, 17);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    SetTime(1848 - 200 + 221 - 373, 17);
    pao_operator.pao({{1, 7.3}, {5, 7.3}});
    SetTime(12 + 1848 - 298, 17);
    ice_filler.coffee();

    // wave18 I-PPdd
    SetTime(1627 - 200 - 373, 18);
    pao_operator.pao({{1, 8.8}, {5, 8.8}});
    SetTime(1627 - 200 + 349 - 373, 18);
    pao_operator.pao({{1, 2.5}, {5, 2.5}});
    SetTime(12 + 1627 - 298, 18);
    ice_filler.coffee();

    // wave19 IN-PPDDDD-PP
    SetTime(969 - 298, 19);
    Card(COFFEE_BEAN, 3, 2);
    SetTime(1848 - 200 + 9 - 212 - 373, 19);
    pao_operator.pao({{2, 8.475}, {5, 8.475}});
    SetTime(1848 - 200 + 9 - 373, 19);
    pao_operator.pao({{1, 8.475}, {5, 8.475}});
    SetTime(1848 - 200 + 9 - 373 + 224, 19);
    pao_operator.pao({{1, 8.8}, {5, 8.8}});
    SetTime(1848 - 200 + 9 + 224 + 10, 19);
    EndingTheWave(19);

    // wave20 PPSSDA
    // 炮消珊瑚
    SetTime(223 - 373, 20);
    pao_operator.pao(4, 7.5875);
    SetTime(395 - 373, 20);
    pao_operator.pao({{4, 2}, {4, 5.5}});
    SetTime(341 - 376, 20);
    pao_operator.pao({{2, 8.8}, {5, 8.8}, {2, 8.8}, {5, 8.8}});
    SetTime(341 + 110 - 100, 20);
    Card(CHERRY_BOMB, 5, 9);
    SetTime(341 + 110 - 373, 20);
    pao_operator.pao(1, 8.8);
    SetTime(341 + 110, 20);
    EndingTheWave(20);
}
int GetRowHaveHigherZombieHp(int wave)
{
    auto zombies = GetMainObject()->zombieArray();
    int hp_of_up_ground_zombies = 0;
    int hp_of_down_ground_zombies = 0;
    for (int index = 0; index < GetMainObject()->zombieTotal(); ++index) {
        if (!zombies[index].isDead() && !zombies[index].isDisappeared() && zombies[index].existTime() <= NowTime(wave)) {
            if (zombies[index].row() + 1 <= 3) {
                hp_of_up_ground_zombies += zombies[index].hp() + zombies[index].oneHp() + zombies[index].twoHp() / 5;
            } else if (zombies[index].row() + 1 >= 4) {
                hp_of_down_ground_zombies += zombies[index].hp() + zombies[index].oneHp() + zombies[index].twoHp() / 5;
            }
        }
    }
    if (hp_of_up_ground_zombies > hp_of_down_ground_zombies) {
        return 2;
    } else {
        return 5;
    }
}
void EndingTheWave(int wave)
{
    InsertOperation([=]() {
        int remaining_row = -1;
        std::vector<int> is_exist_zombie_in_the_row(6, 0);
        auto zombies = GetMainObject()->zombieArray();
        for (int index = 0; index < GetMainObject()->zombieTotal(); ++index) {
            if (!zombies[index].isDead() && !zombies[index].isDisappeared() && (zombies[index].type() == ZOMBIE || zombies[index].type() == CONEHEAD_ZOMBIE || zombies[index].type() == BUCKETHEAD_ZOMBIE || zombies[index].type() == SCREEN_DOOR_ZOMBIE || zombies[index].type() == NEWSPAPER_ZOMBIE || zombies[index].type() == GARGANTUAR || zombies[index].type() == GIGA_GARGANTUAR)) {
                is_exist_zombie_in_the_row[zombies[index].row()] += 1;
            }
        }
        SetTime(NowTime(wave), wave);
        // 选择水路僵尸数量较少的一路
        if (is_exist_zombie_in_the_row[3 - 1] > 0 || is_exist_zombie_in_the_row[4 - 1] > 0) {
            if (is_exist_zombie_in_the_row[3 - 1] < is_exist_zombie_in_the_row[4 - 1]) {
                pao_operator.recoverPao({{1, 8}, {5, 8}});
                remaining_row = 3;
            } else {
                pao_operator.recoverPao({{2, 8}, {6, 8}});
                remaining_row = 4;
            }
            // 选择边路僵尸数量较少的一路
        } else if (is_exist_zombie_in_the_row[1 - 1] > 0 || is_exist_zombie_in_the_row[6 - 1] > 0) {
            if (is_exist_zombie_in_the_row[1 - 1] < is_exist_zombie_in_the_row[6 - 1]) {
                pao_operator.recoverPao({{3, 8}, {5, 8}});
                remaining_row = 1;
            } else {
                pao_operator.recoverPao({{2, 8}, {4, 8}});
                remaining_row = 6;
            }
        } else { //无可以拖住的僵尸，拖收尾失败
            pao_operator.recoverPao({{2, 7.5}, {5, 8}});
            return;
        }
        int index_snow_pea_seed = GetSeedIndex(SNOW_PEA);
        CardNotInQueue(index_snow_pea_seed + 1, remaining_row, 7);
        block_giga.pushFunc([=]() {
            BlockGargantuar({{remaining_row, 7}});
        });
        if (wave == 9 || wave == 19) {
            SetTime(4500 - 200 - 298, wave);
            Card(LILY_PAD, 3, 8);
            Card(DOOM_SHROOM, 3, 8);
            Card(COFFEE_BEAN, 3, 8);
        } else { // wave == 20
            SetTime(4000 - 373, wave);
            pao_operator.recoverPao({{2, 7.7}, {5, 7.7}});
        }
        block_giga.stop();
        SetTime(5500, wave);
        Shovel({{remaining_row, 7}});
    });
}
void BlockGargantuar(std::vector<Grid> pos)
{
    for (Grid each : pos) {
        auto zombies = GetMainObject()->zombieArray();
        auto seeds = GetMainObject()->seedArray();
        std::vector<int> indices_seed = {GetSeedIndex(SNOW_PEA), GetSeedIndex(PUFF_SHROOM), GetSeedIndex(POTATO_MINE), GetSeedIndex(TALL_NUT)};
        for (int index = 0; index < GetMainObject()->zombieTotal(); ++index) {
            if (!zombies[index].isDead() && !zombies[index].isDisappeared() && (zombies[index].type() == GARGANTUAR || zombies[index].type() == GIGA_GARGANTUAR) && zombies[index].row() + 1 == each.row && (zombies[index].abscissa() <= 40 + (each.col - 1) * 80 + 30 + 1 && zombies[index].abscissa() >= 40 + (each.col - 1) * 80 - 5) && zombies[index].state() == 0) {
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