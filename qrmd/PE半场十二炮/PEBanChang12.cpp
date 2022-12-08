/*
 * @Author: qrmd
 * @Date: 2022-06-28 15:46:44
 * @LastEditors: qrmd
 * @LastEditTime: 2022-06-28 15:46:55
 * @Description:PE半场十二炮 全难度极限出怪运阵演示脚本
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

PlantFixer pumpkin_fixer;
PlantFixer lily_pad_fixer;

void Script()
{
    // 脚本在游戏主界面和选择植物界面生效
    OpenMultipleEffective('Q', MAIN_UI_OR_FIGHT_UI);
    // 全难度极限出怪：普僵、撑杆、橄榄、舞王、冰车、小丑、矿工、跳跳、小偷、扶梯、投篮、白眼、红眼、海豚
    SetZombies({ZOMBIE, POLE_VAULTING_ZOMBIE, FOOTBALL_ZOMBIE, DANCING_ZOMBIE, ZOMBONI, JACK_IN_THE_BOX_ZOMBIE, DIGGER_ZOMBIE, POGO_ZOMBIE, BUNGEE_ZOMBIE, LADDER_ZOMBIE, CATAPULT_ZOMBIE, GARGANTUAR, GIGA_GARGANTUAR, DOLPHIN_RIDER_ZOMBIE});
    // 选择植物：咖啡豆、寒冰菇、模仿寒冰菇、睡莲叶、毁灭菇、樱桃炸弹、火爆辣椒、南瓜头、小喷菇、花盆
    SelectCards({COFFEE_BEAN, ICE_SHROOM, M_ICE_SHROOM, LILY_PAD, DOOM_SHROOM, CHERRY_BOMB, JALAPENO, PUMPKIN, PUFF_SHROOM, FLOWER_POT});
    SetTime(-599, 1);
    // 填充炮列表
    pao_operator.autoGetPaoList();
    // 开始自动存冰
    ice_filler.start({{4, 5}, {4, 6}, {4, 7}, {4, 8}, {5, 5}});
    // 开始自动修补南瓜头
    SetTime(-599, 1);
    lily_pad_fixer.start(LILY_PAD, {{4, 8}, {4, 7}, {4, 6}, {4, 5}});
    pumpkin_fixer.start(PUMPKIN, {{4, 8}, {4, 7}, {4, 6}, {4, 5}}, 1200);
    // 主体节奏 ch4 BI-c-PDD/P-d 每波执行确定的操作，不考虑非旗帜波的刷新延迟

    // wave1 PAD/PD
    SetTime(315 - 373, 1);
    pao_operator.pao(2, 8.75);
    SetTime(315 + 110 - 100, 1);
    Card(CHERRY_BOMB, 1, 9);
    SetTime(315 + 110 + 110 - 373, 1);
    pao_operator.pao(1, 8.675);
    SetTime(338 - 373, 1);
    pao_operator.pao(5, 8.75);
    SetTime(338 + 110 - 373, 1);
    pao_operator.pao(5, 8.175);

    // wave2 cBI-c-PDD/P-d
    SetTime(147, 2);
    Card({{PUFF_SHROOM, 1, 9}, {FLOWER_POT, 2, 9}});
    SetTime(147 + 80, 2);
    Shovel({{1, 9}, {2, 9}});
    SetTime(372 - 373, 2);
    pao_operator.pao(2, 8.1125);
    SetTime(372 - 298, 2);
    ice_filler.coffee();
    ice_filler.resetFillList({{4, 5}, {4, 6}, {4, 7}, {4, 8}});
    SetTime(807 - 373, 2);
    pao_operator.pao(5, 2.5);
    SetTime(1200, 2);
    Card({{PUFF_SHROOM, 1, 9}, {FLOWER_POT, 2, 9}});
    SetTime(1336, 2);
    Shovel({{1, 9}, {2, 9}});
    SetTime(1738 - 200 - 373, 2);
    pao_operator.pao({{2, 8.75}, {5, 8.425}});
    SetTime(1738 - 200 + 215 - 373, 2);
    pao_operator.pao(1, 8.675);
    SetTime(1738 - 200 + 215 + 215 - 373, 2);
    pao_operator.pao(1, 8.275);

    // wave3 BI-c-PDD/P-d
    SetTime(372 - 373, 3);
    pao_operator.pao(2, 8.1125);
    SetTime(372 - 298, 3);
    ice_filler.coffee();
    SetTime(807 - 373, 3);
    pao_operator.pao(5, 2.5);
    SetTime(1200, 3);
    Card({{PUFF_SHROOM, 1, 9}, {FLOWER_POT, 2, 9}});
    SetTime(1336, 3);
    Shovel({{1, 9}, {2, 9}});
    SetTime(1738 - 200 - 373, 3);
    pao_operator.pao({{2, 8.75}, {5, 8.425}});
    SetTime(1738 - 200 + 215 - 373, 3);
    pao_operator.pao(1, 8.675);
    SetTime(1738 - 200 + 215 + 215 - 373, 3);
    pao_operator.pao(1, 8.275);

    // wave4 BI-c-PDD/P-d
    SetTime(372 - 373, 4);
    pao_operator.pao(2, 8.1125);
    SetTime(372 - 298, 4);
    ice_filler.coffee();
    SetTime(807 - 373, 4);
    pao_operator.pao(5, 2.5);
    SetTime(1200, 4);
    Card({{PUFF_SHROOM, 1, 9}, {FLOWER_POT, 2, 9}});
    SetTime(1336, 4);
    Shovel({{1, 9}, {2, 9}});
    SetTime(1738 - 200 - 373, 4);
    pao_operator.pao({{2, 8.75}, {5, 8.425}});
    SetTime(1738 - 200 + 215 - 373, 4);
    pao_operator.pao(1, 8.675);
    SetTime(1738 - 200 + 215 + 215 - 373, 4);
    pao_operator.pao(1, 8.275);

    // wave5 BI-c-PDD/P-d
    SetTime(372 - 373, 5);
    pao_operator.pao(2, 8.1125);
    SetTime(372 - 298, 5);
    ice_filler.coffee();
    SetTime(807 - 373, 5);
    pao_operator.pao(5, 2.5);
    SetTime(1200, 5);
    Card({{PUFF_SHROOM, 1, 9}, {FLOWER_POT, 2, 9}});
    SetTime(1336, 5);
    Shovel({{1, 9}, {2, 9}});
    SetTime(1738 - 200 - 373, 5);
    pao_operator.pao({{2, 8.75}, {5, 8.425}});
    SetTime(1738 - 200 + 215 - 373, 5);
    pao_operator.pao(1, 8.675);
    SetTime(1738 - 200 + 215 + 215 - 373, 5);
    pao_operator.pao(1, 8.275);

    // wave6 BI-c-PDD/P-d
    SetTime(372 - 373, 6);
    pao_operator.pao(2, 8.1125);
    SetTime(372 - 298, 6);
    ice_filler.coffee();
    SetTime(807 - 373, 6);
    pao_operator.pao(5, 2.5);
    SetTime(1200, 6);
    Card({{PUFF_SHROOM, 1, 9}, {FLOWER_POT, 2, 9}});
    SetTime(1336, 6);
    Shovel({{1, 9}, {2, 9}});
    SetTime(1738 - 200 - 373, 6);
    pao_operator.pao({{2, 8.75}, {5, 8.425}});
    SetTime(1738 - 200 + 215 - 373, 6);
    pao_operator.pao(1, 8.675);
    SetTime(1738 - 200 + 215 + 215 - 373, 6);
    pao_operator.pao(1, 8.275);

    // wave7 BI-c-PDD/P-d
    SetTime(372 - 373, 7);
    pao_operator.pao(2, 8.1125);
    SetTime(372 - 298, 7);
    ice_filler.coffee();
    SetTime(807 - 373, 7);
    pao_operator.pao(5, 2.5);
    SetTime(1200, 7);
    Card({{PUFF_SHROOM, 1, 9}, {FLOWER_POT, 2, 9}});
    SetTime(1336, 7);
    Shovel({{1, 9}, {2, 9}});
    SetTime(1738 - 200 - 373, 7);
    pao_operator.pao({{2, 8.75}, {5, 8.425}});
    SetTime(1738 - 200 + 215 - 373, 7);
    pao_operator.pao(1, 8.675);
    SetTime(1738 - 200 + 215 + 215 - 373, 7);
    pao_operator.pao(1, 8.275);

    // wave8 BI-c-PDD/P-d
    SetTime(372 - 373, 8);
    pao_operator.pao(2, 8.1125);
    SetTime(372 - 298, 8);
    ice_filler.coffee();
    SetTime(807 - 373, 8);
    pao_operator.pao(5, 2.5);
    SetTime(1200, 8);
    Card({{PUFF_SHROOM, 1, 9}, {FLOWER_POT, 2, 9}});
    SetTime(1336, 8);
    Shovel({{1, 9}, {2, 9}});
    SetTime(1738 - 200 - 373, 8);
    pao_operator.pao({{2, 8.75}, {5, 8.425}});
    SetTime(1738 - 200 + 215 - 373, 8);
    pao_operator.pao(1, 8.675);
    SetTime(1738 - 200 + 215 + 215 - 373, 8);
    pao_operator.pao(1, 8.275);

    // wave9 BI-c-PDD/P-d
    SetTime(372 - 373, 9);
    pao_operator.pao(2, 8.1125);
    SetTime(372 - 298, 9);
    ice_filler.coffee();
    SetTime(807 - 373, 9);
    pao_operator.pao(5, 2.5);
    SetTime(1200, 9);
    Card({{PUFF_SHROOM, 1, 9}, {FLOWER_POT, 2, 9}});
    SetTime(1336, 9);
    Shovel({{1, 9}, {2, 9}});

    SetTime(1738 - 200 - 373, 9);
    pao_operator.pao({{2, 8.75}, {5, 8.425}});
    SetTime(1738 - 200 + 215 - 373, 9);
    pao_operator.pao(1, 8.675);
    SetTime(1738 - 200 + 215 + 215 - 373, 9);
    pao_operator.pao(1, 8.275);
    SetTime(552, 9);
    Card(LILY_PAD, 3, 9);
    SetTime(1738 - 200 + 215 - 298, 9);
    Card({{DOOM_SHROOM, 3, 9}, {COFFEE_BEAN, 3, 9}});
    SetTime(2200 - 373, 9);
    pao_operator.pao(5, 4);
    SetTime(1738 + 1738 - 200 - 373, 9);
    pao_operator.pao(5, 7);

    // wave10 PAD/PD
    // 椒杀蹦极
    SetTime(395 - 100, 10);
    Card(LILY_PAD, 4, 9);
    Card(JALAPENO, {{4, 8}, {4, 7}, {4, 6}, {4, 5}, {4, 9}});
    SetTime(315 - 373, 10);
    pao_operator.pao(2, 8.75);
    SetTime(315 + 110 - 100, 10);
    Card(CHERRY_BOMB, 1, 9);
    SetTime(315 + 110 + 110 - 373, 10);
    pao_operator.pao(1, 8.675);
    SetTime(338 - 373, 10);
    pao_operator.pao(5, 8.75);
    SetTime(338 + 110 - 373, 10);
    pao_operator.pao(5, 8.175);

    // wave11 cBI-c-PDD/P-d
    SetTime(147, 11);
    Card({{PUFF_SHROOM, 1, 9}, {FLOWER_POT, 2, 9}});
    SetTime(147 + 80, 11);
    Shovel({{1, 9}, {2, 9}});
    SetTime(372 - 373, 11);
    pao_operator.pao(2, 8.1125);
    SetTime(372 - 298, 11);
    ice_filler.coffee();
    SetTime(807 - 373, 11);
    pao_operator.pao(5, 2.5);
    SetTime(1200, 11);
    Card({{PUFF_SHROOM, 1, 9}, {FLOWER_POT, 2, 9}});
    SetTime(1336, 11);
    Shovel({{1, 9}, {2, 9}});
    SetTime(1738 - 200 - 373, 11);
    pao_operator.pao({{2, 8.75}, {5, 8.425}});
    SetTime(1738 - 200 + 215 - 373, 11);
    pao_operator.pao(1, 8.675);
    SetTime(1738 - 200 + 215 + 215 - 373, 11);
    pao_operator.pao(1, 8.275);

    // wave12 BI-c-PDD/P-d
    SetTime(372 - 373, 12);
    pao_operator.pao(2, 8.1125);
    SetTime(372 - 298, 12);
    ice_filler.coffee();
    SetTime(807 - 373, 12);
    pao_operator.pao(5, 2.5);
    SetTime(1200, 12);
    Card({{PUFF_SHROOM, 1, 9}, {FLOWER_POT, 2, 9}});
    SetTime(1336, 12);
    Shovel({{1, 9}, {2, 9}});
    SetTime(1738 - 200 - 373, 12);
    pao_operator.pao({{2, 8.75}, {5, 8.425}});
    SetTime(1738 - 200 + 215 - 373, 12);
    pao_operator.pao(1, 8.675);
    SetTime(1738 - 200 + 215 + 215 - 373, 12);
    pao_operator.pao(1, 8.275);

    // wave13 BI-c-PDD/P-d
    SetTime(372 - 373, 13);
    pao_operator.pao(2, 8.1125);
    SetTime(372 - 298, 13);
    ice_filler.coffee();
    SetTime(807 - 373, 13);
    pao_operator.pao(5, 2.5);
    SetTime(1200, 13);
    Card({{PUFF_SHROOM, 1, 9}, {FLOWER_POT, 2, 9}});
    SetTime(1336, 13);
    Shovel({{1, 9}, {2, 9}});
    SetTime(1738 - 200 - 373, 13);
    pao_operator.pao({{2, 8.75}, {5, 8.425}});
    SetTime(1738 - 200 + 215 - 373, 13);
    pao_operator.pao(1, 8.675);
    SetTime(1738 - 200 + 215 + 215 - 373, 13);
    pao_operator.pao(1, 8.275);

    // wave14 BI-c-PDD/P-d
    SetTime(372 - 373, 14);
    pao_operator.pao(2, 8.1125);
    SetTime(372 - 298, 14);
    ice_filler.coffee();
    SetTime(807 - 373, 14);
    pao_operator.pao(5, 2.5);
    SetTime(1200, 14);
    Card({{PUFF_SHROOM, 1, 9}, {FLOWER_POT, 2, 9}});
    SetTime(1336, 14);
    Shovel({{1, 9}, {2, 9}});
    SetTime(1738 - 200 - 373, 14);
    pao_operator.pao({{2, 8.75}, {5, 8.425}});
    SetTime(1738 - 200 + 215 - 373, 14);
    pao_operator.pao(1, 8.675);
    SetTime(1738 - 200 + 215 + 215 - 373, 14);
    pao_operator.pao(1, 8.275);

    // wave15 BI-c-PDD/P-d
    SetTime(372 - 373, 15);
    pao_operator.pao(2, 8.1125);
    SetTime(372 - 298, 15);
    ice_filler.coffee();
    SetTime(807 - 373, 15);
    pao_operator.pao(5, 2.5);
    SetTime(1200, 15);
    Card({{PUFF_SHROOM, 1, 9}, {FLOWER_POT, 2, 9}});
    SetTime(1336, 15);
    Shovel({{1, 9}, {2, 9}});
    SetTime(1738 - 200 - 373, 15);
    pao_operator.pao({{2, 8.75}, {5, 8.425}});
    SetTime(1738 - 200 + 215 - 373, 15);
    pao_operator.pao(1, 8.675);
    SetTime(1738 - 200 + 215 + 215 - 373, 15);
    pao_operator.pao(1, 8.275);

    // wave16 BI-c-PDD/P-d
    SetTime(372 - 373, 16);
    pao_operator.pao(2, 8.1125);
    SetTime(372 - 298, 16);
    ice_filler.coffee();
    SetTime(807 - 373, 16);
    pao_operator.pao(5, 2.5);
    SetTime(1200, 16);
    Card({{PUFF_SHROOM, 1, 9}, {FLOWER_POT, 2, 9}});
    SetTime(1336, 16);
    Shovel({{1, 9}, {2, 9}});
    SetTime(1738 - 200 - 373, 16);
    pao_operator.pao({{2, 8.75}, {5, 8.425}});
    SetTime(1738 - 200 + 215 - 373, 16);
    pao_operator.pao(1, 8.675);
    SetTime(1738 - 200 + 215 + 215 - 373, 16);
    pao_operator.pao(1, 8.275);

    // wave17 BI-c-PDD/P-d
    SetTime(372 - 373, 17);
    pao_operator.pao(2, 8.1125);
    SetTime(372 - 298, 17);
    ice_filler.coffee();
    SetTime(807 - 373, 17);
    pao_operator.pao(5, 2.5);
    SetTime(1200, 17);
    Card({{PUFF_SHROOM, 1, 9}, {FLOWER_POT, 2, 9}});
    SetTime(1336, 17);
    Shovel({{1, 9}, {2, 9}});
    SetTime(1738 - 200 - 373, 17);
    pao_operator.pao({{2, 8.75}, {5, 8.425}});
    SetTime(1738 - 200 + 215 - 373, 17);
    pao_operator.pao(1, 8.675);
    SetTime(1738 - 200 + 215 + 215 - 373, 17);
    pao_operator.pao(1, 8.275);

    // wave18 BI-c-PDD/P-d
    SetTime(372 - 373, 18);
    pao_operator.pao(2, 8.1125);
    SetTime(372 - 298, 18);
    ice_filler.coffee();
    SetTime(807 - 373, 18);
    pao_operator.pao(5, 2.5);
    SetTime(1200, 18);
    Card({{PUFF_SHROOM, 1, 9}, {FLOWER_POT, 2, 9}});
    SetTime(1336, 18);
    Shovel({{1, 9}, {2, 9}});
    SetTime(1738 - 200 - 373, 18);
    pao_operator.pao({{2, 8.75}, {5, 8.425}});
    SetTime(1738 - 200 + 215 - 373, 18);
    pao_operator.pao(1, 8.675);
    SetTime(1738 - 200 + 215 + 215 - 373, 18);
    pao_operator.pao(1, 8.275);

    // wave19 BI-c-PDD/P-d
    SetTime(372 - 373, 19);
    pao_operator.pao(2, 8.1125);
    SetTime(372 - 298, 19);
    ice_filler.coffee();
    SetTime(807 - 373, 19);
    pao_operator.pao(5, 2.5);
    SetTime(1200, 19);
    Card({{PUFF_SHROOM, 1, 9}, {FLOWER_POT, 2, 9}});
    SetTime(1336, 19);
    Shovel({{1, 9}, {2, 9}});
    SetTime(1738 - 200 - 373, 19);
    pao_operator.pao({{2, 8.75}, {5, 8.425}});
    SetTime(1738 - 200 + 215 - 373, 19);
    pao_operator.pao(1, 8.675);
    SetTime(1738 - 200 + 215 + 215 - 373, 19);
    pao_operator.pao(1, 8.275);
    SetTime(552, 19);
    Card(LILY_PAD, 3, 9);
    SetTime(1738 - 200 + 215 - 298, 19);
    Card({{DOOM_SHROOM, 3, 9}, {COFFEE_BEAN, 3, 9}});
    SetTime(2200 - 373, 19);
    pao_operator.pao(5, 3.5);
    SetTime(1738 + 1738 - 200 - 373, 19);
    pao_operator.pao(5, 7);
    InsertTimeOperation(4500 - 200 - 373, 19, [=]() {
        auto zombies = GetMainObject()->zombieArray();
        for (int index = 0; index < GetMainObject()->zombieTotal(); ++index) {
            if (!zombies[index].isDead() && !zombies[index].isDisappeared() && zombies[index].row() + 1 == 6 && zombies[index].type() == BACKUP_DANCER) {
                SetTime(4500 - 200 - 373, 19);
                pao_operator.pao(5, zombies[index].abscissa() / 80.0);
                break;
            }
        }
        for (int index = 0; index < GetMainObject()->zombieTotal(); ++index) {
            if (!zombies[index].isDead() && !zombies[index].isDisappeared() && zombies[index].row() + 1 == 6 && zombies[index].type() == GIGA_GARGANTUAR) {
                SetTime(4500 - 200 - 373, 19);
                pao_operator.pao(5, zombies[index].abscissa() / 80.0);
                break;
            }
        }
    });

    // wave20 PPSSDD
    // 炮消珊瑚
    SetTime(225 - 373, 20);
    pao_operator.pao(4, 7.5875);
    // 椒杀蹦极
    SetTime(395 - 100, 20);
    Card(JALAPENO, {{4, 9}, {4, 8}, {4, 7}, {4, 6}});
    SetTime(338 - 373, 20);
    pao_operator.pao({{2, 8.75}, {5, 8.75}, {2, 8.75}, {5, 8.75}});
    SetTime(338 + 110 - 373, 20);
    pao_operator.pao({{1, 8.675}, {5, 8.75}});
    SetTime(1100 - 373, 20);
    pao_operator.pao({{2, 8.75}, {4, 8.75}});
    SetTime(1100, 20);
    Card({{PUFF_SHROOM, 6, 1}, {FLOWER_POT, 6, 2}});
    ice_filler.resetFillList({{4, 5}, {4, 6}, {4, 7}, {4, 8}, {5, 5}});
    InsertTimeOperation(5500 - 373, 20, [=]() {
        auto zombies = GetMainObject()->zombieArray();
        for (int index = 0; index < GetMainObject()->zombieTotal(); ++index) {
            if (!zombies[index].isDead() && !zombies[index].isDisappeared() && zombies[index].row() + 1 == 6) {
                SetTime(5500 - 373, 20);
                pao_operator.pao(6, zombies[index].abscissa() / 80.0);
                break;
            }
        }
    });
}
