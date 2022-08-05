/*
 * @Author: qrmd
 * @Date: 2022-04-20 20:34:07
 * @LastEditors: qrmd
 * @LastEditTime: 2022-08-05 09:20:09
 * @Description:PE&FE垫材十二炮 挂机冲关脚本
 * 使用方法：1、前往https:// gitee.com/std::vector-wlc/AsmVsZombies，根据教程下载并安装好AsmVsZombies
 *          2、前往游戏存档文件夹C:/ProgramData/PopCap Games/PlantsVsZombies/userdata，备份原游戏存档，然后用脚本配套的存档文件替换同名文件
 *          3、在Visul Studio Code中打开本脚本，右键点击编辑区空白处，在弹出菜单中选择“AvZ:Run Script”
 *          4、脚本支持游戏倍速和跳帧功能，分别删除第45行和第43行的注释符“//”并保存，可使相应功能在下一次运行脚本时生效
 * 来自AvZScript公开脚本仓库：
 * 主库：https://github.com/qrmd0/AvZScript
 * 镜像库：https://gitee.com/qrmd/AvZScript
 * Copyright (c) 2022 by qrmd, All Rights Reserved.
 */

#include "avz.h"
using namespace AvZ;

// *** Not In Queue
// 返回场上处于就绪或装填状态的玉米加农炮数量
int GetNumberofCannonReady();

// *** Not In Queue
// 返回前场是否存在僵尸
bool GetIsExistZombieInTheFrountOfGround();

// *** Not In Queue
// 返回场上是否存在[wave]波的红眼巨人僵尸
bool GetIsExistGIGA(int wave);

// *** In Queue
// 在{pos}位置存在[wave]波刷出的红眼巨人僵尸时，在此位置放置临时植物并在{time}厘秒后铲除，优先选择阳光消耗低的植物
void BlockGigas(std::vector<Grid> pos, int wave, int time);

// *** In Queue
// 跳帧运行，阵型受损时停止
void SkipTickToDamaged();

