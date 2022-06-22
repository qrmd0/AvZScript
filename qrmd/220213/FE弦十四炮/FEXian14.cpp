/*
 * @Author: qrmd
 * @Date: 2022-06-22 16:45:24
 * @LastEditors: qrmd
 * @LastEditTime: 2022-06-22 20:02:35
 * @Description:FE弦十四炮 全难度极限出怪运阵演示脚本
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
// 自动在指定位置放置植物触发巨人僵尸举锤阻挡其前进。结合TickRunner使用
void BlockGargantuar(std::vector<Grid> pos);
TickRunner block_giga;
void Script()
{
    // 脚本在游戏主界面和选择植物界面生效
    OpenMultipleEffective('Q', MAIN_UI_OR_FIGHT_UI);
    // 全难度极限出怪：普僵、撑杆、橄榄、舞王、冰车、小丑、矿工、跳跳、小偷、扶梯、投篮、白眼、红眼、海豚
    SetZombies({ZOMBIE, POLE_VAULTING_ZOMBIE, FOOTBALL_ZOMBIE, DANCING_ZOMBIE, ZOMBONI, JACK_IN_THE_BOX_ZOMBIE, DIGGER_ZOMBIE, POGO_ZOMBIE, BUNGEE_ZOMBIE, LADDER_ZOMBIE, CATAPULT_ZOMBIE, GARGANTUAR, GIGA_GARGANTUAR, DOLPHIN_RIDER_ZOMBIE});
    // 选择植物：毁灭菇、模仿毁灭菇、睡莲叶、樱桃炸弹、火爆辣椒、小喷菇、花盆、胆小菇、阳光菇、南瓜头
    SelectCards({DOOM_SHROOM, M_DOOM_SHROOM, LILY_PAD, CHERRY_BOMB, JALAPENO, PUFF_SHROOM, FLOWER_POT, SCAREDY_SHROOM, SUN_SHROOM, PUMPKIN});
    SetTime(-599, 1);
    // 填充炮列表
    pao_operator.resetPaoList({{1, 2}, {6, 2}, {1, 4}, {6, 4}, {2, 3}, {5, 3}, {2, 5}, {5, 5}, {3, 1}, {4, 1}, {3, 3}, {4, 3}, {3, 5}, {4, 5}});
    // 铲除临时植物
    Shovel({{1, 6}, {6, 6}, {2, 7}, {5, 7}, {2, 9}, {5, 9}});
    // 主体节奏 P4-N cccc-PPDD|cccc-PPDD|cccc-PPDD|cccc-NDD 869|869|869|869 每波执行确定的操作，不考虑非旗帜波的刷新延迟

    // wave1 cccc-PPDD
    SetTime(147, 1);
    Card(FLOWER_POT, 2, 9);
    Card(SCAREDY_SHROOM, 5, 9);
    SetTime(147 + 79, 1);
    Shovel({{2, 9}, {5, 9}});
    SetTime(869 - 200 - 373, 1);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    SetTime(869 - 200 + 118 - 373, 1);
    pao_operator.pao({{1, 7.1125}, {5, 7.1125}});

    // wave2 cccc-PPDD
    SetTime(0, 2);
    Card(PUFF_SHROOM, 2, 7);
    Card(SUN_SHROOM, 5, 7);
    SetTime(147, 2);
    Card(FLOWER_POT, 2, 9);
    Card(SCAREDY_SHROOM, 5, 9);
    SetTime(147 + 79, 2);
    Shovel({{2, 9}, {5, 9}});
    SetTime(869 - 200 - 209, 2);
    Shovel({{2, 7}, {5, 7}});
    SetTime(869 - 200 - 373, 2);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    SetTime(869 - 200 + 118 - 373, 2);
    pao_operator.pao({{1, 7.1125}, {5, 7.1125}});

    // wave3 cccc-PPDD
    SetTime(0, 3);
    Card(PUFF_SHROOM, 2, 7);
    Card(SUN_SHROOM, 5, 7);
    SetTime(147, 3);
    Card(FLOWER_POT, 2, 9);
    Card(SCAREDY_SHROOM, 5, 9);
    SetTime(147 + 79, 3);
    Shovel({{2, 9}, {5, 9}});
    SetTime(869 - 200 - 209, 3);
    Shovel({{2, 7}, {5, 7}});
    SetTime(869 - 200 - 373, 3);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    SetTime(869 - 200 + 118 - 373, 3);
    pao_operator.pao({{1, 7.1125}, {5, 7.1125}});

    // wave4 cccc-NDD
    SetTime(0, 4);
    Card(PUFF_SHROOM, 2, 7);
    Card(SUN_SHROOM, 5, 7);
    SetTime(147, 4);
    Card(FLOWER_POT, 2, 9);
    Card(SCAREDY_SHROOM, 5, 9);
    SetTime(147 + 79, 4);
    Shovel({{2, 9}, {5, 9}});
    SetTime(869 - 200 - 209, 4);
    Shovel({{2, 7}, {5, 7}});
    SetTime(869 - 200 - 100 - 751, 4);
    Card(LILY_PAD, 3, 8);
    SetTime(549 - 100, 4);
    Card(CHERRY_BOMB, 3, 8);
    SetTime(549 + 1, 4);
    Shovel(3, 8);
    SetTime(869 - 200 - 100, 4);
    Card(LILY_PAD, 3, 9);
    Card(DOOM_SHROOM, 3, 9);
    SetTime(869 - 200 + 117 - 373, 4);
    pao_operator.pao({{1, 7.1125}, {5, 7.1125}});

    // wave5 cccc-PPDD
    SetTime(0, 5);
    Card(PUFF_SHROOM, 2, 7);
    Card(SUN_SHROOM, 5, 7);
    SetTime(147, 5);
    Card(FLOWER_POT, 2, 9);
    Card(SCAREDY_SHROOM, 5, 9);
    SetTime(147 + 79, 5);
    Shovel({{2, 9}, {5, 9}});
    SetTime(869 - 200 - 209, 5);
    Shovel({{2, 7}, {5, 7}});
    SetTime(869 - 200 - 373, 5);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    SetTime(869 - 200 + 118 - 373, 5);
    pao_operator.pao({{1, 7.1125}, {5, 7.1125}});

    // wave6 cccc-PPDD
    SetTime(0, 6);
    Card(PUFF_SHROOM, 2, 7);
    Card(SUN_SHROOM, 5, 7);
    SetTime(147, 6);
    Card(FLOWER_POT, 2, 9);
    Card(SCAREDY_SHROOM, 5, 9);
    SetTime(147 + 79, 6);
    Shovel({{2, 9}, {5, 9}});
    SetTime(869 - 200 - 209, 6);
    Shovel({{2, 7}, {5, 7}});
    SetTime(869 - 200 - 373, 6);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    SetTime(869 - 200 + 118 - 373, 6);
    pao_operator.pao({{1, 7.1125}, {5, 7.1125}});

    // wave7 cccc-PPDD
    SetTime(0, 7);
    Card(PUFF_SHROOM, 2, 7);
    Card(SUN_SHROOM, 5, 7);
    SetTime(147, 7);
    Card(FLOWER_POT, 2, 9);
    Card(SCAREDY_SHROOM, 5, 9);
    SetTime(147 + 79, 7);
    Shovel({{2, 9}, {5, 9}});
    SetTime(869 - 200 - 209, 7);
    Shovel({{2, 7}, {5, 7}});
    SetTime(869 - 200 - 373, 7);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    SetTime(869 - 200 + 118 - 373, 7);
    pao_operator.pao({{1, 7.1125}, {5, 7.1125}});

    // wave8 cccc-NDD
    SetTime(0, 8);
    Card(PUFF_SHROOM, 2, 7);
    Card(SUN_SHROOM, 5, 7);
    SetTime(147, 8);
    Card(FLOWER_POT, 2, 9);
    Card(SCAREDY_SHROOM, 5, 9);
    SetTime(147 + 79, 8);
    Shovel({{2, 9}, {5, 9}});
    SetTime(869 - 200 - 209, 8);
    Shovel(5, 7);
    SetTime(549 - 100, 8);
    Shovel(2, 7);
    Card(JALAPENO, 2, 7);
    SetTime(869 - 200 - 419, 8);
    Card(LILY_PAD, 3, 8);
    Card(PUMPKIN, 3, 8);
    Card(M_DOOM_SHROOM, 3, 8);
    SetTime(869 - 200 + 118 - 373, 8);
    pao_operator.pao({{1, 7.1125}, {5, 7.1125}});

    // wave9 cccc-PPDD-PP-PP-PP
    SetTime(0, 9);
    Card(PUFF_SHROOM, 2, 7);
    Card(SUN_SHROOM, 5, 7);
    SetTime(147, 9);
    Card(FLOWER_POT, 2, 9);
    Card(SCAREDY_SHROOM, 5, 9);
    SetTime(147 + 79, 9);
    Shovel({{2, 9}, {5, 9}});
    SetTime(869 - 200 - 209, 9);
    Shovel({{2, 7}, {5, 7}});
    SetTime(869 - 200 - 373, 9);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    SetTime(869 - 200 + 118 - 373, 9);
    pao_operator.pao({{1, 7.1125}, {5, 7.1125}});
    SetTime(0 + 869, 9);
    Card(PUFF_SHROOM, 2, 7);
    Card(SUN_SHROOM, 5, 7);
    SetTime(869 - 200 + 869 - 209, 9);
    Shovel({{2, 7}, {5, 7}});
    SetTime(869 - 200 + 869 - 373, 9);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    SetTime(869 - 200 + 869 + 118 - 373, 9);
    pao_operator.pao({{1, 7.1125}, {5, 7.1125}});
    pao_operator.recoverPao({{2, 7}, {5, 7}});
    SetTime(869 - 200 + 869 + 4, 9);
    InsertOperation([=]() {
        block_giga.pushFunc([]() {
            BlockGargantuar({{2, 7}, {5, 7}, {1, 6}, {6, 6}});
        });
    });

    // wave10 cccc-PPDD
    SetTime(0, 10);
    block_giga.pause();
    Shovel({{1, 6}, {6, 6}});
    SetTime(241, 10);
    Card(FLOWER_POT, 2, 9);
    Card(SCAREDY_SHROOM, 5, 9);
    SetTime(241 + 79, 10);
    Shovel({{2, 9}, {5, 9}});
    SetTime(869 - 200 - 373, 10);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    SetTime(869 - 200 + 118 - 373, 10);
    pao_operator.pao({{1, 7.1125}, {5, 7.1125}});

    // wave11 cccc-PPDD
    SetTime(0, 11);
    Card(PUFF_SHROOM, 2, 7);
    Card(SUN_SHROOM, 5, 7);
    SetTime(147, 11);
    Card(FLOWER_POT, 2, 9);
    Card(SCAREDY_SHROOM, 5, 9);
    SetTime(147 + 79, 11);
    Shovel({{2, 9}, {5, 9}});
    SetTime(869 - 200 - 209, 11);
    Shovel({{2, 7}, {5, 7}});
    SetTime(869 - 200 - 373, 11);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    SetTime(869 - 200 + 118 - 373, 11);
    pao_operator.pao({{1, 7.1125}, {5, 7.1125}});

    // wave12 cccc-PPDD
    SetTime(0, 12);
    Card(PUFF_SHROOM, 2, 7);
    Card(SUN_SHROOM, 5, 7);
    SetTime(147, 12);
    Card(FLOWER_POT, 2, 9);
    Card(SCAREDY_SHROOM, 5, 9);
    SetTime(147 + 79, 12);
    Shovel({{2, 9}, {5, 9}});
    SetTime(869 - 200 - 209, 12);
    Shovel({{2, 7}, {5, 7}});
    SetTime(869 - 200 - 373, 12);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    SetTime(869 - 200 + 118 - 373, 12);
    pao_operator.pao({{1, 7.1125}, {5, 7.1125}});

    // wave13 cccc-NDD
    SetTime(0, 13);
    Card(PUFF_SHROOM, 2, 7);
    Card(SUN_SHROOM, 5, 7);
    SetTime(147, 13);
    Card(FLOWER_POT, 2, 9);
    Card(SCAREDY_SHROOM, 5, 9);
    SetTime(147 + 79, 13);
    Shovel({{2, 9}, {5, 9}});
    SetTime(869 - 200 - 209, 13);
    Shovel({{2, 7}, {5, 7}});
    SetTime(869 - 200 - 100 - 751, 13);
    Card(LILY_PAD, 4, 8);
    SetTime(549 - 100, 13);
    Card(CHERRY_BOMB, 4, 8);
    SetTime(549 + 1, 13);
    Shovel(4, 8);
    SetTime(869 - 200 - 100, 13);
    Card(LILY_PAD, 4, 9);
    Card(DOOM_SHROOM, 4, 9);
    SetTime(869 - 200 + 117 - 373, 13);
    pao_operator.pao({{1, 7.1125}, {5, 7.1125}});

    // wave14 cccc-PPDD
    SetTime(0, 14);
    Card(PUFF_SHROOM, 2, 7);
    Card(SUN_SHROOM, 5, 7);
    SetTime(147, 14);
    Card(FLOWER_POT, 2, 9);
    Card(SCAREDY_SHROOM, 5, 9);
    SetTime(147 + 79, 14);
    Shovel({{2, 9}, {5, 9}});
    SetTime(869 - 200 - 209, 14);
    Shovel({{2, 7}, {5, 7}});
    SetTime(869 - 200 - 373, 14);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    SetTime(869 - 200 + 118 - 373, 14);
    pao_operator.pao({{1, 7.1125}, {5, 7.1125}});

    // wave15 cccc-PPDD
    SetTime(0, 15);
    Card(PUFF_SHROOM, 2, 7);
    Card(SUN_SHROOM, 5, 7);
    SetTime(147, 15);
    Card(FLOWER_POT, 2, 9);
    Card(SCAREDY_SHROOM, 5, 9);
    SetTime(147 + 79, 15);
    Shovel({{2, 9}, {5, 9}});
    SetTime(869 - 200 - 209, 15);
    Shovel({{2, 7}, {5, 7}});
    SetTime(869 - 200 - 373, 15);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    SetTime(869 - 200 + 118 - 373, 15);
    pao_operator.pao({{1, 7.1125}, {5, 7.1125}});

    // wave16 cccc-PPDD
    SetTime(0, 16);
    Card(PUFF_SHROOM, 2, 7);
    Card(SUN_SHROOM, 5, 7);
    SetTime(147, 16);
    Card(FLOWER_POT, 2, 9);
    Card(SCAREDY_SHROOM, 5, 9);
    SetTime(147 + 79, 16);
    Shovel({{2, 9}, {5, 9}});
    SetTime(869 - 200 - 209, 16);
    Shovel({{2, 7}, {5, 7}});
    SetTime(869 - 200 - 373, 16);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    SetTime(869 - 200 + 118 - 373, 16);
    pao_operator.pao({{1, 7.1125}, {5, 7.1125}});

    // wave17 cccc-NDD
    SetTime(0, 17);
    Card(PUFF_SHROOM, 2, 7);
    Card(SUN_SHROOM, 5, 7);
    SetTime(147, 17);
    Card(FLOWER_POT, 2, 9);
    Card(SCAREDY_SHROOM, 5, 9);
    SetTime(147 + 79, 17);
    Shovel({{2, 9}, {5, 9}});
    SetTime(869 - 200 - 209, 17);
    Shovel(2, 7);
    SetTime(549 - 100, 17);
    Shovel(5, 7);
    Card(JALAPENO, 5, 7);
    SetTime(869 - 200 - 419, 17);
    Card(LILY_PAD, 4, 8);
    Card(PUMPKIN, 4, 8);
    Card(M_DOOM_SHROOM, 4, 8);
    SetTime(869 - 200 + 118 - 373, 17);
    pao_operator.pao({{1, 7.1125}, {5, 7.1125}});

    // wave18 cccc-PPDD
    SetTime(0, 18);
    Card(PUFF_SHROOM, 2, 7);
    Card(SUN_SHROOM, 5, 7);
    SetTime(147, 18);
    Card(FLOWER_POT, 2, 9);
    Card(SCAREDY_SHROOM, 5, 9);
    SetTime(147 + 79, 18);
    Shovel({{2, 9}, {5, 9}});
    SetTime(869 - 200 - 209, 18);
    Shovel({{2, 7}, {5, 7}});
    SetTime(869 - 200 - 373, 18);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    SetTime(869 - 200 + 118 - 373, 18);
    pao_operator.pao({{1, 7.1125}, {5, 7.1125}});

    // wave19 cccc-PPDD
    SetTime(0, 19);
    Card(PUFF_SHROOM, 2, 7);
    Card(SUN_SHROOM, 5, 7);
    SetTime(147, 19);
    Card(FLOWER_POT, 2, 9);
    Card(SCAREDY_SHROOM, 5, 9);
    SetTime(147 + 79, 19);
    Shovel({{2, 9}, {5, 9}});
    SetTime(869 - 200 - 209, 19);
    Shovel({{2, 7}, {5, 7}});
    SetTime(869 - 200 - 373, 19);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    SetTime(869 - 200 + 118 - 373, 19);
    pao_operator.pao({{1, 7.1125}, {5, 7.1125}});
    SetTime(0 + 869, 19);
    Card(PUFF_SHROOM, 2, 7);
    Card(SUN_SHROOM, 5, 7);
    SetTime(869 - 200 + 869 - 209, 19);
    Shovel({{2, 7}, {5, 7}});
    SetTime(869 - 200 + 869 - 373, 19);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    SetTime(869 - 200 + 869 + 118 - 373, 19);
    pao_operator.pao({{1, 7.1125}, {5, 7.1125}});
    pao_operator.recoverPao({{2, 7}, {5, 7}});
    SetTime(869 - 200 + 869 + 4, 19);
    block_giga.goOn();

    // wave20 cccc-PPDD
    // 炮消珊瑚
    SetTime(223 - 373, 20);
    pao_operator.pao(4, 7.5875);
    SetTime(1, 20);
    Card(PUFF_SHROOM, 2, 7);
    Card(SUN_SHROOM, 5, 7);
    SetTime(241, 20);
    Card(FLOWER_POT, 2, 9);
    Card(SCAREDY_SHROOM, 5, 9);
    SetTime(241 + 79, 20);
    Shovel({{2, 9}, {5, 9}});
    SetTime(869 - 200 - 373, 20);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    SetTime(869 - 200 + 118 - 373, 20);
    pao_operator.pao({{1, 7.1125}, {5, 7.1125}});
    SetTime(1700 - 373, 20);
    pao_operator.pao({{2, 8}, {5, 8}, {2, 8}, {5, 8}, {2, 8}, {5, 8}});
}
void BlockGargantuar(std::vector<Grid> pos)
{
    for (Grid each : pos) {
        auto zombies = GetMainObject()->zombieArray();
        auto seeds = GetMainObject()->seedArray();
        std::vector<int> indices_seed = {GetSeedIndex(PUFF_SHROOM), GetSeedIndex(FLOWER_POT), GetSeedIndex(SCAREDY_SHROOM), GetSeedIndex(SUN_SHROOM)};
        for (int index = 0; index < GetMainObject()->zombieTotal(); ++index) {
            if (!zombies[index].isDead() && !zombies[index].isDisappeared() && (zombies[index].type() == GARGANTUAR || zombies[index].type() == GIGA_GARGANTUAR) && zombies[index].row() + 1 == each.row && (zombies[index].abscissa() <= 40 + (each.col - 1) * 80 + 50 + 1 && zombies[index].abscissa() >= 40 + (each.col - 1) * 80 - 5) && zombies[index].state() == 0) {
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