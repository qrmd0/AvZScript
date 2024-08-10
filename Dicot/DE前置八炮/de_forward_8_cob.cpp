/*
 * 阵名: DE前置八炮
 * 出处: https://tieba.baidu.com/p/3943536673
 * 节奏: ch5: PP|I-PP|IPP-PP, (601|1437|1437)
 */
#include <avz.h>

// 连接(使用宏定义简化)
#define Connect(wave, time, ...) AConnect(ATime(wave, time), [=] { __VA_ARGS__; })

ALogger<AConsole> consoleLogger; // 日志对象-控制台

void AScript()
{
    // ASetReloadMode(AReloadMode::MAIN_UI_OR_FIGHT_UI);

    ASetZombies({
        AZOMBIE,                 // 普僵
        APOLE_VAULTING_ZOMBIE,   // 撑杆
        ADANCING_ZOMBIE,         // 舞王
        AZOMBONI,                // 冰车
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
        ACOFFEE_BEAN,    // 咖啡豆
        AICE_SHROOM,     // 寒冰菇
        AM_ICE_SHROOM,   // 复制冰
        ACHERRY_BOMB,    // 樱桃
        ASQUASH,         // 窝瓜
        AWALL_NUT,       // 坚果
        AFLOWER_POT,     // 花盆
        ASCAREDY_SHROOM, // 胆小菇
        ASUN_SHROOM,     // 阳光菇
        APUFF_SHROOM,    // 小喷菇
    });

    Connect(1, -599,
            aCobManager.SetList({{1, 1}, {1, 5}, {3, 1}, {3, 5}, {2, 5}, {4, 5}, {5, 1}, {5, 5}});
            aIceFiller.Start({{2, 1}, {4, 1}, {3, 7}}));

    for (int wave = 1; wave < 21; ++wave)
    {
        Connect(wave, -200, consoleLogger.Info("当前操作波次: {}", wave));

        // PP
        if (ARangeIn(wave, {1, 4, 7, 10, 13, 16, 19}))
        {
            Connect(wave, -40, aCobManager.Fire({{2, 9}, {4, 9}}));
            Connect(wave, 601 + 10 - 298, aIceFiller.Coffee());
            if (wave == 19)
            {
                Connect(wave, 601 + 1437 - 200 - 373, aCobManager.Fire({{2, 8.7}, {4, 8.7}}));
                Connect(wave, /*601 + 1437 - 150*/ 4500 - 200 - 373,
                        aCobManager.Fire({{2, 8.4}, {4, 8.4}}));
            }
        }

        // I-PP
        else if (ARangeIn(wave, {2, 5, 8, 11, 14, 17}))
        {
            if (wave == 2)
            {
                Connect(wave, 10 + 400, ACard(ASQUASH, 3, 9)); // 压冰车护存冰
                Connect(wave, 750, ACard(APUFF_SHROOM, 3, 8)); // 垫撑杆
                Connect(wave, 750 + 100, ARemovePlant(3, 8));
            }
            if (wave == 11)
            {
                Connect(wave, 10 + 400 - 100, ACard(ACHERRY_BOMB, 3, 8)); // 炸冰车小偷护存冰
            }
            Connect(wave, 1437 - 200 - 373, aCobManager.Fire({{2, 8.7}, {4, 8.7}}));
            Connect(wave, 1437 + 20 - 298, aIceFiller.Coffee());
        }

        // IPP-PP
        else if (ARangeIn(wave, {3, 6, 9, 12, 15, 18}))
        {
            Connect(wave, -150, aCobManager.Fire({{2, 8.5}, {4, 8.5}}));
            Connect(wave, 1437 - 200 - 373, aCobManager.Fire({{2, 8.7}, {4, 8.7}}));
            if (wave == 9)
            {
                Connect(wave, 1437 - 40, aCobManager.Fire({{2, 8.7}, {4, 8.7}}));
                Connect(wave, /*1437 + 601 + 1437 - 200 - 373*/ 4500 - 200 - 373,
                        aCobManager.Fire({{2, 8.4}, {4, 8.4}}));
            }
        }

        else if (wave == 20)
        {
            Connect(wave, -60, aCobManager.Fire({{1, 9}, {2, 9}, {4, 9}, {5, 9}}));
            Connect(wave, -60 + 108, aCobManager.Fire({{1, 8.8}, {4, 8.8}}));
            Connect(wave, 300,
                    aIceFiller.Coffee();                        // 冰杀小偷
                    aIceFiller.SetIceSeedList({AM_ICE_SHROOM}); // 最后一个存冰
                    consoleLogger.Info("第 {} 波手动收尾.", wave));
        }
    }
}
