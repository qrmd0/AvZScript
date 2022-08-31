/*
 * @Author: qrmd
 * @Date: 2022-08-31 15:34:24
 * @LastEditors: qrmd
 * @LastEditTime: 2022-08-31 17:25:29
 * @Description:植物僵尸2（ZomBotany2）挂机脚本
 * 使用方法：1、前往https://gitee.com/vector-wlc/AsmVsZombies，根据教程下载并安装好AsmVsZombies
 *          2、前往游戏存档文件夹C:/ProgramData/PopCap Games/PlantsVsZombies/userdata，备份原游戏存档，然后用脚本配套的存档文件替换同名文件
 *          3、在Visul Studio Code中打开本脚本，右键点击编辑区空白处，在弹出菜单中选择“AvZ:Run Script”
 * 来自AvZScript公开脚本仓库：
 * 主库：https://github.com/qrmd0/AvZScript
 * 镜像库：https://gitee.com/qrmd/AvZScript
 * Copyright (c) 2022 by qrmd, All Rights Reserved.
 */
#include "PlantFixerPlus.h"
#include "avz.h"
#include "tick_planter.h"
using namespace AvZ;

// *** Not In Queue
// 在位置列表[grids]存在僵尸时放置[types]中的植物以拖延其前进。结合TickRunner使用。
void AutoBlock(std::vector<PlantType> types, std::vector<Grid> grids);
TickRunner auto_blocker;

// *** Not In Queue
// 只要允许，就在位置列表[pos_list]种植[types]植物。结合TickRunner使用。
void PrePlant(std::vector<int> types, std::vector<Grid> grid_list);

TickRunner pre_planter;

PlantFixerPlus lily_pad_fixer;
PlantFixerPlus garlic_fixer;

class SpeedController {
private:
    std::vector<float> _game_speeds = {0.1, 0.2, 0.5, 1.0, 2.0, 5.0, 10.0};
    float _default_speed = 1.0;
    KeyConnector _key_connector;
    char _decelerate_key = 'A';
    char _accelerate_key = 'D';
    char _reset_speed_key = 'S';

public:
    // *** Not In Queue
    // 启用按键速度控制，默认速度倍率[speed]
    // [speed]可选取的值有：{0.1, 0.2, 0.5, 1.0, 2.0, 5.0, 10.0}
    void start(float speed = 1.0);
    // *** Not In Queue
    // 设置减速快捷键
    void setDecelerateKey(char key);
    // *** Not In Queue
    // 设置加速快捷键
    void setAccelerateKey(char key);
    // *** Not In Queue
    // 设置恢复默认速度快捷键
    void setResetSpeedKey(char key);
} speed_controller;

void Script()
{
    speed_controller.start();
    SelectCards({LILY_PAD, CATTAIL, GARLIC, PUFF_SHROOM, M_PUFF_SHROOM, FLOWER_POT, SCAREDY_SHROOM, SUN_SHROOM, SPIKEROCK, COB_CANNON});
    SetTime(-1799, 1);
    tick_planter.start();
    auto_blocker.pushFunc([]() {
        AutoBlock({PUFF_SHROOM, M_PUFF_SHROOM, FLOWER_POT, SCAREDY_SHROOM, SUN_SHROOM}, {{1, 1}, {2, 1}, {5, 1}, {6, 1}, {1, 2}, {2, 2}, {5, 2}, {6, 2}});
        AutoBlock({LILY_PAD}, {{4, 1}, {4, 2}, {4, 3}});
    });
    pre_planter.pushFunc([]() {
        PrePlant({PUFF_SHROOM, M_PUFF_SHROOM}, {{1, 1}, {2, 1}, {5, 1}, {6, 1}, {1, 2}, {2, 2}, {5, 2}, {6, 2}, {1, 3}, {2, 3}, {5, 3}, {6, 3}, {1, 4}, {2, 4}, {5, 4}, {6, 4}, {1, 5}, {2, 5}, {5, 5}, {6, 5}, {1, 6}, {2, 6}, {5, 6}, {6, 6}, {1, 7}, {2, 7}, {5, 7}, {6, 7}, {1, 8}, {2, 8}, {5, 8}, {6, 8}});
    });
    InsertOperation([=]() {
        SetNowTime();
        tick_planter.clear();
        tick_planter.waitPlantNotInQuene(LILY_PAD, {{3, 4}});
        tick_planter.waitPlantNotInQuene(CATTAIL, {{3, 4}});
        tick_planter.waitPlantNotInQuene(LILY_PAD, {{3, 9}});
        tick_planter.waitPlantNotInQuene(GARLIC, {{3, 9}});
        tick_planter.waitPlantNotInQuene(LILY_PAD, {{3, 8}});
        tick_planter.waitPlantNotInQuene(GARLIC, {{3, 8}});
        tick_planter.waitPlantNotInQuene(LILY_PAD, {{3, 3}});
        tick_planter.waitPlantNotInQuene(CATTAIL, {{3, 3}});
        tick_planter.waitPlantNotInQuene(LILY_PAD, {{3, 2}});
        tick_planter.waitPlantNotInQuene(CATTAIL, {{3, 2}});
        tick_planter.waitPlantNotInQuene(LILY_PAD, {{3, 1}});
        tick_planter.waitPlantNotInQuene(CATTAIL, {{3, 1}});
        tick_planter.waitPlantNotInQuene(LILY_PAD, {{3, 5}});
        tick_planter.waitPlantNotInQuene(CATTAIL, {{3, 5}});
        tick_planter.waitPlantNotInQuene(LILY_PAD, {{3, 6}});
        tick_planter.waitPlantNotInQuene(CATTAIL, {{3, 6}});
        tick_planter.waitPlantNotInQuene(LILY_PAD, {{3, 7}});
        tick_planter.waitPlantNotInQuene(CATTAIL, {{3, 7}});
    });
    SetTime(0, 7);
    lily_pad_fixer.start(LILY_PAD, {{3, 9}, {3, 8}}, 0);
    garlic_fixer.start(GARLIC, {{3, 9}, {3, 8}}, 0.3);
}

