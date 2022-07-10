/*
 * @Author: qrmd
 * @Date: 2022-06-14 21:55:26
 * @LastEditors: qrmd
 * @LastEditTime: 2022-06-15 12:30:35
 * @Description:ME核聚变六炮 全难度极限出怪运阵演示脚本
 * 使用方法：1、前往https://gitee.com/vector-wlc/AsmVsZombies，根据教程下载并安装好AsmVsZombies
 *          2、在Visul Studio Code中打开本脚本，右键点击编辑区空白处，在弹出菜单中选择“AvZ:Run Script”
 * 更多AvZ脚本尽在AvZScript公开脚本仓库：
 * 主库：https://github.com/qrmd0/AvZScript
 * 镜像库：https://gitee.com/qrmd/AvZScript
 * Copyright (c) 2022 by qrmd , All Rights Reserved.
 */

#include "avz.h"

using namespace AvZ;
// 后场风炮
PaoOperator slope_cannon;
// 前场平地炮
PaoOperator flat_cannon;

void Script()
{
    // 脚本在游戏主界面和选择植物界面生效
    OpenMultipleEffective('Q', MAIN_UI_OR_FIGHT_UI);
    // 全难度极限出怪：普僵、撑杆、橄榄、冰车、小丑、跳跳、小偷、扶梯、投篮、白眼、红眼
    SetZombies({ZOMBIE, POLE_VAULTING_ZOMBIE, FOOTBALL_ZOMBIE, ZOMBONI, JACK_IN_THE_BOX_ZOMBIE, POGO_ZOMBIE, BUNGEE_ZOMBIE, LADDER_ZOMBIE, CATAPULT_ZOMBIE, GARGANTUAR, GIGA_GARGANTUAR});
    // 选择植物：花盆、寒冰菇、毁灭菇、模仿毁灭菇、倭瓜、樱桃炸弹、火爆辣椒、南瓜头、三叶草、叶子保护伞
    SelectCards({FLOWER_POT, ICE_SHROOM, DOOM_SHROOM, M_DOOM_SHROOM, SQUASH, CHERRY_BOMB, JALAPENO, PUMPKIN, BLOVER, UMBRELLA_LEAF});
    SetTime(-599, 1);
    // 铲除临时植物
    Shovel({{1, 8}, {2, 8}, {3, 8}, {4, 8}, {5, 8}});
    InsertTimeOperation(-599, 1, [=]() {
        if (GetPlantIndex(4, 2) >= 0) {
            ShovelNotInQueue(4, 2);
        }
    });
    // 开始自动修补南瓜头
    plant_fixer.start(PUMPKIN, {{1, 5}, {2, 5}, {3, 5}, {4, 5}, {5, 5}, {4, 4}, {5, 4}, {1, 3}, {2, 3}, {3, 3}, {4, 3}, {5, 3}}, 1200);
    // 填充炮列表
    slope_cannon.resetPaoList({{1, 1}, {2, 1}, {3, 1}});
    flat_cannon.resetPaoList({{1, 6}, {3, 6}, {5, 6}});
    // 主体节奏 对C7n I-PP|N|PP|PP|N|PP 1252|750|750|750|750|750 每波执行确定的操作，不考虑非旗帜波的刷新延迟
    // wave1 PP
    SetTime(750 - 200 - 387, 1);
    slope_cannon.roofPao(2, 9);
    flat_cannon.roofPao(4, 9);
    // wave2 PP
    SetTime(750 - 200 - 387, 2);
    slope_cannon.roofPao(2, 9);
    flat_cannon.roofPao(4, 9);
    // wave3 N
    SetTime(129 - 100, 3);
    Card(JALAPENO, 4, 2);
    SetTime(750 - 200 - 100, 3);
    Card(FLOWER_POT, 4, 9);
    Card(DOOM_SHROOM, 4, 9);
    // wave4 PP
    SetTime(750 - 200 - 387, 4);
    slope_cannon.roofPao(2, 9);
    flat_cannon.roofPao(4, 9);
    // wave5 I-PP
    // 98cs为巨人僵尸最早入场时机，在此之前生效以保证全部巨人在原速下受冰冻
    SetTime(98 - 1 - 100, 5);
    Card(ICE_SHROOM, 4, 2);
    SetTime(400, 5);
    Card(FLOWER_POT, 2, 8);
    Card(SQUASH, 2, 8);
    SetTime(1252 - 200 - 387, 5);
    slope_cannon.roofPao(2, 9);
    flat_cannon.roofPao(4, 9);
    // wave6 N
    // 樱桃炸弹炸上波巨人保护模仿毁灭菇，尽量不伤本波僵尸以防激活刷新
    SetTime(129 - 100, 6);
    Card(FLOWER_POT, 1, 8);
    Card(CHERRY_BOMB, 1, 8);
    SetTime(750 - 200 - 319 - 100, 6);
    Card(M_DOOM_SHROOM, 2, 8);
    // wave7 PP
    SetTime(750 - 200 - 387, 7);
    slope_cannon.roofPao(2, 9);
    flat_cannon.roofPao(4, 9);
    // wave8 PP
    SetTime(750 - 200 - 387, 8);
    slope_cannon.roofPao(2, 9);
    flat_cannon.roofPao(4, 9);
    // wave9 N(-PP-PP)
    SetTime(750 - 200 - 100, 9);
    Card(FLOWER_POT, 2, 9);
    Card(DOOM_SHROOM, 2, 9);
    slope_cannon.recoverPao({{2, 9}, {2, 9}});
    flat_cannon.recoverPao({{4, 9}, {4, 9}});
    Card(UMBRELLA_LEAF, 4, 2);
    // wave10 PP
    SetTime(-200, 10);
    Card(FLOWER_POT, 3, 8);
    Card(UMBRELLA_LEAF, 3, 8);
    SetTime(395 + 150, 10);
    Shovel(3, 8);
    // 672cs为能同时冰冻蹦极僵尸和第11波僵尸的最长波长
    SetTime(672 - 200 - 387, 10);
    slope_cannon.roofPao(2, 9);
    flat_cannon.roofPao(4, 9);
    SetTime(672 + 1 - 100, 10);
    Shovel(4, 2);
    Card(ICE_SHROOM, 4, 2);
    // wave11 I-PP
    SetTime(400, 11);
    Card(FLOWER_POT, 3, 8);
    Card(SQUASH, 3, 8);
    SetTime(1252 - 200 - 387, 11);
    slope_cannon.roofPao(2, 9);
    flat_cannon.roofPao(4, 9);
    // wave12 N
    // 樱桃炸弹炸上波巨人保护模仿毁灭菇，尽量不伤本波僵尸以防激活刷新
    SetTime(129 - 100, 12);
    Card(FLOWER_POT, 4, 8);
    Card(CHERRY_BOMB, 4, 8);
    SetTime(750 - 200 - 319 - 100, 12);
    Card(M_DOOM_SHROOM, 3, 8);
    // wave13 PP
    SetTime(750 - 200 - 387, 13);
    slope_cannon.roofPao(2, 9);
    flat_cannon.roofPao(4, 9);
    // wave14 PP
    // 增大波长以保证第18波的毁灭菇复用
    SetTime(750 + 33 - 200 - 387, 14);
    slope_cannon.roofPao(2, 9);
    flat_cannon.roofPao(4, 9);
    // wave15 N
    // 增大波长以保证第18波的毁灭菇复用
    SetTime(750 + 33 - 200 - 100, 15);
    Card(FLOWER_POT, 3, 9);
    Card(DOOM_SHROOM, 3, 9);
    // wave16 PP
    // 增大波长以保证第18波的毁灭菇复用
    SetTime(750 + 33 - 200 - 387, 16);
    slope_cannon.roofPao(2, 9);
    flat_cannon.roofPao(4, 9);
    // wave17 I-PP
    // 98cs为巨人僵尸最早入场时机，在此之前生效以保证全部巨人在原速下受冰冻
    SetTime(98 - 1 - 100, 17);
    Card(ICE_SHROOM, 4, 2);
    SetTime(400, 17);
    Card(FLOWER_POT, 4, 8);
    Card(SQUASH, 4, 8);
    SetTime(1252 - 200 - 387, 17);
    slope_cannon.roofPao(2, 9);
    flat_cannon.roofPao(4, 9);
    // wave18 N
    // 樱桃炸弹炸上波巨人保护模仿毁灭菇，尽量不伤本波僵尸以防激活刷新
    SetTime(129 - 100, 18);
    Card(FLOWER_POT, 5, 8);
    Card(CHERRY_BOMB, 5, 8);
    SetTime(750 - 200 - 319 - 100, 18);
    Card(M_DOOM_SHROOM, 4, 8);
    // wave19 PP-(PP-PP)
    SetTime(750 - 200 - 387, 19);
    slope_cannon.recoverPao({{2, 9}, {2, 9}, {2, 9}});
    flat_cannon.recoverPao({{4, 9}, {4, 9}, {4, 9}});
    Card(UMBRELLA_LEAF, 4, 2);
    // wave20 PP-(N-PP)
    // 冰杀蹦极
    SetTime(450 - 100, 20);
    Shovel(4, 2);
    Card(ICE_SHROOM, 4, 2);
    // 炮消空降
    SetTime(450 + 399 - 387, 20);
    slope_cannon.roofPao(2, 7.5);
    flat_cannon.roofPao(4, 7.5);
    slope_cannon.recoverPao({{2, 9}, {2, 9}});
    flat_cannon.recoverPao({{4, 9}, {4, 9}});
    SetTime(950, 20);
    Card(FLOWER_POT, 5, 8);
    Card(M_DOOM_SHROOM, 5, 8);
    SetTime(950 + 751, 20);
    Card(FLOWER_POT, 1, 8);
    Card(SQUASH, 1, 8);
}