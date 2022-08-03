/*
 * @Author: qrmd
 * @Date: 2022-08-01 19:19:03
 * @LastEditors: qrmd
 * @LastEditTime: 2022-08-01 22:26:33
 * @Description:PE经典十炮·改 全难度极限出怪运阵演示脚本
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

void Script()
{
    // 脚本在游戏主界面和选择植物界面生效
    OpenMultipleEffective('Q', MAIN_UI_OR_FIGHT_UI);
    // 全难度极限出怪：普僵、撑杆、橄榄、舞王、冰车、小丑、矿工、跳跳、小偷、扶梯、投篮、白眼、红眼、海豚
    SetZombies({ZOMBIE, POLE_VAULTING_ZOMBIE, FOOTBALL_ZOMBIE, DANCING_ZOMBIE, ZOMBONI, JACK_IN_THE_BOX_ZOMBIE, DIGGER_ZOMBIE, POGO_ZOMBIE, BUNGEE_ZOMBIE, LADDER_ZOMBIE, CATAPULT_ZOMBIE, GARGANTUAR, GIGA_GARGANTUAR, DOLPHIN_RIDER_ZOMBIE});
    // 选择植物：小喷菇、模仿小喷菇、三叶草、花盆、胆小菇、樱桃炸弹、睡莲叶、咖啡豆、寒冰菇、毁灭菇
    SelectCards({PUFF_SHROOM, M_PUFF_SHROOM, BLOVER, FLOWER_POT, SCAREDY_SHROOM, CHERRY_BOMB, LILY_PAD, COFFEE_BEAN, ICE_SHROOM, DOOM_SHROOM});
    SetTime(-599, 1);
    // 填充炮列表
    pao_operator.resetPaoList({{1, 5}, {6, 5}, {2, 5}, {5, 5}, {3, 1}, {4, 1}, {3, 4}, {4, 4}, {3, 6}, {4, 6}});
    // 主体节奏 P5u PP|PP|PP|ccccPP|ccccPP 601|601|601|836|836 每波执行确定的操作，不考虑非旗帜波的刷新延迟

    // wave1 PP
    SetTime(341 - 376, 1);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});

    // wave2 PP
    SetTime(341 - 376, 2);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});

    // wave3 PP
    SetTime(341 - 376, 3);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});

    // wave4 ccccPP
    SetTime(191, 4);
    Card({{PUFF_SHROOM, 1, 9}, {M_PUFF_SHROOM, 2, 9}, {BLOVER, 5, 9}, {SCAREDY_SHROOM, 6, 9}});
    SetTime(601, 4);
    Shovel({{1, 9}, {2, 9}, {5, 9}, {6, 9}});
    SetTime(836 - 200 - 373, 4);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});

    // wave5 ccccPP
    SetTime(191, 5);
    Card({{PUFF_SHROOM, 1, 9}, {M_PUFF_SHROOM, 2, 9}, {BLOVER, 5, 9}, {SCAREDY_SHROOM, 6, 9}});
    SetTime(601, 5);
    Shovel({{1, 9}, {2, 9}, {5, 9}, {6, 9}});
    SetTime(836 - 200 - 373, 5);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});

    // wave6 PP
    SetTime(341 - 376, 6);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});

    // wave7 PP
    SetTime(341 - 376, 7);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});

    // wave8 PP
    SetTime(341 - 376, 8);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});

    // wave9 ccccPP-(-PP-PP)
    SetTime(191, 9);
    Card({{PUFF_SHROOM, 1, 9}, {M_PUFF_SHROOM, 2, 9}, {BLOVER, 5, 9}, {SCAREDY_SHROOM, 6, 9}});
    SetTime(601, 9);
    Shovel({{1, 9}, {2, 9}, {5, 9}, {6, 9}});
    SetTime(836 - 200 - 373, 9);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    SetTime(836 + 836 - 200 - 373, 9);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    pao_operator.recoverPao({{2, 8.8}, {5, 8.8}});

    // wave10 PP
    SetTime(341 - 376, 10);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});

    // wave11 PP
    SetTime(341 - 376, 11);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});

    // wave12 PP
    SetTime(341 - 376, 12);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});

    // wave13 ccccPP
    SetTime(191, 13);
    Card({{PUFF_SHROOM, 1, 9}, {M_PUFF_SHROOM, 2, 9}, {BLOVER, 5, 9}, {SCAREDY_SHROOM, 6, 9}});
    SetTime(601, 13);
    Shovel({{1, 9}, {2, 9}, {5, 9}, {6, 9}});
    SetTime(836 - 200 - 373, 13);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});

    // wave14 ccccPP
    SetTime(191, 14);
    Card({{PUFF_SHROOM, 1, 9}, {M_PUFF_SHROOM, 2, 9}, {BLOVER, 5, 9}, {SCAREDY_SHROOM, 6, 9}});
    SetTime(601, 14);
    Shovel({{1, 9}, {2, 9}, {5, 9}, {6, 9}});
    SetTime(836 - 200 - 373, 14);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});

    // wave15 PP
    SetTime(341 - 376, 15);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});

    // wave16 PP
    SetTime(341 - 376, 16);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});

    // wave17 PP
    SetTime(341 - 376, 17);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});

    // wave18 ccccPP
    SetTime(191, 18);
    Card({{PUFF_SHROOM, 1, 9}, {M_PUFF_SHROOM, 2, 9}, {BLOVER, 5, 9}, {SCAREDY_SHROOM, 6, 9}});
    SetTime(601, 18);
    Shovel({{1, 9}, {2, 9}, {5, 9}, {6, 9}});
    SetTime(836 - 200 - 373, 18);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});

    // wave19 ccccPP-(PP-PP)
    SetTime(191, 19);
    Card({{PUFF_SHROOM, 1, 9}, {M_PUFF_SHROOM, 2, 9}, {BLOVER, 5, 9}, {SCAREDY_SHROOM, 6, 9}});
    SetTime(601, 19);
    Shovel({{1, 9}, {2, 9}, {5, 9}, {6, 9}});
    SetTime(836 - 200 - 373, 19);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    SetTime(836 + 601 - 376, 19);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    pao_operator.recoverPao({{2, 8.8}, {5, 8.8}});

    // wave20 PA-(PP-PP)
    // 炮消珊瑚
    SetTime(223 - 373, 20);
    pao_operator.pao(4, 7.5875);
    SetTime(341 - 376, 20);
    pao_operator.pao(2, 8.8);
    SetTime(341 - 100, 20);
    Card(CHERRY_BOMB, 5, 9);
    SetTime(341 + 601 - 376, 20);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    pao_operator.recoverPao({{2, 8.8}, {5, 8.8}});
}
