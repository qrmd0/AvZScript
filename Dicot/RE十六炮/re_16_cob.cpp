/*
 * 阵名: RE十六炮
 * 出处: https://tieba.baidu.com/p/1410367512
 * 节奏: ch6: PSD/P|IP-PPD|PSD/P|IP-PPD, (6|12|6|12)
 */
#include <avz.h>

// 连接(使用宏定义简化)
#define Connect(wave, time, ...) AConnect(ATime(wave, time), [=] { __VA_ARGS__; })
#define CoConnect(wave, time, ...) AConnect(ATime(wave, time), [=]() -> ACoroutine { __VA_ARGS__; })
#define Delay(delayTime) co_await ANowDelayTime(delayTime)

ALogger<AConsole> consoleLogger; // 日志对象-控制台

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
        AKERNEL_PULT,  // 玉米
        ACOB_CANNON,   // 玉米炮
        ACHERRY_BOMB,  // 樱桃
        ASQUASH,       // 倭瓜
        AWALL_NUT,     // 坚果
        ADOOM_SHROOM,  // 核蘑菇
        AICE_SHROOM,   // 冰蘑菇
        AM_ICE_SHROOM, // 模仿者寒冰菇
        ACOFFEE_BEAN,  // 咖啡豆
        AFLOWER_POT,   // 花盆
    });

    Connect(1, -599,
            aCobManager.SetList({
                {1, 3}, // P
                {1, 5}, // S
                {1, 7}, //    P
                {1, 1}, // D
                {2, 3}, // P
                {2, 5}, // P
                {2, 7}, //    P
                {2, 1}, // D
                {3, 3}, // P
                {3, 5}, // S
                {3, 7}, //    P
                {3, 1}, // D
                {4, 6}, // P
                {4, 1}, // P
                {5, 6}, //    P
                {5, 1}, // D
            });
            aIceFiller.Start({{5, 3}, {4, 3}}));

    for (int wave = 1; wave < 21; ++wave)
    {
        Connect(wave, -200, consoleLogger.Info("当前操作波次: {}", wave));

        // PPSD
        if (ARangeIn(wave, {1, 3, 5, 7, 9, 10, 12, 14, 16, 18}))
        {
            CoConnect(wave, -10, // -10 + 387 < 377
                      aCobManager.RoofFire({{2, 9}, {2, 9}, {4, 9}});
                      Delay(110); // 110 拦截
                      aCobManager.RoofFire(2, 8.8));
            Connect(wave, 601 + 50 - 298, aIceFiller.Coffee()); // 50cs 预判冰
            if (wave == 9)
            {
                Connect(wave, 601 - 150, aCobManager.RoofFire(2, 9));
                CoConnect(wave, 601 + 1200 - 200 - 387, aCobManager.RoofFire({{5, 9}, {5, 9}});
                          Delay(1100); // 等会儿
                          aCobManager.RoofFire(5, 9));
            }
        }

        // IP-PPD
        else if (ARangeIn(wave, {2, 4, 6, 8, 11, 13, 15, 17, 19}))
        {
            Connect(wave, -150, aCobManager.RoofFire(2, 9));
            CoConnect(wave, 1200 - 200 - 387,                 // 1200cs 波长
                      aCobManager.RoofFire({{2, 9}, {4, 9}}); // 激活炸
                      Delay(220);                             // 220 拦截
                      aCobManager.RoofFire(2, 7.8));
            if (wave == 19)
            {
                CoConnect(wave, 1200 - 10, aCobManager.RoofFire({{2, 9}, {2, 9}, {4, 9}});
                          Delay(110); // 110 拦截
                          aCobManager.RoofFire(2, 8.8));
                Connect(wave, 1200 + 601 - 150, aCobManager.RoofFire(5, 9));
                CoConnect(wave, 1200 + 601 + 1200 - 200 - 387,
                          Delay(50); // 等会儿
                          aCobManager.RoofFire(5, 9));
            }
        }

        else if (wave == 20)
        {
            Connect(wave, -200, aIceFiller.Coffee());                        // 冰消空降
            Connect(wave, -100, aCobManager.RoofFire({{2, 8.5}, {5, 8.5}})); // 炸冰车
            Connect(wave, 50, aCobManager.RoofFire({{4, 2.5}, {4, 6.7}}));   // 炸小偷
            Connect(wave, 800, aCobManager.RoofFire({{2, 9}, {2, 9}, {2, 9}, {2, 9}}));
            Connect(wave, 1000, aCobManager.RoofFire({{4, 9}, {4, 9}, {4, 9}, {4, 9}});
                    consoleLogger.Info("第 {} 波手动收尾.", wave));
        }
    }
}
