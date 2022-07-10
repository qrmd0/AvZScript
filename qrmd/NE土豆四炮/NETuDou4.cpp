/*
 * @Author: qrmd
 * @Date: 2022-06-16 10:27:33
 * @LastEditors: qrmd
 * @LastEditTime: 2022-06-16 19:46:47
 * @Description:NE土豆四炮 全难度极限出怪运阵演示脚本
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
    // 选择植物：寒冰菇、模仿寒冰菇、毁灭菇、樱桃炸弹、火爆辣椒、倭瓜、土豆地雷、墓碑吞噬者、叶子保护伞、高坚果
    SelectCards({ICE_SHROOM, M_ICE_SHROOM, DOOM_SHROOM, CHERRY_BOMB, JALAPENO, SQUASH, POTATO_MINE, GRAVE_BUSTER, UMBRELLA_LEAF, TALL_NUT});
    SetTime(-599, 1);
    // 自动填充炮列表
    pao_operator.resetPaoList({{2, 5}, {4, 5}, {3, 1}, {3, 5}});
    // 铲除和种植临时植物
    Shovel(3, 3);
    Card(TALL_NUT, 1, 1);
    SetTime(-599 + 3001, 1);
    Card(TALL_NUT, 5, 1);
    // 主体节奏 邻C7u I-PP|Ia'-PP|AA'a|N|PP 1620|1819|601|749|601 每波执行确定的操作，不考虑非旗帜波的刷新延迟

    // wave1 PP
    SetTime(341 - 376, 1);
    pao_operator.pao({{2, 9}, {4, 9}});
    SetTime(1 - 419 + 601, 1);
    Shovel(3, 3);
    Card(M_ICE_SHROOM, 3, 3);

    // wave2 I-PP
    // 种植土豆地雷消灭下波矿工僵尸
    SetTime(1044, 2);
    Shovel(3, 3);
    Card(POTATO_MINE, 3, 3);
    SetTime(1614 - 200 - 373, 2);
    pao_operator.pao({{2, 9}, {4, 9}});

    // wave3 Ia'-PP
    SetTime(1 - 100, 3);
    Card(ICE_SHROOM, 1, 5);
    SetTime(1819 - 200 - 373, 3);
    pao_operator.pao({{2, 9}, {4, 9}});

    // wave4 AA'a
    SetTime(341 - 100, 4);
    Card(CHERRY_BOMB, 4, 9);
    SetTime(359 - 100, 4);
    Card(JALAPENO, 1, 2);
    // 199cs为舞王僵尸触碰9列倭瓜并开始召唤的最晚时机
    SetTime(199, 4);
    Card(SQUASH, 2, 9);

    // wave5 N
    // 493cs为舞王僵尸自然召唤的伴舞僵尸啃食7列植物的最早时机
    SetTime(493 - 1 - 100, 5);
    Card(DOOM_SHROOM, {{3, 9}, {3, 8}, {2, 8}});

    // wave6 PP
    SetTime(341 - 376, 6);
    pao_operator.pao({{2, 9}, {4, 9}});
    SetTime(1 - 419 + 601, 6);
    Shovel(3, 3);
    Card(M_ICE_SHROOM, 3, 3);

    // wave7 I-PP
    // 种植土豆地雷消灭下波矿工僵尸
    SetTime(1044, 7);
    Shovel(3, 3);
    Card(POTATO_MINE, 3, 3);
    SetTime(1614 - 200 - 373, 7);
    pao_operator.pao({{2, 9}, {4, 9}});

    // wave8 Ia'-PP
    SetTime(1 - 100, 8);
    Card(ICE_SHROOM, 1, 5);
    SetTime(1819 - 200 - 373, 8);
    pao_operator.pao({{2, 9}, {4, 9}});

    // wave9 AA'a(-N-PP)
    SetTime(341 - 100, 9);
    Card(CHERRY_BOMB, 4, 9);
    SetTime(359 - 100, 9);
    Card(JALAPENO, 1, 2);
    // 199cs为舞王僵尸触碰9列倭瓜并开始召唤的最晚时机
    SetTime(199, 9);
    Card(SQUASH, 2, 9);
    SetTime(549 + 601 - 100, 9);
    Card(DOOM_SHROOM, {{3, 9}, {3, 8}, {2, 8}});
    pao_operator.recoverPao({{2, 7.5}, {4, 7.5}});
    // 开始自动垫巨人僵尸
    InsertOperation([=]() {
        block_giga.pushFunc([]() {
            BlockGargantuar({{2, 7}, {4, 7}});
        });
    });
    // wave10 PP
    SetTime(375 - 1 - 751, 10);
    Card(UMBRELLA_LEAF, 3, 3);
    SetTime(375 - 1, 10);
    block_giga.pause();
    InsertOperation([=]() {
        if ((GetPlantIndex(2, 7, UMBRELLA_LEAF) < 0) && (GetPlantIndex(4, 7, UMBRELLA_LEAF) < 0)) {
            SetTime(375 - 1, 10);
            Shovel({{2, 7}, {4, 7}});
            Card(UMBRELLA_LEAF, 2, 7);
        }
    });
    SetTime(395 + 150, 10);
    Shovel({{2, 7}, {4, 7}});
    SetTime(341 - 376, 10);
    pao_operator.pao({{2, 9}, {4, 9}});
    // 修补高坚果
    SetTime(800, 10);
    Card(TALL_NUT, {{1, 1}, {5, 1}});
    SetTime(800 + 3001, 10);
    Card(TALL_NUT, {{1, 1}, {5, 1}});
    SetTime(1 - 419 + 601, 10);
    Card(M_ICE_SHROOM, 2, 1);
    // wave11 I-PP

    // 种植土豆地雷消灭下波矿工僵尸
    SetTime(1044, 11);
    Shovel(3, 3);
    Card(POTATO_MINE, 3, 3);
    SetTime(1614 - 200 - 373, 11);
    pao_operator.pao({{2, 9}, {4, 9}});

    // wave12 Ia'-PP
    SetTime(1 - 100, 12);
    Card(ICE_SHROOM, 1, 5);
    SetTime(1819 - 200 - 373, 12);
    pao_operator.pao({{2, 9}, {4, 9}});

    // wave13 AA'a
    SetTime(341 - 100, 13);
    Card(CHERRY_BOMB, 4, 9);
    SetTime(359 - 100, 13);
    Card(JALAPENO, 1, 2);
    // 199cs为舞王僵尸触碰9列倭瓜并开始召唤的最晚时机
    SetTime(199, 13);
    Card(SQUASH, 2, 9);

    // wave14 N
    // 493cs为舞王僵尸自然召唤的伴舞僵尸啃食7列植物的最早时机
    SetTime(493 - 1 - 100, 14);
    Card(DOOM_SHROOM, {{3, 9}, {3, 8}, {2, 8}});

    // wave15 PP
    SetTime(341 - 376, 15);
    pao_operator.pao({{2, 9}, {4, 9}});
    SetTime(1 - 419 + 601, 15);
    Shovel(3, 3);
    Card(M_ICE_SHROOM, 3, 3);
    // wave16 I-PP

    // 种植土豆地雷消灭下波矿工僵尸
    SetTime(1044, 16);
    Shovel(3, 3);
    Card(POTATO_MINE, 3, 3);
    SetTime(1614 - 200 - 373, 16);
    pao_operator.pao({{2, 9}, {4, 9}});

    // wave17 Ia'-PP
    SetTime(1 - 100, 17);
    Card(ICE_SHROOM, 1, 5);
    SetTime(1819 - 200 - 373, 17);
    pao_operator.pao({{2, 9}, {4, 9}});

    // wave18 AA'a
    SetTime(341 - 100, 18);
    Card(CHERRY_BOMB, 4, 9);
    SetTime(359 - 100, 18);
    Card(JALAPENO, 1, 2);
    // 199cs为舞王僵尸触碰9列倭瓜并开始召唤的最晚时机
    SetTime(199, 18);
    Card(SQUASH, 2, 9);

    // wave19 N(-PP-PP)
    // 493cs为舞王僵尸自然召唤的伴舞僵尸啃食7列植物的最早时机
    SetTime(493 - 1 - 100, 19);
    Card(DOOM_SHROOM, {{3, 9}, {3, 8}, {2, 8}});
    pao_operator.recoverPao({{2, 9}, {4, 9}, {2, 7.5}, {4, 7.5}});
    Shovel(3, 3);
    Card(UMBRELLA_LEAF, 3, 3);
    block_giga.goOn();

    // wave20 IPP(-PP-PP)
    SetTime(375 - 1 - 751, 20);
    Card(UMBRELLA_LEAF, 3, 3);
    SetTime(375 - 1, 20);
    block_giga.pause();
    InsertOperation([=]() {
        if ((GetPlantIndex(2, 7, UMBRELLA_LEAF) < 0) && (GetPlantIndex(4, 7, UMBRELLA_LEAF) < 0)) {
            SetTime(375 - 1, 20);
            Shovel({{2, 7}, {4, 7}});
            Card(UMBRELLA_LEAF, 2, 7);
        }
    });
    SetTime(395 + 150, 10);
    Shovel({{2, 7}, {4, 7}});
    SetTime(350 - 419, 20);
    Card(M_ICE_SHROOM, 2, 1);
    // 炮消墓碑僵尸
    SetTime(350 - 373, 20);
    pao_operator.pao(3, 7);
    // 吞噬墓碑
    InsertTimeOperation(3500, 20, [=]() {
        Grid grave = GetGraveGrid();
        SetTime(3500, 20);
        Card(GRAVE_BUSTER, grave.row, grave.col);
    });
    SetTime(341 - 376, 20);
    pao_operator.recoverPao({{2, 9}, {4, 9}});
    pao_operator.recoverPao({{2, 9}, {4, 9}, {2, 7.5}});
    SetTime(600, 20);
    Card(CHERRY_BOMB, 4, 9);
}
Grid GetGraveGrid()
{
    Grid grave = {-1, -1};
    std::vector<Grid> grave_generate_pos = {{1, 5}, {2, 5}, {3, 5}, {4, 5}, {5, 5}, {1, 6}, {2, 6}, {3, 6}, {4, 6}, {5, 6}, {1, 7}, {2, 7}, {3, 7}, {4, 7}, {5, 7}, {1, 8}, {2, 8}, {3, 8}, {4, 8}, {5, 8}, {1, 9}, {2, 9}, {3, 9}, {4, 9}, {5, 9}};
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
        vector<int> indices_seed = {GetSeedIndex(UMBRELLA_LEAF), GetSeedIndex(SQUASH)};
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