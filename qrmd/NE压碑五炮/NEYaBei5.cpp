/*
 * @Author: qrmd
 * @Date: 2022-06-16 20:48:54
 * @LastEditors: qrmd
 * @LastEditTime: 2022-06-16 21:56:36
 * @Description:NE压碑五炮 全难度极限出怪运阵演示脚本
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
// *** Not In Quene
// 返回黑夜场景第20波墓碑的生成位置，如果未找到墓碑则返回{-1, -1}
Grid GetGraveGrid();
// 自动在指定位置放置植物触发巨人僵尸举锤阻挡其前进。结合TickRunner使用
void BlockGargantuar(vector<Grid> pos);
TickRunner block_giga;
void Script()
{
    // 脚本在游戏主界面和选择植物界面生效
    OpenMultipleEffective('Q', MAIN_UI_OR_FIGHT_UI);
    // 全难度极限出怪：普僵、撑杆、橄榄、舞王、小丑、矿工、跳跳、小偷、扶梯、投篮、白眼、红眼
    SetZombies({ZOMBIE, POLE_VAULTING_ZOMBIE, FOOTBALL_ZOMBIE, DANCING_ZOMBIE, JACK_IN_THE_BOX_ZOMBIE, DIGGER_ZOMBIE, POGO_ZOMBIE, BUNGEE_ZOMBIE, LADDER_ZOMBIE, CATAPULT_ZOMBIE, GARGANTUAR, GIGA_GARGANTUAR});
    // 选择植物：寒冰菇、模仿寒冰菇、毁灭菇、樱桃炸弹、倭瓜、墓碑吞噬者、小喷菇、花盆、胆小菇、阳光菇
    SelectCards({ICE_SHROOM, M_ICE_SHROOM, DOOM_SHROOM, CHERRY_BOMB, SQUASH, GRAVE_BUSTER, PUFF_SHROOM, FLOWER_POT, SCAREDY_SHROOM, SUN_SHROOM});
    SetTime(-599, 1);
    // 自动填充炮列表
    pao_operator.resetPaoList({{1, 5}, {2, 5}, {4, 5}, {3, 5}, {5, 5}});
    // 主体节奏 邻C7u I-PP|I-PP|PA|N|PP 1768|1768|601|601|601 每波执行确定的操作，不考虑非旗帜波的刷新延迟

    // wave1 PP
    SetTime(341 - 376, 1);
    pao_operator.pao({{2, 9}, {4, 9}});
    SetTime(1 - 419 + 601, 1);
    Card(M_ICE_SHROOM, 1, 1);

    // wave2 I-PP
    SetTime(1768 - 200 - 373, 2);
    pao_operator.pao({{2, 9}, {4, 9}});

    // wave3 I-PP
    SetTime(1 - 100, 3);
    Card(ICE_SHROOM, 1, 1);
    SetTime(1768 - 200 - 373, 3);
    pao_operator.pao({{2, 9}, {4, 9}});

    // wave4 PA
    SetTime(341 - 376, 4);
    pao_operator.pao(2, 9);
    SetTime(341 - 100, 4);
    Card(CHERRY_BOMB, 4, 9);

    // wave5 N
    SetTime(341 - 100, 5);
    Card(DOOM_SHROOM, {{3, 9}, {2, 9}, {2, 8}, {4, 8}});

    // wave6 PP
    SetTime(341 - 376, 6);
    pao_operator.pao({{2, 9}, {4, 9}});
    SetTime(1 - 419 + 601, 6);
    Card(M_ICE_SHROOM, 1, 1);

    // wave7 I-PP
    SetTime(1768 - 200 - 373, 7);
    pao_operator.pao({{2, 9}, {4, 9}});

    // wave8 I-PP
    SetTime(1 - 100, 8);
    Card(ICE_SHROOM, 1, 1);
    SetTime(1768 - 200 - 373, 8);
    pao_operator.pao({{2, 9}, {4, 9}});

    // wave9 PA(-N-PP-P)
    SetTime(341 - 376, 9);
    pao_operator.pao(2, 9);
    SetTime(341 - 100, 9);
    Card(CHERRY_BOMB, 4, 9);
    SetTime(341 + 601 - 100, 9);
    Card(DOOM_SHROOM, {{3, 9}, {2, 9}, {2, 8}, {4, 8}});
    pao_operator.recoverPao({{2, 9}, {4, 9}});
    SetTime(1000, 9);
    // 开始自动垫巨人僵尸
    InsertOperation([=]() {
        block_giga.pushFunc([]() {
            BlockGargantuar({{1, 8}, {5, 8}});
        });
    });

    // wave10 I-PP
    SetTime(0, 10);
    block_giga.pause();
    SetTime(1 - 419, 10);
    Card(M_ICE_SHROOM, 1, 1);
    SetTime(1768 - 200 - 373, 10);
    pao_operator.pao({{2, 9}, {4, 9}});

    // wave11 I-PP
    SetTime(1 - 100, 11);
    Card(ICE_SHROOM, 1, 1);
    SetTime(1768 - 200 - 373, 11);
    pao_operator.pao({{2, 9}, {4, 9}});

    // wave12 PA
    SetTime(341 - 376, 12);
    pao_operator.pao(2, 9);
    SetTime(341 - 100, 12);
    Card(CHERRY_BOMB, 4, 9);

    // wave13 N
    SetTime(341 - 100, 13);
    Card(DOOM_SHROOM, {{3, 9}, {2, 9}, {2, 8}, {4, 8}});

    // wave14 PP
    SetTime(341 - 376, 14);
    pao_operator.pao({{2, 9}, {4, 9}});
    SetTime(1 - 419 + 601, 14);
    Card(M_ICE_SHROOM, 1, 1);

    // wave15 I-PP
    SetTime(1768 - 200 - 373, 15);
    pao_operator.pao({{2, 9}, {4, 9}});

    // wave16 I-PP
    SetTime(1 - 100, 16);
    Card(ICE_SHROOM, 1, 1);
    SetTime(1768 - 200 - 373, 16);
    pao_operator.pao({{2, 9}, {4, 9}});

    // wave17 PA
    SetTime(341 - 376, 17);
    pao_operator.pao(2, 9);
    SetTime(341 - 100, 17);
    Card(CHERRY_BOMB, 4, 9);

    // wave18 N
    SetTime(341 - 100, 18);
    Card(DOOM_SHROOM, {{3, 9}, {2, 9}, {2, 8}, {4, 8}});
    // 199cs为舞王僵尸触碰9列倭瓜并开始召唤的最晚时机
    SetTime(199, 18);
    Card(SQUASH, 1, 9);

    // wave19 PP(-PP-PP)
    SetTime(341 - 376, 19);
    pao_operator.pao({{2, 9}, {4, 9}});
    pao_operator.recoverPao({{2, 9}, {4, 9}});
    block_giga.goOn();
    SetTime(3027, 19);
    pao_operator.recoverPao({{2, 8}, {4, 8}});

    // wave20 N(-PP-PP)
    SetTime(-1, 20);
    Card(PUFF_SHROOM, 3, 8);
    SetTime(350 - 100, 20);
    Shovel(3, 8);
    Card(DOOM_SHROOM, 3, 8);
    // 吞噬墓碑
    InsertTimeOperation(3000, 20, [=]() {
        Grid grave = GetGraveGrid();
        SetTime(3000, 20);
        Card(GRAVE_BUSTER, grave.row, grave.col);
    });
    SetTime(341 - 376, 20);
    pao_operator.recoverPao({{2, 9}, {4, 9}, {2, 9}, {4, 9}});
}
Grid GetGraveGrid()
{
    Grid grave = {-1, -1};
    std::vector<Grid> grave_generate_pos = {{1, 8}, {2, 8}, {3, 8}, {4, 8}, {5, 8}, {1, 9}, {2, 9}, {3, 9}, {4, 9}, {5, 9}};
    for (Grid each : grave_generate_pos) {
        if (Asm::getPlantRejectType(GRAVE_BUSTER, each.row - 1, each.col - 1) == Asm::NIL) {
            grave = each;
            break;
        }
    }
    return grave;
}
void BlockGargantuar(vector<Grid> pos)
{
    for (Grid each : pos) {
        auto zombies = GetMainObject()->zombieArray();
        auto seeds = GetMainObject()->seedArray();
        vector<int> indices_seed = {GetSeedIndex(PUFF_SHROOM), GetSeedIndex(FLOWER_POT), GetSeedIndex(SCAREDY_SHROOM), GetSeedIndex(SUN_SHROOM), GetSeedIndex(SQUASH)};
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