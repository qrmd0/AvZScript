/*
 * @Author: qrmd
 * @Date: 2022-06-28 17:57:27
 * @LastEditors: qrmd
 * @LastEditTime: 2022-06-28 18:45:46
 * @Description:FE神之八炮 全难度极限出怪运阵演示脚本
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
    // 选择植物：小喷菇、模仿小喷菇、花盆、胆小菇、阳光菇、樱桃炸弹、火爆辣椒、倭瓜、寒冰菇、毁灭菇
    SelectCards({PUFF_SHROOM, M_PUFF_SHROOM, FLOWER_POT, SCAREDY_SHROOM, SUN_SHROOM, CHERRY_BOMB, JALAPENO, SQUASH, ICE_SHROOM, DOOM_SHROOM});
    SetTime(-599, 1);
    // 填充炮列表
    pao_operator.resetPaoList({{2, 5}, {5, 5}, {3, 1}, {4, 1}, {3, 4}, {4, 4}, {3, 6}, {4, 6}});
    // 铲除临时植物
    Shovel({{2, 7}, {5, 7}});
    // 主体节奏 P4 ccPP|ccPP|ccPP|ccPP 869|869|869|869 每波执行确定的操作，不考虑非旗帜波的刷新延迟

    // wave1 ccPP
    SetTime(195, 1);
    Card({{PUFF_SHROOM, 2, 9}, {M_PUFF_SHROOM, 5, 9}});
    SetTime(195 + 80, 1);
    Shovel({{2, 9}, {5, 9}});
    SetTime(869 - 200 - 373, 1);
    pao_operator.pao({{2, 8.75}, {5, 8.75}});

    // wave2 ccPP
    SetTime(195, 2);
    Card({{PUFF_SHROOM, 2, 9}, {M_PUFF_SHROOM, 5, 9}});
    SetTime(195 + 80, 2);
    Shovel({{2, 9}, {5, 9}});
    SetTime(869 - 200 - 373, 2);
    pao_operator.pao({{2, 8.75}, {5, 8.75}});

    // wave3 ccPP
    SetTime(195, 3);
    Card({{PUFF_SHROOM, 2, 9}, {M_PUFF_SHROOM, 5, 9}});
    SetTime(195 + 80, 3);
    Shovel({{2, 9}, {5, 9}});
    SetTime(869 - 200 - 373, 3);
    pao_operator.pao({{2, 8.75}, {5, 8.75}});

    // wave4 ccPP
    SetTime(195, 4);
    Card({{PUFF_SHROOM, 2, 9}, {M_PUFF_SHROOM, 5, 9}});
    SetTime(195 + 80, 4);
    Shovel({{2, 9}, {5, 9}});
    SetTime(869 - 200 - 373, 4);
    pao_operator.pao({{2, 8.75}, {5, 8.75}});

    // wave5 ccPP
    SetTime(195, 5);
    Card({{PUFF_SHROOM, 2, 9}, {M_PUFF_SHROOM, 5, 9}});
    SetTime(195 + 80, 5);
    Shovel({{2, 9}, {5, 9}});
    SetTime(869 - 200 - 373, 5);
    pao_operator.pao({{2, 8.75}, {5, 8.75}});

    // wave6 ccPP
    SetTime(195, 6);
    Card({{PUFF_SHROOM, 2, 9}, {M_PUFF_SHROOM, 5, 9}});
    SetTime(195 + 80, 6);
    Shovel({{2, 9}, {5, 9}});
    SetTime(869 - 200 - 373, 6);
    pao_operator.pao({{2, 8.75}, {5, 8.75}});

    // wave7 ccPP
    SetTime(195, 7);
    Card({{PUFF_SHROOM, 2, 9}, {M_PUFF_SHROOM, 5, 9}});
    SetTime(195 + 80, 7);
    Shovel({{2, 9}, {5, 9}});
    SetTime(869 - 200 - 373, 7);
    pao_operator.pao({{2, 8.75}, {5, 8.75}});

    // wave8 ccPP
    SetTime(195, 8);
    Card({{PUFF_SHROOM, 2, 9}, {M_PUFF_SHROOM, 5, 9}});
    SetTime(195 + 80, 8);
    Shovel({{2, 9}, {5, 9}});
    SetTime(869 - 200 - 373, 8);
    pao_operator.pao({{2, 8.75}, {5, 8.75}});

    // wave9 ccPP
    SetTime(195, 9);
    Card({{PUFF_SHROOM, 2, 9}, {M_PUFF_SHROOM, 5, 9}});
    SetTime(195 + 80, 9);
    Shovel({{2, 9}, {5, 9}});
    SetTime(869 - 200 - 373, 9);
    pao_operator.pao({{2, 8.75}, {5, 8.75}});
    pao_operator.recoverPao({{2, 8.75}, {5, 8.75}, {2, 8.75}, {5, 8.75}, {2, 8.75}, {5, 8.75}});
    InsertOperation([=]() {
        block_giga.pushFunc([=]() {
            BlockGargantuar({{2, 7}, {5, 7}});
        });
    });

    // wave10 ccPP
    SetTime(0, 10);
    block_giga.pause();
    Shovel({{2, 7}, {5, 7}});
    SetTime(231, 10);
    Card({{PUFF_SHROOM, 2, 9}, {M_PUFF_SHROOM, 5, 9}});
    SetTime(231 + 80, 10);
    Shovel({{2, 9}, {5, 9}});
    SetTime(869 - 200 - 373, 10);
    pao_operator.pao({{2, 8.75}, {5, 8.75}});

    // wave11 ccPP
    SetTime(195, 11);
    Card({{PUFF_SHROOM, 2, 9}, {M_PUFF_SHROOM, 5, 9}});
    SetTime(195 + 80, 11);
    Shovel({{2, 9}, {5, 9}});
    SetTime(869 - 200 - 373, 11);
    pao_operator.pao({{2, 8.75}, {5, 8.75}});

    // wave12 ccPP
    SetTime(195, 12);
    Card({{PUFF_SHROOM, 2, 9}, {M_PUFF_SHROOM, 5, 9}});
    SetTime(195 + 80, 12);
    Shovel({{2, 9}, {5, 9}});
    SetTime(869 - 200 - 373, 12);
    pao_operator.pao({{2, 8.75}, {5, 8.75}});

    // wave13 ccPP
    SetTime(195, 13);
    Card({{PUFF_SHROOM, 2, 9}, {M_PUFF_SHROOM, 5, 9}});
    SetTime(195 + 80, 13);
    Shovel({{2, 9}, {5, 9}});
    SetTime(869 - 200 - 373, 13);
    pao_operator.pao({{2, 8.75}, {5, 8.75}});

    // wave14 ccPP
    SetTime(195, 14);
    Card({{PUFF_SHROOM, 2, 9}, {M_PUFF_SHROOM, 5, 9}});
    SetTime(195 + 80, 14);
    Shovel({{2, 9}, {5, 9}});
    SetTime(869 - 200 - 373, 14);
    pao_operator.pao({{2, 8.75}, {5, 8.75}});

    // wave15 ccPP
    SetTime(195, 15);
    Card({{PUFF_SHROOM, 2, 9}, {M_PUFF_SHROOM, 5, 9}});
    SetTime(195 + 80, 15);
    Shovel({{2, 9}, {5, 9}});
    SetTime(869 - 200 - 373, 15);
    pao_operator.pao({{2, 8.75}, {5, 8.75}});

    // wave16 ccPP
    SetTime(195, 16);
    Card({{PUFF_SHROOM, 2, 9}, {M_PUFF_SHROOM, 5, 9}});
    SetTime(195 + 80, 16);
    Shovel({{2, 9}, {5, 9}});
    SetTime(869 - 200 - 373, 16);
    pao_operator.pao({{2, 8.75}, {5, 8.75}});

    // wave17 ccPP
    SetTime(195, 17);
    Card({{PUFF_SHROOM, 2, 9}, {M_PUFF_SHROOM, 5, 9}});
    SetTime(195 + 80, 17);
    Shovel({{2, 9}, {5, 9}});
    SetTime(869 - 200 - 373, 17);
    pao_operator.pao({{2, 8.75}, {5, 8.75}});

    // wave18 ccPP
    SetTime(195, 18);
    Card({{PUFF_SHROOM, 2, 9}, {M_PUFF_SHROOM, 5, 9}});
    SetTime(195 + 80, 18);
    Shovel({{2, 9}, {5, 9}});
    SetTime(869 - 200 - 373, 18);
    pao_operator.pao({{2, 8.75}, {5, 8.75}});

    // wave19 ccPP
    SetTime(195, 19);
    Card({{PUFF_SHROOM, 2, 9}, {M_PUFF_SHROOM, 5, 9}});
    SetTime(195 + 80, 19);
    Shovel({{2, 9}, {5, 9}});
    SetTime(869 - 200 - 373, 19);
    pao_operator.pao({{2, 8.75}, {5, 8.75}});
    pao_operator.recoverPao({{2, 8.75}, {5, 8.75}, {2, 8.75}, {5, 8.75}});
    block_giga.goOn();
    SetTime(869 * 3 + 869 - 200 + 123 - 373, 19);
    pao_operator.recoverPao({{2, 8.75}, {5, 8.75}});

    // wave20 PP-(PP-PP)
    // 炮消珊瑚
    SetTime(223 - 373, 20);
    pao_operator.pao(4, 7.5875);
    SetTime(0, 20);
    Shovel({{2, 9}, {5, 9}});
    SetTime(231, 20);
    Card({{PUFF_SHROOM, 2, 9}, {M_PUFF_SHROOM, 5, 9}});
    SetTime(231 + 80, 20);
    Shovel({{2, 9}, {5, 9}});
    SetTime(869 - 200 - 373, 20);
    pao_operator.pao({{2, 8.75}, {5, 8.75}});
    pao_operator.recoverPao({{2, 8.75}, {5, 8.75}, {2, 8.75}, {5, 8.75}, {2, 8.75}, {5, 8.75}});
}
void BlockGargantuar(std::vector<Grid> pos)
{
    for (Grid each : pos) {
        auto zombies = GetMainObject()->zombieArray();
        auto seeds = GetMainObject()->seedArray();
        std::vector<int> indices_seed = {GetSeedIndex(PUFF_SHROOM), GetSeedIndex(M_PUFF_SHROOM)};
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