void AutoBlock(std::vector<PlantType> types, std::vector<Grid> grids)
{
    auto zombies = GetMainObject()->zombieArray();
    auto seeds = GetMainObject()->seedArray();
    std::vector<int> indices_seed;
    for (int each : types)
        indices_seed.emplace_back(each > IMITATOR ? GetSeedIndex(each - (IMITATOR + 1), true) : GetSeedIndex(each, false));
    for (Grid each : grids) {
        for (int index = 0; index < GetMainObject()->zombieTotal(); ++index) {
            if (!zombies[index].isDead() && !zombies[index].isDisappeared() && zombies[index].row() + 1 == each.row) {
                if ((zombies[index].abscissa() > each.col * 80 - 10 - 40 && zombies[index].abscissa() < each.col * 80 - 10 + 1) && zombies[index].state() == 0) {
                    for (int index_seed : indices_seed) {
                        if (index_seed >= 0) {
                            if (seeds[index_seed].isUsable() && (GetPlantIndex(each.row, each.col) < 0 && GetPlantIndex(each.row, each.col, FLOWER_POT) < 0) && Asm::getPlantRejectType(FLOWER_POT, each.row - 1, each.col - 1) == Asm::NIL) {
                                CardNotInQueue(index_seed + 1, each.row, each.col);
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
}
void PrePlant(std::vector<int> types, std::vector<Grid> grids)
{
    if (GetMainObject()->gameClock() % 1 != 0)
        return;
    auto seeds = GetMainObject()->seedArray();
    auto zombies = GetMainObject()->zombieArray();
    std::vector<int> indices_seed;
    int i;
    for (int each : types)
        indices_seed.emplace_back(each > IMITATOR ? GetSeedIndex(each - (IMITATOR + 1), true) : GetSeedIndex(each, false));
    for (auto each : grids) {
        for (int index = 0; index < GetMainObject()->zombieTotal(); ++index) {
            if (!zombies[index].isDead() && !zombies[index].isDisappeared() && zombies[index].row() + 1 == each.row) {
                if (zombies[index].abscissa() > each.col * 80 - 10 - 40 && zombies[index].abscissa() < each.col * 80 - 10 + 1)
                    return;
            }
        }
        i = 0;
        for (int each_seed : indices_seed) {
            if (GetPlantIndex(each.row, each.col) < 0 && GetPlantIndex(each.row, each.col, FLOWER_POT) < 0 && Asm::getPlantRejectType(types[i], each.row - 1, each.col - 1) == Asm::NIL && seeds[each_seed].isUsable()) {
                CardNotInQueue(each_seed + 1, each.row, each.col);
                return;
            }
            i += 1;
        }
    }
}

void SpeedController::start(float speed)
{
    SetGameSpeed(speed);
    _default_speed = 10.0 / GetPvzBase()->tickMs();
    _key_connector.add(_decelerate_key, [=]() {
        int game_speed_gear = 7;
        float game_speed = 10.0 / GetPvzBase()->tickMs();
        for (int i = 0; i < _game_speeds.size(); ++i) {
            if (game_speed <= _game_speeds[i]) {
                game_speed_gear = i;
                break;
            }
        }
        if (game_speed_gear > 0)
            SetGameSpeed(_game_speeds[game_speed_gear - 1]);
    });
    _key_connector.add(_accelerate_key, [=]() {
        int game_speed_gear = 0;
        float game_speed = 10.0 / GetPvzBase()->tickMs();
        for (int i = _game_speeds.size() - 1; i >= 0; --i) {
            if (game_speed >= _game_speeds[i]) {
                game_speed_gear = i;
                break;
            }
        }
        if (game_speed_gear < _game_speeds.size() - 1)
            SetGameSpeed(_game_speeds[game_speed_gear + 1]);
    });
    _key_connector.add(_reset_speed_key, [=]() {
        SetGameSpeed(_default_speed);
    });
}
void SpeedController::setDecelerateKey(char key)
{
    _decelerate_key = key;
}
void SpeedController::setAccelerateKey(char key)
{
    _accelerate_key = key;
}
void SpeedController::setResetSpeedKey(char key)
{
    _reset_speed_key = key;
}
