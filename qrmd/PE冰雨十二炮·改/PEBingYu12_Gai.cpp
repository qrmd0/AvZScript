/*
 * @Author: qrmd
 * @Date: 2022-06-02 13:11:05
 * @Last Modified by: qrmd
 * @Last Modified time: 2022-06-02 13:11:05
 * @Description: PE冰雨十二炮·改 演示脚本
 */

#include "avz.h"

using namespace AvZ;
// 如果[wave]波上半场刷出的僵尸总血量较高，返回2，否则返回5。用于6行场地的智能樱桃消延迟
int GetRowHaveHigherZombieHp(int wave);

void Script()
{
    // 脚本在游戏主界面和选择植物界面生效
    OpenMultipleEffective('Q', MAIN_UI_OR_FIGHT_UI);
    // 全难度极限出怪：普僵、撑杆、橄榄、舞王、冰车、小丑、矿工、跳跳、小偷、扶梯、投篮、白眼、红眼、海豚
    SetZombies({ZOMBIE, POLE_VAULTING_ZOMBIE, FOOTBALL_ZOMBIE, DANCING_ZOMBIE, ZOMBONI, JACK_IN_THE_BOX_ZOMBIE, DIGGER_ZOMBIE, POGO_ZOMBIE, BUNGEE_ZOMBIE, LADDER_ZOMBIE, CATAPULT_ZOMBIE, GARGANTUAR, GIGA_GARGANTUAR, DOLPHIN_RIDER_ZOMBIE});
    // 选择植物：咖啡豆、寒冰菇、模仿寒冰菇、南瓜头、倭瓜、樱桃炸弹、小喷菇、花盆、胆小菇、阳光菇
    SelectCards({COFFEE_BEAN, ICE_SHROOM, M_ICE_SHROOM, PUMPKIN, SQUASH, CHERRY_BOMB, PUFF_SHROOM, FLOWER_POT, SCAREDY_SHROOM, SUN_SHROOM});
    SetTime(-599, 1);
    // 开始自动存冰
    ice_filler.start({{4, 9}});
    // 开始自动修补南瓜头
    plant_fixer.start(PUMPKIN, {{3, 9}, {4, 9}}, 1200);
    // 填充炮列表
    pao_operator.resetPaoList({{1, 7}, {6, 7}, {2, 7}, {5, 7}, {3, 1}, {4, 1}, {3, 3}, {4, 3}, {3, 5}, {4, 5}, {3, 7}, {4, 7}});
    // 主体节奏 P6 PP|PP|PP|PP|PP|PP 601|601|601|601|601|601 每波执行确定的操作，不考虑非旗帜波的刷新延迟
    // wave1 PP
    SetTime(295 - 376, 1);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    // wave2 PP
    SetTime(295 - 376, 2);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    // wave3 PP
    SetTime(295 - 376, 3);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    // wave4 PP
    SetTime(295 - 376, 4);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    // wave5 PP
    SetTime(295 - 376, 5);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    // wave6 PP
    SetTime(295 - 376, 6);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    // wave7 PP
    SetTime(295 - 376, 7);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    // wave8 PP
    SetTime(295 - 376, 8);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    // wave9 PP-(-PP-PP)
    SetTime(295 - 376, 9);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    pao_operator.recoverPao({{2, 8.8}, {5, 8.8}, {2, 8.8}, {5, 8.8}});
    // wave10 PP
    SetTime(341 - 376, 10);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    // 冰杀蹦极
    SetTime(601 - 1 - 298, 10);
    ice_filler.coffee();
    // 智能樱桃消中场延迟
    InsertTimeOperation(401, 10, [=]() {
        if (GetRunningWave() == 10) {
            SetTime(401, 10);
            Card(CHERRY_BOMB, GetRowHaveHigherZombieHp(10), 9);
        }
    });
    // wave11 PP
    SetTime(295 - 376, 11);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    // wave12 PP
    SetTime(295 - 376, 12);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    // wave13 PP
    SetTime(295 - 376, 13);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    // wave14 PP
    SetTime(295 - 376, 14);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    // wave15 PP
    SetTime(295 - 376, 15);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    // wave16 PP
    SetTime(295 - 376, 16);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    // wave17 PP
    SetTime(295 - 376, 17);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    // wave18 PP
    SetTime(295 - 376, 18);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    // wave19 PP-(PP-PP)
    SetTime(295 - 376, 19);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    pao_operator.recoverPao({{2, 8.8}, {5, 8.8}, {2, 8.8}, {5, 8.8}});
    // wave20 PP-(PP-PP)
    // 炮消珊瑚
    SetTime(223 - 373, 20);
    pao_operator.pao(4, 7.5875);
    // 冰杀蹦极
    SetTime(395 - 298, 20);
    ice_filler.coffee();
    SetTime(341 - 376, 20);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    pao_operator.recoverPao({{2, 8.8}, {5, 8.8}, {2, 8.8}, {5, 8.8}});
    InsertTimeOperation(1850, 20, [=]() {
        // 如果前场仍存活僵尸，补炸收尾
        bool is_exist_zombie = false;
        auto zombies = GetMainObject()->zombieArray();
        for (int index = 0; index < GetMainObject()->zombieTotal(); ++index) {
            if (!zombies[index].isDead() && !zombies[index].isDisappeared() && zombies[index].abscissa() >= 7 * 80.0) {
                is_exist_zombie = true;
                break;
            }
        }
        if (is_exist_zombie) {
            SetTime(1850, 20);
            pao_operator.recoverPao({{2, 8.8}, {5, 8.8}});
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
