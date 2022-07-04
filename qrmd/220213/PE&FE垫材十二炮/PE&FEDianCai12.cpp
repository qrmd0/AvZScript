/*
 * @Author: qrmd
 * @Date: 2022-04-20 20:34:07
 * @LastEditors: qrmd
 * @LastEditTime: 2022-07-04 19:01:46
 * @Description:PE&FE垫材十二炮 挂机冲关脚本
 * 使用方法：1、前往https:// gitee.com/std::vector-wlc/AsmVsZombies，根据教程下载并安装好AsmVsZombies
 *          2、前往游戏存档文件夹C:/ProgramData/PopCap Games/PlantsVsZombies/userdata，备份原游戏存档，然后用脚本配套的存档文件替换同名文件
 *          3、在Visul Studio Code中打开本脚本，右键点击编辑区空白处，在弹出菜单中选择“AvZ:Run Script”
 *          4、脚本支持游戏倍速和跳帧功能，分别删除第83行和第81行的注释符“//”并保存，可使相应功能在下一次运行脚本时生效
 * 来自AvZScript公开脚本仓库：
 * 主库：https:// github.com/qrmd0/AvZScript
 * 镜像库：https:// gitee.com/qrmd/AvZScript
 * Copyright (c) 2022 by qrmd, All Rights Reserved.
 */

#include "avz.h"
using namespace AvZ;

// 在[wave]波刷新[time_plant]厘秒后在[pos]位置放置植物并在[time_shovel_offset]后铲除，优先选择阳光消耗低的植物
void PlantFodder(Position pos, int time_plant, int time_shovel_offset, int wave);

// 在[wave]波刷新[time_plant]厘秒后在[col]列存在红眼巨人僵尸的行放置植物，[time_shovel_offset]厘秒后将其铲除以拖延该列红眼巨人僵尸前进
void BlockGargantuarZombie(int time, int time_shovel_offset, int wave, float col);

// 在[wave]波刷新[time_plant]厘秒后在[col]列及其右侧存在红眼巨人僵尸的行放置植物以拖延该列红眼巨人僵尸前进
void DelayBlockGargantuarZombie(int time, int wave, float col);

// 返回当前7列以右是否存在僵尸
bool GetIsTheFrountOfGroundExistZombie();

