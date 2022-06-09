/*
 * @Author: qrmd
 * @Date: 2022-06-03 11:23:06
 * @Last Modified by: qrmd
 * @Last Modified time: 2022-06-03 16:11:08
 * @Description: PE玉米八炮 演示脚本
 */

#include "avz.h"

using namespace AvZ;
using namespace std;
// 如果[wave]波上半场刷出的僵尸总血量较高，返回2，否则返回5。用于6行场地的智能樱桃消延迟
int GetRowHaveHigherZombieHp(int wave);
// 自动在指定位置放置植物触发巨人僵尸举锤阻挡其前进。结合TickRunner使用
void BlockGargantuar(vector<Grid> pos);
TickRunner block_giga;
// 在[wave]波[time]厘秒，如果陆路存在列表[zombie_types]中的僵尸，选择阳光消耗较低的植物放置在对应路的9列并在[shovel_time]厘秒后铲除
void PlantToBlockTheZombies(int time, int wave, std::vector<int> zombie_types, int row = 1, int shovel_time = 79);
void Script()
{
    // 脚本在游戏主界面和选择植物界面生效
    OpenMultipleEffective('Q', MAIN_UI_OR_FIGHT_UI);
    // 全难度极限出怪：普僵、撑杆、橄榄、舞王、冰车、小丑、矿工、跳跳、小偷、扶梯、投篮、白眼、红眼、海豚
    SetZombies({ZOMBIE, POLE_VAULTING_ZOMBIE, FOOTBALL_ZOMBIE, DANCING_ZOMBIE, ZOMBONI, JACK_IN_THE_BOX_ZOMBIE, DIGGER_ZOMBIE, POGO_ZOMBIE, BUNGEE_ZOMBIE, LADDER_ZOMBIE, CATAPULT_ZOMBIE, GARGANTUAR, GIGA_GARGANTUAR, DOLPHIN_RIDER_ZOMBIE});
    // 选择植物：咖啡豆、寒冰菇、模仿寒冰菇、南瓜头、樱桃炸弹、小喷菇、胆小菇、花盆、阳光菇、向日葵
    SelectCards({COFFEE_BEAN, ICE_SHROOM, M_ICE_SHROOM, PUMPKIN, CHERRY_BOMB, PUFF_SHROOM, SCAREDY_SHROOM, FLOWER_POT, SUN_SHROOM, SUNFLOWER});
    SetTime(-599, 1);
    Shovel({{1, 8}, {2, 8}, {5, 8}, {6, 8}});
    // 开始自动存冰
    ice_filler.start({{3, 6}, {4, 6}});
    // 开始自动修补南瓜头
    plant_fixer.start(PUMPKIN, {{1, 1}, {2, 1}, {5, 1}, {6, 1}}, 1200);
    // 填充炮列表
    pao_operator.resetPaoList({{1, 6}, {6, 6}, {2, 6}, {5, 6}, {3, 1}, {4, 1}, {3, 3}, {4, 3}});
    // 主体节奏 ch6 PP|I-PP|PP|I-PP 601|1202|601|1202 每波执行确定的操作，不考虑非旗帜波的刷新延迟
    // wave1 PP 首代
    SetTime(341 - 376, 1);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    // wave2 PP
    SetTime(341 - 376, 2);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    // wave3 I-PP
    SetTime(-200, 3);
    ice_filler.coffee();
    SetTime(1002 - 373, 3);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    // wave4 PP
    SetTime(341 - 376, 4);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    // wave5 I-PP
    SetTime(-200, 5);
    ice_filler.coffee();
    SetTime(1002 - 373, 5);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    // wave6 PP
    SetTime(341 - 376, 6);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    // wave7 I-PP
    SetTime(-200, 7);
    ice_filler.coffee();
    SetTime(1002 - 373, 7);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    // wave8 PP
    SetTime(341 - 376, 8);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    // wave9 I-PP-(-PP-PP-PP)
    SetTime(-200, 9);
    ice_filler.coffee();
    SetTime(1002 - 373, 9);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    pao_operator.recoverPao({{2, 8.8}, {5, 8.8}, {2, 8.8}, {5, 8.8}, {2, 8.8}, {5, 8.8}});
    // 开始自动垫巨人僵尸
    InsertTimeOperation(1002, 9, [=]() {
        block_giga.pushFunc([]() {
            BlockGargantuar({{1, 8}, {2, 8}, {5, 8}, {6, 8}});
        });
    });
    // wave10 PP
    SetTime(500, 10);
    Shovel({{1, 8}, {2, 8}, {5, 8}, {6, 8}});
    block_giga.stop();
    PlantToBlockTheZombies(191, 10, {DANCING_ZOMBIE});
    SetTime(410 - 373, 10);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    // 智能樱桃消中场延迟
    InsertTimeOperation(373, 10, [=]() {
        SetTime(373, 10);
        Card(CHERRY_BOMB, GetRowHaveHigherZombieHp(10), 9);
    });
    // wave11 I-PP
    SetTime(675 - 298, 10);
    ice_filler.coffee();
    SetTime(1002 - 373, 11);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    // wave12 PP
    SetTime(341 - 376, 12);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    // wave13 I-PP
    SetTime(-200, 13);
    ice_filler.coffee();
    SetTime(1002 - 373, 13);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    // wave14 PP
    SetTime(341 - 376, 14);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    // wave15 I-PP
    SetTime(-200, 15);
    ice_filler.coffee();
    SetTime(1002 - 373, 15);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    // wave16 PP
    SetTime(341 - 376, 16);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    // wave17 I-PP
    SetTime(-200, 17);
    ice_filler.coffee();
    SetTime(1002 - 373, 17);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    // wave18 PP
    SetTime(341 - 376, 18);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    // wave19 I-PP-(PP-PP-PP)
    SetTime(-200, 19);
    ice_filler.coffee();
    SetTime(1002 - 373, 19);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    pao_operator.recoverPao({{2, 8.8}, {5, 8.8}, {2, 8.8}, {5, 8.8}});
    SetTime(341 + 1202 * 2 + 601 + 100 - 373, 19);
    pao_operator.recoverPao({{2, 8.8}, {5, 8.8}});
    // 开始自动垫巨人僵尸
    InsertTimeOperation(1002, 19, [=]() {
        block_giga.pushFunc([]() {
            BlockGargantuar({{1, 8}, {2, 8}, {5, 8}, {6, 8}});
        });
    });
    // wave20 PP-(PP-PP-PP)
    // 炮消珊瑚
    SetTime(223 - 373, 20);
    pao_operator.pao(4, 7.5875);
    // 冰杀小偷
    SetTime(395 - 298, 20);
    ice_filler.coffee();
    SetTime(500, 20);
    Shovel({{1, 8}, {2, 8}, {5, 8}, {6, 8}});
    PlantToBlockTheZombies(191, 20, {DANCING_ZOMBIE});
    SetTime(410 - 373, 20);
    pao_operator.pao(2, 8.8);
    SetTime(410 - 100, 20);
    Card(CHERRY_BOMB, 5, 9);
    SetTime(341 + 601 - 376, 20);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    pao_operator.recoverPao({{2, 8.8}, {5, 8.8}, {2, 8.8}, {5, 8.8}});
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