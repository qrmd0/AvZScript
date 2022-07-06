/*
 * @Author: qrmd
 * @Date: 2022-06-01 13:22:56
 * @Last Modified by: qrmd
 * @Last Modified time: 2022-06-01 13:22:56
 * @Description: FE神之四炮 演示脚本
 */

#include "avz.h"

using namespace AvZ;
using namespace std;
// 自动在[row]行[col]列种植三叶草清除浓雾。结合TickRunner使用
void CleanFog(int row, int col);
TickRunner fog_cleaner;
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
    // 选择植物：睡莲叶、寒冰菇、模仿寒冰菇、毁灭菇、三叶草、南瓜头、樱桃炸弹、小喷菇、花盆、胆小菇
    SelectCards({LILY_PAD, ICE_SHROOM, M_ICE_SHROOM, DOOM_SHROOM, BLOVER, PUMPKIN, CHERRY_BOMB, PUFF_SHROOM, FLOWER_POT, SCAREDY_SHROOM});
    SetTime(-599, 1);
    Card(LILY_PAD, 3, 7);
    Shovel({{2, 6}, {5, 6}, {1, 3}, {6, 3}, {1, 2}, {6, 2}, {1, 1}, {6, 1}});
    // 开始自动清除浓雾
    fog_cleaner.pushFunc([]() {
        CleanFog(2, 1);
    });
    // 开始自动垫巨人僵尸
    block_giga.pushFunc([]() {
        BlockGargantuar({{2, 6}, {5, 6}, {1, 3}, {6, 3}, {1, 2}, {6, 2}, {1, 1}, {6, 1}});
    });
    // 开始自动修补南瓜头
    plant_fixer.start(PUMPKIN, {{3, 5}, {3, 6}, {4, 5}, {4, 6}}, 1200);
    // 自动填充炮列表
    pao_operator.autoGetPaoList();
    // 主体节奏 邻C6u I-PP|I-PP|N|PP 1738|1738|869|869 每波执行确定的操作，不考虑非旗帜波的刷新延迟
    // wave1 PP 首代
    SetTime(486 - 373, 1);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    // wave2 I-PP
    SetTime(-99, 2);
    Card(ICE_SHROOM, 3, 7);
    SetTime(1538 - 373, 2);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    // wave3 I-PP
    SetTime(-200, 3);
    Card(M_ICE_SHROOM, 3, 7);
    SetTime(1538 - 373, 3);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    // wave4 N
    SetTime(669 - 100, 4);
    Card(LILY_PAD, 3, 9);
    Card(DOOM_SHROOM, 3, 9);
    // wave5 PP
    SetTime(669 - 373, 5);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    // wave6 I-PP
    SetTime(-99, 6);
    Card(ICE_SHROOM, 3, 7);
    SetTime(1538 - 373, 6);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    // wave7 I-PP
    SetTime(-200, 7);
    Card(M_ICE_SHROOM, 3, 7);
    SetTime(1538 - 373, 7);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    // wave8 N
    SetTime(669 - 100, 8);
    Card(LILY_PAD, 4, 9);
    Card(DOOM_SHROOM, 4, 9);
    // wave9 PP-(PP-cc)
    SetTime(669 - 373, 9);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    pao_operator.recoverPao({{2, 7}, {5, 7}});
    // wave10 PP
    SetTime(500, 10);
    Shovel({{2, 6}, {5, 6}, {1, 3}, {6, 3}, {1, 2}, {6, 2}, {1, 1}, {6, 1}});
    SetTime(341 - 376, 10);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    // 智能樱桃消中场延迟
    InsertTimeOperation(373, 10, [=]() {
        SetTime(373, 10);
        Card(CHERRY_BOMB, GetRowHaveHigherZombieHp(10), 9);
    });
    // wave11 I-PP
    SetTime(-99, 11);
    Card(ICE_SHROOM, 3, 7);
    SetTime(1538 - 373, 11);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    // wave12 I-PP
    SetTime(-200, 12);
    Card(M_ICE_SHROOM, 3, 7);
    SetTime(1538 - 373, 12);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    // wave13 N
    SetTime(669 - 100, 13);
    Card(LILY_PAD, 3, 8);
    Card(DOOM_SHROOM, 3, 8);
    // wave14 PP
    SetTime(669 - 373, 14);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    // wave15 I-PP
    SetTime(-99, 15);
    Card(ICE_SHROOM, 3, 7);
    SetTime(1538 - 373, 15);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    // wave16 I-PP
    SetTime(-200, 16);
    Card(M_ICE_SHROOM, 3, 7);
    SetTime(1538 - 373, 16);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    // wave17 N
    SetTime(669 - 100, 17);
    Card(LILY_PAD, 4, 8);
    Card(DOOM_SHROOM, 4, 8);
    // wave18 PP
    SetTime(669 - 373, 18);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    // wave19 I-PP-(PP-cc)
    SetTime(-99, 19);
    Card(ICE_SHROOM, 3, 7);
    SetTime(1538 - 373, 19);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    pao_operator.recoverPao({{2, 7}, {5, 7}});
    // wave20 PP-(PP-PP)
    SetTime(500, 20);
    Shovel({{2, 6}, {5, 6}, {1, 3}, {6, 3}, {1, 2}, {6, 2}, {1, 1}, {6, 1}});
    SetTime(395 - 319 - 100, 20);
    Card(M_ICE_SHROOM, 3, 7);
    SetTime(341 - 376, 20);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    pao_operator.recoverPao({{2, 8.8}, {5, 8.8}, {2, 7}, {5, 7}});
    SetTime(396, 20);
    Shovel(3, 7);
}
void CleanFog(int row, int col)
{
    // 浓雾未蔓延至可见区域的最小倒计时
    const int min_countdown_invisible_fog = 1556;
    // 三叶草生效时长
    const int time_blover_activate = 100;
    // 浓雾倒计时
    int countdown_fog = ReadMemory<int>(0x6A9EC0, 0x768, 0x5D4);
    auto seeds = GetMainObject()->seedArray();
    int index_blover = GetSeedIndex(BLOVER);
    if (countdown_fog - time_blover_activate < min_countdown_invisible_fog && seeds[index_blover].isUsable()) {
        CardNotInQueue(index_blover + 1, row, col);
    }
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
    auto zombies = GetMainObject()->zombieArray();
    auto seeds = GetMainObject()->seedArray();
    vector<int> indices_seed = {GetSeedIndex(PUFF_SHROOM), GetSeedIndex(PUFF_SHROOM, true), GetSeedIndex(SUN_SHROOM), GetSeedIndex(FLOWER_POT), GetSeedIndex(SCAREDY_SHROOM), GetSeedIndex(SUNFLOWER), GetSeedIndex(GARLIC), GetSeedIndex(FUME_SHROOM)};
    for (Grid each : pos) {
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