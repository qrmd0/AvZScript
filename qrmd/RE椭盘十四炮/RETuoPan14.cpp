#include "avz.h"

using namespace AvZ;
PaoOperator slope_pao;
PaoOperator flat_pao;
// *** Not In Queue
// 在位置列表[pos_list]存在巨人僵尸或橄榄僵尸时放置[types]中的植物以拖延其前进，附近存在持杆的撑杆僵尸时自动铲除。结合TickRunner使用。
void AutoBlock(std::vector<PlantType> types, std::vector<Grid> pos_list);
TickRunner auto_blocker;
void Script()
{
    // 脚本在游戏主界面和选择植物界面生效
    OpenMultipleEffective('Q', MAIN_UI_OR_FIGHT_UI);
    // 全难度极限出怪：普僵、撑杆、橄榄、冰车、小丑、跳跳、小偷、扶梯、投篮、白眼、红眼
    SetZombies({ZOMBIE, POLE_VAULTING_ZOMBIE, FOOTBALL_ZOMBIE, ZOMBONI, JACK_IN_THE_BOX_ZOMBIE, POGO_ZOMBIE, BUNGEE_ZOMBIE, LADDER_ZOMBIE, CATAPULT_ZOMBIE, GARGANTUAR, GIGA_GARGANTUAR});
    // 选择植物：咖啡豆、寒冰菇、模仿寒冰菇、毁灭菇、樱桃炸弹、火爆辣椒、倭瓜、寒冰射手、花盆、坚果
    SelectCards({COFFEE_BEAN, ICE_SHROOM, M_ICE_SHROOM, DOOM_SHROOM, CHERRY_BOMB, JALAPENO, SQUASH, SNOW_PEA, FLOWER_POT, WALL_NUT});
    SetTime(-599, 1);
    // 填充炮列表
    slope_pao.resetPaoList({{2, 1}, {1, 2}, {1, 4}, {3, 1}, {4, 2}, {3, 3}});
    flat_pao.resetPaoList({{3, 5}, {2, 6}, {3, 7}, {2, 4}, {4, 4}, {5, 6}, {4, 7}, {5, 4}});
    // 开始自动存冰
    ice_filler.start({{1, 1}, {2, 3}, {4, 6}, {1, 6}, {1, 7}});
    // 种植临时植物
    Card(FLOWER_POT, 1, 7);
    // 主体节奏 ch4 I3PPDD-Bc-PP|I3PPDD-Bc-PP| 1738|1738 每波执行确定的操作，不考虑非旗帜波的刷新延迟

    // wave1 PPDDDD
    SetTime(372 - 387, 1);
    slope_pao.roofPao(2, 9);
    flat_pao.roofPao(4, 9);
    SetTime(372 + 133 - 387, 1);
    flat_pao.roofPao(1, 9);
    slope_pao.roofPao(4, 9);
    SetTime(372 + 133 + 133 - 387, 1);
    flat_pao.roofPao(1, 8.8375);
    slope_pao.roofPao(4, 8.8375);
    SetTime(372 + 133 + 105 + 2 - 298, 1);
    ice_filler.coffee();

    // wave2 I-ABc-PP
    SetTime(317 - 100, 2);
    Card({{FLOWER_POT, 2, 9}, {CHERRY_BOMB, 2, 9}});
    SetTime(317, 2);
    Shovel(2, 9);
    SetTime(1139 - 387, 2);
    flat_pao.roofPao(4, 8.1);
    SetTime(1231, 2);
    Card(FLOWER_POT, 2, 8);
    SetTime(1231 + 100, 2);
    Shovel(2, 8);
    SetTime(1738 - 200 - 387, 2);
    slope_pao.roofPao(2, 9);
    flat_pao.roofPao(4, 9);
    SetTime(1738 - 200 + 210 - 298, 2);
    Ice3(298);
    ice_filler.coffee();
    ice_filler.resetFillList({{1, 1}, {2, 3}, {4, 6}});

    // wave3 I3PPDD-B-PP
    SetTime(-200 + 210 + 400 - 387, 3);
    slope_pao.roofPao(2, 9);
    flat_pao.roofPao(4, 9);
    SetTime(-200 + 210 + 400 + 216 - 387, 3);
    slope_pao.roofPao(1, 9);
    flat_pao.roofPao(4, 8.575);
    SetTime(1139 - 387, 3);
    flat_pao.roofPao(4, 8.1);
    SetTime(1231, 3);
    Card(FLOWER_POT, 2, 8);
    SetTime(1231 + 100, 3);
    Shovel(2, 8);
    SetTime(1738 - 200 - 387, 3);
    slope_pao.roofPao(2, 9);
    flat_pao.roofPao(4, 9);
    SetTime(1738 - 200 + 210 - 298, 3);
    Ice3(298);
    ice_filler.coffee();

    // wave4 I3PPDD-B-PP
    SetTime(-200 + 210 + 400 - 387, 4);
    slope_pao.roofPao(2, 9);
    flat_pao.roofPao(4, 9);
    SetTime(-200 + 210 + 400 + 216 - 387, 4);
    slope_pao.roofPao(1, 9);
    flat_pao.roofPao(4, 8.575);
    SetTime(1139 - 387, 4);
    flat_pao.roofPao(4, 8.1);
    SetTime(1231, 4);
    Card(FLOWER_POT, 2, 8);
    SetTime(1231 + 100, 4);
    Shovel(2, 8);
    SetTime(1738 - 200 - 387, 4);
    slope_pao.roofPao(2, 9);
    flat_pao.roofPao(4, 9);
    SetTime(1738 - 200 + 210 - 298, 4);
    Ice3(298);
    ice_filler.coffee();

    // wave5 I3PPDD-B-PP
    SetTime(-200 + 210 + 400 - 387, 5);
    slope_pao.roofPao(2, 9);
    flat_pao.roofPao(4, 9);
    SetTime(-200 + 210 + 400 + 216 - 387, 5);
    slope_pao.roofPao(1, 9);
    flat_pao.roofPao(4, 8.575);
    SetTime(1139 - 387, 5);
    flat_pao.roofPao(4, 8.1);
    SetTime(1231, 5);
    Card(FLOWER_POT, 2, 8);
    SetTime(1231 + 100, 5);
    Shovel(2, 8);
    SetTime(1738 - 200 - 387, 5);
    slope_pao.roofPao(2, 9);
    flat_pao.roofPao(4, 9);
    SetTime(1738 - 200 + 210 - 298, 5);
    Ice3(298);
    ice_filler.coffee();

    // wave6 I3PPDD-B-PP
    SetTime(-200 + 210 + 400 - 387, 6);
    slope_pao.roofPao(2, 9);
    flat_pao.roofPao(4, 9);
    SetTime(-200 + 210 + 400 + 216 - 387, 6);
    slope_pao.roofPao(1, 9);
    flat_pao.roofPao(4, 8.575);
    SetTime(1139 - 387, 6);
    flat_pao.roofPao(4, 8.1);
    SetTime(1231, 6);
    Card(FLOWER_POT, 2, 8);
    SetTime(1231 + 100, 6);
    Shovel(2, 8);
    SetTime(1738 - 200 - 387, 6);
    slope_pao.roofPao(2, 9);
    flat_pao.roofPao(4, 9);
    SetTime(1738 - 200 + 210 - 298, 6);
    Ice3(298);
    ice_filler.coffee();

    // wave7 I3PPDD-B-PP
    SetTime(-200 + 210 + 400 - 387, 7);
    slope_pao.roofPao(2, 9);
    flat_pao.roofPao(4, 9);
    SetTime(-200 + 210 + 400 + 216 - 387, 7);
    slope_pao.roofPao(1, 9);
    flat_pao.roofPao(4, 8.575);
    SetTime(1139 - 387, 7);
    flat_pao.roofPao(4, 8.1);
    SetTime(1231, 7);
    Card(FLOWER_POT, 2, 8);
    SetTime(1231 + 100, 7);
    Shovel(2, 8);
    SetTime(1738 - 200 - 387, 7);
    slope_pao.roofPao(2, 9);
    flat_pao.roofPao(4, 9);
    SetTime(1738 - 200 + 210 - 298, 7);
    Ice3(298);
    ice_filler.coffee();

    // wave8 I3PPDD-B-PP
    SetTime(-200 + 210 + 400 - 387, 8);
    slope_pao.roofPao(2, 9);
    flat_pao.roofPao(4, 9);
    SetTime(-200 + 210 + 400 + 216 - 387, 8);
    slope_pao.roofPao(1, 9);
    flat_pao.roofPao(4, 8.575);
    SetTime(1139 - 387, 8);
    flat_pao.roofPao(4, 8.1);
    SetTime(1231, 8);
    Card(FLOWER_POT, 2, 8);
    SetTime(1231 + 250, 8);
    Shovel(2, 8);
    SetTime(1887 - 200 - 387, 8);
    slope_pao.roofPao(2, 9);
    flat_pao.roofPao(4, 9);
    SetTime(1887 - 200 + 210 - 298, 8);
    Ice3(298);
    ice_filler.coffee();

    // wave9 I3PPDD-B-NDD
    SetTime(-200 + 210 + 400 - 387, 9);
    slope_pao.roofPao(2, 9);
    flat_pao.roofPao(4, 9);
    SetTime(-200 + 210 + 400 + 216 - 387, 9);
    slope_pao.roofPao(1, 9);
    flat_pao.roofPao(4, 8.575);
    SetTime(1139 - 387, 9);
    flat_pao.roofPao(4, 8.1);
    SetTime(709, 9);
    Card(FLOWER_POT, 2, 9);
    SetTime(1231 + 100, 9);
    Shovel(2, 8);
    SetTime(1998 - 224 - 280 - 387, 9);
    slope_pao.roofPao(2, 9);
    flat_pao.roofPao(4, 9);
    SetTime(1998 - 224 - 298, 9);
    Card({{FLOWER_POT, 2, 8}, {DOOM_SHROOM, 2, 8}, {COFFEE_BEAN, 2, 8}});
    SetTime(1998 - 387, 9);
    slope_pao.roofPao(1, 9);
    flat_pao.roofPao(4, 9);
    SetTime(2214 - 387, 9);
    slope_pao.roofPao(3, 9);
    flat_pao.roofPao(4, 9);
    SetTime(2214, 9);
    Card(SNOW_PEA, 1, 6);
    InsertTimeOperation(2214, 9, [=]() {
        auto_blocker.pushFunc([]() {
            AutoBlock({{FLOWER_POT}}, {{1, 6}, {1, 7}, {1, 8}});
        });
    });

    SetTime(4500 - 200 - 182 - 751, 9);
    auto_blocker.pause();
    SetTime(4500 - 200 - 182, 9);
    Shovel(1, 6);
    Card({{FLOWER_POT, 1, 6}, {SQUASH, 1, 6}});

    // wave10 PSd/PSD
    SetTime(372 - 387, 10);
    slope_pao.roofPao({{2, 9}, {2, 9}});
    flat_pao.roofPao({{4, 9}, {4, 9}});
    SetTime(372 + 219 - 387, 10);
    slope_pao.roofPao(2, 5);
    SetTime(372 + 165 - 387, 10);
    flat_pao.roofPao(4, 6.5);
    SetTime(601 + 10 - 298, 10);
    ice_filler.coffee();

    // wave11 I-aPA-PPDD
    SetTime(318 - 100, 11);
    Card({{JALAPENO, 1, 6}, {FLOWER_POT, 4, 9}, {CHERRY_BOMB, 4, 9}});
    SetTime(318, 11);
    Shovel(4, 9);
    SetTime(1109 - 387, 11);
    flat_pao.roofPao(3, 8.1);
    SetTime(1738 - 200 - 387, 11);
    slope_pao.roofPao(2, 9);
    flat_pao.roofPao(4, 9);
    SetTime(1738 - 200 + 210 - 298, 11);
    Ice3(298);
    ice_filler.coffee();

    // wave12 I3PPDD-B-PP
    SetTime(-200 + 210 + 400 - 387, 12);
    slope_pao.roofPao(2, 9);
    flat_pao.roofPao(4, 9);
    SetTime(-200 + 210 + 400 + 216 - 387, 12);
    slope_pao.roofPao(1, 9);
    flat_pao.roofPao(4, 8.575);
    SetTime(1139 - 387, 12);
    flat_pao.roofPao(4, 8.1);
    SetTime(1231, 12);
    Card(FLOWER_POT, 2, 8);
    SetTime(1231 + 100, 12);
    Shovel(2, 8);
    SetTime(1738 - 200 - 387, 12);
    slope_pao.roofPao(2, 9);
    flat_pao.roofPao(4, 9);
    SetTime(1738 - 200 + 210 - 298, 12);
    Ice3(298);
    ice_filler.coffee();

    // wave13 I3PPDD-B-PP
    SetTime(-200 + 210 + 400 - 387, 13);
    slope_pao.roofPao(2, 9);
    flat_pao.roofPao(4, 9);
    SetTime(-200 + 210 + 400 + 216 - 387, 13);
    slope_pao.roofPao(1, 9);
    flat_pao.roofPao(4, 8.575);
    SetTime(1139 - 387, 13);
    flat_pao.roofPao(4, 8.1);
    SetTime(1231, 13);
    Card(FLOWER_POT, 2, 8);
    SetTime(1231 + 100, 13);
    Shovel(2, 8);
    SetTime(1738 - 200 - 387, 13);
    slope_pao.roofPao(2, 9);
    flat_pao.roofPao(4, 9);
    SetTime(1738 - 200 + 210 - 298, 13);
    Ice3(298);
    ice_filler.coffee();

    // wave14 I3PPDD-B-PP
    SetTime(-200 + 210 + 400 - 387, 14);
    slope_pao.roofPao(2, 9);
    flat_pao.roofPao(4, 9);
    SetTime(-200 + 210 + 400 + 216 - 387, 14);
    slope_pao.roofPao(1, 9);
    flat_pao.roofPao(4, 8.575);
    SetTime(1139 - 387, 14);
    flat_pao.roofPao(4, 8.1);
    SetTime(1231, 14);
    Card(FLOWER_POT, 2, 8);
    SetTime(1231 + 100, 14);
    Shovel(2, 8);
    SetTime(1738 - 200 - 387, 14);
    slope_pao.roofPao(2, 9);
    flat_pao.roofPao(4, 9);
    SetTime(1738 - 200 + 210 - 298, 14);
    Ice3(298);
    ice_filler.coffee();

    // wave15 I3PPDD-B-PP
    SetTime(-200 + 210 + 400 - 387, 15);
    slope_pao.roofPao(2, 9);
    flat_pao.roofPao(4, 9);
    SetTime(-200 + 210 + 400 + 216 - 387, 15);
    slope_pao.roofPao(1, 9);
    flat_pao.roofPao(4, 8.575);
    SetTime(1139 - 387, 15);
    flat_pao.roofPao(4, 8.1);
    SetTime(1231, 15);
    Card(FLOWER_POT, 2, 8);
    SetTime(1231 + 100, 15);
    Shovel(2, 8);
    SetTime(1738 - 200 - 387, 15);
    slope_pao.roofPao(2, 9);
    flat_pao.roofPao(4, 9);
    SetTime(1738 - 200 + 210 - 298, 15);
    Ice3(298);
    ice_filler.coffee();

    // wave16 I3PPDD-B-PP
    SetTime(-200 + 210 + 400 - 387, 16);
    slope_pao.roofPao(2, 9);
    flat_pao.roofPao(4, 9);
    SetTime(-200 + 210 + 400 + 216 - 387, 16);
    slope_pao.roofPao(1, 9);
    flat_pao.roofPao(4, 8.575);
    SetTime(1139 - 387, 16);
    flat_pao.roofPao(4, 8.1);
    SetTime(1231, 16);
    Card(FLOWER_POT, 2, 8);
    SetTime(1231 + 100, 16);
    Shovel(2, 8);
    SetTime(1738 - 200 - 387, 16);
    slope_pao.roofPao(2, 9);
    flat_pao.roofPao(4, 9);
    SetTime(1738 - 200 + 210 - 298, 16);
    Ice3(298);
    ice_filler.coffee();

    // wave17 I3PPDD-B-PP
    SetTime(-200 + 210 + 400 - 387, 17);
    slope_pao.roofPao(2, 9);
    flat_pao.roofPao(4, 9);
    SetTime(-200 + 210 + 400 + 216 - 387, 17);
    slope_pao.roofPao(1, 9);
    flat_pao.roofPao(4, 8.575);
    SetTime(1139 - 387, 17);
    flat_pao.roofPao(4, 8.1);
    SetTime(1231, 17);
    Card(FLOWER_POT, 2, 8);
    SetTime(1231 + 100, 17);
    Shovel(2, 8);
    SetTime(1738 - 200 - 387, 17);
    slope_pao.roofPao(2, 9);
    flat_pao.roofPao(4, 9);
    SetTime(1738 - 200 + 210 - 298, 17);
    Ice3(298);
    ice_filler.coffee();

    // wave18 I3PPDD-B-PP
    SetTime(-200 + 210 + 400 - 387, 18);
    slope_pao.roofPao(2, 9);
    flat_pao.roofPao(4, 9);
    SetTime(-200 + 210 + 400 + 216 - 387, 18);
    slope_pao.roofPao(1, 9);
    flat_pao.roofPao(4, 8.575);
    SetTime(1139 - 387, 18);
    flat_pao.roofPao(4, 8.1);
    SetTime(1231, 18);
    Card(FLOWER_POT, 2, 8);
    SetTime(1231 + 100, 18);
    Shovel(2, 8);
    SetTime(1887 - 200 - 387, 18);
    slope_pao.roofPao(2, 9);
    flat_pao.roofPao(4, 9);
    SetTime(1887 - 200 + 210 - 298, 18);
    Ice3(298);
    ice_filler.coffee();

    // wave19 I3PPDD-B-NDD
    SetTime(-200 + 210 + 400 - 387, 19);
    slope_pao.roofPao(2, 9);
    flat_pao.roofPao(4, 9);
    SetTime(-200 + 210 + 400 + 216 - 387, 19);
    slope_pao.roofPao(1, 9);
    flat_pao.roofPao(4, 8.575);
    SetTime(1139 - 387, 19);
    flat_pao.roofPao(4, 8.1);
    SetTime(709, 19);
    Card(FLOWER_POT, 2, 9);
    SetTime(1231 + 100, 19);
    Shovel(2, 8);
    SetTime(1998 - 224 - 280 - 387, 19);
    slope_pao.roofPao(2, 9);
    flat_pao.roofPao(4, 9);
    SetTime(1998 - 224 - 298, 19);
    Card({{FLOWER_POT, 2, 8}, {DOOM_SHROOM, 2, 8}, {COFFEE_BEAN, 2, 8}});
    SetTime(1998 - 387, 19);
    slope_pao.roofPao(1, 9);
    flat_pao.roofPao(4, 9);
    SetTime(2214 - 387, 19);
    slope_pao.roofPao(3, 9);
    flat_pao.roofPao(4, 9);
    SetTime(2214, 19);
    Card(SNOW_PEA, 1, 6);
    auto_blocker.goOn();
    SetTime(4500 - 200 - 182 - 751, 19);
    auto_blocker.pause();
    SetTime(4500 - 200 - 182, 19);
    Shovel(1, 6);
    Card({{FLOWER_POT, 1, 6}, {SQUASH, 1, 6}});

    // wave20 PSd/PSD
    SetTime(0 - 299, 20);
    ice_filler.coffee();
    SetTime(372 - 387, 20);
    slope_pao.roofPao({{2, 9}, {2, 9}});
    flat_pao.roofPao({{4, 9}, {4, 9}});
    SetTime(372 + 219 - 387, 20);
    slope_pao.roofPao(2, 5);
    SetTime(372 + 110 - 387, 20);
    flat_pao.roofPao(4, 9);
    SetTime(814 - 387, 20);
    slope_pao.roofPao(3, 9);
    flat_pao.roofPao({{4, 9}, {3, 9}});
    SetTime(375 + 300 - 100, 20);
    Card(JALAPENO, 1, 6);
    SetTime(375 + 300, 20);
    Card(SNOW_PEA, 1, 6);
    SetTime(800, 20);
    Card(FLOWER_POT, 4, 6);
    auto_blocker.goOn();
    SetTime(5500 - 182 - 751, 20);
    auto_blocker.pause();
    SetTime(5500 - 182 - 1000, 20);
    Shovel(1, 6);
    SetTime(5500 - 182, 20);
    Shovel(1, 6);
    Card({{FLOWER_POT, 1, 6}, {SQUASH, 1, 6}});
}
void AutoBlock(std::vector<PlantType> types, std::vector<Grid> pos_list)
{
    auto zombies = GetMainObject()->zombieArray();
    auto seeds = GetMainObject()->seedArray();
    std::vector<int> indices_seed;
    for (PlantType each : types) {
        if (each > IMITATOR)
            indices_seed.emplace_back(GetSeedIndex(each - (IMITATOR + 1), true));
        else
            indices_seed.emplace_back(GetSeedIndex(each, false));
    }
    for (Grid each : pos_list) {
        for (int index = 0; index < GetMainObject()->zombieTotal(); ++index) {
            if (!zombies[index].isDead() && !zombies[index].isDisappeared() && zombies[index].row() + 1 == each.row) {
                if (zombies[index].type() == POLE_VAULTING_ZOMBIE && (zombies[index].abscissa() > each.col * 80 - 51 && zombies[index].abscissa() < each.col * 80 + 40 && zombies[index].state() == 11)) {
                    if (GetPlantIndex(each.row, each.col) >= 0 || GetPlantIndex(each.row, each.col, FLOWER_POT) >= 0)
                        ShovelNotInQueue(each.row, each.col);
                    return;
                }
                if (((zombies[index].type() == GARGANTUAR || zombies[index].type() == GIGA_GARGANTUAR) && (zombies[index].abscissa() > each.col * 80 + 1 - 70 && zombies[index].abscissa() < each.col * 80 + 40 + 1 - 15)) && zombies[index].state() == 0 || (zombies[index].type() == FOOTBALL_ZOMBIE && (zombies[index].abscissa() > each.col * 80 - 80 && zombies[index].abscissa() < each.col * 80 - 40 + 1 - 30))) {
                    for (int index_seed : indices_seed) {
                        if (index_seed >= 0) {
                            if (seeds[index_seed].isUsable() && (GetPlantIndex(each.row, each.col) < 0 && GetPlantIndex(each.row, each.col, FLOWER_POT) < 0) && Asm::getPlantRejectType(FLOWER_POT, each.row - 1, each.col - 1) == Asm::NIL) {
                                CardNotInQueue(index_seed + 1, each.row, each.col);
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
}