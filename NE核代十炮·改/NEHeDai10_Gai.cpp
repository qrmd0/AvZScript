/*
 * @Author: qrmd
 * @Date: 2022-06-02 09:11:13
 * @Last Modified by: qrmd
 * @Last Modified time: 2022-06-02 12:14:46
 * @Description: NE核代十炮·改 演示脚本
 */

#include "avz.h"

using namespace AvZ;
using namespace std;
// 如果[wave]波上半场刷出的僵尸总血量较高，返回2，否则返回4。用于5行场地的智能樱桃消延迟
int GetRowHaveHigherZombieHp(int wave);
// 自动在指定位置放置植物触发巨人僵尸举锤阻挡其前进。结合TickRunner使用
void BlockGargantuar(vector<Grid> pos);
TickRunner block_giga;
Grid grave_pos;
void Script()
{
    // 脚本在游戏主界面和选择植物界面生效
    OpenMultipleEffective('Q', MAIN_UI_OR_FIGHT_UI);
    // 全难度极限出怪：普僵、撑杆、橄榄、舞王、冰车、小丑、矿工、跳跳、小偷、扶梯、投篮、白眼、红眼
    SetZombies({ZOMBIE, POLE_VAULTING_ZOMBIE, FOOTBALL_ZOMBIE, DANCING_ZOMBIE, ZOMBONI, JACK_IN_THE_BOX_ZOMBIE, DIGGER_ZOMBIE, POGO_ZOMBIE, BUNGEE_ZOMBIE, LADDER_ZOMBIE, CATAPULT_ZOMBIE, GARGANTUAR, GIGA_GARGANTUAR});
    // 选择植物：寒冰菇、毁灭菇、墓碑吞噬者、樱桃炸弹、倭瓜、小喷菇、花盆、胆小菇、阳光菇、向日葵
    SelectCards({ICE_SHROOM, DOOM_SHROOM, GRAVE_BUSTER, CHERRY_BOMB, SQUASH, PUFF_SHROOM, FLOWER_POT, SCAREDY_SHROOM, SUN_SHROOM, SUNFLOWER});
    SetTime(-599, 1);
    Shovel({{1, 7}, {2, 7}, {3, 7}, {4, 7}, {5, 7}});
    // 开始自动垫巨人僵尸
    block_giga.pushFunc([]() {
        BlockGargantuar({{1, 7}, {2, 7}, {3, 7}, {4, 7}, {5, 7}});
    });
    // 自动填充炮列表
    pao_operator.autoGetPaoList();
    // 主体节奏 P6-N PP|PP|PP|PP|PP|N 601|601|601|601|601|601 每波执行确定的操作，不考虑非旗帜波的刷新延迟
    // wave1 PP
    SetTime(341 - 376, 1);
    pao_operator.pao({{2, 9}, {4, 9}});
    // wave2 PP
    SetTime(341 - 376, 2);
    pao_operator.pao({{2, 9}, {4, 9}});
    // wave3 PP
    SetTime(341 - 376, 3);
    pao_operator.pao({{2, 9}, {4, 9}});
    // wave4 PP
    SetTime(341 - 376, 4);
    pao_operator.pao({{2, 9}, {4, 9}});
    // wave5 PP
    SetTime(341 - 376, 5);
    pao_operator.pao({{2, 9}, {4, 9}});
    // wave6 N
    SetTime(341 - 100, 6);
    Card(DOOM_SHROOM, 3, 9);
    // wave7 PP
    SetTime(341 - 376, 7);
    pao_operator.pao({{2, 9}, {4, 9}});
    // wave8 PP
    SetTime(341 - 376, 8);
    pao_operator.pao({{2, 9}, {4, 9}});
    // wave9 PP-(PP-PP-PP)
    SetTime(341 - 376, 9);
    pao_operator.pao({{2, 9}, {4, 9}});
    pao_operator.recoverPao({{2, 9}, {4, 9}, {2, 9}, {4, 9}, {2, 9}, {4, 9}});
    // wave10 PP
    SetTime(500, 10);
    Shovel({{1, 7}, {2, 7}, {3, 7}, {4, 7}, {5, 7}});
    SetTime(341 - 376, 10);
    pao_operator.pao({{2, 9}, {4, 9}});
    // 冰杀蹦极
    SetTime(601 - 1 - 100, 10);
    Card(ICE_SHROOM, 1, 9);
    // 智能樱桃消延迟
    InsertTimeOperation(401, 10, [=]() {
        if (GetRunningWave() == 10) {
            SetTime(401, 10);
            Card(CHERRY_BOMB, GetRowHaveHigherZombieHp(10), 9);
        }
    });
    // wave11 PP
    SetTime(341 - 376, 11);
    pao_operator.pao({{2, 9}, {4, 9}});
    // wave12 PP
    SetTime(341 - 376, 12);
    pao_operator.pao({{2, 9}, {4, 9}});
    // wave13 PP
    SetTime(341 - 376, 13);
    pao_operator.pao({{2, 9}, {4, 9}});
    // wave14 PP
    SetTime(341 - 376, 14);
    pao_operator.pao({{2, 9}, {4, 9}});
    // wave15 N
    SetTime(341 - 100, 15);
    Card(DOOM_SHROOM, 3, 8);
    // wave16 PP
    SetTime(341 - 376, 16);
    pao_operator.pao({{2, 9}, {4, 9}});
    // wave17 PP
    SetTime(341 - 376, 17);
    pao_operator.pao({{2, 9}, {4, 9}});
    // wave18 PP
    SetTime(341 - 376, 18);
    pao_operator.pao({{2, 9}, {4, 9}});
    // wave19 PP-(PP-PP-PP)
    SetTime(341 - 376, 19);
    pao_operator.pao({{2, 9}, {4, 9}});
    pao_operator.recoverPao({{2, 9}, {4, 9}, {2, 9}, {4, 9}, {2, 9}, {4, 9}});
    // wave20 PP-(PP-PP-PP)
    SetTime(500, 20);
    Shovel({{1, 7}, {2, 7}, {3, 7}, {4, 7}, {5, 7}});
    // 利用墓碑吞噬者能否放置确定w20生成的墓碑的位置
    InsertTimeOperation(113, 20, [=]() mutable {
        vector<Grid> grave_generate_pos = {{1, 7}, {2, 7}, {3, 7}, {4, 7}, {5, 7}, {1, 8}, {2, 8}, {3, 8}, {4, 8}, {5, 8}, {1, 9}, {2, 9}, {3, 9}, {4, 9}, {5, 9}};
        for (Grid each : grave_generate_pos) {
            if (Asm::getPlantRejectType(GRAVE_BUSTER, each.row - 1, each.col - 1) == Asm::NIL) {
                grave_pos = each;
                break;
            }
        }
    });
    InsertTimeOperation(395 - 100, 20, [=]() {
        // 冰杀蹦极
        SetTime(395 - 100, 20);
        if (grave_pos.row == 1 && grave_pos.col == 9) {
            Card(ICE_SHROOM, 1, 8);
        } else {
            Card(ICE_SHROOM, 1, 9);
        }
        // 消除墓碑
        SetTime(396, 20);
        Card(GRAVE_BUSTER, grave_pos.row, grave_pos.col);
        // 从7列及其以左的墓碑中钻出的僵尸不会被炸到，用倭瓜消灭
        if (grave_pos.col <= 7) {
            SetTime(396 + 480, 20);
            Card(SQUASH, grave_pos.row, grave_pos.col);
        }
    });
    SetTime(341 - 376, 20);
    pao_operator.pao({{2, 9}, {4, 9}});
    pao_operator.recoverPao({{2, 9}, {4, 9}, {2, 9}, {4, 9}, {2, 9}, {4, 9}});
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
        vector<int> indices_seed = {GetSeedIndex(PUFF_SHROOM), GetSeedIndex(PUFF_SHROOM, true), GetSeedIndex(SUN_SHROOM), GetSeedIndex(FLOWER_POT), GetSeedIndex(SCAREDY_SHROOM), GetSeedIndex(SUNFLOWER), GetSeedIndex(GARLIC), GetSeedIndex(FUME_SHROOM)};
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