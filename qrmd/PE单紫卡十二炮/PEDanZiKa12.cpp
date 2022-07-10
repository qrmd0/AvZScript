/*
 * @Author: qrmd
 * @Date: 2022-06-16 22:14:51
 * @LastEditors: qrmd
 * @LastEditTime: 2022-06-17 00:01:20
 * @Description:PE单紫卡十二炮 全难度极限出怪运阵演示脚本
 * 使用方法：1、前往https://gitee.com/vector-wlc/AsmVsZombies，根据教程下载并安装好AsmVsZombies
 *          2、在Visul Studio Code中打开本脚本，右键点击编辑区空白处，在弹出菜单中选择“AvZ:Run Script”
 * 更多AvZ脚本尽在AvZScript公开脚本仓库：
 * 主库：https://github.com/qrmd0/AvZScript
 * 镜像库：https://gitee.com/qrmd/AvZScript
 * Copyright (c) 2022 by qrmd , All Rights Reserved.
 */

#include "avz.h"

using namespace AvZ;
using namespace std;

// 自动在指定位置放置植物触发巨人僵尸举锤阻挡其前进。结合TickRunner使用
void BlockGargantuar(vector<Grid> pos);
TickRunner block_giga;

void Script()
{
    // 脚本在游戏主界面和选择植物界面生效
    OpenMultipleEffective('Q', MAIN_UI_OR_FIGHT_UI);
    // 全难度极限出怪：普僵、撑杆、橄榄、舞王、冰车、小丑、矿工、跳跳、小偷、扶梯、投篮、白眼、红眼、海豚
    SetZombies({ZOMBIE, POLE_VAULTING_ZOMBIE, FOOTBALL_ZOMBIE, DANCING_ZOMBIE, ZOMBONI, JACK_IN_THE_BOX_ZOMBIE, DIGGER_ZOMBIE, POGO_ZOMBIE, BUNGEE_ZOMBIE, LADDER_ZOMBIE, CATAPULT_ZOMBIE, GARGANTUAR, GIGA_GARGANTUAR, DOLPHIN_RIDER_ZOMBIE});
    // 选择植物：睡莲叶、咖啡豆、寒冰菇、模仿寒冰菇、毁灭菇、樱桃炸弹、小喷菇、花盆、胆小菇、阳光菇
    SelectCards({LILY_PAD, COFFEE_BEAN, ICE_SHROOM, M_ICE_SHROOM, DOOM_SHROOM, CHERRY_BOMB, PUFF_SHROOM, FLOWER_POT, SCAREDY_SHROOM, SUN_SHROOM});
    SetTime(-599, 1);
    // 填充炮列表
    pao_operator.resetPaoList({{1, 5}, {6, 5}, {2, 5}, {5, 5}, {3, 1}, {4, 1}, {3, 3}, {4, 3}, {3, 5}, {4, 5}, {3, 7}, {4, 7}});
    // 开始自动存冰
    ice_filler.start({{3, 9}, {4, 9}});
    // 开始自动修补睡莲叶
    plant_fixer.start(LILY_PAD, {{3, 9}, {4, 9}}, 0);
    // 开始自动垫巨人僵尸
    block_giga.pushFunc([]() {
        BlockGargantuar({{1, 7}, {2, 7}, {5, 7}, {6, 7}});
    });
    // 主体节奏 S6 I-PP|PP|PP|PP|PP 1071|601|601|601|601 每波执行确定的操作，不考虑非旗帜波的刷新延迟

    // wave1 PP
    SetTime(341 - 376, 1);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});

    // wave2 PPSS
    SetTime(341 - 376, 2);
    pao_operator.pao({{2, 8.8}, {5, 8.8}, {2, 8.8}, {5, 8.8}});

    // wave3 PP
    SetTime(341 - 376, 3);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});

    // wave4 PP
    SetTime(341 - 376, 4);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});

    // wave5 I-PP
    SetTime(-200, 5);
    ice_filler.coffee();
    SetTime(1071 - 200 - 373, 5);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});

    // wave6 PP
    SetTime(341 - 376, 6);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});

    // wave7 PPSS
    SetTime(341 - 376, 7);
    pao_operator.pao({{2, 8.8}, {5, 8.8}, {2, 8.8}, {5, 8.8}});

    // wave8 PP
    SetTime(341 - 376, 8);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});

    // wave9 PPI-(-PP-PP-PP)
    SetTime(341 - 376, 9);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    SetTime(341 - 298, 9);
    ice_filler.coffee();
    pao_operator.recoverPao({{2, 8.8}, {5, 8.8}, {2, 8.8}, {5, 8.8}, {2, 8.8}, {5, 8.8}});

    // wave10 ccccN
    SetTime(500, 10);
    Shovel({{1, 7}, {2, 7}, {5, 7}, {6, 7}});
    SetTime(395 - 373, 10);
    pao_operator.pao({{1, 2}, {5, 2}});
    // 舞王僵尸9列触碰小喷菇或阳光菇召唤伴舞僵尸的最晚时机
    SetTime(243, 10);
    Card(PUFF_SHROOM, 1, 9);
    Card(FLOWER_POT, 2, 9);
    Card(SCAREDY_SHROOM, 5, 9);
    Card(SUN_SHROOM, 6, 9);
    SetTime(243 + 79, 10);
    Shovel({{1, 9}, {2, 9}, {6, 9}});
    SetTime(410 - 298, 10);
    Card(DOOM_SHROOM, 2, 8);
    Card(COFFEE_BEAN, 2, 8);
    SetTime(410 - 100, 10);
    Shovel(5, 9);
    Card(CHERRY_BOMB, 5, 9);

    // wave11 PPSS
    SetTime(341 - 376, 11);
    pao_operator.pao({{2, 8.8}, {5, 8.8}, {2, 8.8}, {5, 8.8}});

    // wave12 PP
    SetTime(341 - 376, 12);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});

    // wave13 PP
    SetTime(341 - 376, 13);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});

    // wave14 I-PP
    SetTime(-200, 14);
    ice_filler.coffee();
    // 上次这组炮用于炸蹦极，发射较晚，故本次晚发射以保证复用
    SetTime(1119 - 200 - 373, 14);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});

    // wave15 PP
    SetTime(341 - 376, 15);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});

    // wave16 PPSS
    SetTime(341 - 376, 16);
    pao_operator.pao({{2, 8.8}, {5, 8.8}, {2, 8.8}, {5, 8.8}});

    // wave17 PP
    SetTime(341 - 376, 17);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});

    // wave18 PP
    SetTime(341 - 376, 18);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});

    // wave19 I-PP(-PP-PP-PP)
    SetTime(-200, 19);
    ice_filler.coffee();
    SetTime(1202 - 200 - 373, 19);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    pao_operator.recoverPao({{2, 8.8}, {5, 8.8}, {2, 8.8}, {5, 8.8}, {2, 8.8}, {5, 8.8}});

    // wave20 ccccPP-(PP-PP)
    SetTime(500, 20);
    Shovel({{1, 7}, {2, 7}, {5, 7}, {6, 7}});
    // 炮消珊瑚
    SetTime(223 - 373, 20);
    pao_operator.pao(4, 7.5875);
    SetTime(395 - 373, 20);
    pao_operator.pao({{1, 2}, {5, 2}});
    // 243cs为舞王僵尸9列触碰小喷菇或阳光菇召唤伴舞僵尸的最晚时机
    SetTime(243, 20);
    Card(PUFF_SHROOM, 1, 9);
    Card(FLOWER_POT, 2, 9);
    Card(SCAREDY_SHROOM, 5, 9);
    Card(SUN_SHROOM, 6, 9);
    SetTime(243 + 79, 20);
    Shovel({{1, 9}, {2, 9}, {5, 9}, {6, 9}});
    SetTime(410 - 373, 20);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    pao_operator.recoverPao({{2, 8.8}, {5, 8.8}, {2, 8.8}, {5, 8.8}, {2, 8.8}, {5, 8.8}});
}

void BlockGargantuar(vector<Grid> pos)
{
    for (Grid each : pos) {
        auto zombies = GetMainObject()->zombieArray();
        auto seeds = GetMainObject()->seedArray();
        vector<int> indices_seed = {GetSeedIndex(PUFF_SHROOM), GetSeedIndex(FLOWER_POT), GetSeedIndex(SCAREDY_SHROOM), GetSeedIndex(SUN_SHROOM)};
        for (int index = 0; index < GetMainObject()->zombieTotal(); ++index) {
            if (!zombies[index].isDead() && !zombies[index].isDisappeared() && (zombies[index].type() == GARGANTUAR || zombies[index].type() == GIGA_GARGANTUAR) && zombies[index].row() + 1 == each.row && (zombies[index].abscissa() <= 40 + (each.col - 1) * 80 + 30 + 1 && zombies[index].abscissa() >= 40 + (each.col - 1) * 80 - 5)) {
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