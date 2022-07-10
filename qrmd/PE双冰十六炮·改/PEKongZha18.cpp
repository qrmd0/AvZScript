/*
 * @Author: qrmd
 * @Date: 2022-06-17 00:19:47
 * @LastEditors: qrmd
 * @LastEditTime: 2022-06-17 10:56:16
 * @Description:PE空炸十八炮 全难度极限出怪运阵演示脚本
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
    // 选择植物：樱桃炸弹、倭瓜、小喷菇、模仿小喷菇、花盆、胆小菇、向日葵、睡莲叶、玉米投手、玉米加农炮
    SelectCards({CHERRY_BOMB, SQUASH, PUFF_SHROOM, M_PUFF_SHROOM, FLOWER_POT, SCAREDY_SHROOM, SUNFLOWER, LILY_PAD, KERNEL_PULT, COB_CANNON});
    SetTime(-599, 1);
    // 填充炮列表
    pao_operator.resetPaoList({{1, 1}, {6, 1}, {1, 3}, {2, 3}, {1, 5}, {6, 5}, {2, 1}, {5, 1}, {2, 5}, {5, 5}, {3, 1}, {4, 1}, {3, 3}, {4, 3}, {3, 5}, {4, 5}, {3, 7}, {4, 7}});
    // 铲除临时植物
    Shovel({{5, 8}, {6, 8}});
    // 主体节奏 P6附加轨 PD/P|PD/P|PD/P|PD/P|PD/P 601|601|601|601|601|601 每波执行确定的操作，不考虑非旗帜波的刷新延迟
    // 开始自动垫巨人僵尸
    block_giga.pushFunc([]() {
        BlockGargantuar({{5, 8}, {6, 8}});
    });
    // wave1 PD/P
    SetTime(341 - 376, 1);
    pao_operator.pao(2, 8.8);
    SetTime(341 + 110 - 376, 1);
    pao_operator.pao(1, 7.7);
    SetTime(291 - 376, 1);
    pao_operator.pao(5, 8.8);

    // wave2 PD/P
    SetTime(341 - 376, 2);
    pao_operator.pao(2, 8.8);
    SetTime(341 + 110 - 376, 2);
    pao_operator.pao(1, 7.7);
    SetTime(291 - 376, 2);
    pao_operator.pao(5, 8.8);

    // wave3 PD/P
    SetTime(341 - 376, 3);
    pao_operator.pao(2, 8.8);
    SetTime(341 + 110 - 376, 3);
    pao_operator.pao(1, 7.7);
    SetTime(291 - 376, 3);
    pao_operator.pao(5, 8.8);

    // wave4 PD/P
    SetTime(341 - 376, 4);
    pao_operator.pao(2, 8.8);
    SetTime(341 + 110 - 376, 4);
    pao_operator.pao(1, 7.7);
    SetTime(291 - 376, 4);
    pao_operator.pao(5, 8.8);

    // wave5 PD/P
    SetTime(341 - 376, 5);
    pao_operator.pao(2, 8.8);
    SetTime(341 + 110 - 376, 5);
    pao_operator.pao(1, 7.7);
    SetTime(291 - 376, 5);
    pao_operator.pao(5, 8.8);

    // wave6 PD/P
    SetTime(341 - 376, 6);
    pao_operator.pao(2, 8.8);
    SetTime(341 + 110 - 376, 6);
    pao_operator.pao(1, 7.7);
    SetTime(291 - 376, 6);
    pao_operator.pao(5, 8.8);

    // wave7 PD/P
    SetTime(341 - 376, 7);
    pao_operator.pao(2, 8.8);
    SetTime(341 + 110 - 376, 7);
    pao_operator.pao(1, 7.7);
    SetTime(291 - 376, 7);
    pao_operator.pao(5, 8.8);

    // wave8 PD/P
    SetTime(341 - 376, 8);
    pao_operator.pao(2, 8.8);
    SetTime(341 + 110 - 376, 8);
    pao_operator.pao(1, 7.7);
    SetTime(291 - 376, 8);
    pao_operator.pao(5, 8.8);

    // wave9 PD/P(-PD/P-P-P)
    SetTime(341 - 376, 9);
    pao_operator.pao(2, 8.8);
    SetTime(341 + 110 - 376, 9);
    pao_operator.pao(1, 7.7);
    SetTime(291 - 376, 9);
    pao_operator.pao(5, 8.8);
    SetTime(341 + 601 - 376, 9);
    pao_operator.pao(2, 8.8);
    SetTime(341 + 601 + 110 - 376, 9);
    pao_operator.pao(1, 7.7);
    SetTime(291 + 601 - 376, 9);
    pao_operator.pao(5, 8.8);
    SetTime(341 + 601 + 110 - 376, 9);
    pao_operator.recoverPao({{2, 8.8}, {5, 8.8}, {5, 8.8}});

    // wave10 PD/P
    SetTime(300, 10);
    Shovel({{5, 8}, {6, 8}});
    // 243cs为舞王僵尸9列触碰小喷菇或阳光菇召唤伴舞僵尸的最晚时机
    SetTime(243, 10);
    Card(PUFF_SHROOM, 1, 9);
    Card(M_PUFF_SHROOM, 2, 9);
    Card(FLOWER_POT, 5, 9);
    Card(SCAREDY_SHROOM, 6, 9);
    SetTime(243 + 79, 10);
    Shovel({{1, 9}, {2, 9}, {5, 9}, {6, 9}});
    // 410cs为旗帜波气球僵尸全部入场的最晚时机
    SetTime(410 - 373, 10);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    SetTime(410 + 110 - 373, 10);
    pao_operator.pao(1, 7.7);

    // wave11 PD/P
    SetTime(341 - 376, 11);
    pao_operator.pao(2, 8.8);
    SetTime(341 + 110 - 376, 11);
    pao_operator.pao(1, 7.7);
    SetTime(291 - 376, 11);
    pao_operator.pao(5, 8.8);

    // wave12 PD/P
    SetTime(341 - 376, 12);
    pao_operator.pao(2, 8.8);
    SetTime(341 + 110 - 376, 12);
    pao_operator.pao(1, 7.7);
    SetTime(291 - 376, 12);
    pao_operator.pao(5, 8.8);

    // wave13 PD/P
    SetTime(341 - 376, 13);
    pao_operator.pao(2, 8.8);
    SetTime(341 + 110 - 376, 13);
    pao_operator.pao(1, 7.7);
    SetTime(291 - 376, 13);
    pao_operator.pao(5, 8.8);

    // wave14 PD/P
    SetTime(341 - 376, 14);
    pao_operator.pao(2, 8.8);
    SetTime(341 + 110 - 376, 14);
    pao_operator.pao(1, 7.7);
    SetTime(291 - 376, 14);
    pao_operator.pao(5, 8.8);

    // wave15 PD/P
    SetTime(341 - 376, 15);
    pao_operator.pao(2, 8.8);
    SetTime(341 + 110 - 376, 15);
    pao_operator.pao(1, 7.7);
    SetTime(291 - 376, 15);
    pao_operator.pao(5, 8.8);

    // wave16 PD/P
    SetTime(341 - 376, 16);
    pao_operator.pao(2, 8.8);
    SetTime(341 + 110 - 376, 16);
    pao_operator.pao(1, 7.7);
    SetTime(291 - 376, 16);
    pao_operator.pao(5, 8.8);

    // wave17 PD/P
    SetTime(341 - 376, 17);
    pao_operator.pao(2, 8.8);
    SetTime(341 + 110 - 376, 17);
    pao_operator.pao(1, 7.7);
    SetTime(291 - 376, 17);
    pao_operator.pao(5, 8.8);

    // wave18 PD/P
    SetTime(341 - 376, 18);
    pao_operator.pao(2, 8.8);
    SetTime(341 + 110 - 376, 18);
    pao_operator.pao(1, 7.7);
    SetTime(291 - 376, 18);
    pao_operator.pao(5, 8.8);

    // wave19 PD/P(-PD/P-P-P)
    SetTime(341 - 376, 19);
    pao_operator.pao(2, 8.8);
    SetTime(341 + 110 - 376, 19);
    pao_operator.pao(1, 7.7);
    SetTime(291 - 376, 19);
    pao_operator.pao(5, 8.8);
    SetTime(341 + 601 - 376, 19);
    pao_operator.pao(2, 8.8);
    SetTime(341 + 601 + 110 - 376, 19);
    pao_operator.pao(1, 7.7);
    SetTime(291 + 601 - 376, 19);
    pao_operator.pao(5, 8.8);
    SetTime(341 + 601 + 110 - 376, 19);
    pao_operator.recoverPao({{2, 8.8}, {5, 8.8}, {5, 8.8}});

    // wave20 PD/P(-PD/P-P-P)
    SetTime(300, 20);
    Shovel({{5, 8}, {6, 8}});
    // 炮消珊瑚
    SetTime(223 - 373, 20);
    pao_operator.pao(4, 7.5875);
    // 243cs为舞王僵尸9列触碰小喷菇或阳光菇召唤伴舞僵尸的最晚时机
    SetTime(243, 20);
    Card(PUFF_SHROOM, 1, 9);
    Card(M_PUFF_SHROOM, 2, 9);
    Card(FLOWER_POT, 5, 9);
    Card(SCAREDY_SHROOM, 6, 9);
    SetTime(243 + 79, 20);
    Shovel({{1, 9}, {2, 9}, {5, 9}, {6, 9}});
    // 410cs为旗帜波气球僵尸全部入场的最晚时机
    SetTime(410 - 373, 20);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    SetTime(410 + 110 - 373, 20);
    pao_operator.pao(1, 7.7);
    SetTime(341 + 601 - 376, 20);
    pao_operator.pao(2, 8.8);
    SetTime(341 + 601 + 110 - 376, 20);
    pao_operator.pao(1, 7.7);
    SetTime(291 + 601 - 376, 20);
    pao_operator.pao(5, 8.8);
    SetTime(341 + 601 + 110 - 376, 20);
    pao_operator.recoverPao({{2, 8.8}, {5, 8.8}, {5, 8.8}});
}
void BlockGargantuar(vector<Grid> pos)
{
    for (Grid each : pos) {
        auto zombies = GetMainObject()->zombieArray();
        auto seeds = GetMainObject()->seedArray();
        vector<int> indices_seed = {GetSeedIndex(PUFF_SHROOM), GetSeedIndex(PUFF_SHROOM, true), GetSeedIndex(FLOWER_POT), GetSeedIndex(SUN_SHROOM), GetSeedIndex(SCAREDY_SHROOM), GetSeedIndex(SUNFLOWER), GetSeedIndex(SQUASH)};
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