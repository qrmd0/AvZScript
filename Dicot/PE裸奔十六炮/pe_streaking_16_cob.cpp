/*
 * 阵名: PE裸奔十六炮
 * 出处: https://tieba.baidu.com/p/1289540813
 * 节奏: ch6: PPDC|IPd-PPD|PPDC|IPd-PPD, (6|12|6|12)
 */
#include <avz.h>

// 使用宏定义简化代码
#define Connect(wave, time, ...) AConnect(ATime(wave, time), [=] { __VA_ARGS__; })
#define CoConnect(wave, time, ...) AConnect(ATime(wave, time), [=]() -> ACoroutine { __VA_ARGS__; })
#define Delay(delayTime) (co_await ANowDelayTime(delayTime))

ALogger<AConsole> consoleLogger; // 日志对象-控制台

// 种垫铲垫
ACoroutine DianCai_Up() // 垫上半场
{
    ACard({{APUFF_SHROOM, 1, 7}, {ASUN_SHROOM, 2, 7}});
    Delay(400);
    ARemovePlant({{1, 7}, {2, 7}});
}
ACoroutine DianCai_Low() // 垫下半场
{
    ACard({{APUFF_SHROOM, 5, 9}, {ASUN_SHROOM, 6, 9}});
    Delay(100);
    ARemovePlant({{5, 9}, {6, 9}});
}

// 偷菜
ACoroutine Sunflower() {
    static constexpr std::pair<int, int> sunflowerSpots[] = {{1, 2}, {1, 5}, {1, 6}, {2, 2}, {2, 5}, {2, 6}};
    // 开局种
    for (auto& [row, col] : sunflowerSpots) {
        ACard(ASUNFLOWER, row, col);
        Delay(751 + 1);
    }
    // 等第 20 波刷新
    co_await ATime(20, 0);
    // 等白字出现
    co_await [] { return AGetMainObject()->Words()->MRef<int>(0x8C) == 12; };
    // 结尾铲
    for (auto& [row, col] : sunflowerSpots) {
        ARemovePlant(row, col);
    }
}

void AScript() {
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
        ACOFFEE_BEAN,    // 咖啡豆
        AICE_SHROOM,     // 寒冰菇
        AM_ICE_SHROOM,   // 复制冰
        ACHERRY_BOMB,    // 樱桃
        ASQUASH,         // 窝瓜
        APUMPKIN,        // 南瓜头
        ASUNFLOWER,      // 向日葵
        ASCAREDY_SHROOM, // 胆小菇
        ASUN_SHROOM,     // 阳光菇
        APUFF_SHROOM,    // 小喷菇
    });

    Connect(1, -599,
            // aCobManager.SetList({
            //     {3, 1}, {3, 3}, {3, 5}, {3, 7},
            //     {4, 1}, {4, 3}, {4, 5}, {4, 7},
            //     {5, 1}, {5, 3}, {5, 5}, {5, 7},
            //     {6, 1}, {6, 3}, {6, 5}, {6, 7},
            // });
            aCobManager.AutoSetList();
            aIceFiller.Start({{3, 9}, {4, 9}, {1, 4}, {2, 4}});
            ACoLaunch(Sunflower); // 偷菜协程
    );

    for (int wave = 1; wave < 21; ++wave) {
        Connect(wave, -200, consoleLogger.Info("当前操作波次: {}", wave));

        // PPD|I-
        if (ARangeIn(wave, {1, 3, 5, 7, 9, 10, 12, 14, 16, 18})) {
            if (wave == 10) {
                Connect(wave, -56, aCobManager.Fire({{2, 9}, {5, 9}}));
                Connect(wave, -56 + 110, aCobManager.Fire(5, 8));
                Connect(wave, 601 - 200 - 100, ACard(ACHERRY_BOMB, 2, 9)); // 301; 消延迟 炸小偷
            } else {
                Connect(wave, -133, aCobManager.Fire({{2, 9}, {5, 9}}));
                Connect(wave, -133 + 110, aCobManager.Fire(5, 8));
            }
            Connect(wave, 601 + 50 - 298, aIceFiller.Coffee()); // 353; 50cs 预判冰

            if (wave == 9) // 第 9 波收尾
            {
                Connect(wave, 601 - 135, ACoLaunch(DianCai_Low));
                Connect(wave, 601 - 100, aCobManager.Fire(1, 2.4));
                Connect(wave, 601 + 444 - 373, aCobManager.Fire(5, 7.4));
                CoConnect(wave, 601 + 1200 - 200 - 373, aCobManager.Fire({{2, 9}, {5, 9}});
                          Delay(220); aCobManager.Fire(5, 8.5));
                Connect(wave, 601 + 1200 - 133, aCobManager.Fire({{1, 2.4}, {5, 9}}));
                Connect(wave, 601 + 1200 - 133 + 110, aCobManager.Fire(2, 9));
                CoConnect(wave, 601 + 1200 + 601 - 100,
                          Delay(600);
                          aCobManager.Fire({{2, 9}, {5, 9}}); ACoLaunch(DianCai_Up));
            }
        }

        // C|Pd-PPD
        else if (ARangeIn(wave, {2, 4, 6, 8, 11, 13, 15, 17, 19})) {
            Connect(wave, -135, ACoLaunch(DianCai_Low)); // -135 放垫, 撑杆跳跃用时 180, 落地后 5 冰生效
            Connect(wave, -100,
                    if (wave == 11)
                        aCobManager.Fire(1, 4); // 炸小鬼和小偷
                    else aCobManager.Fire(1, 2.4));
            Connect(wave, 444 - 373, aCobManager.Fire(5, 7.4));
            CoConnect(wave, 1200 - 200 - 373, aCobManager.Fire({{2, 9}, {5, 9}});
                      Delay(220); aCobManager.Fire(5, 8.5));

            if (wave == 19) // 第 19 波收尾
            {
                CoConnect(wave, 1200 - 133, aCobManager.Fire({{2, 9}, {5, 9}});
                          Delay(350); aCobManager.Fire(1, 2.4);
                          Delay(300); aCobManager.Fire(5, 9);
                          Delay(400); aCobManager.Fire(2, 9);
                          Delay(500); aCobManager.Fire(5, 9);
                          Delay(400); aCobManager.Fire(2, 8); ACoLaunch(DianCai_Up));
            }
        }

        else if (wave == 20) {
            Connect(wave, -150, aCobManager.Fire(4, 7); aIceFiller.Stop());
            CoConnect(wave, -60, aCobManager.Fire({{1, 9}, {2, 9}, {5, 9}, {6, 9}}); // 等到刷新前 60cs
                      Delay(108); aCobManager.Fire({{1, 9}, {2, 9}, {5, 9}, {6, 9}});
                      Delay(180); aCobManager.Fire(1, 4); // 尾炸小偷
                      consoleLogger.Info("第 {} 波手动收尾.", wave));
        }
    }
}