void Script()
{
    // 舞王僵尸入场滑步时未被植物阻挡而召唤伴舞僵尸的最晚时间
    const int LATEST_TIME_WW_8_SUMMON_BW_9_NATURALLY = 342;
    // 最慢的巨人僵尸对9列坐标偏移最小的小喷菇的举锤时间
    const int TIME_GIGA_GARGANTUAR_SMASH_XPG_8_AT_9_COL = 777;
    // 巨人僵尸从举锤到命中植物的间隔时间
    const int TIME_GIGA_GARGANTUAR_SMASH_ACTIVATED = 134;
    // 僵尸刷新的最短间隔时间
    const int MINIMUM_TIME_ZOMBIE_REFRESH = 601;
    // 僵尸预刷新倒计时
    const int TIME_ZOMBIE_PREREFRESH = 200;
    // P3节奏最短波长
    const int MINIMUM_TIME_P3 = 1169;
    // 第20波身上附着珊瑚的僵尸浮出水面的时间
    const int TIME_ZOMBIE_WITH_CORAL_EMERGE = 233;
    // 撑杆僵尸跳跃时长
    const int TIME_CG_3_JUMP = 180;
    // 玉米加农炮从发射到生效的最长时间
    const int MAXIMUM_TIME_YMJNP_47_ACTIVATED = 376;
    // 玉米加农炮的引信延迟的最长时间
    const int MAXIMUM_TIME_YMJNP_47_DELAY_ACTIVATED = 3;
    // 樱桃炸弹从被放置到生效的时间
    const int TIME_CHERRY_BOMB_ACTIVATED = 100;
    // 用于拖延巨人僵尸前进的植物的冷却时间
    const int TIME_PLANT_COOL_DOWN = 751;
    // P6常规落点
    const std::vector<Position> P6_ROUNTINE_COB_POSITION = {{2, 8.8}, {5, 8.8}};
    // 炮消珊瑚落点
    const std::vector<Position> COB_KILL_ZOMBIE_WITH_CORAL_POSITION = {{4, 7.5875}};
    // 收尾波红字警告出现的最早时间
    const int RED_WARNING_MINIMUM_TIME = 700;
    // 跳帧运行，阵型受损时停止
    auto condition
        = [=]() {
              std::vector<Grid> plant_list = {{1, 5}, {6, 5}, {2, 5}, {5, 5}, {3, 1}, {4, 1}, {3, 3}, {4, 3}, {3, 5}, {4, 5}, {3, 7}, {4, 7}};
              auto plants = GetMainObject()->plantArray();
              for (each : plant_list) {
                  if (plants[GetPlantIndex(each.row, each.col)].hp() < 300) {
                      return false;
                  }
              }
              return true;
          };
    auto callback = [=]() {
        SetGameSpeed(0.5);
        ShowErrorNotInQueue("发生阵损");
        LeftClick(740, 13);
    };
    // SkipTick(condition, callback);
    // 游戏倍速
    // SetGameSpeed(10);
    // 调试窗口
    // SetErrorMode(CONSOLE);
    // 脚本循环生效
    OpenMultipleEffective('Q', AvZ::MAIN_UI_OR_FIGHT_UI);
    // 选择植物：{樱桃炸弹、倭瓜、大喷菇、大蒜、向日葵、阳光菇、胆小菇、花盆、小喷菇、模仿小喷菇}
    SelectCards({CHERRY_BOMB, SQUASH, FUME_SHROOM, GARLIC, SUNFLOWER, SUN_SHROOM, SCAREDY_SHROOM, FLOWER_POT, PUFF_SHROOM, M_PUFF_SHROOM});
    SetTime(-599, 1);
    pao_operator.resetPaoList({{1, 5}, {6, 5}, {2, 5}, {5, 5}, {3, 1}, {4, 1}, {3, 3}, {4, 3}, {3, 5}, {4, 5}, {3, 7}, {4, 7}});
    for (int wave = 1; wave <= 20; ++wave) {
        // 第20波需要炮消珊瑚，因此用樱桃炸弹代一炮
        if (wave == 20) {
            SetTime(LATEST_TIME_WW_8_SUMMON_BW_9_NATURALLY - 1 - MAXIMUM_TIME_YMJNP_47_ACTIVATED, wave);
            pao_operator.pao(2, 8.85);
            SetTime(LATEST_TIME_WW_8_SUMMON_BW_9_NATURALLY - 1 - TIME_CHERRY_BOMB_ACTIVATED, wave);
            Card(CHERRY_BOMB, 5, 9);
        } else {
            SetTime(LATEST_TIME_WW_8_SUMMON_BW_9_NATURALLY - 1 - MAXIMUM_TIME_YMJNP_47_ACTIVATED, wave);
            pao_operator.pao(P6_ROUNTINE_COB_POSITION);
        }
        // 放置植物拖延红眼巨人僵尸前进
        BlockGargantuarZombie(TIME_GIGA_GARGANTUAR_SMASH_XPG_8_AT_9_COL, 1, wave, 9);
        // 收尾波的收尾操作
        if (wave == 9 || wave == 19 || wave == 20) {
            // 本波的常规操作生效后，如果前场存在僵尸，发炮一次
            InsertTimeOperation(LATEST_TIME_WW_8_SUMMON_BW_9_NATURALLY - 1 + 1, wave, [=]() {
                if (GetIsTheFrountOfGroundExistZombie()) {
                    SetTime(LATEST_TIME_WW_8_SUMMON_BW_9_NATURALLY - 1 + MINIMUM_TIME_ZOMBIE_REFRESH - MAXIMUM_TIME_YMJNP_47_ACTIVATED, wave);
                    pao_operator.recoverPao(P6_ROUNTINE_COB_POSITION);
                }
            });

            InsertTimeOperation(0, wave, [=]() {
                auto zombies = GetMainObject()->zombieArray();
                // 本波是否刷出了红眼巨人僵尸
                bool is_refreshed_GIGA_GARGANTUAR_in_the_wave = false;
                for (int index = 0; index < GetMainObject()->zombieTotal(); ++index) {
                    if (zombies[index].type() == GIGA_GARGANTUAR && !zombies[index].isDead() && !zombies[index].isDisappeared() && zombies[index].existTime() == NowTime(wave)) {
                        is_refreshed_GIGA_GARGANTUAR_in_the_wave = true;
                        break;
                    }
                }
                // 如果本波刷出了红眼巨人僵尸，再发炮两次
                if (is_refreshed_GIGA_GARGANTUAR_in_the_wave) {
                    SetTime(LATEST_TIME_WW_8_SUMMON_BW_9_NATURALLY - 1 + MINIMUM_TIME_ZOMBIE_REFRESH * 2 - MAXIMUM_TIME_YMJNP_47_ACTIVATED, wave);
                    pao_operator.recoverPao(P6_ROUNTINE_COB_POSITION);
                    SetTime(LATEST_TIME_WW_8_SUMMON_BW_9_NATURALLY - 1 + MINIMUM_TIME_ZOMBIE_REFRESH * 3 - MAXIMUM_TIME_YMJNP_47_ACTIVATED, wave);
                    pao_operator.recoverPao(P6_ROUNTINE_COB_POSITION);
                } else {
                    // 如果前场存在僵尸且红色字体的大波僵尸警示未较早显示，再发炮一次
                    InsertTimeOperation(RED_WARNING_MINIMUM_TIME, wave, [=]() {
                        if (GetIsTheFrountOfGroundExistZombie()) {
                            if (GetRunningWave() == wave) {
                                SetTime(LATEST_TIME_WW_8_SUMMON_BW_9_NATURALLY - 1 + MINIMUM_TIME_ZOMBIE_REFRESH * 2 - MAXIMUM_TIME_YMJNP_47_ACTIVATED, wave);
                                pao_operator.recoverPao(P6_ROUNTINE_COB_POSITION);
                            } else {
                                DelayBlockGargantuarZombie(TIME_GIGA_GARGANTUAR_SMASH_XPG_8_AT_9_COL - MINIMUM_TIME_ZOMBIE_REFRESH + TIME_PLANT_COOL_DOWN, wave, 7);
                            }
                        }
                    });
                }
            });
        } else { // 非收尾波的常规操作未激活僵尸刷新的处理
            InsertTimeOperation(MINIMUM_TIME_P3 - TIME_ZOMBIE_PREREFRESH - MAXIMUM_TIME_YMJNP_47_ACTIVATED + MAXIMUM_TIME_YMJNP_47_DELAY_ACTIVATED, wave, [=]() {
                if (GetRunningWave() == wave) {
                    SetTime(MINIMUM_TIME_P3 - TIME_ZOMBIE_PREREFRESH - MAXIMUM_TIME_YMJNP_47_ACTIVATED + MAXIMUM_TIME_YMJNP_47_DELAY_ACTIVATED, wave);
                    pao_operator.pao(P6_ROUNTINE_COB_POSITION);
                }
            });
        }
    }
    // 炮消珊瑚
    SetTime(TIME_ZOMBIE_WITH_CORAL_EMERGE - MAXIMUM_TIME_YMJNP_47_ACTIVATED, 20);
    pao_operator.pao(COB_KILL_ZOMBIE_WITH_CORAL_POSITION);
}

