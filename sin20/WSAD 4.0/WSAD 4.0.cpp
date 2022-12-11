/*
 * @Author: SKOSKX
 * @Date: 2022-10-23(update:2022-12-11)
 * @Description: WSAD小游戏
 * 更新内容：修复了可以在暂停时移动植物的bug；修复了玉米炮前轮移到弹坑上的bug；增加了修补植物功能
 * 初始提供15个植物，栈位依次为：
 * 0-玉米炮   Cob Cannon[47]
 * 1,2-忧郁菇 Gloom Shroom[42]
 * 3-冰瓜     Winter Melon[44]
 * 4-钢地刺   Spikerock[46]
 * 5-大喷菇   Fume Shroom[10]
 * 6-高坚果   Tall nut[23]
 * 7-机枪射手 Gatlin Pea[40]
 * 8-大蒜     Garlic[36]
 * 9-火炬树桩 Torchwood[22]
 * 10-仙人掌  Cactus[26]
 * 11-伞叶    Umbrella Leaf[37]
 * 场外吊两个阳光菇(12, 13)阳光菇，大大的，香香的，软乎乎的，好可爱[口水黄豆]
 */

#include "avz.h"
#include "avz_more.h"

using namespace AvZ;
using namespace cresc;

int plantID = -1; //正在被控制的植物的索引
#define prow pa[plantID].row()
#define pcol pa[plantID].col()

bool CheckGrave(int row, int col)
{
    auto place = ((cresc::MainObjectAZM *)GetMainObject())->placeArray();
    for (int i = 0; i < ((cresc::MainObjectAZM *)GetMainObject())->placeTotal(); ++i, ++place)
    {
        if (!place->isDisappeared() && place->row() == row - 1 &&
            place->col() == col - 1 && place->type() == 1)
            return true;
    }
    return false;
}
bool CheckCrater(int row, int col)
{
    auto place = ((cresc::MainObjectAZM *)GetMainObject())->placeArray();
    for (int i = 0; i < ((cresc::MainObjectAZM *)GetMainObject())->placeTotal(); ++i, ++place)
    {
        if (!place->isDisappeared() && place->row() == row - 1 &&
            place->col() == col - 1 && place->type() == 2)
            return true;
    }
    return false;
}

//判断某个格子是否没有墓碑、弹坑或植物
bool isEmpty(int row, int col)
{
    if (!CheckGrave(row, col) &&
        !CheckCrater(row, col) &&
        CheckPlant(row, col) == -1 &&
        CheckPlant(row, col - 1) != 0) //这一行利用了玉米炮只有一台且序号是0
        return true;
    else
        return false;
}

//生成植物函数
//在[r]行[c]列生成一株[type]种类的植物
void PutPlant(int r, int c, int type, bool imitater = false)
{
    r -= 1;
    c -= 1;
    __asm__ __volatile__(
        "pushal;"
        "pushl $-1;"
        "pushl %[type];"
        "movl %[r],%%eax;"
        "pushl %[c];"
        "movl 0x6a9ec0,%%ebp;"
        "movl 0x768(%%ebp), %%edi;"
        "pushl %%edi;"
        "movl $0x40d120, %%edx;"
        "calll *%%edx;"
        "popal;"
        :
        : [r] "m"(r), [c] "m"(c), [type] "m"(type)
        :);
}

