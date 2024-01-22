/*
 * 阵名: PE最后之作
 * 出处: https://tieba.baidu.com/p/5102612180
 * 节奏: ch5u-35.62s: PPDD|I-PPdd|IPP-PPDDCC, (6|13|16.62)
 */

#include <avz.h>

// 使用宏定义简化代码
#define Connect(time, ...) AConnect(ATime(wave, time), [] { __VA_ARGS__; })
#define Delay(delayTime, ...) AConnect(ANowDelayTime(delayTime), [] { __VA_ARGS__; })

ACoroutine DianCai()
{
    ACard(AUMBRELLA_LEAF, 1, 8);
    ACard(ASCAREDY_SHROOM, 2, 8);
    ACard(ASUN_SHROOM, 5, 8);
    ACard(APUFF_SHROOM, 6, 8);
    co_await ANowDelayTime(10);
    ARemovePlant(1, 8);
    ARemovePlant(2, 8);
    ARemovePlant(5, 8);
    ARemovePlant(6, 8);
}

// 泳池水路 8 列临时高坚果阻挡海豚.
// 残血或被偷后自动补, 中场种伞保护, 关底大波刷出后停止修补.
ACoroutine TallNutKeeper()
{
    // 开场种
    co_await ANowDelayTime(800); // TODO: 让给存冰位先
    ACard({ALILY_PAD, ATALL_NUT}, 3, 8);
    co_await ANowDelayTime(3000 + 1);
    ACard({ALILY_PAD, ATALL_NUT}, 4, 8);
    co_await ANowDelayTime(1);
    aPlantFixer.Start(ATALL_NUT, {{3, 8}, {4, 8}}, 2000);

    // 第 10 波刷新前种伞, 第 11 波铲掉
    co_await ATime(10, -200);
    ACard({ALILY_PAD, AUMBRELLA_LEAF}, 3, 9);
    co_await ATime(11, 0);
    ARemovePlant(3, 9);
    ARemovePlant(3, 9);

    co_await ATime(20, 0);
    aPlantFixer.Stop();
}

void AScript()
{
    // ASetReloadMode(AReloadMode::MAIN_UI_OR_FIGHT_UI);

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
                     ALILY_PAD,       // 荷叶
                     ATALL_NUT,       // 高坚果
                     ACHERRY_BOMB,    // 樱桃炸弹
                     AUMBRELLA_LEAF,  // 叶子保护伞
                     ASCAREDY_SHROOM, // 胆小菇
                     ASUN_SHROOM,     // 阳光菇
                     APUFF_SHROOM,    // 小喷菇
                 },
                 1);

    AConnect(ATime(1, -599), []
             {
            aCobManager.SetList({
                {1, 1},
                {2, 1},
                {5, 1},
                {6, 1},
                {1, 3},
                {2, 3},
                {5, 3},
                {6, 3},
                {1, 6},
                {2, 6},
                {3, 6},
                {4, 6},
                {5, 6},
                {6, 6},
            });
            ACard(ALILY_PAD, 3, 3); // 临时存冰位
            aIceFiller.Start({{1, 5}, {6, 5}, {3, 3}});
            ACoLaunch(TallNutKeeper); });

    for (auto wave : {1})
    {
        Connect(-95, aCobManager.Fire({{2, 9}, {5, 9}});
                Delay(110, aCobManager.Fire({{1, 7.7}, {5, 7.7}})));
    }

    for (auto wave : {2, 10})
    {
        Connect(-15, aCobManager.Fire({{2, 9}, {5, 9}}));
        Connect(-15 + 107, aCobManager.Fire({{1, 7.625}, {5, 7.625}}));
        if (wave == 10)
        {
            Connect(-15 + 373 - 100, ACard(ACHERRY_BOMB, 2, 9)); // A
        }
        Connect(601 + 20 - 298, aIceFiller.Coffee()); // 20cs 预判冰
    }

    // I-PPdd
    for (auto wave : {3, 6, 9, 11, 14, 17})
    {
        Connect(1300 - 200 - 373, aCobManager.Fire({{2, 8.8}, {5, 8.8}}));
        Connect(1300 + 20 - 298, aIceFiller.Coffee());                               // 20cs 预判冰
        Connect(1300 - 200 - 373 + 349, aCobManager.Fire({{1, 2.425}, {5, 2.425}})); // 减速尾炸
        if (wave == 9)
        {
            // Connect(1300 + 180, aCobManager.Fire({{1, 7.2}, {5, 7.2}})); // 可省略
            Connect(1300 + 1662 - 200 - 373, aCobManager.Fire({{2, 8.8}, {5, 8.8}});
                    Delay(81, ACoLaunch(DianCai); aPainter.Draw(AText("手动收尾！", 400, 300), 500);
                          Delay(220 - 81, aCobManager.Fire({{1, 7.8}, {5, 7.8}}); aCobManager.Skip(4))));
        }
    }

    // IPP-PPDDC
    for (auto wave : {4, 7, 12, 15, 18})
    {
        Connect(180, aCobManager.Fire({{1, 7.2}, {5, 7.2}}));
        Connect(1662 - 200 - 373, aCobManager.Fire({{2, 8.8}, {5, 8.8}});
                Delay(81, ACoLaunch(DianCai);
                      Delay(220 - 81, aCobManager.Fire({{1, 7.4}, {5, 7.4}})))); // 左移
    }

    // PPdd
    for (auto wave : {5, 8, 13, 16, 19})
    {
        Connect(-15, aCobManager.Fire({{2, 9}, {5, 9}}));
        Connect(-15 + 107, aCobManager.Fire({{1, 7.625}, {5, 7.625}}));
        Connect(601 + 20 - 298, aIceFiller.Coffee()); // 20cs 预判冰
        if (wave == 19)
        {
            Connect(601 + 1300 - 200 - 373, aPainter.Draw(AText("手动收尾！", 400, 300), 500);
                    Delay(100, aCobManager.Fire({{2, 8.8}, {5, 8.8}}); // 尾炸炮时机微调
                          Delay(220, aCobManager.Fire({{1, 7.5}, {5, 7.5}}); aCobManager.Skip(3))));
        }
    }

    for (auto wave : {20})
    {
        Connect(-150, aCobManager.Fire(4, 7));
        Connect(-60, aCobManager.Fire({{1, 9}, {2, 9}, {5, 9}, {6, 9}});
                Delay(108, aCobManager.RecoverFire({{1, 9}, {2, 9}, {5, 9}, {6, 9}})));
    }
}