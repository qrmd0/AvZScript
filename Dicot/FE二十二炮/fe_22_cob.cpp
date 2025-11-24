/*
 * 阵名: FE二十二炮
 * 出处: None
 * 节奏: C9u-57s: IPP-PPDD|PSD/PDC|IPP-PPDD|PSD/PDC|N+AD/DC|PD/PDC|PSD/PDC, (13.5|6|13.5|6|6|6|6)
 */
#include <avz.h>

// 连接(使用宏定义简化)
#define Connect(wave, time, ...) AConnect(ATime(wave, time), [=] { __VA_ARGS__; })
#define CoConnect(wave, time, ...) AConnect(ATime(wave, time), [=]() -> ACoroutine { __VA_ARGS__; })
#define Delay(delayTime) (co_await ANowDelayTime(delayTime))

ALogger<AConsole> consoleLogger; // 日志对象-控制台

// Cannon Fodder
// 垫材 花盆/胆小菇 阳光菇/小喷菇
// 根据小喷是否可用来决定用哪一组垫材
ACoroutine DianCai() {
    if (AIsSeedUsable(APUFF_SHROOM)) {
        ACard({{ASUN_SHROOM, 5, 9}, {APUFF_SHROOM, 6, 9}});
    } else {
        ACard({{AFLOWER_POT, 5, 9}, {ASCAREDY_SHROOM, 6, 9}});
    }
    Delay(30);
    ARemovePlant({{5, 9}, {6, 9}});
}

