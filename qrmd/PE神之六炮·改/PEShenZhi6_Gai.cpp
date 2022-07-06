/*
 * @Author: qrmd
 * @Date: 2022-06-02 22:34:31
 * @Last Modified by: qrmd
 * @Last Modified time: 2022-06-02 22:34:31
 * @Description: PE神之六炮·改 演示脚本
 */

#include "avz.h"

using namespace AvZ;
using namespace std;
// 如果[wave]波上半场刷出的僵尸总血量较高，返回2，否则返回5。用于6行场地的智能樱桃消延迟
int GetRowHaveHigherZombieHp(int wave);
// 自动在指定位置放置植物触发巨人僵尸举锤阻挡其前进。结合TickRunner使用
void BlockGargantuar(vector<Grid> pos);
TickRunner block_giga;
void Script()
{
    // 脚本在游戏主界面和选择植物界面生效
    OpenMultipleEffective('Q', MAIN_UI_OR_FIGHT_UI);
    // 全难度极限出怪：普僵、撑杆、橄榄、舞王、冰车、小丑、矿工、跳跳、小偷、扶梯、投篮、白眼、红眼、海豚
    SetZombies({ZOMBIE, POLE_VAULTING_ZOMBIE, FOOTBALL_ZOMBIE, DANCING_ZOMBIE, ZOMBONI, JACK_IN_THE_BOX_ZOMBIE, DIGGER_ZOMBIE, POGO_ZOMBIE, BUNGEE_ZOMBIE, LADDER_ZOMBIE, CATAPULT_ZOMBIE, GARGANTUAR, GIGA_GARGANTUAR, DOLPHIN_RIDER_ZOMBIE});
    // 选择植物：咖啡豆、寒冰菇、模仿寒冰菇、高坚果、睡莲叶、樱桃炸弹、叶子保护伞、小喷菇、花盆、胆小菇
    SelectCards({COFFEE_BEAN, ICE_SHROOM, M_ICE_SHROOM, TALL_NUT, LILY_PAD, CHERRY_BOMB, UMBRELLA_LEAF, PUFF_SHROOM, FLOWER_POT, SCAREDY_SHROOM});
    SetTime(-599, 1);
    // 开始自动修补高坚果
    plant_fixer.start(TALL_NUT, {{3, 7}, {4, 7}}, 1200);
    // 开始自动垫巨人僵尸
    block_giga.pushFunc([]() {
        BlockGargantuar({{2, 6}, {5, 6}, {1, 3}, {6, 3}, {1, 2}, {6, 2}, {1, 1}, {6, 1}});
    });
    // 填充炮列表
    pao_operator.resetPaoList({{3, 1}, {4, 1}, {3, 3}, {4, 3}, {3, 5}, {4, 5}});
    // 主体节奏 S4 PP|PP|I-PP 869|869|1737 每波执行确定的操作，不考虑非旗帜波的刷新延迟
    // wave1 PP 首代
    SetTime(341 - 376, 1);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    // wave2 PP
    SetTime(669 - 373, 2);
    pao_operator.pao({{2, 8.6}, {5, 8.6}});
    // wave3 PP
    SetTime(669 - 373, 3);
    pao_operator.pao({{2, 8.6}, {5, 8.6}});
    // wave4 I-PP
    SetTime(-200, 4);
    Card(ICE_SHROOM, 1, 5);
    Card(COFFEE_BEAN, 1, 5);
    SetTime(1537 - 373, 4);
    pao_operator.pao({{2, 8.6}, {5, 8.6}});
    // wave5 PP
    SetTime(669 - 373, 5);
    pao_operator.pao({{2, 8.6}, {5, 8.6}});
    // wave6 PP
    SetTime(669 - 373, 6);
    pao_operator.pao({{2, 8.6}, {5, 8.6}});
    SetTime(601 - 200 - 320, 6);
    Card(M_ICE_SHROOM, 1, 5);
    // wave7 I-PP
    SetTime(-200, 7);
    Card(COFFEE_BEAN, 1, 5);
    SetTime(1537 - 373, 7);
    pao_operator.pao({{2, 8.6}, {5, 8.6}});
    // wave8 PP
    SetTime(669 - 373, 8);
    pao_operator.pao({{2, 8.6}, {5, 8.6}});
    // wave9 PP-(-PP-PP)
    SetTime(669 - 373, 9);
    pao_operator.pao({{2, 8.6}, {5, 8.6}});
    pao_operator.recoverPao({{2, 8.6}, {5, 8.6}, {2, 7}, {5, 7}});
    // wave10 PP
    // 岸路临时放置叶子保护伞防止5列忧郁菇被蹦极僵尸抱走
    SetTime(300 - 751, 10);
    Card(UMBRELLA_LEAF, 2, 6);
    SetTime(300, 10);
    Card(UMBRELLA_LEAF, 5, 6);
    SetTime(450, 10);
    Shovel({{2, 6}, {5, 6}});
    SetTime(669 - 373, 10);
    pao_operator.pao({{2, 8.6}, {5, 8.6}});
    // 智能樱桃消中场延迟
    InsertTimeOperation(669 + 3 + 1, 10, [=]() {
        if (GetRunningWave() == 10) {
            SetTime(669 + 3 + 1, 10);
            Card(CHERRY_BOMB, GetRowHaveHigherZombieHp(10), 9);
        }
    });
    // wave11 PP
    SetTime(669 - 373, 11);
    pao_operator.pao({{2, 8.6}, {5, 8.6}});
    // wave12 PP
    SetTime(669 - 373, 12);
    pao_operator.pao({{2, 8.6}, {5, 8.6}});
    // wave13 I-PP
    SetTime(-200, 13);
    Card(ICE_SHROOM, 1, 5);
    Card(COFFEE_BEAN, 1, 5);
    SetTime(1537 - 373, 13);
    pao_operator.pao({{2, 8.6}, {5, 8.6}});
    // wave14 PP
    SetTime(669 - 373, 14);
    pao_operator.pao({{2, 8.6}, {5, 8.6}});
    // wave15 PP
    SetTime(669 - 373, 15);
    pao_operator.pao({{2, 8.6}, {5, 8.6}});
    SetTime(601 - 200 - 320, 15);
    Card(M_ICE_SHROOM, 1, 5);
    // wave16 I-PP
    SetTime(-200, 16);
    Card(COFFEE_BEAN, 1, 5);
    SetTime(1537 - 373, 16);
    pao_operator.pao({{2, 8.6}, {5, 8.6}});
    // wave17 PP
    SetTime(669 - 373, 17);
    pao_operator.pao({{2, 8.6}, {5, 8.6}});
    // wave18 PP
    SetTime(669 - 373, 18);
    pao_operator.pao({{2, 8.6}, {5, 8.6}});
    // wave19 I-PP-(PP-PP)
    SetTime(-200, 19);
    Card(ICE_SHROOM, 1, 5);
    Card(COFFEE_BEAN, 1, 5);
    SetTime(1537 - 373, 19);
    pao_operator.pao({{2, 8.6}, {5, 8.6}});
    pao_operator.recoverPao({{2, 8.6}, {5, 8.6}, {2, 7}, {5, 7}});
    SetTime(1800, 19);
    Card(M_ICE_SHROOM, 2, 1);
    // wave20 PP-(PP-PP)
    // 岸路临时放置叶子保护伞防止5列忧郁菇被蹦极僵尸抱走
    SetTime(300 - 751, 20);
    Card(UMBRELLA_LEAF, 2, 6);
    SetTime(300, 20);
    Card(UMBRELLA_LEAF, 5, 6);
    SetTime(450, 20);
    Shovel({{2, 6}, {5, 6}});
    // 冰消珊瑚
    SetTime(-99 - 298, 20);
    Card(COFFEE_BEAN, 2, 1);
    SetTime(669 - 373, 20);
    pao_operator.pao({{2, 8.6}, {5, 8.6}});
    SetTime(669 + 869 - 373, 20);
    pao_operator.pao({{2, 8.6}, {5, 8.6}});
    pao_operator.recoverPao({{2, 8.6}, {5, 8.6}});
}
void PlantToBlockTheZombies(int time, int wave, std::vector<int> zombie_types, int row, int shovel_time)
{
    InsertTimeOperation(time, wave, [=]() {
        auto zombies = GetMainObject()->zombieArray();
        bool is_exist_the_zombie = false;
        for (int index = 0; index < GetMainObject()->zombieTotal(); ++index) {
            if (zombies[index].row() == row - 1 && !zombies[index].isDisappeared() && !zombies[index].isDead()) {
                for (int type : zombie_types) {
                    if (zombies[index].type() == type) {
                        is_exist_the_zombie = true;
                        goto END;
                    }
                }
            }
        }
    END:
        auto seeds = GetMainObject()->seedArray();
        int index_seeds[] = {GetSeedIndex(PUFF_SHROOM), GetSeedIndex(PUFF_SHROOM, true), GetSeedIndex(SUN_SHROOM), GetSeedIndex(FLOWER_POT), GetSeedIndex(SCAREDY_SHROOM), GetSeedIndex(SUNFLOWER), GetSeedIndex(GARLIC), GetSeedIndex(FUME_SHROOM), GetSeedIndex(KERNEL_PULT), GetSeedIndex(CABBAGE_PULT)};
        if (is_exist_the_zombie) {
            for (int index : index_seeds) {
                if (index < 0) {
                    continue;
                }
                if (seeds[index].isUsable()) {
                    SetTime(time, wave);
                    Card(index + 1, row, 9);
                    SetTime(time + shovel_time, wave);
                    Shovel(row, 9);
                    break;
                }
            }
        }
        switch (row) {
        case 1:
            PlantToBlockTheZombies(time, wave, zombie_types, 2, shovel_time);
            break;
        case 2:
            PlantToBlockTheZombies(time, wave, zombie_types, 5, shovel_time);
            break;
        case 5:
            PlantToBlockTheZombies(time, wave, zombie_types, 6, shovel_time);
            break;
        default:
            return;
            break;
        }
    });
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