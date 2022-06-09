/*
 * @Author: qrmd
 * @Date: 2022-06-03 16:21:53
 * @Last Modified by: qrmd
 * @Last Modified time: 2022-06-03 16:21:53
 * @Description: RE天台十炮 演示脚本
 */

#include "avz.h"

using namespace AvZ;
using namespace std;
// 后场风炮
PaoOperator slope_cannon;
// 前场平地炮
PaoOperator flat_cannon;

// 如果[wave]波上半场刷出的僵尸总血量较高，返回2，否则返回4。用于5行场地的智能樱桃消延迟
int GetRowHaveHigherZombieHp(int wave);
// 自动在指定位置放置植物触发巨人僵尸举锤阻挡其前进。结合TickRunner使用
void BlockGargantuar(vector<Grid> pos);
TickRunner block_giga;
void Script()
{
    // 脚本在游戏主界面和选择植物界面生效
    OpenMultipleEffective('Q', MAIN_UI_OR_FIGHT_UI);
    // 全难度极限出怪：普僵、撑杆、橄榄、冰车、小丑、跳跳、小偷、扶梯、投篮、白眼、红眼
    SetZombies({ZOMBIE, POLE_VAULTING_ZOMBIE, FOOTBALL_ZOMBIE, ZOMBONI, JACK_IN_THE_BOX_ZOMBIE, POGO_ZOMBIE, BUNGEE_ZOMBIE, LADDER_ZOMBIE, CATAPULT_ZOMBIE, GARGANTUAR, GIGA_GARGANTUAR});
    // 选择植物：花盆、模仿花盆、咖啡豆、寒冰菇、毁灭菇、樱桃炸弹、倭瓜、三叶草、小喷菇、胆小菇
    SelectCards({FLOWER_POT, M_FLOWER_POT, COFFEE_BEAN, ICE_SHROOM, DOOM_SHROOM, CHERRY_BOMB, SQUASH, BLOVER, PUFF_SHROOM, SCAREDY_SHROOM});
    SetTime(-599, 1);
    // 填充炮列表
    slope_cannon.resetPaoList({{1, 1}, {2, 1}, {3, 1}, {4, 1}, {5, 1}});
    flat_cannon.resetPaoList({{1, 6}, {2, 6}, {3, 6}, {4, 6}, {5, 6}});
    // 开始自动垫巨人僵尸
    block_giga.pushFunc([]() {
        BlockGargantuar({{5, 8}, {4, 8}, {3, 8}, {2, 8}, {1, 8}});
    });
    // 主体节奏 P5 PP|PP|PP|PP|PP 695|695|695|695|695 每波执行确定的操作，不考虑非旗帜波的刷新延迟
    // wave1 PP
    SetTime(495 - 387, 1);
    slope_cannon.roofPao(2, 9);
    flat_cannon.roofPao(4, 9);
    // wave2 PP
    SetTime(495 - 387, 2);
    slope_cannon.roofPao(2, 9);
    flat_cannon.roofPao(4, 9);
    // wave3 PP
    SetTime(495 - 387, 3);
    slope_cannon.roofPao(2, 9);
    flat_cannon.roofPao(4, 9);
    // wave4 PP
    SetTime(495 - 387, 4);
    slope_cannon.roofPao(2, 9);
    flat_cannon.roofPao(4, 9);
    // wave5 PP
    SetTime(495 - 387, 5);
    slope_cannon.roofPao(2, 9);
    flat_cannon.roofPao(4, 9);
    // wave6 PP
    SetTime(495 - 387, 6);
    slope_cannon.roofPao(2, 9);
    flat_cannon.roofPao(4, 9);
    // wave7 PP
    SetTime(495 - 387, 7);
    slope_cannon.roofPao(2, 9);
    flat_cannon.roofPao(4, 9);
    // wave8 PP
    SetTime(495 - 387, 8);
    slope_cannon.roofPao(2, 9);
    flat_cannon.roofPao(4, 9);
    // wave9 PP-(PP-PP)
    SetTime(495 - 387, 9);
    slope_cannon.roofPao(2, 9);
    flat_cannon.roofPao(4, 9);
    slope_cannon.recoverPao({{2, 9}, {2, 9}});
    flat_cannon.recoverPao({{4, 9}, {4, 9}});
    // wave10 PP
    SetTime(495 - 387, 10);
    slope_cannon.roofPao(2, 9);
    flat_cannon.roofPao(4, 9);
    // 智能樱桃消中场延迟
    InsertTimeOperation(495 + 1, 10, [=]() {
        SetTime(495 + 1, 10);
        if (GetRunningWave() == 10) {
            int row = GetRowHaveHigherZombieHp(10);
            Card(FLOWER_POT, row, 9);
            Card(CHERRY_BOMB, row, 9);
        }
    });
    // wave11 PP
    SetTime(495 - 387, 11);
    slope_cannon.roofPao(2, 9);
    flat_cannon.roofPao(4, 9);
    // wave12 PP
    SetTime(495 - 387, 12);
    slope_cannon.roofPao(2, 9);
    flat_cannon.roofPao(4, 9);
    // wave13 PP
    SetTime(495 - 387, 13);
    slope_cannon.roofPao(2, 9);
    flat_cannon.roofPao(4, 9);
    // wave14 PP
    SetTime(495 - 387, 14);
    slope_cannon.roofPao(2, 9);
    flat_cannon.roofPao(4, 9);
    // wave15 PP
    SetTime(495 - 387, 15);
    slope_cannon.roofPao(2, 9);
    flat_cannon.roofPao(4, 9);
    // wave16 PP
    SetTime(495 - 387, 16);
    slope_cannon.roofPao(2, 9);
    flat_cannon.roofPao(4, 9);
    // wave17 PP
    SetTime(495 - 387, 17);
    slope_cannon.roofPao(2, 9);
    flat_cannon.roofPao(4, 9);
    // wave18 PP
    SetTime(495 - 387, 18);
    slope_cannon.roofPao(2, 9);
    flat_cannon.roofPao(4, 9);
    // wave19 PP-(PP-PP)
    SetTime(495 - 387, 19);
    slope_cannon.roofPao(2, 9);
    flat_cannon.roofPao(4, 9);
    slope_cannon.recoverPao({{2, 9}, {2, 9}});
    flat_cannon.recoverPao({{4, 9}, {4, 9}});
    // wave20 PP-(PP-PP)
    // 冰消空降
    InsertTimeOperation(-1 - 298 - 320, 20, [=]() {
        auto seeds = GetMainObject()->seedArray();
        int index_flower_pot = GetSeedIndex(FLOWER_POT);
        SetTime(-1 - 298 - 320, 20);
        if (Asm::getPlantRejectType(FLOWER_POT, 1 - 1, 8 - 1) == Asm::NIL) {
            if (seeds[index_flower_pot].isUsable()) {
                Card(FLOWER_POT, 1, 8);
            } else {
                Card(M_FLOWER_POT, 1, 8);
            }
        }
        SetTime(-1 - 298, 20);
        Card(ICE_SHROOM, 1, 8);
        Card(COFFEE_BEAN, 1, 8);
    });
    SetTime(495 - 387, 20);
    slope_cannon.roofPao(2, 9);
    flat_cannon.roofPao(4, 9);
    SetTime(495 + 695 - 387, 20);
    slope_cannon.roofPao(2, 9);
    flat_cannon.roofPao(4, 9);
    slope_cannon.recoverPao({{2, 9}});
    flat_cannon.recoverPao({{4, 9}});
}
int GetRowHaveHigherZombieHp(int wave)
{
    auto zombies = GetMainObject()->zombieArray();
    int hp_of_up_ground_zombies = 0;
    int hp_of_down_ground_zombies = 0;
    for (int index = 0; index < GetMainObject()->zombieTotal(); ++index) {
        if (!zombies[index].isDead() && !zombies[index].isDisappeared() && zombies[index].existTime() <= NowTime(wave)) {
            if (zombies[index].row() + 1 <= 2) {
                hp_of_up_ground_zombies += zombies[index].hp() + zombies[index].oneHp() + zombies[index].twoHp() / 5;
            } else if (zombies[index].row() + 1 >= 4) {
                hp_of_down_ground_zombies += zombies[index].hp() + zombies[index].oneHp() + zombies[index].twoHp() / 5;
            }
        }
    }
    if (hp_of_up_ground_zombies > hp_of_down_ground_zombies) {
        return 2;
    } else {
        return 4;
    }
}
void BlockGargantuar(vector<Grid> pos)
{
    for (Grid each : pos) {
        auto zombies = GetMainObject()->zombieArray();
        auto seeds = GetMainObject()->seedArray();
        vector<int> indices_seed = {GetSeedIndex(FLOWER_POT), GetSeedIndex(FLOWER_POT, true)};
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