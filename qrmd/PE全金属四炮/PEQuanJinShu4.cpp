/*
 * @Author: qrmd
 * @Date: 2022-06-17 15:00:21
 * @LastEditors: qrmd
 * @LastEditTime: 2022-06-18 00:35:59
 * @Description:PE全金属四炮 全难度极限出怪运阵演示脚本
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
// 自动在指定位置放置植物触发巨人僵尸举锤阻挡其前进，撑杆僵尸靠近时自动铲除。结合TickRunner使用
void BlockGargantuar(std::vector<Grid> pos);
TickRunner block_giga;
// 自动在指定位置放置植物触发巨人僵尸举锤阻挡其前进，撑杆僵尸靠近时自动铲除，不使用叶子保护伞。结合TickRunner使用
TickRunner block_giga2;
void BlockGargantuar2(std::vector<Grid> pos) void Script()
{
    // 脚本在游戏主界面和选择植物界面生效
    OpenMultipleEffective('Q', MAIN_UI_OR_FIGHT_UI);
    // 全难度极限出怪：普僵、撑杆、橄榄、舞王、冰车、小丑、矿工、跳跳、小偷、扶梯、投篮、白眼、红眼、海豚
    SetZombies({ZOMBIE, POLE_VAULTING_ZOMBIE, FOOTBALL_ZOMBIE, DANCING_ZOMBIE, ZOMBONI, JACK_IN_THE_BOX_ZOMBIE, DIGGER_ZOMBIE, POGO_ZOMBIE, BUNGEE_ZOMBIE, LADDER_ZOMBIE, CATAPULT_ZOMBIE, GARGANTUAR, GIGA_GARGANTUAR, DOLPHIN_RIDER_ZOMBIE});
    // 选择植物：咖啡豆、寒冰菇、模仿寒冰菇、睡莲叶、毁灭菇、倭瓜、樱桃炸弹、高坚果、小喷菇、叶子保护伞
    SelectCards({COFFEE_BEAN, ICE_SHROOM, M_ICE_SHROOM, LILY_PAD, DOOM_SHROOM, SQUASH, CHERRY_BOMB, TALL_NUT, PUFF_SHROOM, UMBRELLA_LEAF});
    SetTime(-599, 1);
    // 填充炮列表
    pao_operator.resetPaoList({{1, 5}, {6, 5}, {2, 5}, {5, 5}});
    // 开始自动存冰
    ice_filler.start({{3, 1}, {4, 1}, {3, 4}, {4, 4}});
    // 开始自动修补高坚果
    plant_fixer.start(TALL_NUT, {{3, 7}, {4, 7}}, 2000);
    // 开始自动垫巨人僵尸
    block_giga.pushFunc([]() {
        BlockGargantuar({{1, 7}, {2, 7}, {5, 7}, {6, 7}});
    });
    // 种植临时植物
    Card(LILY_PAD, 3, 9);
    SetTime(-599 + 751, 1);
    Card(LILY_PAD, 3, 7);
    Card(TALL_NUT, 3, 7);
    SetTime(-599 + 751 * 2, 1);
    Card(LILY_PAD, 4, 7);
    Card(SQUASH, 4, 7);
    SetTime(-599 + 751 + 3001, 1);
    Card(TALL_NUT, 4, 7);
    // 主体节奏 ch4-N I-PP|I-PP|I-N|PP 1706|1706|1231|601 每波执行确定的操作，不考虑非旗帜波的刷新延迟
    // wave1 N
    SetTime(342 - 299, 1);
    Card(DOOM_SHROOM, {{3, 9}, {3, 8}, {4, 9}, {4, 8}});
    Card(COFFEE_BEAN, {{3, 9}, {3, 8}, {4, 9}, {4, 8}});

    // wave2 PP
    SetTime(341 - 376, 2);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});

    // wave3 I-PP
    SetTime(-200, 3);
    ice_filler.coffee();
    SetTime(1706 - 200 - 373, 3);
    pao_operator.pao({{2, 8.5}, {5, 8.5}});

    // wave4 I-PP
    SetTime(-200, 4);
    ice_filler.coffee();
    SetTime(1706 - 200 - 373, 4);
    pao_operator.pao({{2, 8.5}, {5, 8.5}});

    // wave5 I-N
    SetTime(-200, 5);
    ice_filler.coffee();
    SetTime(1231 - 200 - 298, 5);
    Card(LILY_PAD, {{3, 9}, {3, 8}, {4, 9}, {4, 8}});
    Card(DOOM_SHROOM, {{3, 9}, {3, 8}, {4, 9}, {4, 8}});
    Card(COFFEE_BEAN, {{3, 9}, {3, 8}, {4, 9}, {4, 8}});

    // wave6 PP
    SetTime(341 - 376, 6);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});

    // wave7 I-PP
    SetTime(-200, 7);
    ice_filler.coffee();
    SetTime(1706 - 200 - 373, 7);
    pao_operator.pao({{2, 8.5}, {5, 8.5}});

    // wave8 I-PP
    SetTime(-200, 8);
    ice_filler.coffee();
    SetTime(1706 - 200 - 373, 8);
    pao_operator.pao({{2, 8.5}, {5, 8.5}});

    // wave9 I-N(-PP-PP-PP)
    SetTime(-200, 9);
    ice_filler.coffee();
    SetTime(1231 - 200 - 298, 9);
    Card(LILY_PAD, {{3, 9}, {3, 8}, {4, 9}, {4, 8}});
    Card(DOOM_SHROOM, {{3, 9}, {3, 8}, {4, 9}, {4, 8}});
    Card(COFFEE_BEAN, {{3, 9}, {3, 8}, {4, 9}, {4, 8}});
    SetTime(341 + 1231 - 376, 9);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    SetTime(1706 + 1231 + 601 - 200 - 373, 9);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    SetTime(1706 + 1231 + 601 + 1400 - 200 - 373, 9);
    Shovel({{2, 7}, {5, 7}});
    Card(CHERRY_BOMB, 2, 7);
    Card(SQUASH, 5, 7);

    // wave10 I-N
    SetTime(0, 10);
    Shovel({{1, 7}, {2, 7}, {5, 7}, {6, 7}});
    // 243cs为旗帜波舞王僵尸触碰9列小喷菇召唤伴舞僵尸的最晚时机
    SetTime(243, 10);
    Card(PUFF_SHROOM, 2, 9);
    Card(UMBRELLA_LEAF, 5, 9);
    // 79cs为跳跳僵尸遇到植物起跳的时长
    SetTime(243 + 79, 10);
    Shovel({{2, 9}, {5, 9}});
    // 395cs为蹦极僵尸全部被冰冻的最晚时机
    SetTime(395 - 298, 10);
    ice_filler.coffee();
    SetTime(395 + 751 - 298, 10);
    Card(LILY_PAD, {{3, 9}, {3, 8}, {4, 9}, {4, 8}});
    Card(DOOM_SHROOM, {{3, 9}, {3, 8}, {4, 9}, {4, 8}});
    Card(COFFEE_BEAN, {{3, 9}, {3, 8}, {4, 9}, {4, 8}});

    // wave11 PP
    SetTime(341 - 376, 11);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});

    // wave12 I-PP
    SetTime(-200, 12);
    ice_filler.coffee();
    SetTime(1706 - 200 - 373, 12);
    pao_operator.pao({{2, 8.5}, {5, 8.5}});

    // wave13 I-PP
    SetTime(-200, 13);
    ice_filler.coffee();
    SetTime(1706 - 200 - 373, 13);
    pao_operator.pao({{2, 8.5}, {5, 8.5}});

    // wave14 I-N
    SetTime(-200, 14);
    ice_filler.coffee();
    SetTime(1231 - 200 - 298, 14);
    Card(LILY_PAD, {{3, 9}, {3, 8}, {4, 9}, {4, 8}});
    Card(DOOM_SHROOM, {{3, 9}, {3, 8}, {4, 9}, {4, 8}});
    Card(COFFEE_BEAN, {{3, 9}, {3, 8}, {4, 9}, {4, 8}});

    // wave15 PP
    SetTime(341 - 376, 15);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});

    // wave16 I-PP
    SetTime(-200, 16);
    ice_filler.coffee();
    SetTime(1706 - 200 - 373, 16);
    pao_operator.pao({{2, 8.5}, {5, 8.5}});

    // wave17 I-PP
    SetTime(-200, 17);
    ice_filler.coffee();
    SetTime(1706 - 200 - 373, 17);
    pao_operator.pao({{2, 8.5}, {5, 8.5}});

    // wave18 I-N
    SetTime(-200, 18);
    ice_filler.coffee();
    SetTime(1231 - 200 - 298, 18);
    Card(LILY_PAD, {{3, 9}, {3, 8}, {4, 9}, {4, 8}});
    Card(DOOM_SHROOM, {{3, 9}, {3, 8}, {4, 9}, {4, 8}});
    Card(COFFEE_BEAN, {{3, 9}, {3, 8}, {4, 9}, {4, 8}});

    // wave19 PP-(IPP-PP-AA'c)
    SetTime(341 - 376, 19);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    block_giga.pause();
    Shovel({{1, 7}, {2, 7}, {5, 7}, {6, 7}});
    SetTime(341 - 298, 19);
    ice_filler.coffee();
    SetTime(1706 + 601 - 200 - 373, 19);
    pao_operator.pao({{2, 8.5}, {5, 8.5}});
    block_giga.goOn();
    SetTime(1500 - 751, 19);
    block_giga.pause();
    // 开始自动垫巨人僵尸，不使用叶子保护伞
    InsertOperation([=]() {
        block_giga.pushFunc([]() {
            BlockGargantuar2({{1, 7}, {2, 7}, {5, 7}, {6, 7}});
        });
    });
    SetTime(1500, 19);
    Card(UMBRELLA_LEAF, 2, 1);
    SetTime(1200 + 751, 19);
    Card(UMBRELLA_LEAF, 5, 1);
    SetTime(1200 + 751 * 2, 19);
    Card(UMBRELLA_LEAF, 2, 4);
    SetTime(1200 + 751 * 3, 19);
    Card(UMBRELLA_LEAF, 5, 4);
    SetTime(1200 + 751 * 4, 19);
    Card(UMBRELLA_LEAF, 2, 7);
    SetTime(1200 + 751 * 5, 19);
    Card(UMBRELLA_LEAF, 5, 7);
    SetTime(1706 + 601 + 1706 - 200 - 373, 19);
    pao_operator.pao({{2, 8.5}, {5, 8.5}});
    Shovel({{2, 7}, {5, 7}});
    Card(CHERRY_BOMB, 2, 7);
    Card(SQUASH, 5, 7);

    // wave20 N-IPP-(PP-PP)
    SetTime(395 + 150, 20);
    Shovel({{1, 7}, {6, 7}, {2, 1}, {5, 1}, {2, 4}, {5, 4}});
    block_giga2.pause();
    block_giga.goOn();
    SetTime(250 - 298, 20);
    Card(LILY_PAD, {{3, 9}, {3, 8}, {4, 9}, {4, 8}});
    Card(DOOM_SHROOM, {{3, 9}, {3, 8}, {4, 9}, {4, 8}});
    Card(COFFEE_BEAN, {{3, 9}, {3, 8}, {4, 9}, {4, 8}});
    SetTime(250 + 751 - 298, 20);
    ice_filler.coffee();
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
void BlockGargantuar(std::vector<Grid> pos)
{
    for (Grid each : pos) {
        auto zombies = GetMainObject()->zombieArray();
        auto seeds = GetMainObject()->seedArray();
        std::vector<int> indices_seed = {GetSeedIndex(PUFF_SHROOM), GetSeedIndex(TALL_NUT)};
        for (int index = 0; index < GetMainObject()->zombieTotal(); ++index) {
            if (!zombies[index].isDead() && !zombies[index].isDisappeared() && zombies[index].type() == POLE_VAULTING_ZOMBIE && zombies[index].row() + 1 == each.row && (zombies[index].abscissa() <= 40 + each.col * 80 + 35 && zombies[index].abscissa() >= 40 + (each.col - 1) * 80 - 70 && zombies[index].state() == 11)) {
                if (GetPlantIndex(each.row, each.col) >= 0 || GetPlantIndex(each.row, each.col, FLOWER_POT) >= 0)
                    ShovelNotInQueue(each.row, each.col);
                return;
            }
            if (!zombies[index].isDead() && !zombies[index].isDisappeared() && (zombies[index].type() == GARGANTUAR || zombies[index].type() == GIGA_GARGANTUAR) && zombies[index].row() + 1 == each.row && (zombies[index].abscissa() <= 40 + (each.col - 1) * 80 + 10 && zombies[index].abscissa() >= 40 + (each.col - 1) * 80 - 5)) {
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
void BlockGargantuar2(std::vector<Grid> pos)
{
    for (Grid each : pos) {
        auto zombies = GetMainObject()->zombieArray();
        auto seeds = GetMainObject()->seedArray();
        std::vector<int> indices_seed = {GetSeedIndex(PUFF_SHROOM), GetSeedIndex(UMBRELLA_LEAF), GetSeedIndex(TALL_NUT)};
        for (int index = 0; index < GetMainObject()->zombieTotal(); ++index) {
            if (!zombies[index].isDead() && !zombies[index].isDisappeared() && zombies[index].type() == POLE_VAULTING_ZOMBIE && zombies[index].row() + 1 == each.row && (zombies[index].abscissa() <= 40 + each.col * 80 + 35 && zombies[index].abscissa() >= 40 + (each.col - 1) * 80 - 70 && zombies[index].state() == 11)) {
                if (GetPlantIndex(each.row, each.col) >= 0 || GetPlantIndex(each.row, each.col, FLOWER_POT) >= 0)
                    ShovelNotInQueue(each.row, each.col);
                return;
            }
            if (!zombies[index].isDead() && !zombies[index].isDisappeared() && (zombies[index].type() == GARGANTUAR || zombies[index].type() == GIGA_GARGANTUAR) && zombies[index].row() + 1 == each.row && (zombies[index].abscissa() <= 40 + (each.col - 1) * 80 + 10 && zombies[index].abscissa() >= 40 + (each.col - 1) * 80 - 5)) {
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