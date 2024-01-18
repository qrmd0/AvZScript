/*
 * 阵名: RE椭盘十四炮
 * 出处: https://tieba.baidu.com/p/5029428684
 * 节奏: ch4: AIce3+PPDD+B-PP|AIce3+PPDD+B-PP, (1780|1780)
 */

#include <avz.h>

// 使用宏定义简化代码
#define Connect(time, ...) AConnect(ATime(wave, time), [=] { __VA_ARGS__; })
#define Delay(delayTime, ...) AConnect(ANowDelayTime(delayTime), [] { __VA_ARGS__; })

// 检测 3 路是否漏炸跳跳
bool IsMissTiaoTiao()
{
    for (auto &&zombie : aAliveZombieFilter)
    {
        if (zombie.Row() == 2 && zombie.Type() == APOGO_ZOMBIE && zombie.ExistTime() >= 100)
        {
            return true;
        }
    }
    return false;
}

// 检测 1 路是否出红眼
bool IsSpawnHongYan()
{
    for (auto &&zombie : aAliveZombieFilter)
    {
        if (zombie.Row() == 0 && zombie.Type() == AGIGA_GARGANTUAR && zombie.Hp() >= 3000)
        {
            return true;
        }
    }
    return false;
}

void AScript()
{
    // ASetReloadMode(AReloadMode::MAIN_UI_OR_FIGHT_UI);

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
                     AFLOWER_POT,   // 花盆
                     AICE_SHROOM,   // 寒冰菇
                     AM_ICE_SHROOM, // 模仿寒冰菇
                     ADOOM_SHROOM,  // 毁灭菇
                     ACOFFEE_BEAN,  // 咖啡豆
                     ACHERRY_BOMB,  // 樱桃炸弹
                     AJALAPENO,     // 火爆辣椒
                     ASQUASH,       // 倭瓜
                     ASNOW_PEA,     // 寒冰射手
                     AWALL_NUT,     // 坚果
                 },
                 1);

    AConnect(ATime(1, -599), []
             {
            aCobManager.SetList({
                {4, 2}, // P
                {4, 4}, // P
                {1, 4}, // D
                {5, 4}, // D
                {5, 6}, // B
                {3, 1}, // P
                {4, 7}, // P
                //
                {1, 2}, // P
                {2, 4}, // P
                {3, 3}, // D
                {3, 5}, // D
                {2, 6}, // B
                {2, 1}, // P
                {3, 7}, // P
            });
            // IPPDDP-PP IPPDDP-PP  14
            // PPDDDD    IP-PP      9
            // PPSSDD    IAA'aP-PP  9
            aCobManager.Skip(5); // 调整炮序
            ACard({AFLOWER_POT, AICE_SHROOM}, 1, 7);
            aIceFiller.Start({{4, 6}, {2, 3}, {1, 1}, {1, 6}});
            aIceFiller.SetIceSeedList({AM_ICE_SHROOM, AICE_SHROOM}); });

    for (int wave = 1; wave < 21; ++wave)
    {
        if (wave == 1)
        {
            Connect(377 - 387, aCobManager.RoofFire({{2, 8.8}, {4, 8.8}}));
            Connect(506 - 387, aCobManager.RoofFire({{2, 8.8}, {4, 8.8}}));
            Connect(601 + 34 - 387, aCobManager.RoofFire({{2, 8.7}, {4, 8.7}}));
            Connect(601 + 34 - 298, ACard(ACOFFEE_BEAN, 1, 7)); // aIceFiller.Coffee()
        }

        else if (wave == 2)
        {
            Connect(50, ARemovePlant(1, 7));                                   // 铲
            Connect(1300 - 200 - 387, aCobManager.RoofFire(4, 8.2));           // 713
            Connect(1780 - 200 - 387, aCobManager.RoofFire({{2, 9}, {4, 9}})); // 1193
            Connect(
                1780 - 200 - 100, if (IsMissTiaoTiao()) { ACard({AFLOWER_POT, AJALAPENO}, 3, 9); });
            Connect(1780 + 11 - 298, aIceFiller.Coffee(); AIce3(298)); // 1493
        }

        else if (wave == 10)
        {
            Connect(-15, aCobManager.RoofFire({{2, 9}, {4, 9}, {2, 9}, {4, 9}}));
            Connect(-15 + 110, aCobManager.RoofFire(4, 7.7));         // 95; 空炸小鬼兼小偷
            Connect(-15 + 190, aCobManager.RoofFire(1, 5));           // 175; 2-5? 尾炸小鬼兼小偷
            Connect(601 + 11 - 298, aIceFiller.Coffee(); AIce3(298)); // 314
        }

        else if (wave == 11)
        {
            Connect(10 + 400 - 100, ACard(AJALAPENO, 1, 7); ACard({AFLOWER_POT, ACHERRY_BOMB}, 4, 9));
            Connect(10 + 400 + 10, ARemovePlant(1, 7); ARemovePlant(4, 9)); // 铲
            Connect(1250 - 200 - 387, aCobManager.RoofFire(3, 8.21));       // 1300->1250; 落点改为 3 路炸掉 2 路冰车
            Connect(1780 - 200 - 387, aCobManager.RoofFire({{2, 9}, {4, 9}}));
            Connect(1780 + 11 - 298, aIceFiller.Coffee(); AIce3(298));
        }

        else if (wave == 3 || wave == 12)
        {
            Connect(10 + 400 - 387, aCobManager.RoofFire({{2, 9}, {4, 9}}));
            Connect(10 + 400 - 387 + 220, aCobManager.RoofFire(4, 8.5)); // 空炸
            Connect(10 + 400 - 387 + 300, aCobManager.RoofFire(1, 4.7)); // 尾炸小鬼跳跳
            Connect(1300 - 200 - 387, aCobManager.RoofFire(4, 8.2));
            Connect(1780 - 200 - 387, aCobManager.RoofFire({{2, 9}, {4, 9}}));
            Connect(1780 + 11 - 298, aIceFiller.Coffee(); AIce3(298));
        }

        else if (wave == 9 || wave == 19)
        {
            Connect(10 + 400 - 387, aCobManager.RoofFire({{2, 9}, {4, 9}}));
            Connect(10 + 400 - 387 + 220, aCobManager.RoofFire({{2, 8.5}, {4, 8.5}}));
            Connect(1300 - 200 - 387, aCobManager.RoofFire(3, 8.22)); // 落点改为 3 路减少小丑炸核机率
            // 收尾
            Connect(1705 - 200 - 298, ACard({AFLOWER_POT, ADOOM_SHROOM, ACOFFEE_BEAN}, 3, 9));
            Connect(
                1300 - 200, if (!IsSpawnHongYan()) // TODO: 如果 1 路没有出红眼
                {
                    Connect(1705 - 200 - 298 + 751, ACard({AFLOWER_POT, ASQUASH}, 2, 9);
                            Delay(183, ARemovePlant(2, 9); ARemovePlant(2, 9)));
                    Connect(1705 - 200 + 230 - 387, aCobManager.RoofFire({{2, 7.4}, {4, 8.5}}));       // 拦截
                    Connect(1705 - 200 + 230 + 230 - 387, aCobManager.RoofFire({{3, 8.5}, {4, 8.5}})); // 拦截
                } else {
                    Connect(1705 - 200 + 230 - 387, aCobManager.RoofFire({{2, 8.5}, {4, 8.5}}));       // 拦截
                    Connect(1705 - 200 + 230 + 230 - 387, aCobManager.RoofFire({{2, 8.5}, {4, 8.5}})); // 拦截
                });
            Connect(1705 - 200 + 230 + 230 + 230 - 387, aCobManager.RoofFire({{3, 9}, {4, 9}}); // 留下 1 路
                    Delay(50, ACard(ASNOW_PEA, 1, 6)));
            // 清场
            if (wave == 9)
            {
                Connect(2700, aCobManager.Skip(7 - 4 - 1 + 5); ACard(AFLOWER_POT, 1, 8)); // 调整炮序; 垫一下
                Connect(4500 - 200 - 387,                                                 // 出红字时
                        Delay(400, aCobManager.RoofFire(1, 8)));                          // 等那一门炮; 清场
                Connect(4500 - 200 + 100, ARemovePlant(1, 6));                            // 铲掉冰豆
                Connect(4500 - 5 + 750 - 599, ACard(AFLOWER_POT, 1, 7));                  // 第 10 波刷新前 599
            }
            else if (wave == 19)
            {
                Connect(4500 - 200 - 387, aCobManager.RoofFire(1, 8); // 清场
                        Delay(200, ARemovePlant(1, 6)));              // 铲掉冰豆
            }
        }

        else if (wave == 20)
        {
            Connect(50 - 298, aIceFiller.Coffee());                      // 冰消空降
            Connect(75, aCobManager.RoofFire({{2, 3}, {4, 8}, {2, 8}})); // 炸冰车小偷
            Connect(1250 - 200 - 387, aCobManager.RoofFire({{1, 9}, {2, 9}, {4, 9}, {5, 9}}));
            Connect(1250 - 200 - 387 + 220, aCobManager.RoofFire({{1, 9}, {2, 9}, {4, 9}, {5, 9}}));
            // 第 20 波手动收尾
        }

        else // wave 4, 5, 6, 7, 8, 13, 14, 15, 16, 17, 18
        {
            // 收尾波前一波延长波长
            int WL = (wave == 8 || wave == 18) ? 1925 : 1780;
            Connect(10 + 400 - 387, aCobManager.RoofFire({{2, 9}, {4, 9}}));
            Connect(10 + 400 - 387 + 220, aCobManager.RoofFire({{2, 8.5}, {4, 8.5}}));
            Connect(1300 - 200 - 387, aCobManager.RoofFire(4, 8.14));
            Connect(WL - 200 - 387, aCobManager.RoofFire({{2, 9}, {4, 9}})); // WL - 587
            if (wave == 8 || wave == 18)
            {
                Connect(WL - 200 - 387 + 83, ACard(AFLOWER_POT, 2, 8)); // WL - 504; 垫 2 路梯子
                Connect(WL - 200, ARemovePlant(2, 8));                  // WL - 200; 炮落地铲
            }
            Connect(WL + 11 - 298, aIceFiller.Coffee(); AIce3(298)); // WL - 287
        }
    }
}