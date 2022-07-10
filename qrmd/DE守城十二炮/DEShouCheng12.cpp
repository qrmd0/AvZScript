/*
 * @Author: qrmd
 * @Date: 2022-06-18 08:38:33
 * @LastEditors: qrmd
 * @LastEditTime: 2022-06-20 16:14:39
 * @Description:DE守城十二炮 全难度极限出怪运阵演示脚本
 * 使用方法：1、前往https://gitee.com/vector-wlc/AsmVsZombies，根据教程下载并安装好AsmVsZombies
 *          2、在Visul Studio Code中打开本脚本，右键点击编辑区空白处，在弹出菜单中选择“AvZ:Run Script”
 * 更多AvZ脚本尽在AvZScript公开脚本仓库：
 * 主库：https://github.com/qrmd0/AvZScript
 * 镜像库：https://gitee.com/qrmd/AvZScript
 * Copyright (c) 2022 by qrmd , All Rights Reserved.
 */

#include "avz.h"
using namespace AvZ;
// *** In Queue
// 在[wave]波，留下一行残血巨人，自动放置植物将其拖住以延长收尾，适用于五行场地
void EndingTheWave(int wave);
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
    pao_operator.resetPaoList({{1, 1}, {5, 1}, {1, 3}, {5, 3}, {1, 5}, {5, 5}, {2, 1}, {4, 1}, {2, 3}, {4, 3}, {2, 5}, {4, 5}});
    // 开始自动存冰
    ice_filler.start({{3, 1}, {3, 2}, {3, 3}});
    // 开始自动修补高坚果
    plant_fixer.start(TALL_NUT, {{1, 7}, {2, 7}, {3, 7}, {4, 7}, {5, 7}}, 1000);
    // 主体节奏 ch4 I3PPDD-PP|I3PPDD-PP 1738|1738 每波执行确定的操作，不考虑非旗帜波的刷新延迟

    // wave1 B/PSD 首代
    SetTime(-599, 1);
    Card(M_ICE_SHROOM, 5, 8);
    SetTime(401 - 376, 1);
    pao_operator.pao(2, 8.05);
    SetTime(341 - 376, 1);
    pao_operator.pao({{4, 9}, {4, 9}});
    SetTime(341 + 110 - 376, 1);
    pao_operator.pao(4, 9);
    SetTime(341 + 110 - 100, 1);
    Card(JALAPENO, 3, 8);
    SetTime(1 + 601 - 298, 1);
    Card(COFFEE_BEAN, 5, 8);

    // wave2 IPP-PP 首代
    SetTime(595 - 373, 2);
    pao_operator.pao(2, 7.025);
    SetTime(173 - 373);
    pao_operator.pao(4, 8.3375);
    SetTime(1801 - 200 - 373, 2);
    pao_operator.pao({{2, 8.575}, {4, 8.575}});
    SetTime(1801 - 200 + 210 - 298, 2);
    Ice3(298);
    ice_filler.coffee();

    // wave3 I3PAPDD-PP
    SetTime(-200 + 210 + 400 - 373, 3);
    pao_operator.pao({{2, 8.575}, {4, 8.575}});
    SetTime(-200 + 210 + 400 + 220 - 373, 3);
    pao_operator.pao({{1, 8.575}, {4, 8.575}});
    SetTime(-200 + 210 + 400 + 220 - 100, 3);
    Card(CHERRY_BOMB, 1, 8);
    SetTime(1738 - 200 - 373, 3);
    pao_operator.pao({{2, 8.575}, {4, 8.575}});
    SetTime(1738 - 200 + 210 - 298, 3);
    Ice3(298);
    ice_filler.coffee();

    // wave4 I3PPDD-PP
    SetTime(-200 + 210 + 400 - 373, 4);
    pao_operator.pao({{2, 8.575}, {4, 8.575}});
    SetTime(-200 + 210 + 400 + 220 - 373, 4);
    pao_operator.pao({{1, 8.575}, {4, 8.575}});
    SetTime(1738 - 200 - 373, 4);
    pao_operator.pao({{2, 8.575}, {4, 8.575}});
    SetTime(1738 - 200 + 210 - 298, 4);
    Ice3(298);
    ice_filler.coffee();

    // wave5 I3PPDD-PP
    SetTime(-200 + 210 + 400 - 373, 5);
    pao_operator.pao({{2, 8.575}, {4, 8.575}});
    SetTime(-200 + 210 + 400 + 220 - 373, 5);
    pao_operator.pao({{1, 8.575}, {4, 8.575}});
    SetTime(1738 - 200 - 373, 5);
    pao_operator.pao({{2, 8.575}, {4, 8.575}});
    SetTime(1738 - 200 + 210 - 298, 5);
    Ice3(298);
    ice_filler.coffee();

    // wave6 I3PPDD-PP
    SetTime(-200 + 210 + 400 - 373, 6);
    pao_operator.pao({{2, 8.575}, {4, 8.575}});
    SetTime(-200 + 210 + 400 + 220 - 373, 6);
    pao_operator.pao({{1, 8.575}, {4, 8.575}});
    SetTime(1738 - 200 - 373, 6);
    pao_operator.pao({{2, 8.575}, {4, 8.575}});
    SetTime(1738 - 200 + 210 - 298, 6);
    Ice3(298);
    ice_filler.coffee();

    // wave7 I3PPDD-PP
    SetTime(-200 + 210 + 400 - 373, 7);
    pao_operator.pao({{2, 8.575}, {4, 8.575}});
    SetTime(-200 + 210 + 400 + 220 - 373, 7);
    pao_operator.pao({{1, 8.575}, {4, 8.575}});
    SetTime(1738 - 200 - 373, 7);
    pao_operator.pao({{2, 8.575}, {4, 8.575}});
    SetTime(1738 - 200 + 210 - 298, 7);
    Ice3(298);
    ice_filler.coffee();

    // wave8 I3PPDD-PP
    SetTime(-200 + 210 + 400 - 373, 8);
    pao_operator.pao({{2, 8.575}, {4, 8.575}});
    SetTime(-200 + 210 + 400 + 220 - 373, 8);
    pao_operator.pao({{1, 8.575}, {4, 8.575}});
    SetTime(1875 - 200 - 373, 8);
    pao_operator.pao({{2, 8.575}, {4, 8.575}});
    SetTime(1875 - 200 + 210 - 298, 8);
    Ice3(298);
    ice_filler.coffee();

    // wave9 I3PPDD-PP-N-PP
    SetTime(-200 + 210 + 400 - 373, 9);
    pao_operator.pao({{2, 8.575}, {4, 8.575}});
    SetTime(-200 + 210 + 400 + 220 - 373, 9);
    pao_operator.pao({{1, 8.575}, {4, 8.575}});
    SetTime(1770 - 200 - 373, 9);
    pao_operator.pao({{2, 8.575}, {4, 8.575}});
    SetTime(1770 - 200 + 220 - 298, 9);
    Card(DOOM_SHROOM, 2, 8);
    Card(COFFEE_BEAN, 2, 8);
    SetTime(1770 - 200 + 220 + 220 - 373, 9);
    pao_operator.pao({{1, 8.575}, {4, 8.575}});
    SetTime(1770 - 200 + 220 + 220 + 4, 9);
    EndingTheWave(9);

    // wave10 A'Pd/PSd 首代
    SetTime(199, 10);
    Card(JALAPENO, 2, 9);
    SetTime(199 + 100 + 105 - 373, 10);
    pao_operator.pao(2, 8.575);
    SetTime(199 + 100 + 105 + 257 - 373, 10);
    pao_operator.pao(2, 3.5);
    SetTime(199 + 100 + 105 - 110 - 373, 10);
    pao_operator.pao({{4, 8.575}, {4, 8.575}});
    SetTime(199 + 100 + 105 - 110 + 257 - 373, 10);
    pao_operator.pao(4, 2.975);
    SetTime(1 + 601 - 298, 10);
    Ice3(298);
    ice_filler.coffee();

    // wave11 IPA-PP 首代
    SetTime(594 - 373, 11);
    pao_operator.pao(2, 7.025);
    SetTime(252 - 100, 11);
    Card(CHERRY_BOMB, 4, 8);
    SetTime(1738 - 200 - 373, 11);
    pao_operator.pao({{2, 8.575}, {4, 8.575}});
    SetTime(1738 - 200 + 210 - 298, 11);
    Ice3(298);
    ice_filler.coffee();

    // wave12 I3PaPDD-PP
    SetTime(-200 + 210 + 400 - 373, 12);
    pao_operator.pao({{2, 8.575}, {4, 8.575}});
    SetTime(-200 + 210 + 400 - 182, 12);
    Card(SQUASH, 1, 8);
    SetTime(-200 + 210 + 400 + 220 - 373, 12);
    pao_operator.pao({{1, 8.575}, {4, 8.575}});
    SetTime(1738 - 200 - 373, 12);
    pao_operator.pao({{2, 8.575}, {4, 8.575}});
    SetTime(1738 - 200 + 210 - 298, 12);
    Ice3(298);
    ice_filler.coffee();

    // wave13 I3PPDD-PP
    SetTime(-200 + 210 + 400 - 373, 13);
    pao_operator.pao({{2, 8.575}, {4, 8.575}});
    SetTime(-200 + 210 + 400 + 220 - 373, 13);
    pao_operator.pao({{1, 8.575}, {4, 8.575}});
    SetTime(1738 - 200 - 373, 13);
    pao_operator.pao({{2, 8.575}, {4, 8.575}});
    SetTime(1738 - 200 + 210 - 298, 13);
    Ice3(298);
    ice_filler.coffee();

    // wave14 I3PPDD-PP
    SetTime(-200 + 210 + 400 - 373, 14);
    pao_operator.pao({{2, 8.575}, {4, 8.575}});
    SetTime(-200 + 210 + 400 + 220 - 373, 14);
    pao_operator.pao({{1, 8.575}, {4, 8.575}});
    SetTime(1738 - 200 - 373, 14);
    pao_operator.pao({{2, 8.575}, {4, 8.575}});
    SetTime(1738 - 200 + 210 - 298, 14);
    Ice3(298);
    ice_filler.coffee();

    // wave15 I3PPDD-PP
    SetTime(-200 + 210 + 400 - 373, 15);
    pao_operator.pao({{2, 8.575}, {4, 8.575}});
    SetTime(-200 + 210 + 400 + 220 - 373, 15);
    pao_operator.pao({{1, 8.575}, {4, 8.575}});
    SetTime(1738 - 200 - 373, 15);
    pao_operator.pao({{2, 8.575}, {4, 8.575}});
    SetTime(1738 - 200 + 210 - 298, 15);
    Ice3(298);
    ice_filler.coffee();

    // wave16 I3PPDD-PP
    SetTime(-200 + 210 + 400 - 373, 16);
    pao_operator.pao({{2, 8.575}, {4, 8.575}});
    SetTime(-200 + 210 + 400 + 220 - 373, 16);
    pao_operator.pao({{1, 8.575}, {4, 8.575}});
    SetTime(1738 - 200 - 373, 16);
    pao_operator.pao({{2, 8.575}, {4, 8.575}});
    SetTime(1738 - 200 + 210 - 298, 16);
    Ice3(298);
    ice_filler.coffee();

    // wave17 I3PPDD-PP
    SetTime(-200 + 210 + 400 - 373, 17);
    pao_operator.pao({{2, 8.575}, {4, 8.575}});
    SetTime(-200 + 210 + 400 + 220 - 373, 17);
    pao_operator.pao({{1, 8.575}, {4, 8.575}});
    SetTime(1738 - 200 - 373, 17);
    pao_operator.pao({{2, 8.575}, {4, 8.575}});
    SetTime(1738 - 200 + 210 - 298, 17);
    Ice3(298);
    ice_filler.coffee();

    // wave18 I3PPDD-PP
    SetTime(-200 + 210 + 400 - 373, 18);
    pao_operator.pao({{2, 8.575}, {4, 8.575}});
    SetTime(-200 + 210 + 400 + 220 - 373, 18);
    pao_operator.pao({{1, 8.575}, {4, 8.575}});
    SetTime(1875 - 200 - 373, 18);
    pao_operator.pao({{2, 8.575}, {4, 8.575}});
    SetTime(1875 - 200 + 210 - 298, 18);
    Ice3(298);
    ice_filler.coffee();

    // wave19 I3PPDD-PP-N-PP
    SetTime(-200 + 210 + 400 - 373, 19);
    pao_operator.pao({{2, 8.575}, {4, 8.575}});
    SetTime(-200 + 210 + 400 + 220 - 373, 19);
    pao_operator.pao({{1, 8.575}, {4, 8.575}});
    SetTime(1770 - 200 - 373, 19);
    pao_operator.pao({{2, 8.575}, {4, 8.575}});
    SetTime(1770 - 200 + 220 - 298, 19);
    Card(DOOM_SHROOM, 2, 8);
    Card(COFFEE_BEAN, 2, 8);
    SetTime(1770 - 200 + 220 + 220 - 373, 19);
    pao_operator.pao({{1, 8.575}, {4, 8.575}});
    SetTime(1770 - 200 + 220 + 220 + 4, 19);
    EndingTheWave(19);

    // wave20 PPSSDD
    SetTime(341 - 376, 20);
    pao_operator.pao({{2, 9}, {4, 9}, {2, 9}, {4, 9}});
    SetTime(341 + 110 - 376, 20);
    pao_operator.pao({{1, 8.975}, {4, 8.975}});
    SetTime(737 - 100, 20);
    Card(JALAPENO, 3, 8);
    EndingTheWave(20);
}
void EndingTheWave(int wave)
{
    InsertOperation([=]() {
        std::vector<bool> is_exist_gargantuar_in_the_row(5, false);
        int remaining_row = -1;
        auto zombies = GetMainObject()->zombieArray();
        for (int index = 0; index < GetMainObject()->zombieTotal(); ++index) {
            if (!zombies[index].isDead() && !zombies[index].isDisappeared() && (zombies[index].type() == GARGANTUAR || zombies[index].type() == GIGA_GARGANTUAR)) {
                is_exist_gargantuar_in_the_row[zombies[index].row()] = true;
            }
        }
        // 按{1, 5, 2, 3, 4}的顺序选择留下的巨人的行数
        {
            InsertGuard ig(false);
            if (is_exist_gargantuar_in_the_row[1 - 1]) {
                pao_operator.recoverPao({{3, 9}, {5, 9}});
                remaining_row = 1;
            } else if (is_exist_gargantuar_in_the_row[5 - 1]) {
                pao_operator.recoverPao({{1, 9}, {3, 9}});
                remaining_row = 5;
            } else if (is_exist_gargantuar_in_the_row[2 - 1]) {
                pao_operator.recoverPao(4, 9);
                remaining_row = 2;
            } else if (is_exist_gargantuar_in_the_row[3 - 1]) {
                pao_operator.recoverPao(5, 9);
                remaining_row = 3;
            } else if (is_exist_gargantuar_in_the_row[4 - 1]) {
                remaining_row = 4;
            }
        }
        int index_snow_pea_seed = GetSeedIndex(SNOW_PEA);
        if (wave == 9 || wave == 19) {
            if (index_snow_pea_seed >= 0) {
                CardNotInQueue(index_snow_pea_seed + 1, remaining_row, 8);
            }
        }
        block_giga.pushFunc([=]() {
            BlockGargantuar({{remaining_row, 9}, {remaining_row, 8}});
        });
        int wave_time;
        if (wave == 9 || wave == 19) {
            wave_time = 4500 - 200;
        } else { // wave == 20
            wave_time = 5500;
        }
        SetTime(wave_time - 373, wave);
        pao_operator.recoverPao({{2, 9}, {4, 9}});
        block_giga.stop();
        SetTime(wave_time, wave);
        Shovel({{remaining_row, 9}, {remaining_row, 8}});
    });
}
void BlockGargantuar(std::vector<Grid> pos)
{
    for (Grid each : pos) {
        auto zombies = GetMainObject()->zombieArray();
        auto seeds = GetMainObject()->seedArray();
        std::vector<int> indices_seed = {GetSeedIndex(SNOW_PEA), GetSeedIndex(PUFF_SHROOM)};
        for (int index = 0; index < GetMainObject()->zombieTotal(); ++index) {
            if (!zombies[index].isDead() && !zombies[index].isDisappeared() && (zombies[index].type() == GARGANTUAR || zombies[index].type() == GIGA_GARGANTUAR) && zombies[index].row() + 1 == each.row && (zombies[index].abscissa() <= 40 + (each.col - 1) * 80 + 30 + 1 && zombies[index].abscissa() >= 40 + (each.col - 1) * 80 - 5) && zombies[index].state() == 0) {
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