void PlantFodder(Position pos, int time_plant, int time_shovel_offset, int wave)
{
    InsertTimeOperation(time_plant, wave, [=]() {
        auto seeds = GetMainObject()->seedArray();
        // 垫材选择顺序：{小喷菇、模仿小喷菇、花盆、胆小菇、阳光菇、向日葵、大蒜、大喷菇}
        int seed_indices[] = {GetSeedIndex(XPG_8), GetSeedIndex(XPG_8, true), GetSeedIndex(HP_33), GetSeedIndex(DXG_13), GetSeedIndex(YGG_9), GetSeedIndex(XRK_1), GetSeedIndex(DS_36), GetSeedIndex(DPG_10)};
        for (int index : seed_indices) {
            if (seeds[index].isUsable()) {
                SetTime(time_plant, wave);
                Card(index + 1, pos.row, pos.col);
                SetTime(time_plant + time_shovel_offset, wave);
                Shovel(pos.row, pos.col);
                break;
            }
        }
    });
}
void BlockGargantuarZombie(int time, int time_shovel_offset, int wave, float col)
{
    InsertTimeOperation(time, wave, [=]() {
        auto zombies = GetMainObject()->zombieArray();
        std::vector<Position> pos_list = {{1, col}, {2, col}, {5, col}, {6, col}};
        for (auto pos : pos_list) {
            for (int index = 0; index < GetMainObject()->zombieTotal(); ++index) {
                if (zombies[index].type() == GIGA_GARGANTUAR && zombies[index].row() == pos.row - 1 && (zombies[index].abscissa() >= col * 80.0 - 69.0 && zombies[index].abscissa() < col * 80.0 + 41.0) && !zombies[index].isDead() && !zombies[index].isDisappeared()) {
                    PlantFodder({pos.row, pos.col}, time, time_shovel_offset, wave);
                    break;
                }
            }
        }
    });
}
void DelayBlockGargantuarZombie(int time, int wave, float col)
{
    InsertTimeOperation(time, wave, [=]() {
        auto zombies = GetMainObject()->zombieArray();
        std::vector<Position> pos_list = {{1, col}, {2, col}, {5, col}, {6, col}};
        for (auto pos : pos_list) {
            for (int index = 0; index < GetMainObject()->zombieTotal(); ++index) {
                if (zombies[index].type() == GIGA_GARGANTUAR && zombies[index].row() == pos.row - 1 && zombies[index].abscissa() >= col * 80.0 - 69.0 && !zombies[index].isDead() && !zombies[index].isDisappeared()) {
                    PlantFodder({pos.row, pos.col}, time, 1000, wave);
                    break;
                }
            }
        }
    });
}
bool GetIsTheFrountOfGroundExistZombie()
{
    bool is_the_frount_of_ground_exist_zombie = false;
    auto zombies = GetMainObject()->zombieArray();
    for (int index = 0; index < GetMainObject()->zombieTotal(); ++index) {
        if (!zombies[index].isDead() && !zombies[index].isDisappeared() && zombies[index].abscissa() > 7 * 80.0) {
            is_the_frount_of_ground_exist_zombie = true;
            break;
        }
    }
    return is_the_frount_of_ground_exist_zombie;
}