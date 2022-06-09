/*
 * @Author: qrmd
 * @Date: 2022-06-02 20:43:26
 * @Last Modified by: qrmd
 * @Last Modified time: 2022-06-02 20:43:26
 * @Description: PE经典十二炮 演示脚本
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
    // 选择植物：樱桃炸弹、倭瓜、小喷菇、模仿小喷菇、花盆、胆小菇、向日葵、睡莲叶、玉米投手、玉米加农炮
    SelectCards({CHERRY_BOMB, SQUASH, PUFF_SHROOM, M_PUFF_SHROOM, FLOWER_POT, SCAREDY_SHROOM, SUNFLOWER, LILY_PAD, KERNEL_PULT, COB_CANNON});
    SetTime(-599, 1);
    // 填充炮列表
    pao_operator.resetPaoList({{1, 5}, {6, 5}, {2, 5}, {5, 5}, {3, 1}, {4, 1}, {3, 3}, {4, 3}, {3, 5}, {4, 5}, {3, 7}, {4, 7}});
    // 主体节奏 P6 PP|PP|PP|PP|PP|PP 601|601|601|601|601|601 每波执行确定的操作，不考虑非旗帜波的刷新延迟
    // wave1 PP
    SetTime(341 - 376, 1);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    // wave2 PP
    SetTime(341 - 376, 2);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    // wave3 PP
    SetTime(341 - 376, 3);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    // wave4 PP
    SetTime(341 - 376, 4);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    // wave5 PP
    SetTime(341 - 376, 5);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    // wave6 PP
    SetTime(341 - 376, 6);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    // wave7 PP
    SetTime(341 - 376, 7);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    // wave8 PP
    SetTime(341 - 376, 8);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    // wave9 PP-(-PP-PP)
    SetTime(341 - 376, 9);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    SetTime(341 + 601 - 376, 9);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    pao_operator.recoverPao({{2, 8.8}, {5, 8.8}});
    // wave10 PP
    SetTime(341 - 376, 10);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    // 智能樱桃消中场延迟
    InsertTimeOperation(401, 10, [=]() {
        if (GetRunningWave() == 10) {
            SetTime(401, 10);
            Card(CHERRY_BOMB, GetRowHaveHigherZombieHp(10), 9);
        }
    });
    // wave11 PP
    SetTime(341 - 376, 11);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    // wave12 PP
    SetTime(341 - 376, 12);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    // wave13 PP
    SetTime(341 - 376, 13);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    // wave14 PP
    SetTime(341 - 376, 14);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    // wave15 PP
    SetTime(341 - 376, 15);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    // wave16 PP
    SetTime(341 - 376, 16);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    // wave17 PP
    SetTime(341 - 376, 17);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    // wave18 PP
    SetTime(341 - 376, 18);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    // wave19 PP-(PP-PP)
    SetTime(341 - 376, 19);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    SetTime(341 + 601 - 376, 19);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    pao_operator.recoverPao({{2, 8.8}, {5, 8.8}});
    // wave20 PP-(PP-PP)
    // 炮消珊瑚
    SetTime(223 - 373, 20);
    pao_operator.pao(4, 7.5875);
    SetTime(341 - 376, 20);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    SetTime(341 + 601 - 376, 20);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    pao_operator.recoverPao({{2, 8.8}, {5, 8.8}});
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