void Script()
{
    OpenMultipleEffective('O', MAIN_UI_OR_FIGHT_UI);
    item_collector.stop(); //防止AvZ自动收集
    auto pa = GetMainObject()->plantArray();

    //读取并锁定鼠标所在格植物
    KeyConnect(VK_LBUTTON, [=](){
        plantID = CheckPlant(MouseRow(), MouseCol() + 0.5); //鼠标所在格植物索引
        if (plantID != -1 && //鼠标所在格有植物
            RangeIn(pa[plantID].type(), {COB_CANNON, GLOOM_SHROOM, WINTER_MELON, SPIKEROCK, FUME_SHROOM, TALL_NUT, GATLING_PEA, GARLIC, TORCHWOOD, CACTUS, UMBRELLA_LEAF}))
        {
            pa[plantID].mRef<int>(0xBC) = 30; //使植物发亮0.3s
            if (pa[plantID].type() == COB_CANNON)
                SafeClick();
        }
        else plantID = -1;
    });

    //左移
    KeyConnect('A', [=](){
        if (plantID != -1 && //当前选中了植物
            !pa[plantID].isDisappeared() && !pa[plantID].isCrushed() &&
            !GetMainObject()->gamePaused() &&
            isEmpty(prow + 1, pcol) &&
            pcol != 0)
        {
            pcol -= 1;
            pa[plantID].xi() -= 80;
            pa[plantID].mRef<int>(0x20) += 80;
        }
    });

    //右移
    KeyConnect('D', [=](){
        if (plantID != -1 && //当前选中了植物
            !pa[plantID].isDisappeared() && !pa[plantID].isCrushed() &&
            !GetMainObject()->gamePaused() &&
            pcol != 8)
        {
            if (pa[plantID].type() == COB_CANNON)
            {
                if (CheckGrave(prow + 1, pcol + 2) ||
                    CheckCrater(prow + 1, pcol + 3) ||
                    CheckPlant(prow + 1, pcol + 3) != -1)
                return; //对玉米炮的特判
            }
            else if(!isEmpty(prow + 1, pcol + 2))
                return;
            pcol += 1;
            pa[plantID].xi() += 80;
            pa[plantID].mRef<int>(0x20) -= 80;
        }
    });

    //上移
    KeyConnect('W', [=](){
        if (plantID != -1 && //当前选中了植物
            !pa[plantID].isDisappeared() && !pa[plantID].isCrushed() &&
            !GetMainObject()->gamePaused() &&
            isEmpty(prow, pcol + 1) &&
            prow != 0)
        {
            if (pa[plantID].type() == COB_CANNON &&
                (CheckCrater(prow, pcol + 2) ||
                CheckPlant(prow, pcol + 2) != -1))
                return; //对玉米炮的特判
            prow -= 1;
            pa[plantID].yi() -= 100; //这里仅针对前院行距
            pa[plantID].mRef<int>(0x20) -= 10000;
        }
    });

    //下移
    KeyConnect('S', [=](){
        if (plantID != -1 && //当前选中了植物
            !pa[plantID].isDisappeared() && !pa[plantID].isCrushed() &&
            !GetMainObject()->gamePaused() &&
            isEmpty(prow + 2, pcol + 1) &&
            prow != 4)
        {
            if (pa[plantID].type() == COB_CANNON &&
                (CheckCrater(prow + 2, pcol + 2) ||
                CheckPlant(prow + 2, pcol + 2) != -1))
                return; //对玉米炮的特判
            prow += 1;
            pa[plantID].yi() += 100; //这里仅针对前院行距
            pa[plantID].mRef<int>(0x20) += 10000;
        }
    });

    //修补植物（限钢地刺、高坚果、大蒜）
    KeyConnect('F', [=](){
        if (plantID != -1 &&
            !pa[plantID].isDisappeared() && !pa[plantID].isCrushed() &&
            !GetMainObject()->gamePaused())
        {
            if (pa[plantID].type() == SPIKEROCK && pa[plantID].hp() <= 150 &&
                GetMainObject()->sun() >= 600)
            {
                GetMainObject()->sun() -= 600; //修补需要花费四倍阳光
                auto p_row = prow + 1;
                auto p_col = pcol + 1;
                ShovelNotInQueue(p_row, p_col);
                PutPlant(p_row, p_col, SPIKEROCK, false);
            }
            else if (pa[plantID].type() == TALL_NUT && pa[plantID].hp() <= 2680 &&
                     GetMainObject()->sun() >= 500)
            {
                GetMainObject()->sun() -= 500; //修补需要花费四倍阳光
                pa[plantID].hp() = pa[plantID].hpMax();
            }
            else if (pa[plantID].type() == GARLIC && pa[plantID].hp() <= 140 &&
                     GetMainObject()->sun() >= 200)
            {
                GetMainObject()->sun() -= 200; //修补需要花费四倍阳光
                pa[plantID].hp() = pa[plantID].hpMax();
            }
        }
    });
}