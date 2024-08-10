/*
 * 阵名: PE最后之作
 * 出处: https://tieba.baidu.com/p/5102612180
 * 节奏: ch5u-35.62s: PPDD|I-PPdd|IPP-PPDDCC, (6|13|16.62)
 */
#include <avz.h>

// 连接(使用宏定义简化)
#define Connect(wave, time, ...) AConnect(ATime(wave, time), [=] { __VA_ARGS__; })
#define CoConnect(wave, time, ...) AConnect(ATime(wave, time), [=]() -> ACoroutine { __VA_ARGS__; })
#define Delay(delayTime) co_await ANowDelayTime(delayTime)

ALogger<AConsole> consoleLogger; // 日志对象-控制台

ACoroutine DianCai()
{
    ACard({
        {AUMBRELLA_LEAF, 1, 8},
        {ASCAREDY_SHROOM, 2, 8},
        {ASUN_SHROOM, 5, 8},
        {APUFF_SHROOM, 6, 8},
    });
    Delay(10);
    ARemovePlant({{1, 8}, {2, 8}, {5, 8}, {6, 8}});
}

// 泳池水路 8 列临时高坚果阻挡海豚.
// 残血或被偷后自动补, 中场种伞保护, 关底大波刷出后停止修补.
ACoroutine TallNutKeeper()
{
    // 开场种
    Delay(800); // TODO: 让给存冰位先
    ACard({ALILY_PAD, ATALL_NUT}, 3, 8);
    Delay(3000 + 1);
    ACard({ALILY_PAD, ATALL_NUT}, 4, 8);
    Delay(1);
    aPlantFixer.Start(ATALL_NUT, {{3, 8}, {4, 8}}, 2000);

    // 第 10 波刷新前种伞, 第 11 波铲掉
    co_await ATime(10, -200);
    ACard({ALILY_PAD, AUMBRELLA_LEAF}, 3, 9);
    co_await ATime(11, 0);
    ARemovePlant({{3, 9}, {3, 9}});

    co_await ATime(20, 0);
    aPlantFixer.Stop();
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
        ACOFFEE_BEAN,    // 咖啡豆
        AICE_SHROOM,     // 寒冰菇
        AM_ICE_SHROOM,   // 复制冰
        ALILY_PAD,       // 睡莲
        ATALL_NUT,       // 高坚果
        ACHERRY_BOMB,    // 樱桃
        AUMBRELLA_LEAF,  // 保护伞
        ASCAREDY_SHROOM, // 胆小
        ASUN_SHROOM,     // 阳光
        APUFF_SHROOM,    // 小喷
    });

    Connect(1, -599,
            // aCobManager.SetList({
            //     {1, 1}, {2, 1}, {5, 1}, {6, 1},
            //     {1, 3}, {2, 3}, {5, 3}, {6, 3},
            //     {1, 6}, {2, 6}, {3, 6}, {4, 6}, {5, 6}, {6, 6},
            // });
            aCobManager.AutoSetList();
            ACard(ALILY_PAD, 3, 3); // 临时存冰位
            aIceFiller.Start({{1, 5}, {6, 5}, {3, 3}});
            ACoLaunch(TallNutKeeper));

    for (int wave = 1; wave < 21; ++wave)
    {
        Connect(wave, -200, consoleLogger.Info("当前操作波次: {}", wave));

        if (wave == 1)
        {
            CoConnect(wave, -95, aCobManager.Fire({{2, 9}, {5, 9}});
                      Delay(110); aCobManager.Fire({{1, 7.7}, {5, 7.7}}));
        }

        else if (ARangeIn(wave, {2, 10}))
        {
            Connect(wave, -15, aCobManager.Fire({{2, 9}, {5, 9}}));
            Connect(wave, -15 + 107, aCobManager.Fire({{1, 7.625}, {5, 7.625}}));
            if (wave == 10)
            {
                Connect(wave, -15 + 373 - 100, ACard(ACHERRY_BOMB, 2, 9)); // A
            }
            Connect(wave, 601 + 20 - 298, aIceFiller.Coffee()); // 20cs 预判冰
        }

        // I-PPdd
        else if (ARangeIn(wave, {3, 6, 9, 11, 14, 17}))
        {
            Connect(wave, 1300 - 200 - 373, aCobManager.Fire({{2, 8.8}, {5, 8.8}}));
            Connect(wave, 1300 + 20 - 298, aIceFiller.Coffee());                               // 20cs 预判冰
            Connect(wave, 1300 - 200 - 373 + 349, aCobManager.Fire({{1, 2.425}, {5, 2.425}})); // 减速尾炸
            if (wave == 9)
            {
                // Connect(wave, 1300 + 180, aCobManager.Fire({{1, 7.2}, {5, 7.2}})); // 可省略
                CoConnect(wave, 1300 + 1662 - 200 - 373, aCobManager.Fire({{2, 8.8}, {5, 8.8}});
                          Delay(81); ACoLaunch(DianCai);
                          Delay(220 - 81); aCobManager.Fire({{1, 7.8}, {5, 7.8}}); aCobManager.Skip(4);
                          consoleLogger.Info("第 {} 波手动收尾.", wave));
            }
        }

        // IPP-PPDDC
        else if (ARangeIn(wave, {4, 7, 12, 15, 18}))
        {
            Connect(wave, 180, aCobManager.Fire({{1, 7.2}, {5, 7.2}}));
            CoConnect(wave, 1662 - 200 - 373, aCobManager.Fire({{2, 8.8}, {5, 8.8}});
                      Delay(81); ACoLaunch(DianCai);
                      Delay(220 - 81); aCobManager.Fire({{1, 7.4}, {5, 7.4}})); // 左移
        }

        // PPdd
        else if (ARangeIn(wave, {5, 8, 13, 16, 19}))
        {
            Connect(wave, -15, aCobManager.Fire({{2, 9}, {5, 9}}));
            Connect(wave, -15 + 107, aCobManager.Fire({{1, 7.625}, {5, 7.625}}));
            Connect(wave, 601 + 20 - 298, aIceFiller.Coffee()); // 20cs 预判冰
            if (wave == 19)
            {
                CoConnect(wave, 601 + 1300 - 200 - 373,
                          Delay(100); aCobManager.Fire({{2, 8.8}, {5, 8.8}}); // 尾炸炮时机微调
                          Delay(220); aCobManager.Fire({{1, 7.5}, {5, 7.5}}); aCobManager.Skip(3);
                          consoleLogger.Info("第 {} 波手动收尾.", wave));
            }
        }

        else if (wave == 20)
        {
            Connect(wave, -150, aCobManager.Fire(4, 7));
            CoConnect(wave, -60, aCobManager.Fire({{1, 9}, {2, 9}, {5, 9}, {6, 9}});
                      Delay(108); aCobManager.Fire({{1, 9}, {2, 9}, {5, 9}, {6, 9}}));
        }
    }
}
