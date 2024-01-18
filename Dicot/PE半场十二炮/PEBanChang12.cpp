/*
 * 阵名: PE半场十二炮
 * 出处: https://tieba.baidu.com/p/1801759994
 * 节奏: ch4: I+BC/d-PDD/P|I+BC/d-PDD/P, (18|18)
 */

#include <avz.h>
#define Connect(time, ...) AConnect(ATime(wave, time), [=] { __VA_ARGS__; }) // 使用宏定义简化代码

// 种垫铲垫
ACoroutine DianCai()
{
    ACard({{APUFF_SHROOM, 1, 9}, {ASUN_SHROOM, 2, 9}});
    co_await ANowDelayTime(100);
    ARemovePlant(1, 9);
    ARemovePlant(2, 9);
}

// 烧小偷
ACoroutine 口吐金蛇()
{
    co_await ATime(10, 400); // 等第 10 波刷新
    ACard({ALILY_PAD, AJALAPENO}, 4, 9);
    co_await ANowDelayTime(100 + 1);
    ARemovePlant(4, 9);

    co_await ATime(20, 400); // 等第 20 波刷新
    ACard({ALILY_PAD, AJALAPENO}, 4, 9);
    co_await ANowDelayTime(100 + 1);
    ARemovePlant(4, 9);
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
                     AM_ICE_SHROOM, // 模仿寒冰菇
                     AICE_SHROOM,   // 寒冰菇
                     ACOFFEE_BEAN,  // 咖啡豆
                     ALILY_PAD,     // 荷叶
                     APUMPKIN,      // 南瓜头
                     ACHERRY_BOMB,  // 樱桃炸弹
                     AJALAPENO,     // 火爆辣椒
                     ASQUASH,       // 倭瓜
                     ASUN_SHROOM,   // 阳光菇
                     APUFF_SHROOM,  // 小喷菇
                 },
                 1);

    AConnect(ATime(1, -599), []
             {
            aCobManager.SetList({
                {1, 3},
                {2, 3},
                {3, 3},
                {1, 5},
                {2, 5},
                {3, 5},
                {1, 7},
                {2, 7},
                {3, 7},
                {1, 1},
                {2, 1},
                {3, 1},
            });
            ACard(AICE_SHROOM, 5, 5);           // 临时存冰
            ACard({ALILY_PAD, APUMPKIN}, 3, 9); // 临时存冰位, 其实不需要南瓜头
            aIceFiller.Start({{4, 5}, {4, 6}, {4, 7}, {4, 8}, {3, 9}});
            aPlantFixer.Start(APUMPKIN, {{4, 5}, {4, 6}, {4, 7}, {4, 8}}, 4000 * 0.3); // TODO
            ACoLaunch(口吐金蛇); });

    for (int wave = 1; wave < 21; ++wave)
    {
        if (wave == 1 || wave == 10)
        {
            Connect(-95, aCobManager.Fire(1, 9));
            Connect(-15, aCobManager.Fire({{2, 9}, {5, 9}}));
            Connect(-15 + 110, aCobManager.Fire(5, 7.7));
            Connect(-15 + 110 + 373 - 100, ACard(ACHERRY_BOMB, 1, 9)); // 368
        }

        else if (wave == 20)
        {
            Connect(-150, aCobManager.Fire(4, 7));
            Connect(-60, aCobManager.Fire({{2, 9}, {5, 9}, {2, 9}, {5, 9}})); // 等到刷新前 60cs
            Connect(-60 + 110, aCobManager.Fire({{1, 8.8}, {2, 8.8}}); aPlantFixer.Stop());
            Connect(-60 + 110 + 373 - 100, ACard(ACHERRY_BOMB, 5, 9));
            Connect(517, aCobManager.Fire(2, 9));
            // 第 20 波手动收尾
        }

        else
        {
            Connect(-133, aCobManager.Fire(1, 8.0));       // 拦截上波红眼, 分离部分快速僵尸
            Connect(360 - 273, aCobManager.Fire(2, 8.15)); // 无冰分离
            Connect(
                360 - 298, if (wave != 2) { aIceFiller.Coffee(); } else { ACard(ACOFFEE_BEAN, 5, 5); }); // 360cs 反应冰
            Connect(
                360 + 500 - 373, if (wave != 2 && wave != 11) { aCobManager.Fire(5, 3); }); // 下半场尾炸
            Connect(1800 - 200 - 373, aCobManager.Fire({{2, 9}, {5, 8.1}}));                // 激活炸
            Connect(1800 - 200 - 373 + 10, ACoLaunch(DianCai));                             // 垫撑杆
            Connect(1800 - 200 - 373 + 220, aCobManager.Fire(1, 8.2));                      // 秒白眼, 触发红眼投掷

            if (wave == 9 || wave == 19) // 收尾波次
            {
                Connect(1800 - 133, aCobManager.Fire(1, 8.0));
                Connect(1800 + 360 - 373, aCobManager.Fire(2, 8.8));
                Connect(1800 + 360 + 500 - 373, aCobManager.Fire(5, 2.5));
                Connect(1800 + 1800 - 200 - 373, aCobManager.Fire(5, 6));
                Connect(1800 + 1800 - 200 - 373 + 110, aCobManager.Fire(5, 6));
                Connect(1800 + 1800 - 200 - 373 + 110 + 110, aCobManager.Fire(5, 3));
                Connect(
                    4500 - 200 - 373, aCobManager.Fire(5, 5);
                    if (wave == 9) {
                        aCobManager.Skip(2); // 中场调整炮序
                    } else {
                        ARemovePlant(3, 9); // 第 20 波刷新前铲掉
                        ARemovePlant(3, 9);
                    });
            }
        }
    }
}