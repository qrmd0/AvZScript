/*
 * 阵名: ME十三炮
 * 出处: https://tieba.baidu.com/p/5288033944
 * 节奏: C5u-35s: PPD|PPD|PPD|IP-PPD, (6|6|6|17)
 */
#include <avz.h>

// 连接(使用宏定义简化)
#define Connect(wave, time, ...) AConnect(ATime(wave, time), [=] { __VA_ARGS__; })

ALogger<AConsole> consoleLogger; // 日志对象-控制台

ACoroutine I()
{
    ACard({AFLOWER_POT, AICE_SHROOM}, 3, 7);
    co_await ANowDelayTime(100 + 1);
    ARemovePlant(3, 7);
}

ACoroutine II()
{
    ACard({AFLOWER_POT, AM_ICE_SHROOM}, 3, 7);
    co_await ANowDelayTime(320 + 100 + 1);
    ARemovePlant(3, 7);
}

void AScript()
{
    // ASetReloadMode(AReloadMode::MAIN_UI_OR_FIGHT_UI);

    ASetZombies({
        AZOMBIE,                 // 普僵
        APOLE_VAULTING_ZOMBIE,   // 撑杆
        AFOOTBALL_ZOMBIE,        // 橄榄
        AZOMBONI,                // 冰车
        AJACK_IN_THE_BOX_ZOMBIE, // 小丑
        ABALLOON_ZOMBIE,         // 气球
        APOGO_ZOMBIE,            // 跳跳
        ABUNGEE_ZOMBIE,          // 蹦极
        ALADDER_ZOMBIE,          // 扶梯
        ACATAPULT_ZOMBIE,        // 篮球
        AGARGANTUAR,             // 白眼
        AGIGA_GARGANTUAR,        // 红眼
    });
    ASelectCards({
        AKERNEL_PULT,   // 玉米
        ACOB_CANNON,    // 玉米炮
        ABLOVER,        // 三叶草
        AUMBRELLA_LEAF, // 保护伞
        ACHERRY_BOMB,   // 樱桃
        ASQUASH,        // 倭瓜
        AWALL_NUT,      // 坚果
        AFLOWER_POT,    // 花盆
        AICE_SHROOM,    // 寒冰菇
        AM_ICE_SHROOM,  // 复制冰
    });

    Connect(1, -599,
            aCobManager.SetList({
                {1, 3}, {1, 5}, {1, 1}, //
                {2, 3}, {2, 5}, {2, 1}, //
                {3, 3}, {3, 5}, {3, 1}, //
                {4, 6}, //
                {4, 1}, {5, 6}, {5, 1}, //
            }));

    for (int wave = 1; wave < 21; ++wave)
    {
        Connect(wave, -200, consoleLogger.Info("当前操作波次: {}", wave));

        if (wave == 20)
        {
            Connect(wave, 10 - 320, ACoLaunch(II)); // 冰消空降
            Connect(wave, 100, aCobManager.RoofFire(5, 8));
            Connect(wave, 800, aCobManager.RoofFire({{2, 9}, {2, 9}, {2, 9}, {2, 9}}));
            Connect(wave, 1000, aCobManager.RoofFire({{4, 9}, {4, 9}, {4, 9}, {4, 9}});
                    consoleLogger.Info("第 {} 波手动收尾.", wave));
        }

        // IP-PPD
        else if (ARangeIn(wave, {4, 8, 10, 14, 18}))
        {
            if (ARangeIn(wave, {4, 10, 18}))
            {
                Connect(wave, 5 - 100, ACoLaunch(I)); // 本波原版冰
            }
            Connect(wave, 100, aCobManager.RoofFire(5, 8));
            Connect(wave, 1700 - 200 - 387, aCobManager.RoofFire({{2, 8.5}, {4, 8.5}}));
            Connect(wave, 1700 - 200 - 387 + 230, aCobManager.RoofFire(2, 7)); // 减速延迟 230 炸小鬼
        }

        // PPD
        else // else if (ARangeIn(wave, {1, 2, 3, 5, 6, 7, 9, 11, 12, 13, 15, 16, 17, 19}))
        {
            Connect(wave, 10, aCobManager.RoofFire({{2, 8.5}, {4, 8.5}})); // 刷新后
            Connect(wave, 10 + 130, aCobManager.RoofFire(2, 7.6));         // 原速延迟 130 炸小鬼
            if (ARangeIn(wave, {7, 13}))
            {
                Connect(wave, 601 + 5 - 100 - 320, ACoLaunch(II)); // 下一波的复制冰
            }
            if (ARangeIn(wave, {9, 19})) // 收尾
            {
                Connect(wave, 601, aCobManager.RoofFire({{2, 8.5}, {4, 8.5}}));
                Connect(wave, 601 + 130, aCobManager.RoofFire(2, 7.6));
                // 自动操作收尾
                Connect(wave, 601 + 601, aCobManager.RoofFire(2, 7.4));
                Connect(wave, 601 + 601 + 300, aCobManager.RoofFire(5, 8));
                Connect(wave, 601 + 601 + 300 + 500, aCobManager.RoofFire(5, 8));
            }
        }
    }
}
