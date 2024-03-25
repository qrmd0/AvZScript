/*
 * 阵名: NE十五炮
 * 出处: https://tieba.baidu.com/p/1067040250
 * 节奏: C8u: IPP-PP|PADC|PPDD|IPP-PP|NDC|PPDD, (13|6|6|13|6|6)
 */
#include <avz.h>

// 使用宏定义简化代码
#define Connect(wave, time, ...) AConnect(ATime(wave, time), [=] { __VA_ARGS__; })
#define Delay(delayTime, ...) AConnect(ANowDelayTime(delayTime), [] { __VA_ARGS__; })

ACoroutine DianCai()
{
    ACard({{APUFF_SHROOM, 4, 9}, {ASUN_SHROOM, 5, 9}});
    co_await ANowDelayTime(120);
    ARemovePlant(4, 9);
    ARemovePlant(5, 9);
}

void AScript()
{
    // ASetReloadMode(AReloadMode::MAIN_UI_OR_FIGHT_UI);

    ASetZombies({
        APJ_0,  // 普僵
        ACG_3,  // 撑杆
        AWW_8,  // 舞王
        AXC_15, // 小丑
        AQQ_16, // 气球
        AKG_17, // 矿工
        ATT_18, // 跳跳
        ABJ_20, // 蹦极
        AFT_21, // 扶梯
        ATL_22, // 投篮
        ABY_23, // 白眼
        AHY_32, // 红眼
    });
    ASelectCards({
        AM_ICE_SHROOM, // 模仿寒冰菇
        AICE_SHROOM,   // 寒冰菇
        ADOOM_SHROOM,  // 毁灭菇
        ACHERRY_BOMB,  // 樱桃炸弹
        ASQUASH,       // 倭瓜
        AGRAVE_BUSTER, // 墓碑吞噬者
        APUMPKIN,      // 南瓜头
        ABLOVER,       // 三叶草
        ASUN_SHROOM,   // 阳光菇
        APUFF_SHROOM,  // 小喷菇
    });

    Connect(1, -599, aCobManager.SetList({
                         {1, 1},
                         {2, 1},
                         {3, 1},
                         {4, 1},
                         {5, 1},
                         {1, 5},
                         {2, 5},
                         {3, 5},
                         {4, 5},
                         {5, 5},
                         {1, 7},
                         {2, 7},
                         {3, 7},
                         {4, 7},
                         {5, 7},
                     }));

    for (int wave = 1; wave < 21; ++wave)
    {
        // PPD
        if (wave == 10)
        {
            Connect(wave, -56, aCobManager.Fire({{2, 9}, {4, 9}}));
            Connect(wave, 0, aCobManager.Fire(2, 9));
        }

        // IPP-PP
        else if (ARangeIn(wave, {1, 7, 11, 17}))
        {
            Connect(wave, -150, aCobManager.Fire({{2, 8.5}, {4, 8.5}}));
            Connect(wave, 5 - 100, ACard(AICE_SHROOM, 1, 9));
            if (wave == 11)
            {
                Connect(wave, -150 + 83, ACoLaunch(DianCai));
            }
            Connect(wave, 1300 - 200 - 373, aCobManager.Fire({{2, 9}, {4, 9}}));
        }

        // PADC
        else if (ARangeIn(wave, {2, 8, 12, 18}))
        {
            Connect(wave, -95, aCobManager.Fire(2, 9));
            Connect(wave, -12, aCobManager.Fire(2, 9));
            Connect(wave, -95 + 373 - 100, ACard(ACHERRY_BOMB, 5, 9));
        }

        // PPDD
        else if (ARangeIn(wave, {3, 9, 13, 19}))
        {
            Connect(wave, -95, aCobManager.Fire({{2, 9}, {5, 9}}));
            Connect(wave, -15, aCobManager.Fire({{1, 9}, {4, 9}}));
            Connect(wave, 0, ACoLaunch(DianCai));
            Connect(wave, 601 + 44 - 100 - 320, ACard(AM_ICE_SHROOM, 1, 9)); // 44cs 预判冰

            if (ARangeIn(wave, {9, 19}))
            {
                Connect(wave, 601 - 150, aCobManager.Fire(4, 9);
                        Delay(450, aCobManager.Fire(1, 9)));
                Connect(wave, 601 + 1300 - 200 - 373,
                        Delay(300, aCobManager.Fire({{2, 9}, {5, 9}})));
            }
        }

        // IPP-PP
        else if (ARangeIn(wave, {4, 14}))
        {
            Connect(wave, -150, aCobManager.Fire({{2, 8.5}, {4, 8.5}}));
            Connect(wave, 1300 - 200 - 373, aCobManager.Fire({{2, 9}, {4, 9}}));
        }

        // NDC
        else if (ARangeIn(wave, {5, 15}))
        {
            Connect(wave, -12, aCobManager.Fire(2, 9));
            Connect(wave, -95 + 373 - 100, wave == 5 ? ACard(ADOOM_SHROOM, 3, 9) : ACard(ADOOM_SHROOM, 2, 9));
            // 是 wave 5 弹坑在 3-9, 否则在 2-9
        }

        // PPDD
        else if (ARangeIn(wave, {6, 16}))
        {
            Connect(wave, -95, aCobManager.Fire({{2, 9}, {5, 9}}));
            Connect(wave, -12, aCobManager.Fire({{1, 9}, {4, 9}}));
            Connect(wave, 0, ACoLaunch(DianCai));
        }

        else if (wave == 20)
        {
            Connect(wave, -56, aCobManager.Fire({{1, 9}, {4, 9}}));
            Connect(wave, -35, aCobManager.Fire({{2, 9}, {5, 9}})); // 炸墓碑冒出的僵尸
            Connect(wave, 601 - 100 - 83, aCobManager.Fire({{1, 8.3}, {4, 8.3}});
                    Delay(100, ACard(AICE_SHROOM, {{1, 9}, {2, 9}, {3, 9}, {4, 9}, {5, 9}}))); // 冰杀小偷
            Connect(wave, 601, aCobManager.Fire({{2, 8.2}, {5, 8.2}}));
            // 第 20 波手动收尾
        }
    }
}