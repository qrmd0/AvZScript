/*
 * @Author: qrmd
 * @Date: 2022-06-18 08:38:33
 * @LastEditors: qrmd
 * @LastEditTime: 2022-07-14 15:12:27
 * @Description:PE双冰十六炮·改 全难度极限出怪运阵演示脚本
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
    // 全难度极限出怪：普僵、撑杆、橄榄、舞王、冰车、小丑、矿工、跳跳、小偷、扶梯、投篮、白眼、红眼
    SetZombies({ZOMBIE, POLE_VAULTING_ZOMBIE, FOOTBALL_ZOMBIE, DANCING_ZOMBIE, ZOMBONI, JACK_IN_THE_BOX_ZOMBIE, DIGGER_ZOMBIE, POGO_ZOMBIE, BUNGEE_ZOMBIE, LADDER_ZOMBIE, CATAPULT_ZOMBIE, GARGANTUAR, GIGA_GARGANTUAR});
    // 选择植物：咖啡豆、寒冰菇、模仿寒冰菇、毁灭菇、樱桃炸弹、火爆辣椒、倭瓜、寒冰射手、小喷菇、高坚果
    SelectCards({COFFEE_BEAN, ICE_SHROOM, M_ICE_SHROOM, DOOM_SHROOM, CHERRY_BOMB, JALAPENO, SQUASH, SNOW_PEA, PUFF_SHROOM, TALL_NUT});
    SetTime(-599, 1);
    // 填充炮列表
    pao_operator.resetPaoList({{1, 5}, {6, 5}, {1, 7}, {6, 7}, {2, 5}, {5, 5}, {2, 7}, {5, 7}, {3, 1}, {4, 1}, {3, 3}, {4, 3}, {3, 5}, {4, 5}, {3, 7}, {4, 7}});
    // 开始自动存冰
    ice_filler.start({{2, 1}, {5, 1}});
    // 开始自动修补高坚果
    plant_fixer.start(TALL_NUT, {{1, 1}}, 1000);
    // 主体节奏 ch6附加轨 IPP-PP|PPDD|IPP-PP|PPDD 1151|601|1151|601 每波执行确定的操作，不考虑非旗帜波的刷新延迟
    // wave1 PPDD
    SetTime(295 - 376, 1);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    SetTime(401 - 376, 1);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});

    // wave2 IPP-PP
    SetTime(-200, 2);
    ice_filler.coffee();
    // 8.2625为消灭全部冰车的最左准心列数
    pao_operator.pao({{2, 8.2625}, {5, 8.2625}});
    SetTime(1151 - 200 - 373, 2);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    SetTime(1151 - 200 + 100, 2);
    Card(PUFF_SHROOM, 6, 9);
    SetTime(1151 - 200 + 100 + 238, 2);
    Shovel(6, 9);

    // wave3 PPDD
    SetTime(295 - 376, 3);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    SetTime(401 - 376, 3);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});

    // wave4 IPP-PP
    SetTime(-200, 4);
    ice_filler.coffee();
    // 8.2625为消灭全部冰车的最左准心列数
    pao_operator.pao({{2, 8.2625}, {5, 8.2625}});
    SetTime(1151 - 200 - 373, 4);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    SetTime(1151 - 200 + 100, 4);
    Card(PUFF_SHROOM, 6, 9);
    SetTime(1151 - 200 + 100 + 238, 4);
    Shovel(6, 9);

    // wave5 PPDD
    SetTime(295 - 376, 5);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    SetTime(401 - 376, 5);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});

    // wave6 IPP-PP
    SetTime(-200, 6);
    ice_filler.coffee();
    // 8.2625为消灭全部冰车的最左准心列数
    pao_operator.pao({{2, 8.2625}, {5, 8.2625}});
    SetTime(1151 - 200 - 373, 6);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    SetTime(1151 - 200 + 100, 6);
    Card(PUFF_SHROOM, 6, 9);
    SetTime(1151 - 200 + 100 + 238, 6);
    Shovel(6, 9);

    // wave7 PPDD
    SetTime(295 - 376, 7);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    SetTime(401 - 376, 7);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});

    // wave8 IPP-PP
    SetTime(-200, 8);
    ice_filler.coffee();
    // 8.2625为消灭全部冰车的最左准心列数
    pao_operator.pao({{2, 8.2625}, {5, 8.2625}});
    SetTime(1151 - 200 - 373, 8);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    SetTime(1151 - 200 + 100, 8);
    Card(PUFF_SHROOM, 6, 9);
    SetTime(1151 - 200 + 100 + 238, 8);
    Shovel(6, 9);

    // wave9 PPDD-PP-PP
    SetTime(295 - 376, 9);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    SetTime(401 - 376, 9);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    pao_operator.recoverPao({{2, 8.8}, {5, 8.8}, {2, 8.8}, {5, 8.8}});
    SetTime(401, 9);
    InsertOperation([=]() {
        block_giga.pushFunc([]() {
            BlockGargantuar({{1, 9}, {2, 9}, {5, 9}, {6, 9}});
        });
    });

    // wave10 PPDD
    SetTime(0, 10);
    Shovel({{1, 9}, {2, 9}, {5, 9}, {6, 9}});
    block_giga.pause();
    SetTime(295 - 376, 10);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    SetTime(410 - 373, 10);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});

    // wave11 IPP-PP
    SetTime(-200, 11);
    ice_filler.coffee();
    // 8.2625为消灭全部冰车的最左准心列数
    pao_operator.pao({{2, 8.2625}, {5, 8.2625}});
    SetTime(1157 - 200 - 373, 11);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    SetTime(1151 - 200 + 100, 11);
    Card(PUFF_SHROOM, 6, 9);
    SetTime(1151 - 200 + 100 + 238, 11);
    Shovel(6, 9);

    // wave12 PPDD
    SetTime(295 - 376, 12);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    SetTime(401 - 376, 12);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});

    // wave13 IPP-PP
    SetTime(-200, 13);
    ice_filler.coffee();
    // 8.2625为消灭全部冰车的最左准心列数
    pao_operator.pao({{2, 8.2625}, {5, 8.2625}});
    SetTime(1157 - 200 - 373, 13);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    SetTime(1151 - 200 + 100, 13);
    Card(PUFF_SHROOM, 6, 9);
    SetTime(1151 - 200 + 100 + 238, 13);
    Shovel(6, 9);

    // wave14 PPDD
    SetTime(295 - 376, 14);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    SetTime(401 - 376, 14);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});

    // wave15 IPP-PP
    SetTime(-200, 15);
    ice_filler.coffee();
    // 8.2625为消灭全部冰车的最左准心列数
    pao_operator.pao({{2, 8.2625}, {5, 8.2625}});
    SetTime(1151 - 200 - 373, 15);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    SetTime(1151 - 200 + 100, 15);
    Card(PUFF_SHROOM, 6, 9);
    SetTime(1151 - 200 + 100 + 238, 15);
    Shovel(6, 9);

    // wave16 PPDD
    SetTime(295 - 376, 16);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    SetTime(401 - 376, 16);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});

    // wave17 IPP-PP
    SetTime(-200, 17);
    ice_filler.coffee();
    // 8.2625为消灭全部冰车的最左准心列数
    pao_operator.pao({{2, 8.2625}, {5, 8.2625}});
    SetTime(1151 - 200 - 373, 17);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    SetTime(1151 - 200 + 100, 17);
    Card(PUFF_SHROOM, 6, 9);
    SetTime(1151 - 200 + 100 + 238, 17);
    Shovel(6, 9);

    // wave18 PPDD
    SetTime(295 - 376, 18);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    SetTime(401 - 376, 18);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});

    // wave19 PPDD-(PP-PP)
    SetTime(295 - 376, 19);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    SetTime(486 - 298, 19);
    ice_filler.coffee();
    pao_operator.recoverPao({{2, 8.8}, {5, 8.8}, {2, 8.8}, {5, 8.8}, {2, 8.8}, {5, 8.8}});
    SetTime(401, 19);
    block_giga.goOn();

    // wave20 PPDD(-PP-PP)
    SetTime(0, 10);
    Shovel({{1, 9}, {2, 9}, {5, 9}, {6, 9}});
    // 炮消珊瑚
    SetTime(223 - 373, 20);
    pao_operator.pao(4, 7.5875);
    SetTime(295 - 376, 20);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    SetTime(410 - 373, 20);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    SetTime(814 - 373, 20);
    pao_operator.recoverPao({{2, 8.8}, {5, 8.8}, {2, 8.8}, {5, 8.8}});
}
void BlockGargantuar(std::vector<Grid> pos)
{
    for (Grid each : pos) {
        auto zombies = GetMainObject()->zombieArray();
        auto seeds = GetMainObject()->seedArray();
        std::vector<int> indices_seed = {GetSeedIndex(SNOW_PEA), GetSeedIndex(PUFF_SHROOM), GetSeedIndex(TALL_NUT), GetSeedIndex(FLOWER_POT), GetSeedIndex(SCAREDY_SHROOM), GetSeedIndex(SUN_SHROOM), GetSeedIndex(SQUASH)};
        for (int index = 0; index < GetMainObject()->zombieTotal(); ++index) {
            if (!zombies[index].isDead() && !zombies[index].isDisappeared() && zombies[index].type() == POLE_VAULTING_ZOMBIE && zombies[index].row() + 1 == each.row && (zombies[index].abscissa() <= 40 + each.col * 80 + 35 && zombies[index].abscissa() >= 40 + (each.col - 1) * 80 - 70 && zombies[index].state() == 11)) {
                if (GetPlantIndex(each.row, each.col) >= 0 || GetPlantIndex(each.row, each.col, FLOWER_POT) >= 0)
                    ShovelNotInQueue(each.row, each.col);
                return;
            }
            if (!zombies[index].isDead() && !zombies[index].isDisappeared() && (zombies[index].type() == GARGANTUAR || zombies[index].type() == GIGA_GARGANTUAR) && zombies[index].row() + 1 == each.row && (zombies[index].abscissa() <= 40 + (each.col - 1) * 80 + 10 && zombies[index].abscissa() >= 40 + (each.col - 1) * 80 - 5)) {
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