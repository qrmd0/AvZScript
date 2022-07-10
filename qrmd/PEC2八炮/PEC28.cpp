/*
 * @Author: qrmd
 * @Date: 2022-06-21 13:07:19
 * @LastEditors: qrmd
 * @LastEditTime: 2022-06-22 15:19:40
 * @Description:PEC2八炮 全难度极限出怪运阵演示脚本
 * 使用方法：1、前往https://gitee.com/vector-wlc/AsmVsZombies，根据教程下载并安装好AsmVsZombies
 *          2、在Visul Studio Code中打开本脚本，右键点击编辑区空白处，在弹出菜单中选择“AvZ:Run Script”
 * 更多AvZ脚本尽在AvZScript公开脚本仓库：
 * 主库：https://github.com/qrmd0/AvZScript
 * 镜像库：https://gitee.com/qrmd/AvZScript
 * Copyright (c) 2022 by qrmd , All Rights Reserved.
 */

#include "avz.h"
using namespace AvZ;
// 自动在指定位置放置植物触发巨人僵尸举锤阻挡其前进。结合TickRunner使用
void BlockGargantuar(std::vector<Grid> pos);
TickRunner block_giga;

void Script()
{
    // 脚本在游戏主界面和选择植物界面生效
    OpenMultipleEffective('Q', MAIN_UI_OR_FIGHT_UI);
    // 全难度极限出怪：普僵、撑杆、橄榄、舞王、冰车、小丑、矿工、跳跳、小偷、扶梯、投篮、白眼、红眼、海豚
    SetZombies({ZOMBIE, POLE_VAULTING_ZOMBIE, FOOTBALL_ZOMBIE, DANCING_ZOMBIE, ZOMBONI, JACK_IN_THE_BOX_ZOMBIE, DIGGER_ZOMBIE, POGO_ZOMBIE, BUNGEE_ZOMBIE, LADDER_ZOMBIE, CATAPULT_ZOMBIE, GARGANTUAR, GIGA_GARGANTUAR, DOLPHIN_RIDER_ZOMBIE});
    // 选择植物：咖啡豆、寒冰菇、模仿寒冰菇、睡莲叶、南瓜头、毁灭菇、火爆辣椒、小喷菇、花盆、胆小菇
    SelectCards({COFFEE_BEAN, ICE_SHROOM, M_ICE_SHROOM, LILY_PAD, PUMPKIN, DOOM_SHROOM, JALAPENO, PUFF_SHROOM, FLOWER_POT, SCAREDY_SHROOM});
    SetTime(-599, 1);
    // 填充炮列表
    pao_operator.resetPaoList({{1, 2}, {6, 2}, {1, 4}, {6, 4}, {2, 3}, {5, 3}, {3, 3}, {4, 3}});
    // 开始自动存冰
    ice_filler.start({{3, 1}, {4, 1}, {3, 2}, {2, 6}});
    // 铲除临时植物
    Shovel({{1, 6}, {1, 7}, {1, 8}});
    // 开始自动修补南瓜头
    plant_fixer.start(PUMPKIN, {{3, 5}, {4, 5}, {3, 6}, {4, 6}}, 1200);
    // 主体节奏 ch4 I-PPDD|I-PPDD 1737|1738 每波执行确定的操作，不考虑非旗帜波的刷新延迟

    // wave1 PPDD 首代
    SetTime(341 - 376, 1);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    SetTime(341 + 110 - 376, 1);
    pao_operator.pao({{1, 7.7}, {5, 7.7}});
    SetTime(1 + 601 - 298, 1);
    ice_filler.coffee();

    // wave2 I-PPDD
    SetTime(1737 - 200 - 373, 2);
    pao_operator.pao({{2, 8.5}, {5, 8.5}});
    SetTime(1737 - 200 + 225 - 373, 2);
    pao_operator.pao({{1, 7.3625}, {5, 7.3625}});
    SetTime(12 + 1737 - 298, 2);
    ice_filler.coffee();

    // wave3 I-PPDD
    SetTime(1738 - 200 - 373, 3);
    pao_operator.pao({{2, 8.5}, {5, 8.5}});
    SetTime(1738 - 200 + 225 - 373, 3);
    pao_operator.pao({{1, 7.3625}, {5, 7.3625}});
    SetTime(12 + 1738 - 298, 3);
    ice_filler.coffee();

    // wave4 I-PPDD
    SetTime(1737 - 200 - 373, 4);
    pao_operator.pao({{2, 8.5}, {5, 8.5}});
    SetTime(1737 - 200 + 225 - 373, 4);
    pao_operator.pao({{1, 7.3625}, {5, 7.3625}});
    SetTime(12 + 1737 - 298, 4);
    ice_filler.coffee();

    // wave5 I-PPDD
    SetTime(1738 - 200 - 373, 5);
    pao_operator.pao({{2, 8.5}, {5, 8.5}});
    SetTime(1738 - 200 + 225 - 373, 5);
    pao_operator.pao({{1, 7.3625}, {5, 7.3625}});
    SetTime(12 + 1738 - 298, 5);
    ice_filler.coffee();

    // wave6 I-PPDD
    SetTime(1737 - 200 - 373, 6);
    pao_operator.pao({{2, 8.5}, {5, 8.5}});
    SetTime(1737 - 200 + 225 - 373, 6);
    pao_operator.pao({{1, 7.3625}, {5, 7.3625}});
    SetTime(12 + 1737 - 298, 6);
    ice_filler.coffee();

    // wave7 I-PPDD
    SetTime(1738 - 200 - 373, 7);
    pao_operator.pao({{2, 8.5}, {5, 8.5}});
    SetTime(1738 - 200 + 225 - 373, 7);
    pao_operator.pao({{1, 7.3625}, {5, 7.3625}});
    SetTime(12 + 1738 - 298, 7);
    ice_filler.coffee();

    // wave8 I-PPDD
    SetTime(1737 - 200 - 373, 8);
    pao_operator.pao({{2, 8.5}, {5, 8.5}});
    SetTime(1737 - 200 + 225 - 373, 8);
    pao_operator.pao({{1, 7.3625}, {5, 7.3625}});
    SetTime(12 + 1737 - 298, 8);
    ice_filler.coffee();

    // wave9 I-PPDD
    SetTime(1738 - 200 - 373, 9);
    pao_operator.pao({{2, 8.5}, {5, 8.5}});
    SetTime(1738 - 200 + 4, 9);
    Card(PUFF_SHROOM, 1, 7);
    Card(FLOWER_POT, 6, 7);
    SetTime(1738 - 200 + 225 - 373, 9);
    pao_operator.pao({{1, 7.3625}, {5, 7.3625}});
    SetTime(1738 - 200 + 225 + 1, 9);
    InsertOperation([=]() {
        block_giga.pushFunc([]() {
            BlockGargantuar({{1, 6}});
        });
    });
    SetTime(1738 - 200 + 1738 - 110 - 208, 9);
    block_giga.pause();
    Shovel(1, 6);
    SetTime(1738 - 200 + 1738 - 110 - 100, 9);
    Card(JALAPENO, 6, 6);
    SetTime(1738 - 200 + 1738 - 110 - 298, 9);
    Card(LILY_PAD, 3, 7);
    Card(DOOM_SHROOM, 3, 7);
    Card(COFFEE_BEAN, 3, 7);
    SetTime(1738 - 200 + 1738 - 373, 9);
    pao_operator.pao({{1, 6}, {5, 6}});
    SetTime(1738 - 200 + 1738 - 110 + 4, 9);
    block_giga.goOn();

    // wave10 PPDD 首代
    SetTime(0, 10);
    block_giga.pause();
    Shovel(1, 6);
    SetTime(341 - 376, 10);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    SetTime(341 + 110 - 376, 10);
    pao_operator.pao({{1, 7.7}, {5, 7.7}});
    SetTime(1 + 601 - 298, 10);
    ice_filler.coffee();

    // wave11 I-PPDD
    SetTime(1737 - 200 - 373, 11);
    pao_operator.pao({{2, 8.5}, {5, 8.5}});
    SetTime(1737 - 200 + 225 - 373, 11);
    pao_operator.pao({{1, 7.3625}, {5, 7.3625}});
    SetTime(12 + 1737 - 298, 11);
    ice_filler.coffee();

    // wave12 I-PPDD
    SetTime(1738 - 200 - 373, 12);
    pao_operator.pao({{2, 8.5}, {5, 8.5}});
    SetTime(1738 - 200 + 225 - 373, 12);
    pao_operator.pao({{1, 7.3625}, {5, 7.3625}});
    SetTime(12 + 1738 - 298, 12);
    ice_filler.coffee();

    // wave13 I-PPDD
    SetTime(1737 - 200 - 373, 13);
    pao_operator.pao({{2, 8.5}, {5, 8.5}});
    SetTime(1737 - 200 + 225 - 373, 13);
    pao_operator.pao({{1, 7.3625}, {5, 7.3625}});
    SetTime(12 + 1737 - 298, 13);
    ice_filler.coffee();

    // wave14 I-PPDD
    SetTime(1738 - 200 - 373, 14);
    pao_operator.pao({{2, 8.5}, {5, 8.5}});
    SetTime(1738 - 200 + 225 - 373, 14);
    pao_operator.pao({{1, 7.3625}, {5, 7.3625}});
    SetTime(12 + 1738 - 298, 14);
    ice_filler.coffee();

    // wave15 I-PPDD
    SetTime(1737 - 200 - 373, 15);
    pao_operator.pao({{2, 8.5}, {5, 8.5}});
    SetTime(1737 - 200 + 225 - 373, 15);
    pao_operator.pao({{1, 7.3625}, {5, 7.3625}});
    SetTime(12 + 1737 - 298, 15);
    ice_filler.coffee();

    // wave16 I-PPDD
    SetTime(1738 - 200 - 373, 16);
    pao_operator.pao({{2, 8.5}, {5, 8.5}});
    SetTime(1738 - 200 + 225 - 373, 16);
    pao_operator.pao({{1, 7.3625}, {5, 7.3625}});
    SetTime(12 + 1738 - 298, 16);
    ice_filler.coffee();

    // wave17 I-PPDD
    SetTime(1737 - 200 - 373, 17);
    pao_operator.pao({{2, 8.5}, {5, 8.5}});
    SetTime(1737 - 200 + 225 - 373, 17);
    pao_operator.pao({{1, 7.3625}, {5, 7.3625}});
    SetTime(12 + 1737 - 298, 17);
    ice_filler.coffee();

    // wave18 I-PPDD
    SetTime(1738 - 200 - 373, 18);
    pao_operator.pao({{2, 8.5}, {5, 8.5}});
    SetTime(1738 - 200 + 225 - 373, 18);
    pao_operator.pao({{1, 7.3625}, {5, 7.3625}});
    SetTime(12 + 1738 - 298, 18);
    ice_filler.coffee();

    // wave19 I-PPDD
    SetTime(1737 - 200 - 373, 19);
    pao_operator.pao({{2, 8.5}, {5, 8.5}});
    SetTime(1737 - 200 + 4, 19);
    Card(PUFF_SHROOM, 1, 7);
    Card(FLOWER_POT, 6, 7);
    SetTime(1737 - 200 + 225 - 373, 19);
    pao_operator.pao({{1, 7.3625}, {5, 7.3625}});
    SetTime(1737 - 200 + 225 + 1, 19);
    block_giga.goOn();
    SetTime(1737 - 200 + 1738 - 110 - 208, 19);
    block_giga.pause();
    Shovel(1, 6);
    SetTime(1737 - 200 + 1738 - 110 - 100, 19);
    Card(JALAPENO, 6, 6);
    SetTime(1737 - 200 + 1738 - 110 - 298, 19);
    Card(LILY_PAD, 3, 7);
    Card(DOOM_SHROOM, 3, 7);
    Card(COFFEE_BEAN, 3, 7);
    SetTime(1737 - 200 + 1738 - 373, 19);
    pao_operator.pao({{1, 6}, {5, 6}});
    SetTime(1737 - 200 + 1738 - 110 + 4, 19);
    block_giga.goOn();

    // wave20 PPSSDD
    SetTime(341 - 376, 20);
    pao_operator.pao({{2, 8.8}, {5, 8.8}, {2, 8.8}, {5, 8.8}});
    SetTime(341 + 110 - 376, 20);
    pao_operator.pao({{1, 8.8}, {5, 8.8}});
    // 冰杀小偷
    SetTime(341 + 110 - 3 + 2 - 298, 20);
    ice_filler.coffee();
    SetTime(341, 20);
    block_giga.stop();
    InsertOperation([=]() {
        block_giga.pushFunc([]() {
            BlockGargantuar({{1, 6}, {1, 7}, {1, 8}});
        });
    });
    SetTime(3200, 20);
    Card(JALAPENO, 6, 6);
}
void BlockGargantuar(std::vector<Grid> pos)
{
    for (Grid each : pos) {
        auto zombies = GetMainObject()->zombieArray();
        auto seeds = GetMainObject()->seedArray();
        std::vector<int> indices_seed = {GetSeedIndex(PUFF_SHROOM), GetSeedIndex(FLOWER_POT), GetSeedIndex(SCAREDY_SHROOM)};
        for (int index = 0; index < GetMainObject()->zombieTotal(); ++index) {
            if (!zombies[index].isDead() && !zombies[index].isDisappeared() && (zombies[index].type() == GARGANTUAR || zombies[index].type() == GIGA_GARGANTUAR) && zombies[index].row() + 1 == each.row && (zombies[index].abscissa() <= 40 + (each.col - 1) * 80 + 50 + 1 && zombies[index].abscissa() >= 40 + (each.col - 1) * 80 - 5) && zombies[index].state() == 0) {
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