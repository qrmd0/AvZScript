/*
 * @Author: qrmd
 * @Date: 2022-06-15 12:42:11
 * @LastEditors: qrmd
 * @LastEditTime: 2022-06-16 10:22:41
 * @Description:ME神之六炮 全难度极限出怪运阵演示脚本
 * 使用方法：1、前往https://gitee.com/vector-wlc/AsmVsZombies，根据教程下载并安装好AsmVsZombies
 *          2、在Visul Studio Code中打开本脚本，右键点击编辑区空白处，在弹出菜单中选择“AvZ:Run Script”
 * 更多AvZ脚本尽在AvZScript公开脚本仓库：
 * 主库：https://github.com/qrmd0/AvZScript
 * 镜像库：https://gitee.com/qrmd/AvZScript
 * Copyright (c) 2022 by qrmd , All Rights Reserved.
 */

#include "avz.h"

using namespace AvZ;
using namespace std;
// 后场风炮
PaoOperator slope_cannon;
// 前场平地炮
PaoOperator flat_cannon;
// 自动在指定位置放置植物触发巨人僵尸举锤阻挡其前进。结合TickRunner使用
void BlockGargantuar(vector<Grid> pos);
TickRunner block_giga;
// *** Not In Queue
// 返回[wave]波[row]行是否刷新了红眼巨人僵尸
bool GetIsRefreshGiga(int wave, int row);
void Script()
{
    // 脚本在游戏主界面和选择植物界面生效
    OpenMultipleEffective('Q', MAIN_UI_OR_FIGHT_UI);
    // 全难度极限出怪：普僵、撑杆、橄榄、冰车、小丑、跳跳、小偷、扶梯、投篮、白眼、红眼
    SetZombies({ZOMBIE, POLE_VAULTING_ZOMBIE, FOOTBALL_ZOMBIE, ZOMBONI, JACK_IN_THE_BOX_ZOMBIE, POGO_ZOMBIE, BUNGEE_ZOMBIE, LADDER_ZOMBIE, CATAPULT_ZOMBIE, GARGANTUAR, GIGA_GARGANTUAR});
    // 选择植物：花盆、寒冰菇、模仿寒冰菇、毁灭菇、倭瓜、樱桃炸弹、火爆辣椒、高坚果、三叶草、叶子保护伞
    SelectCards({FLOWER_POT, ICE_SHROOM, M_ICE_SHROOM, DOOM_SHROOM, SQUASH, CHERRY_BOMB, JALAPENO, TALL_NUT, BLOVER, UMBRELLA_LEAF});
    SetTime(-599, 1);
    // 填充炮列表
    slope_cannon.resetPaoList({{2, 1}, {3, 1}, {4, 1}});
    flat_cannon.resetPaoList({{2, 6}, {3, 6}, {4, 6}});
    // 种植临时植物
    Card(FLOWER_POT, 1, 1);
    SetTime(-599 + 751, 1);
    Card(FLOWER_POT, 1, 2);
    Card(TALL_NUT, 1, 2);
    SetTime(-599 + 751 + 751, 1);
    Card(FLOWER_POT, 5, 2);
    SetTime(-599 + 751 + 3001, 1);
    Card(TALL_NUT, 5, 2);
    // 主体节奏 邻C7u IP-PP|IPa-PP|PA|N|PP 1738|1738|601|601|601 每波执行确定的操作，不考虑非旗帜波的刷新延迟
    // wave1 PP
    SetTime(601 - 200 - 387 - 3, 1);
    slope_cannon.roofPao(2, 9);
    flat_cannon.roofPao(4, 9);

    // wave2 IP-PP
    SetTime(1 - 100, 2);
    Card(ICE_SHROOM, 1, 1);
    // 402cs为保证下次PA波炮复用的最晚时机
    SetTime(402 - 387 - 3, 2);
    flat_cannon.roofPao(3, 8.5);
    SetTime(1738 - 200 - 387, 2);
    slope_cannon.roofPao(2, 9);
    flat_cannon.roofPao(4, 9);

    // wave3 IPa-PP
    SetTime(-200, 3);
    Card(M_ICE_SHROOM, 1, 1);
    // 402cs为保证下次PA波炮复用的最晚时机
    SetTime(402 - 387 - 3, 3);
    slope_cannon.roofPao(3, 8.5);
    // 689cs为冰道覆盖9列的最早时机
    SetTime(689 - 1 - 182, 3);
    Card(FLOWER_POT, 4, 9);
    Card(SQUASH, 4, 9);
    SetTime(1738 - 200 - 387, 3);
    slope_cannon.roofPao(2, 9);
    flat_cannon.roofPao(4, 9);

    // wave4 PA
    SetTime(601 - 200 - 387 - 3, 4);
    flat_cannon.roofPao(2, 9);
    SetTime(601 - (751 - (401 - 100)), 4);
    Card(FLOWER_POT, 4, 9);
    // 283cs为投篮僵尸碾压9列花盆的最早时机
    SetTime(283 - 1, 4);
    Card(CHERRY_BOMB, 4, 9);

    // wave5 N
    SetTime(601 - 200 - 100, 5);
    Card(FLOWER_POT, 3, 9);
    Card(DOOM_SHROOM, 3, 9);

    // wave6 PP
    SetTime(601 - 200 - 387 - 3, 6);
    slope_cannon.roofPao(2, 9);
    flat_cannon.roofPao(4, 9);

    // wave7 IPa-PP
    SetTime(1 - 100, 7);
    Card(ICE_SHROOM, 1, 1);
    // 402cs为保证下次PA波炮复用的最晚时机
    SetTime(402 - 387 - 3, 7);
    slope_cannon.roofPao(3, 8.5);
    SetTime(689 - 1 - 182, 7);
    Card(FLOWER_POT, 4, 9);
    Card(SQUASH, 4, 9);
    SetTime(1738 - 200 - 387, 7);
    slope_cannon.roofPao(2, 9);
    flat_cannon.roofPao(4, 9);

    // wave8 IP-PP
    SetTime(-200, 8);
    Card(M_ICE_SHROOM, 1, 1);
    // 402cs为保证下次PA波炮复用的最晚时机
    SetTime(402 - 387 - 3, 8);
    flat_cannon.roofPao(3, 8.5);
    SetTime(1738 - 200 - 387, 8);
    slope_cannon.roofPao(2, 9);
    flat_cannon.roofPao(4, 9);

    // wave9 PA(-N-PP-AA')
    SetTime(601 - 200 - 387 - 3, 9);
    slope_cannon.roofPao(2, 9);
    // 283cs为投篮僵尸碾压9列花盆的最早时机
    SetTime(283 - 1, 9);
    Card(FLOWER_POT, 4, 9);
    Card(CHERRY_BOMB, 4, 9);
    slope_cannon.recoverPao({{2, 9}});
    flat_cannon.recoverPao({{3, 9}, {4, 9}});
    SetTime(283 - 1 + 751, 9);
    Card(FLOWER_POT, 2, 9);
    Card(DOOM_SHROOM, 2, 9);
    SetTime(283 - 1 + 751 + 751, 9);
    Card(FLOWER_POT, 5, 3);
    SetTime(3600 - 100, 9);
    Card(JALAPENO, 1, 1);
    // wave10 PP
    SetTime(0, 10);
    Card(UMBRELLA_LEAF, 1, 1);
    SetTime(395 + 100, 10);
    Shovel(1, 1);
    SetTime(395 + 1500, 10);
    Card(FLOWER_POT, 5, 2);
    Card(TALL_NUT, 5, 2);
    SetTime(601 - 200 - 387, 10);
    slope_cannon.roofPao(2, 9);
    flat_cannon.roofPao(4, 9);

    // wave11 IPa-PP
    SetTime(1 - 100, 11);
    Card(ICE_SHROOM, 1, 1);
    // 402cs为保证下次PA波炮复用的最晚时机
    SetTime(402 - 387 - 3, 11);
    slope_cannon.roofPao(3, 8.5);
    // 689cs为冰道覆盖9列的最早时机
    SetTime(689 - 1 - 182, 11);
    Card(FLOWER_POT, 4, 9);
    Card(SQUASH, 4, 9);
    SetTime(1738 - 200 - 387, 11);
    slope_cannon.roofPao(2, 9);
    flat_cannon.roofPao(4, 9);

    // wave12 IP-PP
    SetTime(-200, 12);
    Card(M_ICE_SHROOM, 1, 1);
    // 402cs为保证下次PA波炮复用的最晚时机
    SetTime(402 - 387 - 3, 12);
    flat_cannon.roofPao(3, 8.5);
    SetTime(1738 - 200 - 387, 12);
    slope_cannon.roofPao(2, 9);
    flat_cannon.roofPao(4, 9);

    // wave13 PA
    SetTime(601 - 200 - 387 - 3, 13);
    slope_cannon.roofPao(2, 9);
    SetTime(601 - (751 - (401 - 100)), 13);
    Card(FLOWER_POT, 4, 9);
    // 283cs为投篮僵尸碾压9列花盆的最早时机
    SetTime(283 - 1, 13);
    Card(CHERRY_BOMB, 4, 9);

    // wave14 N
    SetTime(601 - 200 - 100, 14);
    Card(FLOWER_POT, 4, 9);
    Card(DOOM_SHROOM, 4, 9);

    // wave15 PP
    SetTime(601 - 200 - 387 - 3, 15);
    slope_cannon.roofPao(2, 9);
    flat_cannon.roofPao(4, 9);

    // wave16 IP-PP
    SetTime(1 - 100, 16);
    Card(ICE_SHROOM, 1, 1);
    // 402cs为保证下次PA波炮复用的最晚时机
    SetTime(402 - 387 - 3, 16);
    flat_cannon.roofPao(3, 8.5);
    SetTime(1738 - 200 - 387, 16);
    slope_cannon.roofPao(2, 9);
    flat_cannon.roofPao(4, 9);

    // wave17 IPa-PP
    SetTime(-200, 17);
    Card(M_ICE_SHROOM, 1, 1);
    // 402cs为保证下次PA波炮复用的最晚时机
    SetTime(402 - 387 - 3, 17);
    slope_cannon.roofPao(3, 8.5);
    SetTime(689 - 1 - 182, 17);
    Card(FLOWER_POT, 4, 8);
    Card(SQUASH, 4, 8);
    SetTime(1738 - 200 - 387, 17);
    slope_cannon.roofPao(2, 9);
    flat_cannon.roofPao(4, 9);

    // wave18 PA
    // 550cs为小丑爆炸的最早时机
    SetTime(550 - 1 - 387, 18);
    flat_cannon.roofPao(2, 9);
    SetTime(700 - 100, 18);
    Card(FLOWER_POT, 4, 8);
    Card(CHERRY_BOMB, 4, 8);

    // wave19 N(-PP-PA-PP)
    SetTime(601 - 200 - 387 - 3, 19);
    slope_cannon.recoverPao(2, 9);
    flat_cannon.recoverPao(4, 9);
    SetTime(609, 19);
    Card(FLOWER_POT, 3, 9);
    Card(DOOM_SHROOM, 3, 9);
    Card(JALAPENO, 1, 1);
    slope_cannon.recoverPao({{2, 9}, {2, 9}});
    flat_cannon.recoverPao({{4, 9}, {3, 9}});
    SetTime(609 + 751, 19);
    Card(FLOWER_POT, 4, 8);
    Card(SQUASH, 4, 8);
    // 开始自动垫巨人僵尸
    InsertOperation([=]() {
        block_giga.pushFunc([]() {
            BlockGargantuar({{2, 8}, {4, 8}});
        });
    });

    // wave20 PP(-PP-Aa-N)
    SetTime(0, 20);
    Card(UMBRELLA_LEAF, 1, 1);
    SetTime(395 + 100, 20);
    Shovel(1, 1);
    // 冰冻空降
    SetTime(450 - 100, 20);
    Card(FLOWER_POT, 5, 1);
    Card(ICE_SHROOM, 5, 1);
    // 炮消空降
    SetTime(450 + 399 - 387, 20);
    slope_cannon.roofPao(2, 7.5);
    flat_cannon.roofPao(4, 7.5);
    slope_cannon.recoverPao({{2, 9}, {2, 9}});
    flat_cannon.recoverPao({{4, 9}, {4, 9}});
    SetTime(450 - 100 + 751, 20);
    Card(FLOWER_POT, 1, 9);
    Card(CHERRY_BOMB, 1, 9);
    SetTime(450 + 751, 20);
    Card(DOOM_SHROOM, 1, 9);
    SetTime(450 - 100 + 751 + 751, 20);
    Card(FLOWER_POT, 4, 8);
    Card(SQUASH, 4, 8);
    SetTime(450 - 100 + 751 + 751 + 751, 20);
    Card(FLOWER_POT, 5, 3);
    Card(JALAPENO, 5, 3);
}
void BlockGargantuar(vector<Grid> pos)
{
    for (Grid each : pos) {
        auto zombies = GetMainObject()->zombieArray();
        auto seeds = GetMainObject()->seedArray();
        vector<int> indices_seed = {GetSeedIndex(FLOWER_POT)};
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
bool GetIsRefreshGiga(int wave, int row)
{
    auto zombies = GetMainObject()->zombieArray();
    for (int index = 0; index < GetMainObject()->zombieTotal(); ++index) {
        if (!zombies[index].isDisappeared() && !zombies[index].isDead() && zombies[index].type() == GIGA_GARGANTUAR && zombies[index].row() + 1 == row && zombies[index].existTime() <= NowTime(wave)) {
            return true;
        }
    }
    return false;
}