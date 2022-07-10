/*
 * @Author: qrmd
 * @Date: 2022-06-16 23:33:45
 * @LastEditors: qrmd
 * @LastEditTime: 2022-06-17 00:17:10
 * @Description:PE经典十八炮 全难度极限出怪运阵演示脚本
 * 使用方法：1、前往https://gitee.com/vector-wlc/AsmVsZombies，根据教程下载并安装好AsmVsZombies
 *          2、在Visul Studio Code中打开本脚本，右键点击编辑区空白处，在弹出菜单中选择“AvZ:Run Script”
 * 更多AvZ脚本尽在AvZScript公开脚本仓库：
 * 主库：https://github.com/qrmd0/AvZScript
 * 镜像库：https://gitee.com/qrmd/AvZScript
 * Copyright (c) 2022 by qrmd , All Rights Reserved.
 */

#include "avz.h"

using namespace AvZ;
// 如果[wave]波上半场刷出的僵尸总血量较高，返回2，否则返回5。用于6行场地的智能樱桃消延迟
int GetRowHaveHigherZombieHp(int wave);

void Script()
{
    // 脚本在游戏主界面和选择植物界面生效
    OpenMultipleEffective('Q', MAIN_UI_OR_FIGHT_UI);
    // 全难度极限出怪：普僵、撑杆、橄榄、舞王、冰车、小丑、矿工、跳跳、小偷、扶梯、投篮、白眼、红眼、海豚
    SetZombies({ZOMBIE, POLE_VAULTING_ZOMBIE, FOOTBALL_ZOMBIE, DANCING_ZOMBIE, ZOMBONI, JACK_IN_THE_BOX_ZOMBIE, DIGGER_ZOMBIE, POGO_ZOMBIE, BUNGEE_ZOMBIE, LADDER_ZOMBIE, CATAPULT_ZOMBIE, GARGANTUAR, GIGA_GARGANTUAR, DOLPHIN_RIDER_ZOMBIE});
    // 选择植物：咖啡豆、寒冰菇、樱桃炸弹、南瓜头、小喷菇、模仿小喷菇、花盆、胆小菇、玉米投手、玉米加农炮
    SelectCards({COFFEE_BEAN, ICE_SHROOM, CHERRY_BOMB, PUMPKIN, PUFF_SHROOM, M_PUFF_SHROOM, FLOWER_POT, SCAREDY_SHROOM, KERNEL_PULT, COB_CANNON});
    SetTime(-599, 1);
    // 填充炮列表
    pao_operator.resetPaoList({{1, 5}, {6, 5}, {1, 7}, {6, 7}, {2, 1}, {5, 1}, {2, 5}, {5, 5}, {2, 7}, {5, 7}, {3, 1}, {4, 1}, {3, 3}, {4, 3}, {3, 5}, {4, 5}, {3, 7}, {4, 7}});
    // 主体节奏 P6附加轨 BP/P|P/BP|BP/P|P/BP|BP/P|P/BP 601|601|601|601|601|601 每波执行确定的操作，不考虑非旗帜波的刷新延迟

    // wave1 BP/P
    // 610cs为撑杆僵尸对着8列炮起跳的最早时机
    // 180cs为撑杆僵尸从起跳到落地的时长
    SetTime(610 + 180 - 1 - 601 - 376, 1);
    pao_operator.pao(2, 8.8);
    SetTime(359 - 373, 1);
    pao_operator.pao(2, 8.8);
    SetTime(296 - 1 - 376, 1);
    pao_operator.pao(5, 8.8);

    // wave2 P/BP
    SetTime(296 - 1 - 376, 2);
    pao_operator.pao(2, 8.8);
    // 610cs为撑杆僵尸对着8列炮起跳的最早时机
    // 180cs为撑杆僵尸从起跳到落地的时长
    SetTime(610 + 180 - 1 - 601 - 376, 2);
    pao_operator.pao(5, 8.8);
    SetTime(359 - 373, 2);
    pao_operator.pao(5, 8.8);

    // wave3 BP/P
    // 610cs为撑杆僵尸对着8列炮起跳的最早时机
    // 180cs为撑杆僵尸从起跳到落地的时长
    SetTime(610 + 180 - 1 - 601 - 376, 3);
    pao_operator.pao(2, 8.8);
    SetTime(359 - 373, 3);
    pao_operator.pao(2, 8.8);
    SetTime(296 - 1 - 376, 3);
    pao_operator.pao(5, 8.8);

    // wave4 P/BP
    SetTime(296 - 1 - 376, 4);
    pao_operator.pao(2, 8.8);
    // 610cs为撑杆僵尸对着8列炮起跳的最早时机
    // 180cs为撑杆僵尸从起跳到落地的时长
    SetTime(610 + 180 - 1 - 601 - 376, 4);
    pao_operator.pao(5, 8.8);
    SetTime(359 - 373, 4);
    pao_operator.pao(5, 8.8);

    // wave5 BP/P
    // 610cs为撑杆僵尸对着8列炮起跳的最早时机
    // 180cs为撑杆僵尸从起跳到落地的时长
    SetTime(610 + 180 - 1 - 601 - 376, 5);
    pao_operator.pao(2, 8.8);
    SetTime(359 - 373, 5);
    pao_operator.pao(2, 8.8);
    SetTime(296 - 1 - 376, 5);
    pao_operator.pao(5, 8.8);

    // wave6 P/BP
    SetTime(296 - 1 - 376, 6);
    pao_operator.pao(2, 8.8);
    // 610cs为撑杆僵尸对着8列炮起跳的最早时机
    // 180cs为撑杆僵尸从起跳到落地的时长
    SetTime(610 + 180 - 1 - 601 - 376, 6);
    pao_operator.pao(5, 8.8);
    SetTime(359 - 373, 6);
    pao_operator.pao(5, 8.8);

    // wave7 BP/P
    // 610cs为撑杆僵尸对着8列炮起跳的最早时机
    // 180cs为撑杆僵尸从起跳到落地的时长
    SetTime(610 + 180 - 1 - 601 - 376, 7);
    pao_operator.pao(2, 8.8);
    SetTime(359 - 373, 7);
    pao_operator.pao(2, 8.8);
    SetTime(296 - 1 - 376, 7);
    pao_operator.pao(5, 8.8);

    // wave8 P/BP
    SetTime(296 - 1 - 376, 8);
    pao_operator.pao(2, 8.8);
    // 610cs为撑杆僵尸对着8列炮起跳的最早时机
    // 180cs为撑杆僵尸从起跳到落地的时长
    SetTime(610 + 180 - 1 - 601 - 376, 8);
    pao_operator.pao(5, 8.8);
    SetTime(359 - 373, 8);
    pao_operator.pao(5, 8.8);

    // wave9 BP/P(-PP-PP-PP)
    // 610cs为撑杆僵尸对着8列炮起跳的最早时机
    // 180cs为撑杆僵尸从起跳到落地的时长
    SetTime(610 + 180 - 1 - 601 - 376, 9);
    pao_operator.pao(2, 8.8);
    SetTime(359 - 373, 9);
    pao_operator.pao(2, 8.8);
    SetTime(296 - 1 - 376, 9);
    pao_operator.pao(5, 8.8);
    SetTime(359 - 373, 9);
    pao_operator.recoverPao({{2, 8.8}, {5, 8.8}, {2, 8.8}, {5, 8.8}, {2, 8.8}, {5, 8.8}});

    // wave10 ccccPP
    // 冰杀蹦极
    SetTime(601 - 1 - 300, 10);
    Card(ICE_SHROOM, 1, 1);
    Card(COFFEE_BEAN, 1, 1);
    // 243cs为舞王僵尸9列触碰小喷菇或阳光菇召唤伴舞僵尸的最晚时机
    SetTime(243, 10);
    Card(PUFF_SHROOM, 1, 9);
    Card(M_PUFF_SHROOM, 2, 9);
    Card(FLOWER_POT, 5, 9);
    Card(SCAREDY_SHROOM, 6, 9);
    SetTime(243 + 79, 10);
    Shovel({{1, 9}, {2, 9}, {5, 9}, {6, 9}});
    SetTime(410 - 373, 10);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    // 智能樱桃消中场延迟
    InsertTimeOperation(410, 10, [=]() {
        if (GetRunningWave() == 10) {
            SetTime(410, 10);
            Card(CHERRY_BOMB, GetRowHaveHigherZombieHp(10), 9);
        }
    });

    // wave11 BP/P
    // 610cs为撑杆僵尸对着8列炮起跳的最早时机
    // 180cs为撑杆僵尸从起跳到落地的时长
    SetTime(610 + 180 - 1 - 601 - 376, 11);
    pao_operator.pao(2, 8.8);
    SetTime(359 - 373, 11);
    pao_operator.pao(2, 8.8);
    SetTime(296 - 1 - 376, 11);
    pao_operator.pao(5, 8.8);

    // wave12 P/BP
    SetTime(296 - 1 - 376, 12);
    pao_operator.pao(2, 8.8);
    // 610cs为撑杆僵尸对着8列炮起跳的最早时机
    // 180cs为撑杆僵尸从起跳到落地的时长
    SetTime(610 + 180 - 1 - 601 - 376, 12);
    pao_operator.pao(5, 8.8);
    SetTime(359 - 373, 12);
    pao_operator.pao(5, 8.8);

    // wave13 BP/P
    // 610cs为撑杆僵尸对着8列炮起跳的最早时机
    // 180cs为撑杆僵尸从起跳到落地的时长
    SetTime(610 + 180 - 1 - 601 - 376, 13);
    pao_operator.pao(2, 8.8);
    SetTime(359 - 373, 13);
    pao_operator.pao(2, 8.8);
    SetTime(296 - 1 - 376, 13);
    pao_operator.pao(5, 8.8);

    // wave14 P/BP
    SetTime(296 - 1 - 376, 14);
    pao_operator.pao(2, 8.8);
    // 610cs为撑杆僵尸对着8列炮起跳的最早时机
    // 180cs为撑杆僵尸从起跳到落地的时长
    SetTime(610 + 180 - 1 - 601 - 376, 14);
    pao_operator.pao(5, 8.8);
    SetTime(359 - 373, 14);
    pao_operator.pao(5, 8.8);

    // wave15 BP/P
    // 610cs为撑杆僵尸对着8列炮起跳的最早时机
    // 180cs为撑杆僵尸从起跳到落地的时长
    SetTime(610 + 180 - 1 - 601 - 376, 15);
    pao_operator.pao(2, 8.8);
    SetTime(359 - 373, 15);
    pao_operator.pao(2, 8.8);
    SetTime(296 - 1 - 376, 15);
    pao_operator.pao(5, 8.8);

    // wave16 P/BP
    SetTime(296 - 1 - 376, 16);
    pao_operator.pao(2, 8.8);
    // 610cs为撑杆僵尸对着8列炮起跳的最早时机
    // 180cs为撑杆僵尸从起跳到落地的时长
    SetTime(610 + 180 - 1 - 601 - 376, 16);
    pao_operator.pao(5, 8.8);
    SetTime(359 - 373, 16);
    pao_operator.pao(5, 8.8);

    // wave17 BP/P
    // 610cs为撑杆僵尸对着8列炮起跳的最早时机
    // 180cs为撑杆僵尸从起跳到落地的时长
    SetTime(610 + 180 - 1 - 601 - 376, 17);
    pao_operator.pao(2, 8.8);
    SetTime(359 - 373, 17);
    pao_operator.pao(2, 8.8);
    SetTime(296 - 1 - 376, 17);
    pao_operator.pao(5, 8.8);

    // wave18 P/BP
    SetTime(296 - 1 - 376, 18);
    pao_operator.pao(2, 8.8);
    // 610cs为撑杆僵尸对着8列炮起跳的最早时机
    // 180cs为撑杆僵尸从起跳到落地的时长
    SetTime(610 + 180 - 1 - 601 - 376, 18);
    pao_operator.pao(5, 8.8);
    SetTime(359 - 373, 18);
    pao_operator.pao(5, 8.8);

    // wave19 BP/P(-PP-PP-PP)
    // 610cs为撑杆僵尸对着8列炮起跳的最早时机
    // 180cs为撑杆僵尸从起跳到落地的时长
    SetTime(610 + 180 - 1 - 601 - 376, 19);
    pao_operator.pao(2, 8.8);
    SetTime(359 - 373, 19);
    pao_operator.pao(2, 8.8);
    SetTime(296 - 1 - 376, 19);
    pao_operator.pao(5, 8.8);
    SetTime(359 - 373, 19);
    pao_operator.recoverPao({{2, 8.8}, {5, 8.8}, {2, 8.8}, {5, 8.8}, {2, 8.8}, {5, 8.8}});

    // wave20 ccccPP-(PP-PP-PP)
    // 炮消珊瑚
    SetTime(223 - 373, 20);
    pao_operator.pao(4, 7.5875);
    // 冰杀蹦极
    SetTime(601 - 1 - 300, 20);
    Card(ICE_SHROOM, 1, 1);
    Card(COFFEE_BEAN, 1, 1);
    // 243cs为舞王僵尸9列触碰小喷菇或阳光菇召唤伴舞僵尸的最晚时机
    SetTime(243, 20);
    Card(PUFF_SHROOM, 1, 9);
    Card(M_PUFF_SHROOM, 2, 9);
    Card(FLOWER_POT, 5, 9);
    Card(SCAREDY_SHROOM, 6, 9);
    SetTime(243 + 79, 20);
    Shovel({{1, 9}, {2, 9}, {5, 9}, {6, 9}});
    SetTime(410 - 373, 20);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    pao_operator.recoverPao({{2, 8.8}, {5, 8.8}, {2, 8.8}, {5, 8.8}, {2, 8.8}, {5, 8.8}});
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