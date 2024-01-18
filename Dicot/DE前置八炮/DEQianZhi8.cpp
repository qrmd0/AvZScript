/*
 * 阵名: DE前置八炮
 * 出处: https://tieba.baidu.com/p/3943536673
 * 节奏: ch5: PP|I-PP|IPP-PP, (601|1437|1437)
 */

#include <avz.h>
#define Connect(time, ...) AConnect(ATime(wave, time), [] { __VA_ARGS__; }) // 使用宏定义简化代码

void AScript()
{
    // ASetReloadMode(AReloadMode::MAIN_UI_OR_FIGHT_UI);

    ASetZombies({
        APJ_0,  // 普僵
        ACG_3,  // 撑杆
        AWW_8,  // 舞王
        AXC_15, // 小丑
        AQQ_16, // 气球
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
                     ACHERRY_BOMB,    // 樱桃炸弹
                     ASQUASH,         // 倭瓜
                     AWALL_NUT,       // 坚果
                     AFLOWER_POT,     // 花盆
                     ASCAREDY_SHROOM, // 胆小菇
                     ASUN_SHROOM,     // 阳光菇
                     APUFF_SHROOM,    // 小喷菇
                 },
                 1);

    AConnect(ATime(1, -599), []
             {
            aCobManager.SetList({{1, 1}, {1, 5}, {3, 1}, {3, 5}, {2, 5}, {4, 5}, {5, 1}, {5, 5}});
            aIceFiller.Start({{2, 1}, {4, 1}, {3, 7}}); });

    // PP
    for (auto wave : {1, 4, 7, 10, 13, 16, 19})
    {
        Connect(-40, aCobManager.Fire({{2, 9}, {4, 9}}));
        Connect(601 + 10 - 298, aIceFiller.Coffee());
        if (wave == 19)
        {
            Connect(601 + 1437 - 200 - 373, aCobManager.Fire({{2, 8.7}, {4, 8.7}}));
            Connect(4500 - 200 - 373, aCobManager.Fire({{2, 8.4}, {4, 8.4}}));
        }
    }

    // I-PP
    for (auto wave : {2, 5, 8, 11, 14, 17})
    {
        if (wave == 2)
        {
            Connect(10 + 400, ACard(ASQUASH, 3, 9)); // 压冰车护存冰
        }
        if (wave == 11)
        {
            Connect(10 + 400 - 100, ACard(ACHERRY_BOMB, 3, 8)); // 炸冰车小偷护存冰
        }
        if (wave == 2)
        {
            Connect(750, ACard(APUFF_SHROOM, 3, 8)); // 垫撑杆
            Connect(750 + 100, ARemovePlant(3, 8));
        }
        Connect(1437 - 200 - 373, aCobManager.Fire({{2, 8.7}, {4, 8.7}}));
        Connect(1437 + 20 - 298, aIceFiller.Coffee());
    }

    // IPP-PP
    for (auto wave : {3, 6, 9, 12, 15, 18})
    {
        Connect(-150, aCobManager.Fire({{2, 8.5}, {4, 8.5}}));
        Connect(1437 - 200 - 373, aCobManager.Fire({{2, 8.7}, {4, 8.7}}));
        if (wave == 9)
        {
            Connect(1437 - 40, aCobManager.Fire({{2, 8.7}, {4, 8.7}}));
            Connect(4500 - 200 - 373, aCobManager.Fire({{2, 8.4}, {4, 8.4}}));
        }
    }

    for (auto wave : {20})
    {
        Connect(-60, aCobManager.Fire({{1, 9}, {2, 9}, {4, 9}, {5, 9}}));
        Connect(-60 + 108, aCobManager.Fire({{1, 8.8}, {4, 8.8}}));
        Connect(300, aIceFiller.Coffee(); aIceFiller.SetIceSeedList({AM_ICE_SHROOM})); // 冰杀小偷; 最后一个存冰
        // 第 20 波手动收尾
    }
}