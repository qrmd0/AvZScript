/*
 * @Author: qrmd
 * @Date: 2022-06-02 20:09:56
 * @Last Modified by: qrmd
 * @Last Modified time: 2022-06-02 20:09:56
 * @Description: PE经典八炮 演示脚本
 */

#include "avz.h"

using namespace AvZ;
// 在[wave]波[time]厘秒，如果陆路存在列表[zombie_types]中的僵尸，选择阳光消耗较低的植物放置在对应路的9列并在[shovel_time]厘秒后铲除
void PlantToBlockTheZombies(int time, int wave, std::vector<int> zombie_types, int row = 1, int shovel_time = 79);
// 如果[wave]波上半场刷出的僵尸总血量较高，返回2，否则返回5。用于6行场地的智能樱桃消延迟
int GetRowHaveHigherZombieHp(int wave);

void Script()
{
    // 脚本在游戏主界面和选择植物界面生效
    OpenMultipleEffective('Q', MAIN_UI_OR_FIGHT_UI);
    // 全难度极限出怪：普僵、撑杆、橄榄、舞王、冰车、小丑、矿工、跳跳、小偷、扶梯、投篮、白眼、红眼、海豚
    SetZombies({ZOMBIE, POLE_VAULTING_ZOMBIE, FOOTBALL_ZOMBIE, DANCING_ZOMBIE, ZOMBONI, JACK_IN_THE_BOX_ZOMBIE, DIGGER_ZOMBIE, POGO_ZOMBIE, BUNGEE_ZOMBIE, LADDER_ZOMBIE, CATAPULT_ZOMBIE, GARGANTUAR, GIGA_GARGANTUAR, DOLPHIN_RIDER_ZOMBIE});
    // 选择植物：南瓜头、樱桃炸弹、小喷菇、模仿小喷菇、花盆、胆小菇、向日葵、咖啡豆、大喷菇、忧郁菇
    SelectCards({PUMPKIN, CHERRY_BOMB, PUFF_SHROOM, M_PUFF_SHROOM, FLOWER_POT, SCAREDY_SHROOM, SUNFLOWER, COFFEE_BEAN, FUME_SHROOM, GLOOM_SHROOM});
    SetTime(-599, 1);
    // 开始自动修补南瓜头
    plant_fixer.start(PUMPKIN, {{3, 5}, {4, 5}, {3, 6}, {4, 6}, {3, 7}, {4, 7}}, 1200);
    // 填充炮列表
    pao_operator.resetPaoList({{1, 5}, {6, 5}, {2, 5}, {5, 5}, {3, 1}, {4, 1}, {3, 3}, {4, 3}});
    // 主体节奏 P4 PP|PP|PP|PP 869|869|869|869 每波执行确定的操作，不考虑非旗帜波的刷新延迟
    // wave1 PP
    SetTime(669 - 373, 1);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    PlantToBlockTheZombies(191, 1, {DANCING_ZOMBIE});
    // wave2 PP
    SetTime(669 - 373, 2);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    PlantToBlockTheZombies(191, 2, {DANCING_ZOMBIE});
    // wave3 PP
    SetTime(669 - 373, 3);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    PlantToBlockTheZombies(191, 3, {DANCING_ZOMBIE});
    // wave4 PP
    SetTime(669 - 373, 4);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    PlantToBlockTheZombies(191, 4, {DANCING_ZOMBIE});
    // wave5 PP
    SetTime(669 - 373, 5);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    PlantToBlockTheZombies(191, 5, {DANCING_ZOMBIE});
    // wave6 PP
    SetTime(669 - 373, 6);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    PlantToBlockTheZombies(191, 6, {DANCING_ZOMBIE});
    // wave7 PP
    SetTime(669 - 373, 7);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    PlantToBlockTheZombies(191, 7, {DANCING_ZOMBIE});
    // wave8 PP
    SetTime(669 - 373, 8);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    PlantToBlockTheZombies(191, 8, {DANCING_ZOMBIE});
    // wave9 PP-(-PP-PP)
    SetTime(669 - 373, 9);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    pao_operator.recoverPao({{2, 8.8}, {5, 8.8}, {2, 8.8}, {5, 8.8}});
    PlantToBlockTheZombies(191, 9, {DANCING_ZOMBIE});
    // wave10 PP
    SetTime(669 - 373, 10);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    PlantToBlockTheZombies(230, 10, {DANCING_ZOMBIE});
    // 智能樱桃消中场延迟
    InsertTimeOperation(669 + 3 + 1, 10, [=]() {
        if (GetRunningWave() == 10) {
            SetTime(669 + 3 + 1, 10);
            Card(CHERRY_BOMB, GetRowHaveHigherZombieHp(10), 9);
        }
    });
    // wave11 PP
    SetTime(669 - 373, 11);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    PlantToBlockTheZombies(191, 11, {DANCING_ZOMBIE});
    // wave12 PP
    SetTime(669 - 373, 12);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    PlantToBlockTheZombies(191, 12, {DANCING_ZOMBIE});
    // wave13 PP
    SetTime(669 - 373, 13);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    PlantToBlockTheZombies(191, 13, {DANCING_ZOMBIE});
    // wave14 PP
    SetTime(669 - 373, 14);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    PlantToBlockTheZombies(191, 14, {DANCING_ZOMBIE});
    // wave15 PP
    SetTime(669 - 373, 15);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    PlantToBlockTheZombies(191, 15, {DANCING_ZOMBIE});
    // wave16 PP
    SetTime(669 - 373, 16);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    PlantToBlockTheZombies(191, 16, {DANCING_ZOMBIE});
    // wave17 PP
    SetTime(669 - 373, 17);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    PlantToBlockTheZombies(191, 17, {DANCING_ZOMBIE});
    // wave18 PP
    SetTime(669 - 373, 18);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    PlantToBlockTheZombies(191, 18, {DANCING_ZOMBIE});
    // wave19 PP-(PP-PP)
    SetTime(669 - 373, 19);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    pao_operator.recoverPao({{2, 8.8}, {5, 8.8}, {2, 8.8}, {5, 8.8}});
    PlantToBlockTheZombies(191, 19, {DANCING_ZOMBIE});
    // wave20 PP-(PP-PP)
    SetTime(669 - 373, 20);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    pao_operator.recoverPao({{2, 8.8}, {5, 8.8}, {2, 8.8}, {5, 8.8}});
    PlantToBlockTheZombies(230, 20, {DANCING_ZOMBIE});
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
