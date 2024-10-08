/*
 * 阵名: RE椭盘十四炮
 * 出处: https://tieba.baidu.com/p/5029428684
 * 节奏: ch4: AIce3+PPDD+B-PP|AIce3+PPDD+B-PP, (1780|1780)
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
        AFLOWER_POT,   // 花盆
        AICE_SHROOM,   // 寒冰菇
        AM_ICE_SHROOM, // 模仿者寒冰菇
        ADOOM_SHROOM,  // 毁灭菇
        ACOFFEE_BEAN,  // 咖啡豆
        ACHERRY_BOMB,  // 樱桃炸弹
        AJALAPENO,     // 火爆辣椒
        ASQUASH,       // 倭瓜
        ASNOW_PEA,     // 寒冰射手
        AWALL_NUT,     // 坚果墙
    });

    Connect(1, -599,
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
            aIceFiller.SetIceSeedList({AM_ICE_SHROOM, AICE_SHROOM}); // 最后一个存冰优先存白冰, 避免与下一轮选卡蓝冰冲突
    );

    for (int wave = 1; wave < 21; ++wave)
    {
        Connect(wave, -200, consoleLogger.Info("当前操作波次: {}", wave));

        if (wave == 1)
        {
            Connect(wave, 377 - 387, aCobManager.RoofFire({{2, 8.8}, {4, 8.8}}));
            Connect(wave, 506 - 387, aCobManager.RoofFire({{2, 8.8}, {4, 8.8}}));
            Connect(wave, 601 + 34 - 387, aCobManager.RoofFire({{2, 8.7}, {4, 8.7}}));
            Connect(wave, 601 + 34 - 298, ACard(ACOFFEE_BEAN, 1, 7)); // aIceFiller.Coffee()
        }

        else if (wave == 2)
        {
            Connect(wave, 50, ARemovePlant(1, 7));                                   // 铲
            Connect(wave, 1300 - 200 - 387, aCobManager.RoofFire(4, 8.2));           // 713
            Connect(wave, 1780 - 200 - 387, aCobManager.RoofFire({{2, 9}, {4, 9}})); // 1193
            CoConnect(wave, 1780 - 200 - 100, if (AIsZombieExist(APOGO_ZOMBIE, 3)) {
                        ACard({AFLOWER_POT, AJALAPENO}, 3, 9); Delay(100); ARemovePlant(3, 9); });
            Connect(wave, 1780 + 11 - 298, aIceFiller.Coffee(); AIce3(298)); // 1493
        }

        else if (wave == 10)
        {
            Connect(wave, -15, aCobManager.RoofFire({{2, 9}, {4, 9}, {2, 9}, {4, 9}}));
            Connect(wave, -15 + 110, aCobManager.RoofFire(4, 7.7));         // 95; 空炸小鬼兼小偷
            Connect(wave, -15 + 190, aCobManager.RoofFire(1, 5));           // 175; 2-5? 尾炸小鬼兼小偷
            Connect(wave, 601 + 11 - 298, aIceFiller.Coffee(); AIce3(298)); // 314
        }

        else if (wave == 11)
        {
            Connect(wave, 10 + 400 - 100, ACard(AJALAPENO, 1, 7); ACard({AFLOWER_POT, ACHERRY_BOMB}, 4, 9));
            Connect(wave, 10 + 400 + 10, ARemovePlant({{1, 7}, {4, 9}}));   // 铲
            Connect(wave, 1250 - 200 - 387, aCobManager.RoofFire(3, 8.21)); // 1300->1250; 落点改为 3 路炸掉 2 路冰车
            Connect(wave, 1780 - 200 - 387, aCobManager.RoofFire({{2, 9}, {4, 9}}));
            Connect(wave, 1780 + 11 - 298, aIceFiller.Coffee(); AIce3(298));
        }

        else if (ARangeIn(wave, {3, 12}))
        {
            Connect(wave, 10 + 400 - 387, aCobManager.RoofFire({{2, 9}, {4, 9}}));
            Connect(wave, 10 + 400 - 387 + 220, aCobManager.RoofFire(4, 8.5)); // 空炸
            Connect(wave, 10 + 400 - 387 + 300, aCobManager.RoofFire(1, 4.7)); // 尾炸小鬼跳跳
            Connect(wave, 1300 - 200 - 387, aCobManager.RoofFire(4, 8.2));
            Connect(wave, 1780 - 200 - 387, aCobManager.RoofFire({{2, 9}, {4, 9}}));
            Connect(wave, 1780 + 11 - 298, aIceFiller.Coffee(); AIce3(298));
        }

        else if (ARangeIn(wave, {9, 19}))
        {
            Connect(wave, 10 + 400 - 387, aCobManager.RoofFire({{2, 9}, {4, 9}}));
            Connect(wave, 10 + 400 - 387 + 220, aCobManager.RoofFire({{2, 8.5}, {4, 8.5}}));
            Connect(wave, 1300 - 200 - 387, aCobManager.RoofFire(3, 8.22)); // 落点改为 3 路减少小丑炸核机率
            // 收尾
            // TODO: 处理本波没出红眼的情况
            Connect(wave, 1705 - 200 - 298, ACard({AFLOWER_POT, ADOOM_SHROOM, ACOFFEE_BEAN}, 3, 9));
            Connect(wave, 1705 - 200 + 230 - 387, aCobManager.RoofFire({{2, 8.5}, {4, 8.5}}));          // 拦截
            Connect(wave, 1705 - 200 + 230 + 230 - 387, aCobManager.RoofFire({{2, 8.5}, {4, 8.5}}));    // 拦截
            CoConnect(wave, 1705 - 200 + 230 + 230 + 230 - 387, aCobManager.RoofFire({{3, 9}, {4, 9}}); // 留下 1 路
                      Delay(50); ACard(ASNOW_PEA, 1, 6));
            // 清场
            if (wave == 9)
            {
                Connect(wave, 2700,
                        aCobManager.Skip(7 - 4 - 1 + 5); // 调整炮序
                        ACard(AFLOWER_POT, 1, 8);        // 垫一下
                );
                CoConnect(wave, 4500 - 200 - 387,
                          Delay(400);                 // 等那一门炮
                          aCobManager.RoofFire(1, 8); // 清场
                );
                Connect(wave, 4500 - 200 + 100, ARemovePlant(1, 6));           // 铲掉冰豆
                Connect(wave, 4500 - 5 + 750 - 599, ACard(AFLOWER_POT, 1, 7)); // 第 10 波刷新前 599
            }
            else if (wave == 19)
            {
                CoConnect(wave, 4500 - 200 - 387,
                          aCobManager.RoofFire(1, 8);     // 清场
                          Delay(200); ARemovePlant(1, 6); // 铲掉冰豆
                );
            }
        }

        else if (wave == 20)
        {
            Connect(wave, 50 - 298, aIceFiller.Coffee());                      // 冰消空降
            Connect(wave, 75, aCobManager.RoofFire({{2, 3}, {4, 8}, {2, 8}})); // 炸冰车小偷
            Connect(wave, 1250 - 200 - 387, aCobManager.RoofFire({{1, 9}, {2, 9}, {4, 9}, {5, 9}}));
            Connect(wave, 1250 - 200 - 387 + 220, aCobManager.RoofFire({{1, 9}, {2, 9}, {4, 9}, {5, 9}});
                    consoleLogger.Info("第 {} 波手动收尾.", wave));
        }

        else // else if (ARangeIn(wave, {4, 5, 6, 7, 8, 13, 14, 15, 16, 17, 18}))
        {
            // 收尾波前一波延长波长
            int length = ARangeIn(wave, {8, 13}) ? 1925 : 1780;
            Connect(wave, 10 + 400 - 387, aCobManager.RoofFire({{2, 9}, {4, 9}}));
            Connect(wave, 10 + 400 - 387 + 220, aCobManager.RoofFire({{2, 8.5}, {4, 8.5}}));
            Connect(wave, 1300 - 200 - 387, aCobManager.RoofFire(4, 8.14));
            Connect(wave, length - 200 - 387, aCobManager.RoofFire({{2, 9}, {4, 9}})); // length - 587
            if (ARangeIn(wave, {8, 13}))
            {
                Connect(wave, length - 200 - 387 + 83, ACard(AFLOWER_POT, 2, 8)); // length - 504; 垫 2 路梯子
                Connect(wave, length - 200, ARemovePlant(2, 8));                  // length - 200; 炮落地铲
            }
            Connect(wave, length + 11 - 298, aIceFiller.Coffee(); AIce3(298)); // length - 287
        }
    }
}
