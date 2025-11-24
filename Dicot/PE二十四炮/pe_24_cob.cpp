/*
 * 阵名: PE二十四炮
 * 出处: https://tieba.baidu.com/p/991306518
 * 节奏: P6: PPDD|PPI|PPSSDD|PPDD|PPI|PPSSDD
 */
#include <avz.h>

// 连接(使用宏定义简化)
#define Connect(wave, time, ...) AConnect(ATime(wave, time), [=] { __VA_ARGS__; })
#define CoConnect(wave, time, ...) AConnect(ATime(wave, time), [=]() -> ACoroutine { __VA_ARGS__; })
#define Delay(delayTime) (co_await ANowDelayTime(delayTime))

ALogger<AConsole> consoleLogger; // 日志对象-控制台

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
        AM_ICE_SHROOM,   // 复制冰
        AICE_SHROOM,     // 寒冰菇
        ACOFFEE_BEAN,    // 咖啡豆
        APUMPKIN,        // 南瓜
        AWALL_NUT,       // 坚果
        ASQUASH,         // 窝瓜
        AFLOWER_POT,     // 花盆
        ASCAREDY_SHROOM, // 胆小
        ASUN_SHROOM,     // 阳光
        APUFF_SHROOM,    // 小喷
    });

    Connect(1, -599,
            // aCobManager.SetList({
            //     {1, 1}, {1, 3}, {1, 5}, {1, 7},
            //     {2, 1}, {2, 3}, {2, 5}, {2, 7},
            //     {3, 1}, {3, 3}, {3, 5}, {3, 7},
            //     {4, 1}, {4, 3}, {4, 5}, {4, 7},
            //     {5, 1}, {5, 3}, {5, 5}, {5, 7},
            //     {6, 1}, {6, 3}, {6, 5}, {6, 7},
            // });
            // for (int r = 1; r < 7; ++r) for (int c = 1; c < 8; c += 2) aCobManager.MoveToListBottom(r, c);
            aCobManager.AutoSetList();
            aIceFiller.Start({{4, 9}}););

    for (int wave = 1; wave < 21; ++wave) {
        Connect(wave, -200, consoleLogger.Info("当前操作波次: {}", wave));

        // 精准之舞 PPDD
        if (ARangeIn(wave, {1, 4, 7, 11, 14, 17})) {
            CoConnect(wave, -14, aCobManager.Fire({{2, 9}, {5, 9}});
                      Delay(107); aCobManager.Fire({{1, 7.7}, {5, 7.7}}));
        }

        // 冰之旋舞 PPI
        else if (ARangeIn(wave, {2, 5, 8, 12, 15, 18})) {
            CoConnect(wave, -95, aCobManager.Fire({{2, 9}, {5, 9}});
                      Delay(373 - 100 - 198); aIceFiller.Coffee()); // 冰同步于炮生效
        }

        // 六神乱舞 PPSSDD
        else if (ARangeIn(wave, {3, 6, 9, 13, 16, 19})) {
            CoConnect(wave, -95, aCobManager.Fire({{2, 9}, {5, 9}, {2, 9}, {5, 9}});
                      Delay(108); aCobManager.Fire({{1, 8.8}, {5, 8.8}}));
            if (ARangeIn(wave, {9, 19})) // 收尾
            {
                Connect(wave, 601 - 15, aCobManager.Fire({{2, 9}, {5, 9}}));
            }
        }

        // 大波推迟 PPSSDD
        else if (wave == 10) {
            CoConnect(wave, -56, aCobManager.Fire({{2, 9}, {5, 9}, {2, 9}, {5, 9}});
                      Delay(108); aCobManager.Fire({{1, 8.8}, {5, 8.8}}));
        }

        else if (wave == 20) {
            CoConnect(wave, -150, aCobManager.Fire({{4, 6}, {4, 8}});                // 炮炸珊瑚
                      Delay(90); aCobManager.Fire({{1, 9}, {2, 9}, {5, 9}, {6, 9}}); // -60
                      Delay(108); aCobManager.Fire({{1, 9}, {2, 9}, {5, 9}, {6, 9}});
                      consoleLogger.Info("第 {} 波手动收尾.", wave));
        }
    }
}
