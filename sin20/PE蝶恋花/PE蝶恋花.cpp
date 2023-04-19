/*
 * @Author: SKOSKX
 * @Date: 2023-04-11
 * @Description: [PE]蝶恋花七炮_ch6-3475：PP|IP(a)-PP|PP|Ia(P/A)-N(A)，(601|1136|601|1137)
 */

#include "avz.h"
#include "avz_more.h"
#include "sin20_tools.h"
#include "DanceCheat.h"

using namespace AvZ;
using namespace cresc;
using namespace sin20;

TickRunner tick_runner;

void SmartPumpkin()
{
    auto pa = GetMainObject()->plantArray();
    auto doomSite = GetPlantIndex(4, 9, DOOM_SHROOM);
    if (IsUsable(PUMPKIN) && doomSite >= 0 && pa[doomSite].hp() <= 40)
        CardNotInQueue(GetCardIndex(PUMPKIN) + 1, 4, 9);
}

void Script()
{
    OpenMultipleEffective('O');
    A_TAS();
    SetZombies({PJ_0, LZ_2, CG_3, WW_8, QS_11, BC_12, XC_15, KG_17, TT_18, BJ_20, FT_21, BY_23, HY_32}); //出怪：普通路障撑杆舞王潜水 冰车小丑矿工跳跳蹦极 扶梯白眼红眼 13怪
    AverageSpawn({CG_3, BC_12, KG_17, TT_18, HY_32});
    BungeeManipulate({{3, 6}, {2, 2}, {4, 2}, {2, 5}}, {10, 20});
    SelectCards({ICE_SHROOM,      //I
                 M_ICE_SHROOM,    //I'
                 COFFEE_BEAN,     //cof
                 DOOM_SHROOM,     //N
                 PUMPKIN,         //南瓜
                 CHERRY_BOMB,     //A
                 LILY_PAD,        //莲叶
                 SQUASH,          //a
                 SNOW_PEA,        //冰豆
                 UMBRELLA_LEAF}); //伞叶
    KeyConnect('A', []() { pao_operator.pao(MouseRow(), MouseCol()); });
    KeyConnect('S', []() {
        auto id = GetCardIndex(SNOW_PEA);
        if (GetMainObject()->seedArray()[id].isUsable())
            CardNotInQueue(id + 1, 6, 4);
    });
    KeyConnect('D', []() {
        auto id = GetCardIndex(UMBRELLA_LEAF);
        if (GetMainObject()->seedArray()[id].isUsable())
            CardNotInQueue(id + 1, 5, 7);
    });
    //KeyConnect('F', []() { SkipTick(1000, 9); });
    //KeyConnect('G', []() { SkipTick(1000, 19); });
    KeyConnect('F', []() {
        Shovel({{1, 5}, {2, 1}, {1, 1, true}, {2, 4, true}, {2, 6, true}});
    });

    SetTime(-599, 1);
    pao_operator.autoGetPaoList();
    Card(PUMPKIN, 2, 4);
    ice_filler.start({{4, 2}, {6, 5}, {6, 6}});
    Delay(3001);
    Card(PUMPKIN, 2, 6);
    Delay(3001);
    Card(PUMPKIN, 1, 1);

    SetTime(-1, 1);
    DanceCheat(DanceCheatMode::FAST);
    SetTime(-65);
    pao_operator.pao(5, 9);
    Delay(-60);
    pao_operator.pao(2, 9);
    SetTime(601 + 95 - 298);
    ice_filler.coffee();
    Ice3(298);

    SetTime(105 - 100, 2);
    Card(CHERRY_BOMB, 1, 9);
    //会收掉75%的跳跳和约37.7%的气球，被收掉的跳跳和气球总等效血量134.421
    //8列樱桃全收两行冰车最早时机218，但此时撑杆已落地，故不能使用8列樱桃
    SetTime(953 - 373);
    pao_operator.pao({{2, 8.75}, {5, 8.75}});
    Card({{LILY_PAD, 3, 9}, {DOOM_SHROOM, 3, 9}}); //先存3-9，因为前几波没鸭子
    plant_fixer.start(PUMPKIN);
    plant_fixer.resetFixHp(900);

    for (int wave : {3, 5, 7, 9, 12, 14, 16, 18})
    {
        SetTime(-1, wave);
        DanceCheat(DanceCheatMode::FAST);
        if (RangeIn(wave, {3, 7, 12, 16}))
            SetTime(233 - 373);
        else
            SetTime(231 - 373);
        pao_operator.pao(2, 9);
        SetTime(341 - 373);
        pao_operator.pao(5, 9);
        SetTime(308);
        DanceCheat(DanceCheatMode::SLOW);
        SetTime(601 + 112 - 298);
        ice_filler.coffee();
        Ice3(298);
        if (wave == 9) {
            SetTime(659); //最慢撑杆对8炮起跳
            Card(SQUASH, 2, 9);
            SetTime(601 + 936 - 373);
            pao_operator.pao({{2, 8.75}, {1, 8.1125}});
            //第二炮炸8.1125列是为了收掉正在啃食南瓜的撑杆(intx = 450)
            DanceCheat(DanceCheatMode::STOP);
            SetTime(601 + 1375 - 373); //卡5路红眼有利相位
            pao_operator.pao(5, 8.75);
            pao_operator.recoverPao({{1, 8.75}, {5, 8.75}, {4, 8.75}});
            SetTime(4300 - 181);
            Card(SQUASH, 6, 6); //不能用炮收尾，否则W12时炮将不够用
            SetTime(4800);
            Card(UMBRELLA_LEAF, 1, 5);
            Delay(751);
            Card(UMBRELLA_LEAF, 2, 1);
        }
    }

    SetTime(-1, 4);
    DanceCheat(DanceCheatMode::FAST);
    SetTime(185 - 373);
    pao_operator.pao(1, 8.1875); //会收掉30%的跳跳和0.03%的气球
    //要在落地前收撑杆，炮须在189前生效，查表知185为最优热过渡时机，8.1875为全收冰车的最左落点
    SetTime(936 - 298);
    Card(COFFEE_BEAN, 3, 9);
    SetPlantActiveTime(DOOM_SHROOM, 298);

    //W6 Ia-PP 1136
    SetTime(-1, 6);
    DanceCheat(DanceCheatMode::FAST);
    SetTime(401 - 182); //219
    Card(SQUASH, 2, 9); //经计算该窝瓜必定全伤冰车、前波红眼、前波白眼
    SetTime(936 - 373);
    pao_operator.pao({{2, 8.75}, {5, 8.75}});

    //W8 IP-AN 1137
    SetTime(-1, 8);
    DanceCheat(DanceCheatMode::FAST);
    SetTime(185 - 373);
    pao_operator.pao(1, 8.1875);
    SetTime(936 - 298);
    Card({{LILY_PAD, 4, 8}, {DOOM_SHROOM, 4, 8}, {COFFEE_BEAN, 4, 8}});
    SetPlantActiveTime(DOOM_SHROOM, 298);
    SetTime(937 - 100);
    Card(CHERRY_BOMB, {{1, 9}, {2, 9}}); //防止4-8N漏炸1路巨人

    //W10 PA/P+I
    SetTime(-1, 10);
    DanceCheat(DanceCheatMode::FAST);
    SetTime(270 - 373);
    pao_operator.pao(2, 9);
    SetTime(341 - 373);
    pao_operator.pao(5, 9);
    SetTime(350 - 100); //384 770.92, 334 765.505, 349 767.139
    Card(CHERRY_BOMB, 2, 9);
    Delay(100);
    DanceCheat(DanceCheatMode::SLOW);
    SetTime(601 + 73 - 298); //最晚冰杀蹦极
    ice_filler.coffee();
    Ice3(298);

    //W11 IP-PP 1175
    SetTime(-1, 11);
    DanceCheat(DanceCheatMode::FAST);
    SetTime(237 - 373); //该落点全收三行冰车的最早时机
    pao_operator.pao(2, 8.0625); //炮炸蹦极的最右落点
    SetTime(975 - 373);
    pao_operator.pao({{2, 8.75}, {5, 8.75}});
    Delay(373 - 87);
    Card({{LILY_PAD, 4, 9}, {DOOM_SHROOM, 4, 9}});
    DanceCheat(DanceCheatMode::SLOW);
    InsertOperation([]() { tick_runner.pushFunc(SmartPumpkin); });

    //W13 Ia-N 1137
    SetTime(-1, 13);
    DanceCheat(DanceCheatMode::FAST);
    SetTime(401 - 182); //219
    Card(SQUASH, 2, 9);
    SetTime(936 - 298);
    Card(COFFEE_BEAN, 4, 9);
    SetPlantActiveTime(DOOM_SHROOM, 298);
    Delay(100);
    tick_runner.stop();

    for (int wave : {15, 19})
    {
        SetTime(-1, wave);
        DanceCheat(DanceCheatMode::FAST);
        SetTime(209 - 373);
        pao_operator.pao(1, 8.1125); //会收掉25%的跳跳和0%的气球
        SetTime(936 - 373);
        pao_operator.pao({{2, 8.75}, {5, 8.75}});
        if (wave == 19) {
            SetTime(1136 + 233 - 373);
            pao_operator.pao(2, 8.75);
            Delay(373);
            DanceCheat(DanceCheatMode::STOP);
            SetTime(1136 + 341 - 373);
            pao_operator.pao(5, 8.75);
            SetTime(1136 + 233 + 210 - 298); //233+210=443
            ice_filler.coffee();
            Ice3(298); //使用Ice3来尽可能拖延2路红眼步伐
            SetTime(2588 - 181);
            Card(SQUASH, 5, 7);
            SetTime(1136 + 601 + 1137 + 231 - 373);
            pao_operator.pao(1, 8.75);
            SetTime(1136 + 601 + 1137 + 341 - 373);
            pao_operator.pao(2, 8.75);
            pao_operator.recoverPao(5, 8.6625);
        }
    }

    //W17 Ia-AN 1137
    SetTime(-1, 17);
    DanceCheat(DanceCheatMode::FAST);
    SetTime(401 - 182); //219
    Card(SQUASH, 2, 9);
    SetTime(936 - 298);
    Card({{DOOM_SHROOM, 6, 7}, {COFFEE_BEAN, 6, 7}}); //只能收4路27.03%的dcfast鸭子
    SetPlantActiveTime(DOOM_SHROOM, 298);
    SetTime(937 - 100);
    Card(CHERRY_BOMB, 2, 9);

    //W20
    SetTime(-150, 20);
    pao_operator.pao(4, 7.5875);
    SetTime(288 - 373);
    pao_operator.pao({{2, 9}, {5, 8.6625}});
    SetTime(343 - 373);
    pao_operator.pao(2, 9);
    SetTime(344 - 181); //163种植，289起跳
    Card(SQUASH, 5, 9);
    SetTime(343 + 105 - 298); //449时刻双边Ice3
    ice_filler.coffee();
    Ice3(298);
    ice_filler.stop();
    InsertTimeOperation(450, 20, []() {
        for (auto&& zf : alive_zombie_filter)
            if (zf.type() == BJ_20 && zf.row() == 2 && zf.abscissa() == 440)
                zf.freezeCountdown() = 405;
    });
    SetTime(448 + 751 - 1 - 297);
    Card({{DOOM_SHROOM, 5, 8}, {COFFEE_BEAN, 5, 8}});
    SetPlantActiveTime(DOOM_SHROOM, 297);
    SetTime(1505 - 373);
    pao_operator.pao({{2, 8.75}, {2, 8.75}});
    SetTime(1914 - 373);
    pao_operator.pao(5, 8.6625);
    plant_fixer.stop();
}