void Script()
{
    // 跳帧运行，阵型受损时停止
    SkipTickToDamaged();
    // 游戏倍速
    SetGameSpeed(10);
    // 调试窗口
    // SetErrorMode(CONSOLE);
    // 脚本循环生效，按'Q'键停止
    OpenMultipleEffective('Q', AvZ::MAIN_UI_OR_FIGHT_UI);
    // 选择植物：{小喷菇、模仿小喷菇、花盆、胆小菇、阳光菇、向日葵、樱桃炸弹、三叶草、双子向日葵、忧郁菇}
    SelectCards({PUFF_SHROOM, M_PUFF_SHROOM, FLOWER_POT, SCAREDY_SHROOM, SUN_SHROOM, SUNFLOWER, CHERRY_BOMB, BLOVER, TWIN_SUNFLOWER, GLOOM_SHROOM});
    // 本轮是否会刷出红眼巨人僵尸
    bool is_exist_GIGA_GARGANTUAR = GetZombieTypeList()[GIGA_GARGANTUAR];

    SetTime(-599, 1);
    pao_operator.resetPaoList({{1, 5}, {6, 5}, {2, 5}, {5, 5}, {3, 1}, {4, 1}, {3, 3}, {4, 3}, {3, 5}, {4, 5}, {3, 7}, {4, 7}});
    for (int wave = 1; wave <= 20; ++wave) {
        // PP
        if (is_exist_GIGA_GARGANTUAR && wave == 20) {
            InsertTimeOperation(223 - 373, wave, [=]() {
                if (GetNumberofCannonReady() >= 3) {
                    SetTime(341 - 376, wave);
                    pao_operator.pao({{2, 8.8}, {5, 8.8}});
                } else { // 可用的炮不足时，执行PA
                    SetTime(341 - 376, wave);
                    pao_operator.pao(2, 8.8);
                    SetTime(341 - 100, wave);
                    Card(CHERRY_BOMB, 5, 9);
                }
            });
        } else {
            SetTime(341 - 376, wave);
            pao_operator.pao({{2, 8.8}, {5, 8.8}});
        }
        // cccc
        if (is_exist_GIGA_GARGANTUAR) {
            if (wave % 2 == 0) {
                SetTime(777, wave);
                BlockGigas({{1, 9}, {2, 9}}, wave, 1);
                SetTime(601 + 338 + 142, wave);
                BlockGigas({{5, 9}, {6, 9}}, wave, 134);
            } else {
                SetTime(777, wave);
                BlockGigas({{5, 9}, {6, 9}}, wave, 1);
                SetTime(601 + 338 + 142, wave);
                BlockGigas({{1, 9}, {2, 9}}, wave, 134);
            }
        }
        // 收尾
        if (wave == 9 || wave == 19 || wave == 20) {
            // PP生效后，如果前场仍存在僵尸，执行PP'
            InsertTimeOperation(341 + 1, wave, [=]() {
                if (GetIsExistZombieInTheFrountOfGround()) {
                    SetTime(601 + 341 - 376, wave);
                    pao_operator.pao({{2, 8.8}, {5, 8.8}});
                }
            });
            if (is_exist_GIGA_GARGANTUAR) {
                // PP'生效后，前场可能且仅可能存在红眼巨人僵尸
                InsertTimeOperation(601 + 341 + 1, wave, [=]() {
                    // 如果存在本波刷出的红眼巨人僵尸，执行PP''-PP'''
                    if (GetIsExistGIGA(wave)) {
                        SetTime(601 * 2 + 341 - 376, wave);
                        pao_operator.pao({{2, 8.8}, {5, 8.8}});
                        SetTime(601 * 3 + 341 - 376, wave);
                        pao_operator.pao({{2, 8.8}, {5, 8.8}});
                        // 否则如果存在上波刷出的红眼巨人僵尸
                    } else if (GetIsExistGIGA(wave - 1)) {
                        // 如果未刷新红字，执行PP''
                        if (GetRunningWave() == wave) {
                            SetTime(601 * 2 + 341 - 376, wave);
                            pao_operator.pao({{2, 8.8}, {5, 8.8}});
                        } else { // 否则执行cccc
                            SetTime(1611, wave - 1);
                            BlockGigas({{1, 8}, {2, 8}, {5, 8}, {6, 8}}, wave - 1, 134);
                        }
                    }
                });
            }
        } else { // PP延迟时，执行PP'
            InsertTimeOperation(1169 - 200 - 373, wave, [=]() {
                if (GetRunningWave() == wave) {
                    SetTime(1169 - 200 - 373, wave);
                    pao_operator.pao({{2, 8.8}, {5, 8.8}});
                }
            });
        }
    }
    // 炮消珊瑚
    SetTime(223 - 373, 20);
    pao_operator.pao(4, 7.5875);
}
int GetNumberofCannonReady()
{
    int num = 0;
    auto plants = GetMainObject()->plantArray();
    for (int index = 0; index < GetMainObject()->plantTotal(); ++index) {
        if (plants[index].state() == 37 || plants[index].state() == 36) {
            num += 1;
        }
    }
    return num;
}
bool GetIsExistZombieInTheFrountOfGround()
{
    auto zombies = GetMainObject()->zombieArray();
    for (int index = 0; index < GetMainObject()->zombieTotal(); ++index) {
        if (zombies[index].abscissa() > 6 * 80.0 && !zombies[index].isDead() && !zombies[index].isDisappeared())
            return true;
    }
    return false;
}
bool GetIsExistGIGA(int wave)
{
    auto zombies = GetMainObject()->zombieArray();
    for (int index = 0; index < GetMainObject()->zombieTotal(); ++index) {
        if (zombies[index].type() == GIGA_GARGANTUAR && zombies[index].existTime() == NowTime(wave) && !zombies[index].isDead() && !zombies[index].isDisappeared())
            return true;
    }
    return false;
}
void BlockGigas(std::vector<Grid> pos, int wave, int time)
{
    InsertOperation([=]() {
        const std::vector<PlantType> seed_list = {PUFF_SHROOM, M_PUFF_SHROOM, FLOWER_POT, SCAREDY_SHROOM, SUN_SHROOM, SUNFLOWER};
        auto zombies = GetMainObject()->zombieArray();
        auto seeds = GetMainObject()->seedArray();
        for (auto each_pos : pos) {
            for (int index = 0; index < GetMainObject()->zombieTotal(); ++index) {
                if (zombies[index].type() == GIGA_GARGANTUAR && zombies[index].existTime() == NowTime(wave) && zombies[index].row() + 1 == each_pos.row && zombies[index].abscissa() >= each_pos.col * 80.0 - 69.0 && !zombies[index].isDead() && !zombies[index].isDisappeared()) {
                    for (PlantType each_seed : seed_list) {
                        int seed_index = each_seed > IMITATOR ? GetSeedIndex(each_seed - IMITATOR - 1, true) : GetSeedIndex(each_seed);
                        if (seeds[seed_index].isUsable()) {
                            SetTime(NowTime(GetRunningWave()), GetRunningWave());
                            Card(each_seed, each_pos.row, each_pos.col);
                            SetTime(NowTime(GetRunningWave()) + time, GetRunningWave());
                            Shovel(each_pos.row, each_pos.col);
                            break;
                        }
                    }
                    break;
                }
            }
        }
    });
}
void SkipTickToDamaged()
{
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
        SetGameSpeed(1);
        ShowErrorNotInQueue("发生阵损");
    };
    SkipTick(condition, callback);
}