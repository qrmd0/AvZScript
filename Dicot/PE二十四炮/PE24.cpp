/*
 * 阵名: PE二十四炮
 * 出处: https://tieba.baidu.com/p/991306518
 * 节奏: P6: PPDD|PPI|PPSSDD|PPDD|PPI|PPSSDD
 */

#include <avz.h>
#define Connect(wave, time, ...) AConnect(ATime(wave, time), [] { __VA_ARGS__; }) // 使用宏定义简化代码

void AScript()
{
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
        AM_ICE_SHROOM,   // 模仿寒冰菇
        AICE_SHROOM,     // 寒冰菇
        ACOFFEE_BEAN,    // 咖啡豆
        APUMPKIN,        // 南瓜头
        AWALL_NUT,       // 坚果
        ASQUASH,         // 倭瓜
        AFLOWER_POT,     // 花盆
        ASCAREDY_SHROOM, // 胆小菇
        ASUN_SHROOM,     // 阳光菇
        APUFF_SHROOM,    // 小喷菇
    });

    Connect(1, -599,
            aCobManager.AutoSetList();
            aIceFiller.Start({{4, 9}}));

    // 精准之舞 PPDD
    for (auto wave : {1, 4, 7, 11, 14, 17})
    {
        Connect(wave, -14, aCobManager.Fire({{2, 9}, {5, 9}}));
        Connect(wave, -14 + 107, aCobManager.Fire({{1, 7.7}, {5, 7.7}}));
    }

    // 冰之旋舞 PPI
    for (auto wave : {2, 5, 8, 12, 15, 18})
    {
        Connect(wave, -95, aCobManager.Fire({{2, 9}, {5, 9}}));
        Connect(wave, -95 + 373 - 100 - 198, aIceFiller.Coffee()); // 冰同步于炮生效
    }

    // 六神乱舞 PPSSDD
    for (auto wave : {3, 6, 9, 13, 16, 19})
    {
        Connect(wave, -95, aCobManager.Fire({{2, 9}, {5, 9}, {2, 9}, {5, 9}}));
        Connect(wave, -95 + 108, aCobManager.Fire({{1, 8.8}, {5, 8.8}}));
        if (wave == 9 || wave == 19) // 收尾
        {
            Connect(wave, 601 - 15, aCobManager.Fire({{2, 9}, {5, 9}}));
        }
    }

    // 大波推迟 PPSSDD
    for (auto wave : {10})
    {
        Connect(wave, -56, aCobManager.Fire({{2, 9}, {5, 9}, {2, 9}, {5, 9}}));
        Connect(wave, -56 + 108, aCobManager.Fire({{1, 8.8}, {5, 8.8}}));
    }

    for (auto wave : {20})
    {
        Connect(wave, -150, aCobManager.Fire({{4, 6}, {4, 8}}));                      // 炮炸珊瑚
        Connect(wave, -150 + 90, aCobManager.Fire({{1, 9}, {2, 9}, {5, 9}, {6, 9}})); // -60
        Connect(wave, -150 + 90 + 108, aCobManager.Fire({{1, 9}, {2, 9}, {5, 9}, {6, 9}}));
        // 第 20 波手动收尾
    }
}