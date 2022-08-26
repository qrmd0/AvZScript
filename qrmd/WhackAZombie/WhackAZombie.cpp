/*
 * @Author: qrmd
 * @Date: 2022-08-25 10:21:03
 * @LastEditors: qrmd
 * @LastEditTime: 2022-08-25 11:05:01
 * @Description:Whack A Zombie（打僵尸）挂机脚本
 * 使用方法：1、前往https://gitee.com/vector-wlc/AsmVsZombies，根据教程下载并安装好AsmVsZombies
 *          2、在Visul Studio Code中打开本脚本，右键点击编辑区空白处，在弹出菜单中选择“AvZ:Run Script”
 * 来自AvZScript公开脚本仓库：
 * 主库：https://github.com/qrmd0/AvZScript
 * 镜像库：https://gitee.com/qrmd/AvZScript
 * Copyright (c) 2022 by qrmd, All Rights Reserved.
 */
#include "avz.h"
using namespace AvZ;

// *** Not In Queue
// 左键点击场上的僵尸
void ClickZombie();
TickRunner zombie_clicker;

// *** Not In Queue
// 忽略鼠标指针状态，强制自动收集战利品
void ForceCollectItem();
TickRunner force_item_collector;

// *** Not In Queue
// 使用墓碑吞噬者
void UseGraveBuster();
TickRunner grave_buster_user;

void Script()
{
    zombie_clicker.pushFunc(ClickZombie);
    grave_buster_user.pushFunc(UseGraveBuster);
    item_collector.stop();
    force_item_collector.pushFunc(ForceCollectItem);
}

void ClickZombie()
{
    for (auto&& zombie : alive_zombie_filter)
        if (zombie->existTime() > 50)
            LeftClick(int(zombie->abscissa()) + 57, zombie->row() * 100 + 75);
}
void ForceCollectItem()
{
    auto item = GetMainObject()->itemArray();
    int total = GetMainObject()->itemTotal();
    int collect_index = -1;
    for (int index = 0; index < total; ++index, ++item) {
        if (item->isCollected() || item->isDisappeared())
            continue;
        collect_index = index;
        if (RangeIn(item->type(), {4, 5, 6}))
            break;
    }
    if (collect_index == -1)
        return;
    item = GetMainObject()->itemArray() + collect_index;
    float item_x = item->abscissa();
    float item_y = item->ordinate();
    if (item_x >= 0.0 && item_y >= 70) {
        SafeClick();
        int x = static_cast<int>(item_x + 30);
        int y = static_cast<int>(item_y + 30);
        LeftClick(x, y);
        SafeClick();
    }
}
void UseGraveBuster()
{
    if (GetMainObject()->seedArray()[GetSeedIndex(GRAVE_BUSTER)].isUsable() && GetMainObject()->sun() >= 75) {
        for (int col = 1; col <= 9; ++col) {
            for (int row = 1; row <= 5; ++row) {
                if (Asm::getPlantRejectType(GRAVE_BUSTER, row - 1, col - 1) == Asm::NIL) {
                    SetNowTime();
                    Card(GRAVE_BUSTER, row, col);
                    return;
                }
            }
        }
    }
}