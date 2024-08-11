/*
 * 阵名: PE半场十二炮
 * 出处: https://tieba.baidu.com/p/1801759994
 * 节奏: ch4: I+BC/d-PDD/P|I+BC/d-PDD/P, (18|18)
 */
#include <avz.h>

// 连接(使用宏定义简化)
#define Connect(wave, time, ...) AConnect(ATime(wave, time), [=] { __VA_ARGS__; })
#define Delay(delayTime) co_await ANowDelayTime(delayTime)

ALogger<AConsole> consoleLogger; // 日志对象-控制台

// 种垫铲垫
ACoroutine DianCai()
{
    ACard({{APUFF_SHROOM, 1, 9}, {ASUN_SHROOM, 2, 9}});
    Delay(100);
    ARemovePlant({{1, 9}, {2, 9}});
}

// 烧小偷
ACoroutine UseJalapeno() // 口吐金蛇
{
    co_await ATime(10, 400); // 等第 10 波刷新
    ACard({ALILY_PAD, AJALAPENO}, 4, 9);
    Delay(100 + 1);
    ARemovePlant(4, 9);

    co_await ATime(20, 400); // 等第 20 波刷新
    ACard({ALILY_PAD, AJALAPENO}, 4, 9);
    Delay(100 + 1);
    ARemovePlant(4, 9);
}

void AScript()
{
    // ASetReloadMode(AReloadMode::MAIN_UI_OR_FIGHT_UI);

    ASetZombies({
        AZOMBIE,               // 普僵
        APOLE_VAULTING_ZOMBIE, // 撑杆
        ADANCING_ZOMBIE,       // 舞王
        AZOMBONI,              // 冰车
        ADOLPHIN_RIDER_ZOMBIE, // 海豚
        ADIGGER_ZOMBIE,        // 矿工
        APOGO_ZOMBIE,          // 跳跳
        ABUNGEE_ZOMBIE,        // 蹦极
        ALADDER_ZOMBIE,        // 扶梯
        ACATAPULT_ZOMBIE,      // 篮球
        AGARGANTUAR,           // 白眼
        AGIGA_GARGANTUAR,      // 红眼
    });
    ASelectCards({
        AM_ICE_SHROOM, // 白冰
        AICE_SHROOM,   // 冰菇
        ACOFFEE_BEAN,  // 咖啡
        ALILY_PAD,     // 荷叶
        APUMPKIN,      // 南瓜
        ACHERRY_BOMB,  // 樱桃
        AJALAPENO,     // 辣椒
        ASQUASH,       // 倭瓜
        ASUN_SHROOM,   // 阳光
        APUFF_SHROOM,  // 小喷
    });

    Connect(1, -599,
            aCobManager.SetList({
                {1, 3}, {2, 3}, {3, 3}, //
                {1, 5}, {2, 5}, {3, 5}, //
                {1, 7}, {2, 7}, {3, 7}, //
                {1, 1}, {2, 1}, {3, 1}, //
            });
            ACard(AICE_SHROOM, 5, 5);           // 临时存冰
            ACard({ALILY_PAD, APUMPKIN}, 3, 9); // 临时存冰位, 其实不需要南瓜头
            aIceFiller.Start({{4, 5}, {4, 6}, {4, 7}, {4, 8}, {3, 9}});
            aPlantFixer.Start(APUMPKIN, {{4, 5}, {4, 6}, {4, 7}, {4, 8}}, 4000 * 0.3);
            ACoLaunch(UseJalapeno););

    for (int wave = 1; wave < 21; ++wave)
    {
        Connect(wave, -200, consoleLogger.Info("当前操作波次: {}", wave));

        if (ARangeIn(wave, {1, 10}))
        {
            Connect(wave, -95, aCobManager.Fire(1, 9));
            Connect(wave, -15, aCobManager.Fire({{2, 9}, {5, 9}}));
            Connect(wave, -15 + 110, aCobManager.Fire(5, 7.7));
            Connect(wave, -15 + 110 + 373 - 100, ACard(ACHERRY_BOMB, 1, 9)); // 368
        }

        else if (wave == 20)
        {
            Connect(wave, -150, aCobManager.Fire(4, 7));
            Connect(wave, -60, aCobManager.Fire({{2, 9}, {5, 9}, {2, 9}, {5, 9}})); // 等到刷新前 60cs
            Connect(wave, -60 + 110, aCobManager.Fire({{1, 8.8}, {2, 8.8}}); aPlantFixer.Stop());
            Connect(wave, -60 + 110 + 373 - 100, ACard(ACHERRY_BOMB, 5, 9);
                    consoleLogger.Info("第 {} 波手动收尾.", wave));
            Connect(wave, 5500 + 100, ARemovePlant({{3, 9}, {3, 9}})); // 跳白字后铲掉
        }

        else
        {
            Connect(wave, -133, aCobManager.Fire(1, 8.0));                                                // 拦截上波红眼, 分离部分快速僵尸
            Connect(wave, 360 - 273, aCobManager.Fire(2, 8.15));                                          // 无冰分离
            Connect(wave, 360 - 298, if (wave == 2) ACard(ACOFFEE_BEAN, 5, 5); else aIceFiller.Coffee()); // 360cs 反应冰
            Connect(wave, 360 + 500 - 373, if (!ARangeIn(wave, {2, 11})) aCobManager.Fire(5, 3));         // 下半场尾炸
            Connect(wave, 1800 - 200 - 373, aCobManager.Fire({{2, 9}, {5, 8.1}}));                        // 激活炸
            Connect(wave, 1800 - 200 - 373 + 10, ACoLaunch(DianCai));                                     // 垫撑杆
            Connect(wave, 1800 - 200 - 373 + 220, aCobManager.Fire(1, 8.2));                              // 秒白眼, 触发红眼投掷

            if (ARangeIn(wave, {9, 19})) // 收尾波次
            {
                Connect(wave, 1800 - 133, aCobManager.Fire(1, 8.0));
                Connect(wave, 1800 + 360 - 373, aCobManager.Fire(2, 8.8));
                Connect(wave, 1800 + 360 + 500 - 373, aCobManager.Fire(5, 2.5));
                Connect(wave, 1800 + 1800 - 200 - 373, aCobManager.Fire(5, 6));
                Connect(wave, 1800 + 1800 - 200 - 373 + 110, aCobManager.Fire(5, 6));
                Connect(wave, 1800 + 1800 - 200 - 373 + 110 + 110, aCobManager.Fire(5, 3));
                Connect(wave, 4500 - 200 - 373, aCobManager.Fire(5, 5);
                        if (wave == 9) aCobManager.Skip(2); // 中场调整炮序
                        else aIceFiller.Stop());
            }
        }
    }
}
