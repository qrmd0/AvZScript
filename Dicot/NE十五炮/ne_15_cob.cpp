/*
 * 阵名: NE十五炮
 * 出处: https://tieba.baidu.com/p/1067040250
 * 节奏: C8u: IPP-PP|PADC|PPDD|IPP-PP|NDC|PPDD, (13|6|6|13|6|6)
 */
#include <avz.h>

// 连接(使用宏定义简化)
#define Connect(wave, time, ...) AConnect(ATime(wave, time), [=] { __VA_ARGS__; })
#define CoConnect(wave, time, ...) AConnect(ATime(wave, time), [=]() -> ACoroutine { __VA_ARGS__; })
#define Delay(delayTime) co_await ANowDelayTime(delayTime)

ALogger<AConsole> consoleLogger; // 日志对象-控制台

ACoroutine DianCai()
{
    ACard({{APUFF_SHROOM, 4, 9}, {ASUN_SHROOM, 5, 9}});
    Delay(120);
    ARemovePlant({{4, 9}, {5, 9}});
}

void AScript()
{
    // ASetReloadMode(AReloadMode::MAIN_UI_OR_FIGHT_UI);

    ASetZombies({
        AZOMBIE,                 // 普僵
        APOLE_VAULTING_ZOMBIE,   // 撑杆
        ADANCING_ZOMBIE,         // 舞王
        AJACK_IN_THE_BOX_ZOMBIE, // 小丑
        ABALLOON_ZOMBIE,         // 气球
        ADIGGER_ZOMBIE,          // 矿工
        APOGO_ZOMBIE,            // 跳跳
        ABUNGEE_ZOMBIE,          // 蹦极
        ALADDER_ZOMBIE,          // 扶梯
        ACATAPULT_ZOMBIE,        // 篮球
        AGARGANTUAR,             // 白眼
        AGIGA_GARGANTUAR,        // 红眼
    });
    ASelectCards({
        AM_ICE_SHROOM, // 复制冰
        AICE_SHROOM,   // 原版冰
        ADOOM_SHROOM,  // 核蘑菇
        ACHERRY_BOMB,  // 樱桃
        ASQUASH,       // 倭瓜
        AGRAVE_BUSTER, // 墓碑
        APUMPKIN,      // 南瓜
        ABLOVER,       // 三叶草
        ASUN_SHROOM,   // 阳光菇
        APUFF_SHROOM,  // 小喷菇
    });

    Connect(1, -599, aCobManager.AutoSetList();
            // aCobManager.SetList({
            //     {1, 1}, {2, 1}, {3, 1}, {4, 1}, {5, 1},
            //     {1, 5}, {2, 5}, {3, 5}, {4, 5}, {5, 5},
            //     {1, 7}, {2, 7}, {3, 7}, {4, 7}, {5, 7},
            // });
    );

    for (int wave = 1; wave < 21; ++wave)
    {
        Connect(wave, -200, consoleLogger.Info("当前操作波次: {}", wave));

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
                CoConnect(wave, 601 - 150, aCobManager.Fire(4, 9);
                          Delay(450); aCobManager.Fire(1, 9));
                CoConnect(wave, 601 + 1300 - 200 - 373,
                          Delay(300); aCobManager.Fire({{2, 9}, {5, 9}}));
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
            Connect(wave, -95 + 373 - 100, ACard(ADOOM_SHROOM, (wave == 5 ? 3 : 2), 9));
            // 是第 5 波则弹坑在 3-9, 否则在 2-9
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
            CoConnect(wave, 601 - 100 - 83, aCobManager.Fire({{1, 8.3}, {4, 8.3}});
                      Delay(100); ACard(AICE_SHROOM, {{1, 9}, {2, 9}, {3, 9}, {4, 9}, {5, 9}})); // 冰杀小偷
            Connect(wave, 601, aCobManager.Fire({{2, 8.2}, {5, 8.2}});
                    consoleLogger.Info("第 {} 波手动收尾.", wave));
        }
    }
}
