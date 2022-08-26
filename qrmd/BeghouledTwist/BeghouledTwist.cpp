/*
 * @Author: qrmd
 * @Date: 2022-08-25 14:27:28
 * @LastEditors: qrmd
 * @LastEditTime: 2022-08-26 20:50:35
 * @Description: BeghouledTwist（宝石迷阵转转看） 挂机脚本
 * 使用方法：1、前往https://gitee.com/vector-wlc/AsmVsZombies，根据教程下载并安装好AsmVsZombies；
 *          2、启动游戏进入主界面。在Visul Studio Code中打开本脚本，右键点击编辑区空白处，在弹出菜单中选择“AvZ:Run Script”；
 *          3、点击 MINI-GAMES，进入 BeghouledTwist 模式；
 *          4、按 D 键加快游戏运行速度，按 A 键减慢游戏运行速度，按 S 键恢复原速度。
 * 来自AvZScript公开脚本仓库：
 * 主库：https://github.com/qrmd0/AvZScript
 * 镜像库：https://gitee.com/qrmd/AvZScript
 * Copyright (c) 2022 by qrmd, All Rights Reserved.
 */
#include "avz.h"
using namespace AvZ;

// *** Not In Queue
// 返回场上的植物种类到[plant_types]
void GetPlantTypes(std::vector<std::vector<int>>& plant_types);

// *** Not In Queue
// 返回[plant_types]中是否存在三个相连的同种植物
bool CheckIsMatch(std::vector<std::vector<int>>& plant_types);

// *** Not In Queue
// 返回点击可以触发消除的格子
Grid WhereCanTwist(std::vector<std::vector<int>>& plant_types);

void ClickGrid(Grid grid);

// *** Not In Queue
// 点击植物触发消除
void ClickPlant();
TickRunner plant_clicker;

// *** Not In Queue
// 使用卡片
void UseCard();
TickRunner card_user;

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
    // ShowErrorNotInQueue("欢迎使用 宝石迷阵转转看 挂机脚本\n\n按 D 键加快游戏运行速度，按 A 键减慢游戏运行速度，按 S 键恢复原速度\n\n更多键控脚本尽在AvZScript");
    speed_controller.start();
    plant_clicker.pushFunc(ClickPlant);
    card_user.pushFunc(UseCard);
    item_collector.setInterval(1);
}

void GetPlantTypes(std::vector<std::vector<int>>& plant_types)
{
    auto plants = GetMainObject()->plantArray();
    int index;
    std::vector<int> the_row;
    for (int row = 0; row <= 5 + 1; ++row) {
        the_row.clear();
        for (int col = 0; col <= 8 + 1; ++col) {
            index = GetPlantIndex(row, col);
            if (index >= 0)
                the_row.push_back(plants[index].type());
            else
                the_row.push_back(-1);
        }
        plant_types.push_back(the_row);
    }
}
bool CheckIsMatch(std::vector<std::vector<int>>& plant_types)
{
    for (int row = 1; row <= 5; ++row) {
        for (int col = 1; col <= 8; ++col) {
            if ((plant_types[row - 1][col] == plant_types[row][col] && plant_types[row + 1][col] == plant_types[row][col]) || (plant_types[row][col - 1] == plant_types[row][col] && plant_types[row][col + 1] == plant_types[row][col]))
                return true;
        }
    }
    return false;
}
Grid WhereCanTwist(std::vector<std::vector<int>>& plant_types)
{
    Grid result;
    std::vector<std::vector<int>> matrix_copy;
    int up_left, up_right, down_right, down_left;
    for (int row = 4; row >= 1; --row) {
        for (int col = 7; col >= 1; --col) {
            matrix_copy = plant_types;
            up_left = matrix_copy[row][col];
            up_right = matrix_copy[row][col + 1];
            down_right = matrix_copy[row + 1][col + 1];
            down_left = matrix_copy[row + 1][col];
            matrix_copy[row][col] = down_left;
            matrix_copy[row][col + 1] = up_left;
            matrix_copy[row + 1][col + 1] = up_right;
            matrix_copy[row + 1][col] = down_right;
            if (CheckIsMatch(matrix_copy)) {
                result = {row, col};
                return result;
            }
        }
    }
    result = {-1, -1};
    return result;
}
void ClickGrid(Grid grid)
{
    ClickGrid(grid.row, grid.col);
}
void ClickPlant()
{
    std::vector<std::vector<int>> plant_types;
    GetPlantTypes(plant_types);
    ClickGrid(WhereCanTwist(plant_types));
}
void UseCard()
{
    auto seeds = GetMainObject()->seedArray();
    int sun = GetMainObject()->sun();
    // if (sun >= 200 && seeds->count() == 5 && seeds[4].isUsable()) {
    //     LeftClick(seeds[4].ordinate() + 25, seeds[4].abscissa() + 35);
    //     CardNotInQueue(5, 1, 9);
    // }
    if (sun >= 250 && seeds[2].isUsable()) {
        // LeftClick(50 * (3 - 1) + 110, 43);
        CardNotInQueue(3, 1, 9);
    }
    if (sun >= 500 && seeds[1].isUsable()) {
        // LeftClick(50 * (2 - 1) + 110, 43);
        CardNotInQueue(2, 1, 9);
    }
    if (sun >= 1000 && seeds[0].isUsable()) {
        // LeftClick(50 * (1 - 1) + 110, 43);
        CardNotInQueue(1, 1, 9);
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
