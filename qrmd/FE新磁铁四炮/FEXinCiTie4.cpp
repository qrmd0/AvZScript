/*
 * @Author: qrmd
 * @Date: 2022-06-14 16:50:43
 * @LastEditors: qrmd
 * @LastEditTime: 2022-06-14 22:16:24
 * @Description:FE磁铁四炮 变速出怪运阵演示脚本
 * Copyright (c) 2022 by qrmd , All Rights Reserved.
 * 使用方法：1、前往https://gitee.com/vector-wlc/AsmVsZombies，根据教程下载并安装好AsmVsZombies
 *          2、在Visul Studio Code中打开本脚本，右键点击编辑区空白处，在弹出菜单中选择“AvZ:Run Script”
 * 更多AvZ脚本尽在AvZScript公开脚本仓库：
 * 主库：https://github.com/qrmd0/AvZScript
 * 镜像库：https://gitee.com/qrmd/AvZScript
 */

#include "avz.h"

using namespace AvZ;
using namespace std;
// 自动在[row]行[col]列种植三叶草清除浓雾。结合TickRunner使用
void CleanFog(int row, int col);
TickRunner fog_cleaner;
// 自动在指定位置放置植物触发巨人僵尸举锤阻挡其前进。结合TickRunner使用
void BlockGargantuar(vector<Grid> pos);
TickRunner block_giga;
// *** Not In Queue
// 返回场上[row]行是否存在冰车僵尸
bool GetIsExistZomboni(int row);

