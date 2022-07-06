/*
 * @Author: qrmd
 * @Date: 2022-06-02 21:02:13
 * @Last Modified by: qrmd
 * @Last Modified time: 2022-06-02 21:02:13
 * @Description: PE经典四炮 演示脚本
 */

#include "avz.h"

using namespace AvZ;
using namespace std;
// 自动在指定位置放置植物触发巨人僵尸举锤阻挡其前进。结合TickRunner使用
void BlockGargantuar(vector<Grid> pos);
TickRunner block_giga;
void Script()
{
    // 脚本在游戏主界面和选择植物界面生效
    OpenMultipleEffective('Q', MAIN_UI_OR_FIGHT_UI);
    // 全难度极限出怪：普僵、撑杆、橄榄、舞王、冰车、小丑、矿工、跳跳、小偷、扶梯、投篮、白眼、红眼、海豚
    SetZombies({ZOMBIE, POLE_VAULTING_ZOMBIE, FOOTBALL_ZOMBIE, DANCING_ZOMBIE, ZOMBONI, JACK_IN_THE_BOX_ZOMBIE, DIGGER_ZOMBIE, POGO_ZOMBIE, BUNGEE_ZOMBIE, LADDER_ZOMBIE, CATAPULT_ZOMBIE, GARGANTUAR, GIGA_GARGANTUAR, DOLPHIN_RIDER_ZOMBIE});
    // 选择植物：咖啡豆、寒冰菇、模仿寒冰菇、南瓜头、睡莲叶、毁灭菇、三叶草、小喷菇、花盆、胆小菇
    SelectCards({COFFEE_BEAN, ICE_SHROOM, M_ICE_SHROOM, PUMPKIN, LILY_PAD, DOOM_SHROOM, BLOVER, PUFF_SHROOM, FLOWER_POT, SCAREDY_SHROOM});
    SetTime(-599, 1);
    // 开始自动垫巨人僵尸
    block_giga.pushFunc([]() {
        BlockGargantuar({{2, 6}, {5, 6}, {1, 6}, {6, 6}});
    });
    // 开始自动存冰
    ice_filler.start({{3, 5}, {1, 4}, {6, 4}, {1, 5}, {6, 5}});
    // 开始自动修补南瓜头
    plant_fixer.start(PUMPKIN, {{3, 5}, {4, 5}, {3, 6}, {4, 6}}, 1200);
    // 填充炮列表
    pao_operator.resetPaoList({{3, 1}, {4, 1}, {3, 3}, {4, 3}});
    // 主体节奏 ch4 I-PP|I-PP 1738|1738 每波执行确定的操作，不考虑非旗帜波的刷新延迟
    // wave1 PP 首代
    SetTime(341 - 376, 1);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    // wave2 I-PP
    SetTime(-200, 2);
    ice_filler.coffee();
    SetTime(1538 - 373, 2);
    pao_operator.pao({{2, 8.6}, {5, 8.6}});
    // wave3 I-PP
    SetTime(-200, 3);
    ice_filler.coffee();
    SetTime(1538 - 373, 3);
    pao_operator.pao({{2, 8.6}, {5, 8.6}});
    // wave4 I-PP
    SetTime(-200, 4);
    ice_filler.coffee();
    SetTime(1538 - 373, 4);
    pao_operator.pao({{2, 8.6}, {5, 8.6}});
    // wave5 I-PP
    SetTime(-200, 5);
    ice_filler.coffee();
    SetTime(1538 - 373, 5);
    pao_operator.pao({{2, 8.6}, {5, 8.6}});
    // wave6 I-PP
    SetTime(-200, 6);
    ice_filler.coffee();
    SetTime(1538 - 373, 6);
    pao_operator.pao({{2, 8.6}, {5, 8.6}});
    // wave7 I-PP
    SetTime(-200, 7);
    ice_filler.coffee();
    SetTime(1538 - 373, 7);
    pao_operator.pao({{2, 8.6}, {5, 8.6}});
    // wave8 I-PP
    SetTime(-200, 8);
    ice_filler.coffee();
    SetTime(1538 - 373, 8);
    pao_operator.pao({{2, 8.6}, {5, 8.6}});
    // wave9 I-PP-(PP-cc)
    SetTime(-200, 9);
    ice_filler.coffee();
    SetTime(1538 - 373, 9);
    pao_operator.pao({{2, 8.6}, {5, 8.6}});
    pao_operator.recoverPao({{2, 8.6}, {5, 8.6}});
    // wave10 I-PP
    SetTime(395 - 298, 10);
    ice_filler.coffee();
    SetTime(1538 - 373, 10);
    pao_operator.pao({{2, 8.6}, {5, 8.6}});
    // 智能核消中场延迟
    InsertTimeOperation(1538 + 1, 10, [=]() {
        if (GetRunningWave() == 10) {
            SetTime(1538 + 1, 10);
            Card(LILY_PAD, 3, 9);
            Card(DOOM_SHROOM, 3, 9);
            Card(COFFEE_BEAN, 3, 9);
        }
    });
    // wave11 I-PP
    SetTime(-200, 11);
    ice_filler.coffee();
    SetTime(1538 - 373, 11);
    pao_operator.pao({{2, 8.6}, {5, 8.6}});
    // wave12 I-PP
    SetTime(-200, 12);
    ice_filler.coffee();
    SetTime(1538 - 373, 12);
    pao_operator.pao({{2, 8.6}, {5, 8.6}});
    // wave13 I-PP
    SetTime(-200, 13);
    ice_filler.coffee();
    SetTime(1538 - 373, 13);
    pao_operator.pao({{2, 8.6}, {5, 8.6}});
    // wave14 I-PP
    SetTime(-200, 14);
    ice_filler.coffee();
    SetTime(1538 - 373, 14);
    pao_operator.pao({{2, 8.6}, {5, 8.6}});
    // wave15 I-PP
    SetTime(-200, 15);
    ice_filler.coffee();
    SetTime(1538 - 373, 15);
    pao_operator.pao({{2, 8.6}, {5, 8.6}});
    // wave16 I-PP
    SetTime(-200, 16);
    ice_filler.coffee();
    SetTime(1538 - 373, 16);
    pao_operator.pao({{2, 8.6}, {5, 8.6}});
    // wave17 I-PP
    SetTime(-200, 17);
    ice_filler.coffee();
    SetTime(1538 - 373, 17);
    pao_operator.pao({{2, 8.6}, {5, 8.6}});
    // wave18 I-PP
    SetTime(-200, 18);
    ice_filler.coffee();
    SetTime(1538 - 373, 18);
    pao_operator.pao({{2, 8.6}, {5, 8.6}});
    // wave19 I-PP-(PP-cc)
    SetTime(-200, 19);
    ice_filler.coffee();
    SetTime(1538 - 373, 19);
    pao_operator.pao({{2, 8.6}, {5, 8.6}});
    pao_operator.recoverPao({{2, 8.6}, {5, 8.6}});
    // wave20 I-PP-(PP-PP-cc)
    SetTime(395 - 298, 20);
    ice_filler.coffee();
    SetTime(1538 - 373, 20);
    pao_operator.pao({{2, 8.6}, {5, 8.6}});
    pao_operator.recoverPao({{2, 8.6}, {5, 8.6}, {2, 8.6}, {5, 8.6}});
}
void BlockGargantuar(vector<Grid> pos)
{
    for (Grid each : pos) {
        auto zombies = GetMainObject()->zombieArray();
        auto seeds = GetMainObject()->seedArray();
        vector<int> indices_seed = {GetSeedIndex(PUFF_SHROOM), GetSeedIndex(PUFF_SHROOM, true), GetSeedIndex(SUN_SHROOM), GetSeedIndex(FLOWER_POT), GetSeedIndex(SCAREDY_SHROOM), GetSeedIndex(SUNFLOWER), GetSeedIndex(GARLIC), GetSeedIndex(FUME_SHROOM), GetSeedIndex(BLOVER)};
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