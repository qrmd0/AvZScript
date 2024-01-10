/*
 * 阵名: PE裸奔十六炮
 * 出处: https://tieba.baidu.com/p/1289540813
 * 节奏: ch6: PPDC|IPd-PPD|PPDC|IPd-PPD, (6|12|6|12)
 */

#include <avz.h>

// 使用宏定义简化代码
#define Connect(wave, time, ...) AConnect(ATime(wave, time), [=] { __VA_ARGS__; })
#define Delay(delayTime, ...) AConnect(ANowDelayTime(delayTime), [] { __VA_ARGS__; })

// 种垫铲垫
// 垫上半场
ACoroutine DianCai_Up()
{
    ACard({{APUFF_SHROOM, 1, 7}, {ASUN_SHROOM, 2, 7}});
    co_await ANowDelayTime(400);
    ARemovePlant(1, 7);
    ARemovePlant(2, 7);
}
// 垫下半场
ACoroutine DianCai_Low()
{
    ACard({{APUFF_SHROOM, 5, 9}, {ASUN_SHROOM, 6, 9}});
    co_await ANowDelayTime(100);
    ARemovePlant(5, 9);
    ARemovePlant(6, 9);
}

// 偷菜
ACoroutine Sunflower()
{
    using std::vector;
    vector<vector<APosition>> sunflower_spots = {{{1, 2}}, {{1, 5}}, {{1, 6}}, {{2, 2}}, {{2, 5}}, {{2, 6}}};
    // 开局种
    for (auto spot : sunflower_spots)
    {
        ACard(ASUNFLOWER, spot);
        co_await ANowDelayTime(751 + 1);
    }
    // 等第 20 波刷新
    co_await ATime(20, 0);
    // 等白字出现
    co_await []
    { return AGetPvzBase()->MainObject()->Words()->MRef<int>(0x8C) == 12; };
    // 结尾铲
    for (auto row : {1, 2})
    {
        ARemovePlant(row, 2);
        ARemovePlant(row, 5);
        ARemovePlant(row, 6);
    }
}

void AScript()
{
    ASetZombies({
        APJ_0,  // 普僵
        ACG_3,  // 撑杆
        AWW_8,  // 舞王
        ABC_12, // 冰车
        AHT_14, // 海豚
        AKG_17, // 矿工
        ATT_18, // 跳跳
        ABJ_20, // 蹦极
        AFT_21, // 扶梯
        ATL_22, // 投篮
        ABY_23, // 白眼
        AHY_32, // 红眼
    });
    ASelectCards({
        ACOFFEE_BEAN,    // 咖啡豆
        AICE_SHROOM,     // 寒冰菇
        AM_ICE_SHROOM,   // 模仿寒冰菇
        ACHERRY_BOMB,    // 樱桃炸弹
        ASQUASH,         // 倭瓜
        APUMPKIN,        // 南瓜头
        ASUNFLOWER,      // 向日葵
        ASCAREDY_SHROOM, // 胆小菇
        ASUN_SHROOM,     // 阳光菇
        APUFF_SHROOM,    // 小喷菇
    });

    Connect(1, -599,
            aCobManager.AutoSetList();
            aIceFiller.Start({{3, 9}, {4, 9}, {1, 4}, {2, 4}});
            ACoLaunch(Sunflower)); // 偷菜协程

    // PPD|I-
    for (auto wave : {1, 3, 5, 7, 9, 10, 12, 14, 16, 18})
    {
        if (wave == 10)
        {
            Connect(wave, -56, aCobManager.Fire({{2, 9}, {5, 9}}));
            Connect(wave, -56 + 110, aCobManager.Fire(5, 8));
            Connect(wave, 601 - 200 - 100, ACard(ACHERRY_BOMB, 2, 9)); // 301; 消延迟 炸小偷
        }
        else
        {
            Connect(wave, -133, aCobManager.Fire({{2, 9}, {5, 9}}));
            Connect(wave, -133 + 110, aCobManager.Fire(5, 8));
        }
        Connect(wave, 601 + 50 - 298, aIceFiller.Coffee()); // 353; 50cs 预判冰

        if (wave == 9) // 第 9 波收尾
        {
            Connect(wave, 601 - 135, ACoLaunch(DianCai_Low));
            Connect(wave, 601 - 100, aCobManager.Fire(1, 2.4));
            Connect(wave, 601 + 444 - 373, aCobManager.Fire(5, 7.4));
            Connect(wave, 601 + 1200 - 200 - 373, aCobManager.Fire({{2, 9}, {5, 9}});
                    Delay(220, aCobManager.Fire(5, 8.5)));
            Connect(wave, 601 + 1200 - 133, aCobManager.Fire({{1, 2.4}, {5, 9}}));
            Connect(wave, 601 + 1200 - 133 + 110, aCobManager.Fire(2, 9));
            Connect(wave, 601 + 1200 + 601 - 100,
                    Delay(600, aCobManager.Fire({{2, 9}, {5, 9}}); ACoLaunch(DianCai_Up)));
        }
    }

    // C|Pd-PPD
    for (auto wave : {2, 4, 6, 8, 11, 13, 15, 17, 19})
    {
        Connect(wave, -135, ACoLaunch(DianCai_Low)); // -135 放垫, 撑杆跳跃用时 180, 落地后 5 冰生效
        Connect(
            wave, -100,
            if (wave == 11) {
                aCobManager.Fire(1, 4); // 炸小鬼和小偷
            } else {
                aCobManager.Fire(1, 2.4);
            });
        Connect(wave, 444 - 373, aCobManager.Fire(5, 7.4));
        Connect(wave, 1200 - 200 - 373, aCobManager.Fire({{2, 9}, {5, 9}});
                Delay(220, aCobManager.Fire(5, 8.5)));

        if (wave == 19) // 第 19 波收尾
        {
            Connect(wave, 1200 - 133, aCobManager.Fire({{2, 9}, {5, 9}});
                    Delay(350, aCobManager.Fire(1, 2.4);
                          Delay(300, aCobManager.Fire(5, 9);
                                Delay(400, aCobManager.Fire(2, 9);
                                      Delay(500, aCobManager.Fire(5, 9);
                                            Delay(400, aCobManager.Fire(2, 8); ACoLaunch(DianCai_Up)))))));
        }
    }

    for (auto wave : {20})
    {
        Connect(wave, -150, aCobManager.Fire(4, 7); aIceFiller.Stop());
        Connect(wave, -60, aCobManager.Fire({{1, 9}, {2, 9}, {5, 9}, {6, 9}}); // 等到刷新前 60cs
                Delay(108, aCobManager.Fire({{1, 9}, {2, 9}, {5, 9}, {6, 9}});
                      Delay(180, aCobManager.Fire(1, 4)))); // 尾炸小偷
        // 第 20 波手动收尾
    }
}