void Script()
{
    // 脚本在游戏主界面和选择植物界面生效
    OpenMultipleEffective('Q', MAIN_UI_OR_FIGHT_UI);
    // 第18波和第19波不出红眼巨人僵尸，模拟变速出怪：普僵、撑杆、橄榄、舞王、冰车、小丑、矿工、跳跳、小偷、扶梯、投篮、白眼、红眼、海豚
    SetZombies({ZOMBIE, POLE_VAULTING_ZOMBIE, FOOTBALL_ZOMBIE, DANCING_ZOMBIE, ZOMBONI, JACK_IN_THE_BOX_ZOMBIE, DIGGER_ZOMBIE, POGO_ZOMBIE, BUNGEE_ZOMBIE, LADDER_ZOMBIE, CATAPULT_ZOMBIE, GARGANTUAR, GIGA_GARGANTUAR, DOLPHIN_RIDER_ZOMBIE});
    SetWaveZombies(19, {ZOMBIE, POLE_VAULTING_ZOMBIE, FOOTBALL_ZOMBIE, DANCING_ZOMBIE, ZOMBONI, JACK_IN_THE_BOX_ZOMBIE, DIGGER_ZOMBIE, POGO_ZOMBIE, BUNGEE_ZOMBIE, LADDER_ZOMBIE, CATAPULT_ZOMBIE, GARGANTUAR, DOLPHIN_RIDER_ZOMBIE});
    SetWaveZombies(18, {ZOMBIE, POLE_VAULTING_ZOMBIE, FOOTBALL_ZOMBIE, DANCING_ZOMBIE, ZOMBONI, JACK_IN_THE_BOX_ZOMBIE, DIGGER_ZOMBIE, POGO_ZOMBIE, BUNGEE_ZOMBIE, LADDER_ZOMBIE, CATAPULT_ZOMBIE, GARGANTUAR, DOLPHIN_RIDER_ZOMBIE});
    // 选择植物：寒冰菇、模仿寒冰菇、睡莲叶、毁灭菇、南瓜头、樱桃炸弹、倭瓜、火爆辣椒、地刺、三叶草
    SelectCards({ICE_SHROOM, M_ICE_SHROOM, LILY_PAD, DOOM_SHROOM, PUMPKIN, CHERRY_BOMB, SQUASH, JALAPENO, SPIKEWEED, BLOVER});
    SetTime(-599, 1);
    // 开始自动清除浓雾
    fog_cleaner.pushFunc([]() {
        CleanFog(2, 7);
    });
    // 开始自动垫巨人僵尸
    block_giga.pushFunc([]() {
        BlockGargantuar({{1, 6}, {2, 7}, {5, 7}, {6, 6}});
    });
    // 开始自动修补南瓜头
    plant_fixer.start(PUMPKIN, {{1, 3}, {2, 3}, {5, 3}, {6, 3}, {1, 4}, {2, 4}, {5, 4}, {6, 4}, {3, 6}, {4, 6}, {3, 7}, {4, 7}, {2, 6}, {5, 6}, {1, 5}, {6, 5}, {2, 5}, {5, 5}}, 1200);
    // 自动填充炮列表
    pao_operator.resetPaoList({{1, 1}, {6, 1}, {2, 1}, {5, 1}});
    // 主体节奏 对C6u Icc-PP|N|Icc-PA'a|PA 1930|601|1930|601 每波执行确定的操作，不考虑非旗帜波的刷新延迟
    // wave1 PP 首代
    SetTime(341 - 376, 1);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    // wave2 N
    SetTime(341 - 100, 2);
    Card(LILY_PAD, 3, 9);
    Card(DOOM_SHROOM, 3, 9);
    // wave3 Icc-PA'a
    SetSetTime(1 - 100, 3);
    Card(ICE_SHROOM, 1, 6);
    // 292cs为在9列放置地刺伤害全部冰车的最早时机
    InsertTimeOperation(292, 3, [=]() {
        if (GetIsExistZomboni(5)) {
            SetTime(292, 3);
            Card(SPIKEWEED, 5, 9);
            if (GetIsExistZomboni(2)) {
                SetTime(292 + 751, 3);
                Card(SPIKEWEED, 2, 8);
            }
        } else if (GetIsExistZomboni(2)) {
            // 640cs为在8列放置地刺伤害全部冰车的最早时机
            SetTime(640, 3);
            Card(SPIKEWEED, 2, 8);
        }
    });
    SetTime(1930 - 200 - 373, 3);
    pao_operator.pao(2, 8.8);
    SetTime(1200, 3);
    Card(SQUASH, 5, 9);
    SetTime(1930 - 200 - 100, 3);
    Card(JALAPENO, 6, 6);
    // wave4 PA
    SetTime(341 - 376, 4);
    pao_operator.pao(2, 8.8);
    SetTime(341 - 100, 4);
    Card(CHERRY_BOMB, 5, 9);
    // wave5 Icc-PP
    SetTime(-200, 5);
    Card(M_ICE_SHROOM, 1, 6);
    // 292cs为在9列放置地刺伤害全部冰车的最早时机
    InsertTimeOperation(292, 5, [=]() {
        if (GetIsExistZomboni(5)) {
            SetTime(292, 5);
            Card(SPIKEWEED, 5, 9);
            if (GetIsExistZomboni(2)) {
                SetTime(292 + 751, 5);
                Card(SPIKEWEED, 2, 8);
            }
        } else if (GetIsExistZomboni(2)) {
            // 640cs为在8列放置地刺伤害全部冰车的最早时机
            SetTime(640, 5);
            Card(SPIKEWEED, 2, 8);
        }
    });
    SetTime(1930 - 200 - 373, 5);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    // wave6 N
    SetTime(341 - 100, 6);
    Card(LILY_PAD, 3, 8);
    Card(DOOM_SHROOM, 3, 8);
    // wave7 Icc-PA'a
    SetSetTime(1 - 100, 7);
    Card(ICE_SHROOM, 1, 6);
    // 292cs为在9列放置地刺伤害全部冰车的最早时机
    InsertTimeOperation(292, 7, [=]() {
        if (GetIsExistZomboni(5)) {
            SetTime(292, 7);
            Card(SPIKEWEED, 5, 9);
            if (GetIsExistZomboni(2)) {
                SetTime(292 + 751, 7);
                Card(SPIKEWEED, 2, 8);
            }
        } else if (GetIsExistZomboni(2)) {
            // 640cs为在8列放置地刺伤害全部冰车的最早时机
            SetTime(640, 7);
            Card(SPIKEWEED, 2, 8);
        }
    });
    SetTime(1930 - 200 - 373, 7);
    pao_operator.pao(2, 8.8);
    SetTime(1200, 7);
    Card(SQUASH, 5, 9);
    SetTime(1930 - 200 - 100, 7);
    Card(JALAPENO, 6, 6);
    // wave8 PA
    SetTime(341 - 376, 8);
    pao_operator.pao(2, 8.8);
    SetTime(341 - 100, 8);
    Card(CHERRY_BOMB, 5, 9);
    // wave9 PP-(PP-PP)
    SetTime(341 - 376, 9);
    pao_operator.recoverPao({{2, 8.8}, {5, 8.8}, {2, 8.8}, {5, 8.8}, {2, 8.8}, {5, 8.8}});
    SetTime(2000, 9);
    Card(LILY_PAD, 4, 8);
    Card(M_ICE_SHROOM, 4, 8);
    // wave10 N
    SetTime(341 - 100, 10);
    Card(LILY_PAD, 4, 9);
    Card(DOOM_SHROOM, 4, 9);
    // 563cs为允许w14寒冰菇复用的最晚时机
    SetTime(563, 10);
    Card(ICE_SHROOM, 1, 6);
    SetTime(673 - 373, 10);
    pao_operator.recoverPao(3, 3.0625);
    // wave11 Icc-PA'a
    // 292cs为在9列放置地刺伤害全部冰车的最早时机
    InsertTimeOperation(292, 11, [=]() {
        if (GetIsExistZomboni(5)) {
            SetTime(292, 11);
            Card(SPIKEWEED, 5, 9);
            if (GetIsExistZomboni(2)) {
                SetTime(292 + 751, 11);
                Card(SPIKEWEED, 2, 8);
            }
        } else if (GetIsExistZomboni(2)) {
            // 640cs为在8列放置地刺伤害全部冰车的最早时机
            SetTime(640, 11);
            Card(SPIKEWEED, 2, 8);
        }
    });
    SetTime(1930 - 200 - 373, 11);
    pao_operator.pao(2, 8.8);
    SetTime(1200, 11);
    Card(SQUASH, 5, 9);
    SetTime(1930 - 200 - 100, 11);
    Card(JALAPENO, 6, 6);
    // wave12 PA
    SetTime(341 - 376, 12);
    pao_operator.pao(2, 8.8);
    SetTime(341 - 100, 12);
    Card(CHERRY_BOMB, 5, 9);
    // wave13 Icc-PP
    SetTime(-200, 13);
    Card(M_ICE_SHROOM, 1, 6);
    // 292cs为在9列放置地刺伤害全部冰车的最早时机
    InsertTimeOperation(292, 13, [=]() {
        if (GetIsExistZomboni(5)) {
            SetTime(292, 13);
            Card(SPIKEWEED, 5, 9);
            if (GetIsExistZomboni(2)) {
                SetTime(292 + 751, 13);
                Card(SPIKEWEED, 2, 8);
            }
        } else if (GetIsExistZomboni(2)) {
            // 640cs为在8列放置地刺伤害全部冰车的最早时机
            SetTime(640, 13);
            Card(SPIKEWEED, 2, 8);
        }
    });
    SetTime(1930 - 200 - 373, 13);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    // wave14 N
    SetTime(341 - 100, 14);
    Card(LILY_PAD, 4, 8);
    Card(DOOM_SHROOM, 4, 8);
    // wave15 Icc-PA'a
    SetSetTime(1 - 100, 15);
    Card(ICE_SHROOM, 1, 6);
    // 292cs为在9列放置地刺伤害全部冰车的最早时机
    InsertTimeOperation(292, 15, [=]() {
        if (GetIsExistZomboni(5)) {
            SetTime(292, 15);
            Card(SPIKEWEED, 5, 9);
            if (GetIsExistZomboni(2)) {
                SetTime(292 + 751, 15);
                Card(SPIKEWEED, 2, 8);
            }
        } else if (GetIsExistZomboni(2)) {
            // 640cs为在8列放置地刺伤害全部冰车的最早时机
            SetTime(640, 15);
            Card(SPIKEWEED, 2, 8);
        }
    });
    SetTime(1930 - 200 - 373, 15);
    pao_operator.pao(2, 8.8);
    SetTime(1200, 15);
    Card(SQUASH, 5, 9);
    SetTime(1930 - 200 - 100, 15);
    Card(JALAPENO, 6, 6);
    // wave16 PA
    SetTime(341 - 376, 16);
    pao_operator.pao(2, 8.8);
    SetTime(341 - 100, 16);
    Card(CHERRY_BOMB, 5, 9);
    // wave17 Icc-PP
    SetTime(-200, 17);
    Card(M_ICE_SHROOM, 1, 6);
    // 292cs为在9列放置地刺伤害全部冰车的最早时机
    InsertTimeOperation(292, 17, [=]() {
        if (GetIsExistZomboni(5)) {
            SetTime(292, 17);
            Card(SPIKEWEED, 5, 9);
            if (GetIsExistZomboni(2)) {
                SetTime(292 + 751, 17);
                Card(SPIKEWEED, 2, 8);
            }
        } else if (GetIsExistZomboni(2)) {
            // 640cs为在8列放置地刺伤害全部冰车的最早时机
            SetTime(640, 17);
            Card(SPIKEWEED, 2, 8);
        }
    });
    SetTime(1930 - 200 - 373, 17);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    // wave18 N
    SetTime(341 - 100, 18);
    Card(LILY_PAD, 3, 8);
    Card(DOOM_SHROOM, 3, 8);
    // wave19 PP-(PP)
    SetTime(341 - 376, 19);
    pao_operator.recoverPao({{2, 8.8}, {5, 8.8}, {2, 8.8}, {5, 8.8}});
    SetTime(2000, 19);
    Card(ICE_SHROOM, 1, 6);
    // wave20 PP-(PP-PP)
    // 673cs为蹦极僵尸全部被冰冻的最晚时机
    SetTime(673 - 100 - 320, 20);
    Card(M_ICE_SHROOM, 1, 6);
    SetTime(673 - 373, 20);
    pao_operator.recoverPao(3, 3.0625);
    pao_operator.recoverPao({{2, 8.8}, {5, 8.8}, {2, 8.8}, {5, 8.8}});
    SetTime(341, 20);
    Card(SQUASH, 6, 9);
    SetTime(1200, 20);
    Card(DOOM_SHROOM, 2, 9);
    SetTime(4000, 20);
    Card(ICE_SHROOM, 1, 6);
}
void CleanFog(int row, int col)
{
    // 浓雾未蔓延至可见区域的最小倒计时
    const int min_countdown_invisible_fog = 1556;
    // 三叶草生效时长
    const int time_blover_activate = 100;
    // 浓雾倒计时
    int countdown_fog = ReadMemory<int>(0x6A9EC0, 0x768, 0x5D4);
    auto seeds = GetMainObject()->seedArray();
    int index_blover = GetSeedIndex(BLOVER);
    if (countdown_fog - time_blover_activate < min_countdown_invisible_fog && seeds[index_blover].isUsable()) {
        CardNotInQueue(index_blover + 1, row, col);
    }
}
void BlockGargantuar(vector<Grid> pos)
{
    auto zombies = GetMainObject()->zombieArray();
    auto seeds = GetMainObject()->seedArray();
    vector<int> indices_seed = {GetSeedIndex(BLOVER), GetSeedIndex(PUMPKIN)};
    for (Grid each : pos) {
        for (int index = 0; index < GetMainObject()->zombieTotal(); ++index) {
            if (!zombies[index].isDead() && !zombies[index].isDisappeared() && (zombies[index].type() == GARGANTUAR || zombies[index].type() == GIGA_GARGANTUAR) && zombies[index].row() + 1 == each.row && (zombies[index].abscissa() <= 40 + (each.col - 1) * 80 + 30 + 10 && zombies[index].abscissa() >= 40 + (each.col - 1) * 80 - 5)) {
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
bool GetIsExistZomboni(int row)
{
    auto zombies = GetMainObject()->zombieArray();
    for (int index = 0; index < GetMainObject()->zombieTotal(); ++index) {
        if (!zombies[index].isDead() && !zombies[index].isDisappeared() && zombies[index].type() == ZOMBONI && zombies[index].row() + 1 == row) {
            return true;
        }
    }
    return false;
}