/*
 * @Author: qrmd
 * @Date: 2022-06-02 09:10:23
 * @LastEditors: qrmd
 * @LastEditTime: 2022-06-19 16:31:22
 * @Description:NE舞夜惊魂 全难度极限出怪运阵演示脚本
 * 使用方法：1、前往https://gitee.com/std::vector-wlc/AsmVsZombies，根据教程下载并安装好AsmVsZombies
 *          2、在Visul Studio Code中打开本脚本，右键点击编辑区空白处，在弹出菜单中选择“AvZ:Run Script”
 * 更多AvZ脚本尽在AvZScript公开脚本仓库：
 * 主库：https://github.com/qrmd0/AvZScript
 * 镜像库：https://gitee.com/qrmd/AvZScript
 * Copyright (c) 2022 by qrmd , All Rights Reserved.
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
    // 全难度极限出怪：普僵、撑杆、橄榄、舞王、小丑、矿工、跳跳、小偷、扶梯、投篮、白眼、红眼
    SetZombies({ZOMBIE, POLE_VAULTING_ZOMBIE, FOOTBALL_ZOMBIE, DANCING_ZOMBIE, JACK_IN_THE_BOX_ZOMBIE, DIGGER_ZOMBIE, POGO_ZOMBIE, BUNGEE_ZOMBIE, LADDER_ZOMBIE, CATAPULT_ZOMBIE, GARGANTUAR, GIGA_GARGANTUAR});
    // 选择植物：小喷菇、模仿小喷菇、寒冰菇、墓碑吞噬者、樱桃炸弹、倭瓜、毁灭菇、阳光菇、玉米投手、玉米加农炮
    SelectCards({PUFF_SHROOM, M_PUFF_SHROOM, ICE_SHROOM, GRAVE_BUSTER, CHERRY_BOMB, SQUASH, DOOM_SHROOM, SUN_SHROOM, KERNEL_PULT, COB_CANNON});
    // 开启女仆秘籍
    MaidCheats::dancing();
    SetTime(-599, 1);
    // 填充炮列表
    pao_operator.resetPaoList({{1, 1}, {1, 6}, {2, 1}, {2, 6}, {3, 1}, {3, 5}, {4, 1}, {4, 5}, {5, 1}, {5, 6}, {3, 7}, {4, 7}});

    // 主体节奏 P6 PPc|PPc|PPc|PPc|PPc|PPc 601|601|601|601|601|601 每波执行确定的操作，不考虑非旗帜波的刷新延迟

    // wave1 PPc
    SetTime(195, 1);
    Card(PUFF_SHROOM, 4, 9);
    SetTime(195 + 300, 1);
    Shovel(4, 9);
    SetTime(295 - 376, 1);
    pao_operator.pao(2, 9);
    SetTime(359 - 373, 1);
    pao_operator.pao(4, 9);

    // wave2 PPc
    SetTime(195, 2);
    Card(M_PUFF_SHROOM, 4, 9);
    SetTime(195 + 300, 2);
    Shovel(4, 9);
    SetTime(295 - 376, 2);
    pao_operator.pao(2, 9);
    SetTime(359 - 373, 2);
    pao_operator.pao(4, 9);

    // wave3 PPc
    SetTime(195, 3);
    Card(PUFF_SHROOM, 4, 9);
    SetTime(195 + 300, 3);
    Shovel(4, 9);
    SetTime(295 - 376, 3);
    pao_operator.pao(2, 9);
    SetTime(359 - 373, 3);
    pao_operator.pao(4, 9);

    // wave4 PPc
    SetTime(195, 4);
    Card(M_PUFF_SHROOM, 4, 9);
    SetTime(195 + 300, 4);
    Shovel(4, 9);
    SetTime(295 - 376, 4);
    pao_operator.pao(2, 9);
    SetTime(359 - 373, 4);
    pao_operator.pao(4, 9);

    // wave5 PPc
    SetTime(195, 5);
    Card(PUFF_SHROOM, 4, 9);
    SetTime(195 + 300, 5);
    Shovel(4, 9);
    SetTime(295 - 376, 5);
    pao_operator.pao(2, 9);
    SetTime(359 - 373, 5);
    pao_operator.pao(4, 9);

    // wave6 PPc
    SetTime(195, 6);
    Card(M_PUFF_SHROOM, 4, 9);
    SetTime(195 + 300, 6);
    Shovel(4, 9);
    SetTime(295 - 376, 6);
    pao_operator.pao(2, 9);
    SetTime(359 - 373, 6);
    pao_operator.pao(4, 9);

    // wave7 PPc
    SetTime(195, 7);
    Card(PUFF_SHROOM, 4, 9);
    SetTime(195 + 300, 7);
    Shovel(4, 9);
    SetTime(295 - 376, 7);
    pao_operator.pao(2, 9);
    SetTime(359 - 373, 7);
    pao_operator.pao(4, 9);

    // wave8 PPc
    SetTime(195, 8);
    Card(M_PUFF_SHROOM, 4, 9);
    SetTime(195 + 300, 8);
    Shovel(4, 9);
    SetTime(295 - 376, 8);
    pao_operator.pao(2, 9);
    SetTime(359 - 373, 8);
    pao_operator.pao(4, 9);

    // wave9 PPc
    SetTime(195, 9);
    Card(PUFF_SHROOM, 4, 9);
    SetTime(195 + 300, 9);
    Shovel(4, 9);
    // 开始自动垫巨人僵尸
    InsertOperation([=]() {
        block_giga.pushFunc([]() {
            BlockGargantuar({{4, 9}});
        });
    });
    SetTime(295 - 376, 9);
    pao_operator.pao(2, 9);
    SetTime(359 - 373, 9);
    pao_operator.pao(4, 9);
    pao_operator.recoverPao({{2, 9}, {4, 9}, {2, 9}, {4, 9}, {2, 9}, {4, 9}});

    // wave10 PPc
    SetTime(0, 10);
    Shovel(4, 9);
    block_giga.pause();
    SetTime(195, 10);
    Card(PUFF_SHROOM, 4, 9);
    SetTime(195 + 300, 10);
    Shovel(4, 9);
    SetTime(295 - 376, 10);
    pao_operator.pao(2, 9);
    SetTime(359 - 373, 10);
    pao_operator.pao(4, 9);

    // wave11 PPc
    SetTime(195, 11);
    Card(M_PUFF_SHROOM, 4, 9);
    SetTime(195 + 300, 11);
    Shovel(4, 9);
    SetTime(295 - 376, 11);
    pao_operator.pao(2, 9);
    SetTime(359 - 373, 11);
    pao_operator.pao(4, 9);

    // wave12 PPc
    SetTime(195, 12);
    Card(PUFF_SHROOM, 4, 9);
    SetTime(195 + 300, 12);
    Shovel(4, 9);
    SetTime(295 - 376, 12);
    pao_operator.pao(2, 9);
    SetTime(359 - 373, 12);
    pao_operator.pao(4, 9);

    // wave13 PPc
    SetTime(195, 13);
    Card(M_PUFF_SHROOM, 4, 9);
    SetTime(195 + 300, 13);
    Shovel(4, 9);
    SetTime(295 - 376, 13);
    pao_operator.pao(2, 9);
    SetTime(359 - 373, 13);
    pao_operator.pao(4, 9);

    // wave14 PPc
    SetTime(195, 14);
    Card(PUFF_SHROOM, 4, 9);
    SetTime(195 + 300, 14);
    Shovel(4, 9);
    SetTime(295 - 376, 14);
    pao_operator.pao(2, 9);
    SetTime(359 - 373, 14);
    pao_operator.pao(4, 9);

    // wave15 PPc
    SetTime(195, 15);
    Card(M_PUFF_SHROOM, 4, 9);
    SetTime(195 + 300, 15);
    Shovel(4, 9);
    SetTime(295 - 376, 15);
    pao_operator.pao(2, 9);
    SetTime(359 - 373, 15);
    pao_operator.pao(4, 9);

    // wave16 PPc
    SetTime(195, 16);
    Card(PUFF_SHROOM, 4, 9);
    SetTime(195 + 300, 16);
    Shovel(4, 9);
    SetTime(295 - 376, 16);
    pao_operator.pao(2, 9);
    SetTime(359 - 373, 16);
    pao_operator.pao(4, 9);

    // wave17 PPc
    SetTime(195, 17);
    Card(M_PUFF_SHROOM, 4, 9);
    SetTime(195 + 300, 17);
    Shovel(4, 9);
    SetTime(295 - 376, 17);
    pao_operator.pao(2, 9);
    SetTime(359 - 373, 17);
    pao_operator.pao(4, 9);

    // wave18 PPc
    SetTime(195, 18);
    Card(PUFF_SHROOM, 4, 9);
    SetTime(195 + 300, 18);
    Shovel(4, 9);
    SetTime(295 - 376, 18);
    pao_operator.pao(2, 9);
    SetTime(359 - 373, 18);
    pao_operator.pao(4, 9);

    // wave19 PPc
    SetTime(195, 19);
    Card(M_PUFF_SHROOM, 4, 9);
    SetTime(195 + 300, 19);
    Shovel(4, 9);
    block_giga.goOn();
    SetTime(295 - 376, 19);
    pao_operator.pao(2, 9);
    SetTime(359 - 373, 19);
    pao_operator.pao(4, 9);
    pao_operator.recoverPao({{2, 9}, {4, 9}, {2, 9}, {4, 9}, {2, 9}, {4, 9}});

    // wave20 PPc
    // 炮消墓碑僵尸
    SetTime(350 - 373, 20);
    pao_operator.pao({{2, 8}, {5, 8}});
    SetTime(195, 20);
    Card(M_PUFF_SHROOM, 4, 9);
    SetTime(195 + 300, 20);
    Shovel(4, 9);
    block_giga.goOn();
    SetTime(295 - 376, 20);
    pao_operator.pao(2, 9);
    SetTime(359 - 373, 20);
    pao_operator.pao(4, 9);
    pao_operator.recoverPao({{2, 9}, {4, 9}, {2, 9}, {4, 9}, {2, 9}, {4, 9}});
}
void BlockGargantuar(std::vector<Grid> pos)
{
    for (Grid each : pos) {
        auto zombies = GetMainObject()->zombieArray();
        auto seeds = GetMainObject()->seedArray();
        std::vector<int> indices_seed = {GetSeedIndex(PUFF_SHROOM), GetSeedIndex(M_PUFF_SHROOM)};
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