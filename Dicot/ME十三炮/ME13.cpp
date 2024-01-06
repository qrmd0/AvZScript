/*
 * 阵名: ME十三炮
 * 出处: https://tieba.baidu.com/p/5288033944
 * 节奏: C5u-35s: PPD|PPD|PPD|IP-PPD, (6|6|6|17)
 */

#include <avz.h>
#define Connect(wave, time, ...) AConnect(ATime(wave, time), [] { __VA_ARGS__; }) // 使用宏定义简化代码

ACoroutine I()
{
    ACard({{AFLOWER_POT, 3, 7}, {AICE_SHROOM, 3, 7}});
    co_await ANowDelayTime(100 + 1);
    ARemovePlant(3, 7);
}

ACoroutine II()
{
    ACard({{AFLOWER_POT, 3, 7}, {AM_ICE_SHROOM, 3, 7}});
    co_await ANowDelayTime(320 + 100 + 1);
    ARemovePlant(3, 7);
}

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
        AKERNEL_PULT,   // 玉米投手
        ACOB_CANNON,    // 玉米加农炮
        ABLOVER,        // 三叶草
        AUMBRELLA_LEAF, // 叶子保护伞
        ACHERRY_BOMB,   // 樱桃炸弹
        ASQUASH,        // 倭瓜
        AWALL_NUT,      // 坚果
        AFLOWER_POT,    // 花盆
        AICE_SHROOM,    // 寒冰菇
        AM_ICE_SHROOM,  // 模仿寒冰菇
    });

    Connect(1, -599, aCobManager.SetList({
                         {1, 3},
                         {1, 5},
                         {1, 1},
                         {2, 3},
                         {2, 5},
                         {2, 1},
                         {3, 3},
                         {3, 5},
                         {3, 1},
                         {4, 6},
                         {4, 1},
                         {5, 6},
                         {5, 1},
                     }));

    for (int wave = 1; wave < 21; ++wave)
    {
        if (wave == 20)
        {
            Connect(wave, 10 - 320, ACoLaunch(II)); // 冰消空降
            Connect(wave, 100, aCobManager.RoofFire(5, 8));
            Connect(wave, 800, aCobManager.RoofFire({{2, 9}, {2, 9}, {2, 9}, {2, 9}}));
            Connect(wave, 1000, aCobManager.RoofFire({{4, 9}, {4, 9}, {4, 9}, {4, 9}}));
            // 第 20 波手动收尾
        }

        // IP-PPD
        else if (wave == 4 || wave == 8 || wave == 10 || wave == 14 || wave == 18)
        {
            if (wave == 4 || wave == 10 || wave == 18)
            {
                Connect(wave, 5 - 100, ACoLaunch(I)); // 本波原版冰
            }
            Connect(wave, 100, aCobManager.RoofFire(5, 8));
            Connect(wave, 1700 - 200 - 373, aCobManager.RoofFire({{2, 8.5}, {4, 8.5}}));
            Connect(wave, 1700 - 200 - 373 + 230, aCobManager.RoofFire(2, 7)); // 减速延迟 230 炸小鬼
        }

        // PPD
        else // wave 1, 2, 3, 5, 6, 7, 9, 11, 12, 13, 15, 16, 17, 19
        {
            Connect(wave, 10, aCobManager.RoofFire({{2, 8.5}, {4, 8.5}})); // 刷新后
            Connect(wave, 10 + 130, aCobManager.RoofFire(2, 7.6));         // 原速延迟 130 炸小鬼
            if (wave == 7 || wave == 13)
            {
                Connect(wave, 601 + 5 - 100 - 320, ACoLaunch(II)); // 下一波的复制冰
            }
            if (wave == 9 || wave == 19) // 收尾
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
