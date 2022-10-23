#include "avz.h"

using namespace AvZ;
TickRunner smart_blover;

bool IsZBExist(ZombieType type, int row, int abs, int hp) //判定僵尸
{
    bool result = false;
    auto zombie = GetMainObject()->zombieArray();
    for (int index = 0; index < GetMainObject()->zombieTotal(); ++index) {
        if (zombie[index].type() == type && zombie[index].isExist() && !zombie[index].isDead() && zombie[index].row() == row - 1 && zombie[index].abscissa() < abs && zombie[index].hp() >= hp && zombie[index].state() != 70) {
            result = true;
        }
    }
    return result;
}

bool IsZBBeforeExist() //判定前场僵尸
{
    bool result = false;
    auto zombie = GetMainObject()->zombieArray();
    for (int index = 0; index < GetMainObject()->zombieTotal(); ++index) {
        if (zombie[index].isExist() && !zombie[index].isDead() && zombie[index].abscissa() > 480) {
            result = true;
        }
    }
    return result;
}

void SmartBlover() //三叶草
{
    for (int row : {1, 2, 3, 4, 5, 6}) {
        if (IsZBExist(BALLOON_ZOMBIE, row, 0, 0)) {
            CardNotInQueue(GetCardIndex(BLOVER) + 1, 1, 1);
        }
    }
}

void DealDelay(int wave) //处理刷新延迟
{

    //通常波刷新延迟，用核弹
    SetTime(401, wave);
    InsertOperation([=]() {
        if (GetMainObject()->refreshCountdown() > 200 && GetMainObject()->wave() == wave) {
            SetNowTime();
            for (PlantType i : {LILY_PAD, DOOM_SHROOM, COFFEE_BEAN}) {
                Card(GetCardIndex(i) + 1, {{3, 9}, {4, 9}});
            }
        }
    });

    //第10波刷新延迟，优先用樱桃，若仍延迟再用核
    if (wave == 10) {
        auto zombie_type = GetMainObject()->zombieTypeList();
        SetTime(1, wave);
        InsertOperation([=]() {
            int GGCount_up = 0;
            int GGCount_down = 0;
            auto zombie = GetMainObject()->zombieArray();
            for (int index = 0; index < GetMainObject()->zombieTotal(); ++index) {
                if (zombie[index].type() == GIGA_GARGANTUAR && zombie[index].isExist() && !zombie[index].isDead() && (zombie[index].row() == 0 || zombie[index].row() == 1)) {
                    GGCount_up = GGCount_up + 1;
                }
            }
            for (int index = 0; index < GetMainObject()->zombieTotal(); ++index) {
                if (zombie[index].type() == GIGA_GARGANTUAR && zombie[index].isExist() && !zombie[index].isDead() && (zombie[index].row() == 4 || zombie[index].row() == 5)) {
                    GGCount_down = GGCount_down + 1;
                }
            }
            if (zombie_type[GIGA_GARGANTUAR] || zombie_type[BUCKETHEAD_ZOMBIE]) {
                SetTime(399 - 100, wave);
                Card(CHERRY_BOMB, GGCount_down < GGCount_up ? 2 : 5, 9);
            }
        });
    }
}

void Normal_Wave(int wave) //通常波341PP激活
{
    SetTime(341 - 373, wave);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
}

void Flag_Wave(int wave) //旗帜波
{
    SetTime(341 - 373, wave);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});

    // w20冰消珊瑚
    if (wave == 20) {
        SetTime(-300, wave);
        Card({{ICE_SHROOM, 6, 1}, {COFFEE_BEAN, 6, 1}});
    }
}

void Ending_Wave(int wave) //收尾
{
    SetTime(341 - 373, wave);
    for (int i = 0; i < 3; ++i) {
        Delay(601);
        InsertOperation([=]() {
            if (GetMainObject()->refreshCountdown() > 200 && GetMainObject()->wave() == wave && IsZBBeforeExist()) {
                SetNowTime();
                pao_operator.pao({{2, 8.8}, {5, 8.8}});
            }
        });
    }
}

void Script()
{
    OpenMultipleEffective('X', MAIN_UI_OR_FIGHT_UI);
    SelectCards({ICE_SHROOM, COFFEE_BEAN, DOOM_SHROOM, LILY_PAD,
        CHERRY_BOMB, BLOVER, KERNEL_PULT, COB_CANNON, PEASHOOTER, SUNFLOWER});

    // SetGameSpeed(5); // 以倍速运行
    //跳帧，已注释，如需要则去掉两端的 /* 以及 */ 符号
    /*SkipTick([=]() {
        return true;
    });*/

    smart_blover.pushFunc(SmartBlover);

    SetTime(-599, 1);
    pao_operator.autoGetPaoList();

    for (int wave : {1, 2, 3, 4, 5, 6, 7, 8, 9, 11, 12, 13, 14, 15, 16, 17, 18, 19}) {
        Normal_Wave(wave);
    }

    for (int wave : {10, 20}) {
        Flag_Wave(wave);
    }

    for (int wave : {9, 19, 20}) {
        Ending_Wave(wave);
    }

    for (int wave : {1, 2, 3, 4, 5, 6, 7, 8, 10, 11, 12, 13, 14, 15, 16, 17, 18}) {
        DealDelay(wave);
    }
}