/*
 * @Author: qrmd
 * @Date: 2022-08-12 15:05:58
 * @LastEditors: qrmd
 * @LastEditTime: 2022-08-12 23:58:08
 * @Description: PE变奏二十二炮 全难度极限出怪运阵演示
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
// *** Not In Queue
// 自动在指定位置放置植物触发巨人僵尸举锤阻挡其前进。结合TickRunner使用
void BlockGargantuar(std::vector<Grid> pos);
TickRunner block_giga;
// *** In Queue
// 留下一行领带僵尸或巨人僵尸，自动放置植物将其拖住以延长第[wave]波收尾，适用于六行场地
void EndingTheWave(int wave);

void Script()
{
    // 脚本在游戏主界面和选择植物界面生效
    OpenMultipleEffective('Q', MAIN_UI_OR_FIGHT_UI);
    // 全难度极限出怪：普僵、撑杆、橄榄、舞王、冰车、小丑、矿工、跳跳、小偷、扶梯、投篮、白眼、红眼、海豚
    SetZombies({ZOMBIE, POLE_VAULTING_ZOMBIE, FOOTBALL_ZOMBIE, DANCING_ZOMBIE, ZOMBONI, JACK_IN_THE_BOX_ZOMBIE, DIGGER_ZOMBIE, POGO_ZOMBIE, BUNGEE_ZOMBIE, LADDER_ZOMBIE, CATAPULT_ZOMBIE, GARGANTUAR, GIGA_GARGANTUAR, DOLPHIN_RIDER_ZOMBIE});
    // 选择植物：咖啡豆、寒冰菇、模仿寒冰菇、南瓜头、樱桃炸弹、小喷菇、花盆、胆小菇、阳光菇、坚果
    SelectCards({COFFEE_BEAN, ICE_SHROOM, M_ICE_SHROOM, PUMPKIN, CHERRY_BOMB, PUFF_SHROOM, FLOWER_POT, SCAREDY_SHROOM, SUN_SHROOM, WALL_NUT});
    SetTime(-599, 1);
    // 填充炮列表
    pao_operator.resetPaoList({{1, 1}, {6, 1}, {1, 3}, {6, 3}, {1, 5}, {6, 5}, {1, 7}, {6, 7}, {2, 1}, {5, 1}, {2, 3}, {5, 3}, {2, 5}, {5, 5}, {2, 7}, {5, 7}, {3, 1}, {4, 1}, {3, 3}, {4, 3}, {3, 5}, {4, 5}});
    // 开始自动存冰
    ice_filler.start({{3, 9}, {4, 9}});
    // 开始自动修补南瓜头
    plant_fixer.start(PUMPKIN, {{3, 9}, {4, 9}}, 1200);
    // 主体节奏 ch6 IPP-PPDD|BPD/BDcc|IPP-PPDD|BPD/BDcc| 1149|601|1149|601 每波执行确定的操作，不考虑非旗帜波的刷新延迟
    // wave1 PPDD
    SetTime(359 - 373, 1);
    pao_operator.pao({{2, 8.75}, {5, 8.75}});
    SetTime(359 - 373 + 107, 1);
    pao_operator.pao({{1, 7.7}, {5, 7.7}});

    // wave2 PSD/PDcc
    SetTime(257 - 373, 2);
    pao_operator.pao({{2, 8.75}, {2, 8.75}});
    SetTime(257 + 110 - 373, 2);
    pao_operator.pao({{1, 8.75}});
    SetTime(313 - 373, 2);
    pao_operator.pao(5, 8.75);
    SetTime(313 - 373 + 110, 2);
    pao_operator.pao(5, 7.7);
    SetTime(446, 2);
    Card({{PUFF_SHROOM, 5, 9}, {FLOWER_POT, 6, 9}});
    SetTime(532, 2);
    Shovel({{5, 9}, {6, 9}});

    // wave3 IPP-PPDD
    SetTime(100 - 298, 3);
    ice_filler.coffee();
    SetTime(173 - 373, 3);
    pao_operator.pao(1, 8.625);
    SetTime(429 - 373, 3);
    pao_operator.pao(5, 7.425);
    SetTime(1149 - 200 - 373, 3);
    pao_operator.pao({{2, 8.75}, {5, 8.75}});
    SetTime(1149 - 200 + 216 - 373, 3);
    pao_operator.pao({{1, 8.75}, {5, 8.75}});

    // wave4 BPD/BDcc
    SetTime(-200 + 216 + 216 - 373, 4);
    pao_operator.pao({{1, 8.75}, {5, 8.75}});
    SetTime(-200 + 216 + 216 + 102 - 373, 4);
    pao_operator.pao(2, 8.75);
    SetTime(-200 + 216 + 216 + 102 + 110 - 373, 4);
    pao_operator.pao(1, 8.75);
    SetTime(-200 + 216 + 216 + 110 - 373, 4);
    pao_operator.pao(5, 8.1625);
    SetTime(446, 4);
    Card({{PUFF_SHROOM, 5, 9}, {FLOWER_POT, 6, 9}});
    SetTime(532, 4);
    Shovel({{5, 9}, {6, 9}});

    // wave5 IPP-PPDD
    SetTime(100 - 298, 5);
    ice_filler.coffee();
    SetTime(173 - 373, 5);
    pao_operator.pao(1, 8.625);
    SetTime(429 - 373, 5);
    pao_operator.pao(5, 7.425);
    SetTime(1149 - 200 - 373, 5);
    pao_operator.pao({{2, 8.75}, {5, 8.75}});
    SetTime(1149 - 200 + 216 - 373, 5);
    pao_operator.pao({{1, 8.75}, {5, 8.75}});

    // wave6 BPD/BDcc
    SetTime(-200 + 216 + 216 - 373, 6);
    pao_operator.pao({{1, 8.75}, {5, 8.75}});
    SetTime(-200 + 216 + 216 + 102 - 373, 6);
    pao_operator.pao(2, 8.75);
    SetTime(-200 + 216 + 216 + 102 + 110 - 373, 6);
    pao_operator.pao(1, 8.75);
    SetTime(-200 + 216 + 216 + 110 - 373, 6);
    pao_operator.pao(5, 8.1625);
    SetTime(446, 6);
    Card({{PUFF_SHROOM, 5, 9}, {FLOWER_POT, 6, 9}});
    SetTime(532, 6);
    Shovel({{5, 9}, {6, 9}});

    // wave7 IPP-PPDD
    SetTime(100 - 298, 7);
    ice_filler.coffee();
    SetTime(173 - 373, 7);
    pao_operator.pao(1, 8.625);
    SetTime(429 - 373, 7);
    pao_operator.pao(5, 7.425);
    SetTime(1149 - 200 - 373, 7);
    pao_operator.pao({{2, 8.75}, {5, 8.75}});
    SetTime(1149 - 200 + 216 - 373, 7);
    pao_operator.pao({{1, 8.75}, {5, 8.75}});

    // wave8 BPD/BDcc
    SetTime(-200 + 216 + 216 - 373, 8);
    pao_operator.pao({{1, 8.75}, {5, 8.75}});
    SetTime(-200 + 216 + 216 + 102 - 373, 8);
    pao_operator.pao(2, 8.75);
    SetTime(-200 + 216 + 216 + 102 + 110 - 373, 8);
    pao_operator.pao(1, 8.75);
    SetTime(-200 + 216 + 216 + 110 - 373, 8);
    pao_operator.pao(5, 8.1625);
    SetTime(446, 8);
    Card({{PUFF_SHROOM, 5, 9}, {FLOWER_POT, 6, 9}});
    SetTime(532, 8);
    Shovel({{5, 9}, {6, 9}});

    // wave9 IPP-PPDD
    SetTime(100 - 298, 9);
    ice_filler.coffee();
    SetTime(173 - 373, 9);
    pao_operator.pao(1, 8.625);
    SetTime(429 - 373, 9);
    pao_operator.pao(5, 7.425);
    SetTime(1149 - 200 - 373, 9);
    pao_operator.pao({{2, 8.75}, {5, 8.75}});
    SetTime(1149 - 200 + 216 - 373, 9);
    pao_operator.pao({{1, 8.75}, {5, 8.75}});
    SetTime(1149 - 200 + 216 + 216 - 373, 9);
    pao_operator.pao({{1, 8.75}, {5, 8.75}});
    SetTime(1149 - 200 + 216 + 216, 9);
    Card({{PUFF_SHROOM, 1, 9}, {FLOWER_POT, 2, 9}, {SCAREDY_SHROOM, 5, 9}, {SUN_SHROOM, 6, 9}});
    SetTime(2500 - 373, 9);
    pao_operator.pao({{2, 8.75}, {5, 8.75}});
    SetTime(2500, 9);
    Shovel({{1, 9}, {2, 9}, {5, 9}, {6, 9}});

    // wave10 PDD/PDA
    SetTime(25 - 200 + 216 + 216 - 373, 10);
    pao_operator.pao({{2, 8.75}, {5, 8.75}});
    SetTime(25 - 200 + 216 + 216 + 102 - 373, 10);
    pao_operator.pao({{2, 8.75}, {5, 8.75}});
    SetTime(25 - 200 + 216 + 216 + 102 + 110 - 373, 10);
    pao_operator.pao(1, 8.75);
    SetTime(25 - 200 + 216 + 216 + 102 + 110 - 100, 10);
    Card(CHERRY_BOMB, 5, 9);

    // wave11 IPP-PPDD
    SetTime(100 - 298, 11);
    ice_filler.coffee();
    SetTime(173 - 373, 11);
    pao_operator.pao(1, 8.625);
    SetTime(429 - 373, 11);
    pao_operator.pao(5, 7.425);
    SetTime(1149 - 200 - 373, 11);
    pao_operator.pao({{2, 8.75}, {5, 8.75}});
    SetTime(1149 - 200 + 216 - 373, 11);
    pao_operator.pao({{1, 8.75}, {5, 8.75}});

    // wave12 BPD/BDcc
    SetTime(-200 + 216 + 216 - 373, 12);
    pao_operator.pao({{1, 8.75}, {5, 8.75}});
    SetTime(-200 + 216 + 216 + 102 - 373, 12);
    pao_operator.pao(2, 8.75);
    SetTime(-200 + 216 + 216 + 102 + 110 - 373, 12);
    pao_operator.pao(1, 8.75);
    SetTime(-200 + 216 + 216 + 110 - 373, 12);
    pao_operator.pao(5, 8.1625);
    SetTime(446, 12);
    Card({{PUFF_SHROOM, 5, 9}, {FLOWER_POT, 6, 9}});
    SetTime(532, 12);
    Shovel({{5, 9}, {6, 9}});

    // wave13 IPP-PPDD
    SetTime(100 - 298, 13);
    ice_filler.coffee();
    SetTime(173 - 373, 13);
    pao_operator.pao(1, 8.625);
    SetTime(429 - 373, 13);
    pao_operator.pao(5, 7.425);
    SetTime(1149 - 200 - 373, 13);
    pao_operator.pao({{2, 8.75}, {5, 8.75}});
    SetTime(1149 - 200 + 216 - 373, 13);
    pao_operator.pao({{1, 8.75}, {5, 8.75}});

    // wave14 BPD/BDcc
    SetTime(-200 + 216 + 216 - 373, 14);
    pao_operator.pao({{1, 8.75}, {5, 8.75}});
    SetTime(-200 + 216 + 216 + 102 - 373, 14);
    pao_operator.pao(2, 8.75);
    SetTime(-200 + 216 + 216 + 102 + 110 - 373, 14);
    pao_operator.pao(1, 8.75);
    SetTime(-200 + 216 + 216 + 110 - 373, 14);
    pao_operator.pao(5, 8.1625);
    SetTime(446, 14);
    Card({{PUFF_SHROOM, 5, 9}, {FLOWER_POT, 6, 9}});
    SetTime(532, 14);
    Shovel({{5, 9}, {6, 9}});

    // wave15 IPP-PPDD
    SetTime(100 - 298, 15);
    ice_filler.coffee();
    SetTime(173 - 373, 15);
    pao_operator.pao(1, 8.625);
    SetTime(429 - 373, 15);
    pao_operator.pao(5, 7.425);
    SetTime(1149 - 200 - 373, 15);
    pao_operator.pao({{2, 8.75}, {5, 8.75}});
    SetTime(1149 - 200 + 216 - 373, 15);
    pao_operator.pao({{1, 8.75}, {5, 8.75}});

    // wave16 BPD/BDcc
    SetTime(-200 + 216 + 216 - 373, 16);
    pao_operator.pao({{1, 8.75}, {5, 8.75}});
    SetTime(-200 + 216 + 216 + 102 - 373, 16);
    pao_operator.pao(2, 8.75);
    SetTime(-200 + 216 + 216 + 102 + 110 - 373, 16);
    pao_operator.pao(1, 8.75);
    SetTime(-200 + 216 + 216 + 110 - 373, 16);
    pao_operator.pao(5, 8.1625);
    SetTime(446, 16);
    Card({{PUFF_SHROOM, 5, 9}, {FLOWER_POT, 6, 9}});
    SetTime(532, 16);
    Shovel({{5, 9}, {6, 9}});

    // wave17 IPP-PPDD
    SetTime(100 - 298, 17);
    ice_filler.coffee();
    SetTime(173 - 373, 17);
    pao_operator.pao(1, 8.625);
    SetTime(429 - 373, 17);
    pao_operator.pao(5, 7.425);
    SetTime(1149 - 200 - 373, 17);
    pao_operator.pao({{2, 8.75}, {5, 8.75}});
    SetTime(1149 - 200 + 216 - 373, 17);
    pao_operator.pao({{1, 8.75}, {5, 8.75}});

    // wave18 BPD/BDcc
    SetTime(-200 + 216 + 216 - 373, 18);
    pao_operator.pao({{1, 8.75}, {5, 8.75}});
    SetTime(-200 + 216 + 216 + 102 - 373, 18);
    pao_operator.pao(2, 8.75);
    SetTime(-200 + 216 + 216 + 102 + 110 - 373, 18);
    pao_operator.pao(1, 8.75);
    SetTime(-200 + 216 + 216 + 110 - 373, 18);
    pao_operator.pao(5, 8.1625);
    SetTime(446, 18);
    Card({{PUFF_SHROOM, 5, 9}, {FLOWER_POT, 6, 9}});
    SetTime(532, 18);
    Shovel({{5, 9}, {6, 9}});

    // wave19 IPP-PPDD
    SetTime(100 - 298, 19);
    ice_filler.coffee();
    SetTime(173 - 373, 19);
    pao_operator.pao(1, 8.625);
    SetTime(429 - 373, 19);
    pao_operator.pao(5, 7.425);
    SetTime(1149 - 200 - 373, 19);
    pao_operator.pao({{2, 8.75}, {5, 8.75}});
    SetTime(1149 - 200 + 216 - 373, 19);
    pao_operator.pao({{1, 8.75}, {5, 8.75}});
    SetTime(1149 - 200 + 216 + 216 - 373, 19);
    pao_operator.pao({{1, 8.75}, {5, 8.75}});
    SetTime(1149 - 200 + 216 + 216, 19);
    Card({{PUFF_SHROOM, 1, 9}, {FLOWER_POT, 2, 9}, {SCAREDY_SHROOM, 5, 9}, {SUN_SHROOM, 6, 9}});
    SetTime(2500 - 373, 19);
    pao_operator.pao({{2, 8.75}, {5, 8.75}});
    SetTime(2500, 19);
    Shovel({{1, 9}, {2, 9}, {5, 9}, {6, 9}});

    // wave20 PDD/PDA
    // 炮消珊瑚
    SetTime(226 - 373, 20);
    pao_operator.pao(4, 7.5875);
    SetTime(25 - 200 + 216 + 216 - 373, 20);
    pao_operator.pao({{2, 8.75}, {5, 8.75}});
    SetTime(25 - 200 + 216 + 216 + 102 - 373, 20);
    pao_operator.pao({{2, 8.75}, {5, 8.75}});
    SetTime(25 - 200 + 216 + 216 + 102 + 110 - 373, 20);
    pao_operator.pao(1, 8.75);
    SetTime(25 - 200 + 216 + 216 + 102 + 110 - 100, 20);
    Card(CHERRY_BOMB, 5, 9);
    SetTime(470, 20);
    Card({{PUFF_SHROOM, 1, 9}, {FLOWER_POT, 2, 9}, {SCAREDY_SHROOM, 5, 9}, {SUN_SHROOM, 6, 9}});
    SetTime(500, 20);
    EndingTheWave(20);
    SetTime(777, 20);
    Shovel({{1, 9}, {2, 9}, {5, 9}, {6, 9}});
}
void BlockGargantuar(std::vector<Grid> pos)
{
    for (Grid each : pos) {
        auto zombies = GetMainObject()->zombieArray();
        auto seeds = GetMainObject()->seedArray();
        std::vector<int> indices_seed = {GetSeedIndex(PUFF_SHROOM), GetSeedIndex(FLOWER_POT), GetSeedIndex(SCAREDY_SHROOM), GetSeedIndex(SUN_SHROOM), GetSeedIndex(WALL_NUT)};
        for (int index = 0; index < GetMainObject()->zombieTotal(); ++index) {
            if (!zombies[index].isDead() && !zombies[index].isDisappeared() && (zombies[index].type() == GARGANTUAR || zombies[index].type() == GIGA_GARGANTUAR || zombies[index].type() == ZOMBIE || zombies[index].type() == CONEHEAD_ZOMBIE || zombies[index].type() == BUCKETHEAD_ZOMBIE || zombies[index].type() == SCREEN_DOOR_ZOMBIE) && zombies[index].row() + 1 == each.row && (zombies[index].abscissa() <= 40 + (each.col - 1) * 80 + 30 + 1 && zombies[index].abscissa() >= 40 + (each.col - 1) * 80 - 5) && zombies[index].state() == 0) {
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
void EndingTheWave(int wave)
{
    InsertOperation([=]() {
        int reserved_row = -1;
        const std::vector<int> zombie_list = {ZOMBIE, CONEHEAD_ZOMBIE, BUCKETHEAD_ZOMBIE, SCREEN_DOOR_ZOMBIE, NEWSPAPER_ZOMBIE};
        const std::vector<int> gargantuar_list = {GARGANTUAR, GIGA_GARGANTUAR};
        std::vector<int> zombie_number(6, 0);
        auto zombies = GetMainObject()->zombieArray();
        for (int index = 0; index < GetMainObject()->zombieTotal(); ++index) {
            if (!zombies[index].isDisappeared() && !zombies[index].isDead()) {
                if (std::find(zombie_list.begin(), zombie_list.end(), zombies[index].type()) != zombie_list.end()) {
                    if (zombies[index].row() + 1 == 3 || zombies[index].row() + 1 == 4)
                        zombie_number[zombies[index].row()] += 1;
                } else if (std::find(gargantuar_list.begin(), gargantuar_list.end(), zombies[index].type()) != gargantuar_list.end()) {
                    if (zombies[index].row() + 1 == 1 || zombies[index].row() + 1 == 6)
                        zombie_number[zombies[index].row()] += 1;
                }
            }
        }
        if (zombie_number[3 - 1] > 0 || zombie_number[4 - 1] > 0) {
            if (zombie_number[3 - 1] < zombie_number[4 - 1] && zombie_number[3 - 1] > 0)
                reserved_row = 3;
            else
                reserved_row = 4;
        } else if (zombie_number[1 - 1] > 0 || zombie_number[6 - 1] > 0) {
            if (zombie_number[1 - 1] < zombie_number[6 - 1] && zombie_number[1 - 1] > 0)
                reserved_row = 1;
            else
                reserved_row = 6;
        }
        SetNowTime();
        switch (reserved_row) {
        case 1:
            pao_operator.recoverPao({{3, 8.75}, {5, 8.75}});
            break;
        case 3:
            pao_operator.recoverPao({{1, 8.75}, {5, 8.75}});
            break;
        case 4:
            pao_operator.recoverPao({{2, 8.75}, {6, 8.75}});
            break;
        case 6:
            pao_operator.recoverPao({{2, 8.75}, {4, 8.75}});
            break;
        default:
            pao_operator.recoverPao({{2, 8.75}, {5, 8.75}});
            break;
        }

        block_giga.pushFunc([]() {
            BlockGargantuar({{1, 9}, {2, 9}, {5, 9}, {6, 9}});
        });
        if (wave == 9 || wave == 19) {
            SetTime(4500 - 200 - 373, wave);

        } else if (wave == 20) {
            SetTime(5000 - 373, wave);
        }
        pao_operator.recoverPao({{2, 8.75}, {5, 8.75}});
        Delay(373);
        block_giga.stop();
        Shovel({{1, 9}, {2, 9}, {5, 9}, {6, 9}});
    });
}