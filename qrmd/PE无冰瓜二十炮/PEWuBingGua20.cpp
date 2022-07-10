/*
 * @Author: qrmd
 * @Date: 2022-06-18 15:35:08
 * @LastEditors: qrmd
 * @LastEditTime: 2022-06-18 15:59:18
 * @Description:PE无冰瓜二十炮 全难度极限出怪运阵演示脚本
 * 使用方法：1、前往https://gitee.com/vector-wlc/AsmVsZombies,根据教程下载并安装好AsmVsZombies
 *          2、在Visul Studio Code中打开本脚本,右键点击编辑区空白处,在弹出菜单中选择“AvZ:Run Script”
 * 更多AvZ脚本尽在AvZScript公开脚本仓库：
 * 主库：https://github.com/qrmd0/AvZScript
 * 镜像库：https://gitee.com/qrmd/AvZScript
 * Copyright (c) 2022 by qrmd , All Rights Reserved.
 */

#include "avz.h"

using namespace AvZ;
void Script()
{
    // 脚本在游戏主界面和选择植物界面生效
    OpenMultipleEffective('Q', MAIN_UI_OR_FIGHT_UI);
    // 全难度极限出怪：普僵、撑杆、橄榄、舞王、冰车、小丑、矿工、跳跳、小偷、扶梯、投篮、白眼、红眼、海豚
    SetZombies({ZOMBIE, POLE_VAULTING_ZOMBIE, FOOTBALL_ZOMBIE, DANCING_ZOMBIE, ZOMBONI, JACK_IN_THE_BOX_ZOMBIE, DIGGER_ZOMBIE, POGO_ZOMBIE, BUNGEE_ZOMBIE, LADDER_ZOMBIE, CATAPULT_ZOMBIE, GARGANTUAR, GIGA_GARGANTUAR, DOLPHIN_RIDER_ZOMBIE});
    // 选择植物：咖啡豆、寒冰菇、模仿寒冰菇、南瓜头、樱桃炸弹、倭瓜、小喷菇、花盆、玉米投手、玉米加农炮
    SelectCards({COFFEE_BEAN, ICE_SHROOM, M_ICE_SHROOM, PUMPKIN, CHERRY_BOMB, SQUASH, PUFF_SHROOM, FLOWER_POT, KERNEL_PULT, COB_CANNON});
    SetTime(-599, 1);
    // 填充炮列表
    pao_operator.resetPaoList({{1, 1}, {6, 1}, {1, 5}, {6, 5}, {1, 7}, {6, 7}, {2, 1}, {5, 1}, {2, 5}, {5, 5}, {2, 7}, {5, 7}, {3, 1}, {4, 1}, {3, 3}, {4, 3}, {3, 5}, {4, 5}, {3, 7}, {4, 7}});
    // 开始自动存冰
    ice_filler.start({{4, 9}});
    // 开始自动修补南瓜头
    plant_fixer.start(PUMPKIN, {{3, 9}, {4, 9}}, 1200);
    // 主体节奏 P6-2I PPDD|PPDD|PPI|PPDD|PPDD|PPI 601|601|601|601|601|601 每波执行确定的操作,不考虑非旗帜波的刷新延迟

    // wave1 PPDD
    SetTime(295 - 376, 1);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    SetTime(401 - 376, 1);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});

    // wave2 PPDD
    SetTime(295 - 376, 2);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    SetTime(401 - 376, 2);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});

    // wave3 PPI
    SetTime(295 - 376, 3);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    SetTime(295 - 298, 3);
    ice_filler.coffee();

    // wave4 PPDD
    SetTime(295 - 376, 4);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    SetTime(401 - 376, 4);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});

    // wave5 PPDD
    SetTime(295 - 376, 5);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    SetTime(401 - 376, 5);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});

    // wave6 PPI
    SetTime(295 - 376, 6);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    SetTime(295 - 298, 6);
    ice_filler.coffee();

    // wave7 PPDD
    SetTime(295 - 376, 7);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    SetTime(401 - 376, 7);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});

    // wave8 PPDD
    SetTime(295 - 376, 8);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    SetTime(401 - 376, 8);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});

    // wave9 PPI(-PP-PP-PP)
    SetTime(295 - 376, 9);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    SetTime(295 - 298, 9);
    ice_filler.coffee();
    pao_operator.recoverPao({{2, 8.8}, {5, 8.8}, {2, 8.8}, {5, 8.8}, {2, 8.8}, {5, 8.8}});

    // wave10 PPDD
    SetTime(295 - 376, 10);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    SetTime(410 - 373, 10);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});

    // wave11 PPDD
    SetTime(295 - 376, 11);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    SetTime(401 - 376, 11);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});

    // wave12 PPI
    SetTime(295 - 376, 12);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    SetTime(295 - 298, 12);
    ice_filler.coffee();

    // wave13 PPDD
    SetTime(295 - 376, 13);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    SetTime(401 - 376, 13);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});

    // wave14 PPDD
    SetTime(295 - 376, 14);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    SetTime(401 - 376, 14);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});

    // wave15 PPI
    SetTime(295 - 376, 15);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    SetTime(295 - 298, 15);
    ice_filler.coffee();

    // wave16 PPDD
    SetTime(295 - 376, 16);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    SetTime(401 - 376, 16);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});

    // wave17 PPDD
    SetTime(295 - 376, 17);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    SetTime(401 - 376, 17);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});

    // wave18 PPI
    SetTime(295 - 376, 18);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    SetTime(295 - 298, 18);
    ice_filler.coffee();

    // wave19 PPDD(-PP-PP)
    SetTime(295 - 376, 19);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    SetTime(401 - 376, 19);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    pao_operator.recoverPao({{2, 8.8}, {5, 8.8}, {2, 8.8}, {5, 8.8}});

    // wave20 PP-(PP-PP-PP)
    // 炮消珊瑚
    SetTime(223 - 373, 20);
    pao_operator.pao(4, 7.5875);
    SetTime(295 - 376, 20);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    SetTime(410 - 376, 20);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    SetTime(814 - 373, 20);
    pao_operator.recoverPao({{2, 8.8}, {5, 8.8}, {2, 8.8}, {5, 8.8}});
}
