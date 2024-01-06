/*
 * 阵名: RE十六炮
 * 出处: https://tieba.baidu.com/p/1410367512
 * 节奏: ch6: PSD/P|IP-PPD|PSD/P|IP-PPD, (6|12|6|12)
 */

#include <avz.h>

// 使用宏定义简化代码
#define Connect(wave, time, ...) AConnect(ATime(wave, time), [] { __VA_ARGS__; })
#define Delay(delayTime, ...) AConnect(ANowDelayTime(delayTime), [] { __VA_ARGS__; })

void AScript()
{
    ASetZombies({
        APJ_0,  // 普僵
        ACG_3,  // 撑杆
        AGL_7,  // 橄榄
        ABC_12, // 冰车
        AXC_15, // 小丑
        AQQ_16, // 气球
        ATT_18, // 跳跳
        ABJ_20, // 蹦极
        AFT_21, // 扶梯
        ATL_22, // 投篮
        ABY_23, // 白眼
        AHY_32, // 红眼
    });
    ASelectCards({
        AKERNEL_PULT,  // 玉米投手
        ACOB_CANNON,   // 玉米加农炮
        ACHERRY_BOMB,  // 樱桃炸弹
        ASQUASH,       // 倭瓜
        AWALL_NUT,     // 坚果
        ADOOM_SHROOM,  // 毁灭菇
        AICE_SHROOM,   // 寒冰菇
        AM_ICE_SHROOM, // 模仿寒冰菇
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

    // PPSD
    for (auto wave : {1, 3, 5, 7, 9, 10, 12, 14, 16, 18})
    {
        Connect(wave, -10, aCobManager.RoofFire({{2, 9}, {2, 9}, {4, 9}}); // -10 + 373 < 377
                Delay(110, aCobManager.RoofFire(2, 8.8)));                 // 110 拦截
        Connect(wave, 601 + 50 - 298, aIceFiller.Coffee());                // 50cs 预判冰
        if (wave == 9)
        {
            Connect(wave, 601 - 150, aCobManager.RoofFire(2, 9));
            Connect(wave, 601 + 1200 - 200 - 373, aCobManager.RoofFire({{5, 9}, {5, 9}});
                    Delay(1100, aCobManager.RoofFire(5, 9))); // 等会儿
        }
    }

    // IP-PPD
    for (auto wave : {2, 4, 6, 8, 11, 13, 15, 17, 19})
    {
        Connect(wave, -150, aCobManager.RoofFire(2, 9));
        Connect(wave, 1200 - 200 - 373, aCobManager.RoofFire({{2, 9}, {4, 9}}); // 1200cs 波长; 激活炸
                Delay(220, aCobManager.RoofFire(2, 7.8)));                      // 220 拦截
        if (wave == 19)
        {
            Connect(wave, 1200 - 10, aCobManager.RoofFire({{2, 9}, {2, 9}, {4, 9}});
                    Delay(110, aCobManager.RoofFire(2, 8.8))); // 110 拦截
            Connect(wave, 1200 + 601 - 150, aCobManager.RoofFire(5, 9));
            Connect(wave, 1200 + 601 + 1200 - 200 - 373, // 等会儿
                    Delay(50, aCobManager.RoofFire(5, 9)));
        }
    }

    for (auto wave : {20})
    {
        Connect(wave, -200, aIceFiller.Coffee());                        // 冰消空降
        Connect(wave, -100, aCobManager.RoofFire({{2, 8.5}, {5, 8.5}})); // 炸冰车
        Connect(wave, 50, aCobManager.RoofFire({{4, 2.5}, {4, 6.7}}));   // 炸小偷
        Connect(wave, 800, aCobManager.RoofFire({{2, 9}, {2, 9}, {2, 9}, {2, 9}}));
        Connect(wave, 1000, aCobManager.RoofFire({{4, 9}, {4, 9}, {4, 9}, {4, 9}}));
        // 第 20 波手动收尾
    }
}