void AScript() {
    // ASetReloadMode(AReloadMode::MAIN_UI_OR_FIGHT_UI);

    AMRef<uint16_t>(0x0041'A68D) = 0xD231; // 浓雾透视

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
        AICE_SHROOM,     // 寒冰菇
        AM_ICE_SHROOM,   // 模仿冰
        ADOOM_SHROOM,    // 毁灭菇
        ALILY_PAD,       // 睡莲
        ACHERRY_BOMB,    // 樱桃
        AWALL_NUT,       // 坚果
        AFLOWER_POT,     // 花盆
        ASCAREDY_SHROOM, // 胆小
        ASUN_SHROOM,     // 阳光
        APUFF_SHROOM,    // 小喷
    });

    Connect(1, -599,
        aCobManager.SetList({
            {1, 1},
            {2, 1},
            {3, 1},
            {4, 1},
            {5, 1},
            {6, 1},
            {1, 3},
            {2, 3},
            {3, 3},
            {4, 3},
            {5, 3},
            {6, 3},
            {1, 5},
            {2, 5},
            {3, 5},
            {4, 5},
            {5, 5},
            {6, 5},
            {1, 7},
            {2, 7},
            // {3, 7},
            // {4, 7},
            {5, 7},
            {6, 7},
        }));

    for (int wave = 1; wave < 21; ++wave) {
        Connect(wave, -200, consoleLogger.Info("当前操作波次: {}", wave));
    }

    // IPP-PPDD
    Connect(1, 5 - 100, ACard(AICE_SHROOM, 2, 9));                              // 本波 5cs 预判冰
    Connect(1, -15, aCobManager.Fire(1, 8.8));                                  // 上半场热过渡, 炸 1 路收跳跳
    Connect(1, 444 - 373, aCobManager.Fire(5, 7.4));                            // 下半场热过渡, 右极限大概 7.43
    Connect(1, 1350 - 200 - 373, aCobManager.Fire({{2, 9}, {5, 8.7}}));         // 激活炮, 下半场落点左移收跳跳
    Connect(1, 1350 - 200 - 373 + 220, aCobManager.Fire({{1, 8.6}, {5, 8.6}})); // 连续拦截之一, 落点左移

    // PSD/PDC
    Connect(2, -133, aCobManager.Fire({{1, 9}, {5, 9}}));        // 133 预判对应上波过 220 继续拦截; 连续拦截之二
    Connect(2, -95, aCobManager.Fire(2, 9));                     // 上半场 S
    Connect(2, -133 + 110, aCobManager.Fire(5, 7.8));            // 下半场 D
    Connect(2, -95 + 110, aCobManager.Fire(1, 8.8));             // 上半场 D
    Connect(2, 601 + 5 - 100 - 320, ACard(AM_ICE_SHROOM, 2, 9)); // 下一波 5cs 预判冰

    // IPP-PPDD
    // 相比 wave 1 多了垫材操作
    Connect(3, -188, ACoLaunch(DianCai)); // 垫上一波撑杆
    Connect(3, -15, aCobManager.Fire(1, 8.8));
    Connect(3, 444 - 373, aCobManager.Fire(5, 7.4));
    Connect(3, 5 + 600, ACoLaunch(DianCai)); // 全部解冻; 垫红眼
    Connect(3, 1350 - 200 - 373, aCobManager.Fire({{2, 9}, {5, 8.7}}));
    Connect(3, 1350 - 200 - 373 + 220, aCobManager.Fire({{1, 8.6}, {5, 8.6}}));

    // PSD/PDC
    // 炸法同 wave 2
    Connect(4, -133, aCobManager.Fire({{1, 9}, {5, 9}}));
    Connect(4, -95, aCobManager.Fire(2, 9));
    Connect(4, -133 + 110, aCobManager.Fire(5, 7.8));
    Connect(4, -95 + 110, aCobManager.Fire(1, 8.8));

    // N+AD/DC
    // 连续加速波下半场对应垫材 24 炮打法, 因此激活炮要尽早生效
    // 最早为 226 可全炸巨人, 相当于 147 预判炮
    // 这里 N 相当于激活炮, 上半场 A 相当于 S
    Connect(5, -145 + 83, ACoLaunch(DianCai));                            // 下半场使撑杆不啃炮的最早放垫材时间; 垫上一波撑杆
    Connect(5, -145 + 110, aCobManager.Fire(5, 7.8));                     // 下半场 D
    Connect(5, -95 + 110, aCobManager.Fire(1, 8.8));                      // 上半场 D
    Connect(5, -145 + 373 - 100, ACard({ALILY_PAD, ADOOM_SHROOM}, 3, 9)); // 等效 145 预判炮
    Connect(5, -95 + 373 - 100, ACard(ACHERRY_BOMB, 2, 9));               // 等效 95 预判炮

    // PD/PDC
    // 下半场对应垫材 24 炮打法, 上半场精准之舞
    Connect(6, -145, aCobManager.Fire(5, 9));         // 下半场 P
    Connect(6, -145 + 83, ACoLaunch(DianCai));        // 垫上一波撑杆
    Connect(6, -145 + 110, aCobManager.Fire(5, 7.8)); // 下半场 D
    Connect(6, -14, aCobManager.Fire(2, 9));          // 上半场 P
    Connect(6, -14 + 107, aCobManager.Fire(1, 7.8));  // 上半场 D

    // PSD/PDC
    Connect(7, -145, aCobManager.Fire(5, 9));            // 下半场 P
    Connect(7, -95, aCobManager.Fire({{2, 9}, {2, 9}})); // 上半场 PS
    Connect(7, -145 + 83, ACoLaunch(DianCai));           // 垫上一波撑杆
    Connect(7, -145 + 110, aCobManager.Fire(5, 7.8));    // 下半场 D
    Connect(7, -95 + 110, aCobManager.Fire(1, 8.8));     // 上半场 D

    // IPP-PPDD
    Connect(8, -180, ACoLaunch(DianCai));
    Connect(8, 5 - 100, ACard(AICE_SHROOM, 2, 9));
    Connect(8, -15, aCobManager.Fire(1, 8.8));
    Connect(8, 444 - 373, aCobManager.Fire(5, 7.4));
    Connect(8, 1350 + 15 - 100 - 320 - 373 - 1, aCobManager.Fire(2, 8.2));      // 571
    Connect(8, 5 + 600, ACoLaunch(DianCai));                                    // 全部解冻
    Connect(8, 1350 - 200 - 373, aCobManager.Fire({{2, 9}, {5, 8.7}}));         // 777
    Connect(8, 1350 + 15 - 100 - 320, ACard(AM_ICE_SHROOM, 2, 9));              // 945
    Connect(8, 1350 - 200 - 373 + 220, aCobManager.Fire({{1, 8.8}, {5, 8.6}})); // 997; 上半场炸撑杆

    // 收尾波
    Connect(9, -133, aCobManager.Fire({{1, 9}, {5, 9}}));
    Connect(9, -15, aCobManager.Fire({{1, 9}, {5, 9}}));
    CoConnect(9, 1300 - 200 - 373, aCobManager.Fire({{2, 9}, {5, 9}}); // 1350->1300
              Delay(220); aCobManager.Fire({{1, 9}, {5, 9}});
              Delay(220); aCobManager.Fire({{1, 9}, {5, 9}});
              Delay(600); aCobManager.Fire({{2, 9}, {5, 9}}); // 等冰菇 CD
              Delay(700); aCobManager.Fire({{2, 9}, {5, 9}}); // 清伴舞
    );

    // PSD/PDC
    // 上半场 PSD, 下半场收撑杆省垫材
    Connect(10, -83, aCobManager.Fire(1, 9));               // -83
    Connect(10, -14, aCobManager.Fire(5, 9));               // -14
    Connect(10, -83 + 104, aCobManager.Fire(2, 9));         // 394-373=21
    Connect(10, -14 + 110, aCobManager.Fire(5, 7.8));       // 96
    Connect(10, -83 + 104 + 110, aCobManager.Fire(1, 8.8)); // 131

    // IPP-PPDD
    // 相比 wave 1 多了垫红眼操作
    Connect(11, 5 - 100, ACard(AICE_SHROOM, 2, 9));
    Connect(11, -15, aCobManager.Fire(1, 8.8));
    Connect(11, 444 - 373, aCobManager.Fire(5, 7.4));
    Connect(11, 5 + 600, ACoLaunch(DianCai)); // 全部解冻
    Connect(11, 1350 - 200 - 373, aCobManager.Fire({{2, 9}, {5, 8.7}}));
    Connect(11, 1350 - 200 - 373 + 220, aCobManager.Fire({{1, 8.6}, {5, 8.6}}));

    // PSD/PDC
    Connect(12, -133, aCobManager.Fire({{1, 9}, {5, 9}}));        // 133 预判对应上波过 220 继续拦截; 连续拦截之二
    Connect(12, -95, aCobManager.Fire(2, 9));                     // 上半场 S
    Connect(12, -133 + 110, aCobManager.Fire(5, 7.8));            // 下半场 D
    Connect(12, -95 + 110, aCobManager.Fire(1, 8.8));             // 上半场 D
    Connect(12, 601 + 5 - 100 - 320, ACard(AM_ICE_SHROOM, 2, 9)); // 下一波 5cs 预判冰

    // IPP-PPDD
    // 相比 wave 11 多了垫材操作
    Connect(13, -180, ACoLaunch(DianCai)); // 垫上一波撑杆
    Connect(13, -15, aCobManager.Fire(1, 8.8));
    Connect(13, 444 - 373, aCobManager.Fire(5, 7.4));
    Connect(13, 5 + 600, ACoLaunch(DianCai)); // 全部解冻; 垫红眼
    Connect(13, 1350 - 200 - 373, aCobManager.Fire({{2, 9}, {5, 8.7}}));
    Connect(13, 1350 - 200 - 373 + 220, aCobManager.Fire({{1, 8.6}, {5, 8.6}}));

    // PSD/PDC
    // 炸法同 wave 12
    Connect(14, -133, aCobManager.Fire({{1, 9}, {5, 9}}));
    Connect(14, -95, aCobManager.Fire(2, 9));
    Connect(14, -133 + 110, aCobManager.Fire(5, 7.8));
    Connect(14, -95 + 110, aCobManager.Fire(1, 8.8));

    // N+AD/DC
    // 操作同 wave 5,  弹坑改为 4-9
    Connect(15, -145 + 83, ACoLaunch(DianCai));
    Connect(15, -145 + 110, aCobManager.Fire(5, 7.8));
    Connect(15, -95 + 110, aCobManager.Fire(1, 8.8));
    Connect(15, -145 + 373 - 100, ACard({ALILY_PAD, ADOOM_SHROOM}, 4, 9));
    Connect(15, -95 + 373 - 100, ACard(ACHERRY_BOMB, 2, 9));

    // PD/PDC
    // 下半场对应垫材 24 炮打法, 上半场精准之舞
    Connect(16, -145, aCobManager.Fire(5, 9));         // 下半场 P
    Connect(16, -145 + 83, ACoLaunch(DianCai));        // 垫上一波撑杆
    Connect(16, -145 + 110, aCobManager.Fire(5, 7.8)); // 下半场 D
    Connect(16, -14, aCobManager.Fire(2, 9));          // 上半场 P
    Connect(16, -14 + 107, aCobManager.Fire(1, 7.8));  // 上半场 D

    // PSD/PDC
    Connect(17, -145, aCobManager.Fire(5, 9));            // 下半场 P
    Connect(17, -95, aCobManager.Fire({{2, 9}, {2, 9}})); // 上半场 PS
    Connect(17, -145 + 83, ACoLaunch(DianCai));           // 垫上一波撑杆
    Connect(17, -145 + 110, aCobManager.Fire(5, 7.8));    // 下半场 D
    Connect(17, -95 + 110, aCobManager.Fire(1, 8.8));     // 上半场 D

    // IPP-PPDD
    Connect(18, -180, ACoLaunch(DianCai));
    Connect(18, 5 - 100, ACard(AICE_SHROOM, 2, 9));
    Connect(18, -15, aCobManager.Fire(1, 8.8));
    Connect(18, 444 - 373, aCobManager.Fire(5, 7.4));
    Connect(18, 1350 + 15 - 100 - 320 - 373 - 1, aCobManager.Fire(2, 8.2));      // 571
    Connect(18, 5 + 600, ACoLaunch(DianCai));                                    // 全部解冻
    Connect(18, 1350 - 200 - 373, aCobManager.Fire({{2, 9}, {5, 8.7}}));         // 777
    Connect(18, 1350 + 15 - 100 - 320, ACard(AM_ICE_SHROOM, 2, 9));              // 945
    Connect(18, 1350 - 200 - 373 + 220, aCobManager.Fire({{1, 8.8}, {5, 8.6}})); // 997; 上半场炸撑杆

    // 收尾波
    Connect(19, -133, aCobManager.Fire({{1, 9}, {5, 9}}));
    Connect(19, -15, aCobManager.Fire({{1, 9}, {5, 9}}));
    CoConnect(19, 1300 - 200 - 373, aCobManager.Fire({{2, 9}, {5, 9}}); // 1350->1300
              Delay(220); aCobManager.Fire({{1, 9}, {5, 9}});
              Delay(220); aCobManager.Fire({{1, 9}, {5, 9}});
              Delay(600); aCobManager.Fire({{2, 9}, {5, 9}}); // 等冰菇 CD
              Delay(700); aCobManager.Fire({{2, 9}, {5, 9}}); // 清伴舞
    );

    // PP-PPPPPPPP
    Connect(20, -150, aCobManager.Fire(4, 7));             // 炮炸珊瑚
    CoConnect(20, -60, aCobManager.Fire({{2, 9}, {5, 9}}); // 等到刷新前 60cs
              Delay(108); aCobManager.Fire({{1, 8.8}, {5, 8.8}});
              Delay(108); aCobManager.Fire({{1, 8.6}, {5, 8.6}});
              Delay(108); aCobManager.Fire({{2, 8.4}, {5, 8.4}}); // 炸小偷
              consoleLogger.Info("最后一大波手动收尾."));
}
