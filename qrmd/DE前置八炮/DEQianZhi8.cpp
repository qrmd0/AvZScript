/*
 * @Author: qrmd
 * @Date: 2022-06-03 20:09:21
 * @Last Modified by: qrmd
 * @Last Modified time: 2022-06-03 20:09:21
 * @Description: DE前置八炮 演示脚本
 */

#include "avz.h"

using namespace AvZ;
using namespace std;
// 如果[wave]波上半场刷出的僵尸总血量较高，返回2，否则返回4。用于5行场地的智能樱桃消延迟
int GetRowHaveHigherZombieHp(int wave);
// 自动在指定位置放置植物触发巨人僵尸举锤阻挡其前进。结合TickRunner使用
void BlockGargantuar(vector<Grid> pos);
TickRunner block_giga;
void Script()
{
    // 脚本在游戏主界面和选择植物界面生效
    OpenMultipleEffective('Q', MAIN_UI_OR_FIGHT_UI);
    // 全难度极限出怪：普僵、撑杆、橄榄、舞王、冰车、小丑、矿工、跳跳、小偷、扶梯、投篮、白眼、红眼
    SetZombies({ZOMBIE, POLE_VAULTING_ZOMBIE, FOOTBALL_ZOMBIE, DANCING_ZOMBIE, ZOMBONI, JACK_IN_THE_BOX_ZOMBIE, DIGGER_ZOMBIE, POGO_ZOMBIE, BUNGEE_ZOMBIE, LADDER_ZOMBIE, CATAPULT_ZOMBIE, GARGANTUAR, GIGA_GARGANTUAR});
    // 选择植物：咖啡豆、寒冰菇、模仿寒冰菇、樱桃炸弹、倭瓜、小喷菇、胆小菇、花盆、阳光菇、向日葵
    SelectCards({COFFEE_BEAN, ICE_SHROOM, M_ICE_SHROOM, CHERRY_BOMB, SQUASH, PUFF_SHROOM, SCAREDY_SHROOM, FLOWER_POT, SUN_SHROOM, SUNFLOWER});
    SetTime(-599, 1);
    Shovel({{1, 7}, {2, 7}, {3, 7}, {4, 7}, {5, 7}});
    // 开始自动存冰
    ice_filler.start({{2, 1}, {4, 1}});
    // 开始自动垫巨人僵尸
    block_giga.pushFunc([]() {
        BlockGargantuar({{1, 7}, {2, 7}, {3, 7}, {4, 7}, {5, 7}});
    });
    // 填充炮列表
    pao_operator.resetPaoList({{1, 1}, {5, 1}, {1, 5}, {5, 5}, {2, 5}, {4, 5}, {3, 1}, {3, 5}});
    // 主体节奏 ch5 PP|I-PP|IPP-PP 601|1437|1437 每波执行确定的操作，不考虑非旗帜波的刷新延迟
    // wave1 PP
    SetTime(341 - 376, 1);
    pao_operator.pao({{2, 9}, {4, 9}});
    // wave2 I-PP
    SetTime(-200, 2);
    ice_filler.coffee();
    SetTime(1237 - 373, 2);
    pao_operator.pao({{2, 9}, {4, 9}});
    // wave3 IPP-PP
    SetTime(-200, 3);
    ice_filler.coffee();
    pao_operator.pao({{2, 9}, {4, 9}});
    SetTime(1237 - 373, 3);
    pao_operator.pao({{2, 9}, {4, 9}});
    // wave4 PP
    SetTime(341 - 376, 4);
    pao_operator.pao({{2, 9}, {4, 9}});
    // wave5 I-PP
    SetTime(-200, 5);
    ice_filler.coffee();
    SetTime(1237 - 373, 5);
    pao_operator.pao({{2, 9}, {4, 9}});
    // wave6 IPP-PP
    SetTime(-200, 6);
    ice_filler.coffee();
    pao_operator.pao({{2, 9}, {4, 9}});
    SetTime(1237 - 373, 6);
    pao_operator.pao({{2, 9}, {4, 9}});
    // wave7 PP
    SetTime(341 - 376, 7);
    pao_operator.pao({{2, 9}, {4, 9}});
    // wave8 I-PP
    SetTime(-200, 8);
    ice_filler.coffee();
    SetTime(1237 - 373, 8);
    pao_operator.pao({{2, 9}, {4, 9}});
    // wave9 IPP-PP(-PP-PP)
    SetTime(-200, 9);
    ice_filler.coffee();
    pao_operator.pao({{2, 9}, {4, 9}});
    SetTime(1237 - 373, 9);
    pao_operator.pao({{2, 9}, {4, 9}});
    pao_operator.recoverPao({{2, 9}, {4, 9}, {2, 9}, {4, 9}});
    // wave10 PP
    SetTime(500, 10);
    Shovel({{1, 7}, {2, 7}, {3, 7}, {4, 7}, {5, 7}});
    SetTime(341 - 376, 10);
    pao_operator.pao({{2, 9}, {4, 9}});
    // 智能樱桃消中场延迟
    InsertTimeOperation(373, 10, [=]() {
        SetTime(373, 10);
        Card(CHERRY_BOMB, GetRowHaveHigherZombieHp(10), 9);
    });
    // wave11 I-PP
    SetTime(674 - 299, 10);
    ice_filler.coffee();
    SetTime(1237 - 373, 11);
    pao_operator.pao({{2, 9}, {4, 9}});
    // wave12 IPP-PP
    SetTime(-200, 12);
    ice_filler.coffee();
    pao_operator.pao({{2, 9}, {4, 9}});
    SetTime(1237 - 373, 12);
    pao_operator.pao({{2, 9}, {4, 9}});
    // wave13 PP
    SetTime(341 - 376, 13);
    pao_operator.pao({{2, 9}, {4, 9}});
    // wave14 I-PP
    SetTime(-200, 14);
    ice_filler.coffee();
    SetTime(1237 - 373, 14);
    pao_operator.pao({{2, 9}, {4, 9}});
    // wave15 IPP-PP
    SetTime(-200, 15);
    ice_filler.coffee();
    pao_operator.pao({{2, 9}, {4, 9}});
    SetTime(1237 - 373, 15);
    pao_operator.pao({{2, 9}, {4, 9}});
    // wave16 PP
    SetTime(341 - 376, 16);
    pao_operator.pao({{2, 9}, {4, 9}});
    // wave17 I-PP
    SetTime(-200, 17);
    ice_filler.coffee();
    SetTime(1237 - 373, 17);
    pao_operator.pao({{2, 9}, {4, 9}});
    // wave18 IPP-PP
    SetTime(-200, 18);
    ice_filler.coffee();
    pao_operator.pao({{2, 9}, {4, 9}});
    SetTime(1237 - 373, 18);
    pao_operator.pao({{2, 9}, {4, 9}});
    // wave19 PP-(PP-PP)
    SetTime(341 - 376, 19);
    pao_operator.pao({{2, 9}, {4, 9}});
    pao_operator.recoverPao({{2, 9}, {4, 9}, {2, 9}, {4, 9}});
    // wave20 PP-(PP-PP)
    SetTime(500, 20);
    Shovel({{1, 7}, {2, 7}, {3, 7}, {4, 7}, {5, 7}});
    SetTime(375 + 300 - 1 - 300, 20);
    ice_filler.coffee();
    SetTime(341 - 376, 20);
    pao_operator.pao({{2, 9}, {4, 9}});
    SetTime(341 + 601 - 376, 20);
    pao_operator.pao({{2, 9}, {4, 9}});
    pao_operator.recoverPao({{2, 9}, {4, 9}});
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