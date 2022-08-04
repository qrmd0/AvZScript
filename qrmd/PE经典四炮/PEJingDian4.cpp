/*
 * @Author: qrmd
 * @Date: 2022-08-02 13:56:29
 * @LastEditors: qrmd
 * @LastEditTime: 2022-08-04 17:51:18
 * @Description:PE经典四炮 挂机冲关脚本
 * 使用方法：1、前往https://gitee.com/vector-wlc/AsmVsZombies，根据教程下载并安装好AsmVsZombies
 *          2、前往游戏存档文件夹C:/ProgramData/PopCap Games/PlantsVsZombies/userdata，备份原游戏存档，然后用脚本配套的存档文件替换同名文件
 *          3、在Visul Studio Code中打开本脚本，右键点击编辑区空白处，在弹出菜单中选择“AvZ:Run Script”
 *          4、脚本支持游戏倍速和跳帧功能，分别删除第72行和第70行的注释符“//”并保存，可使相应功能在下一次运行脚本时生效
 * 来自AvZScript公开脚本仓库：
 * 主库：https://github.com/qrmd0/AvZScript
 * 镜像库：https://gitee.com/qrmd/AvZScript
 * Copyright (c) 2022 by qrmd, All Rights Reserved.
 */

// #include "SetZombiesPlus.h"
#include "avz.h"

using namespace AvZ;
// *** Not In Queue
// 在位置列表[pos_list]存在巨人僵尸或橄榄僵尸时放置[types]中的植物以拖延其前进，附近存在持杆的撑杆僵尸时自动铲除。结合TickRunner使用。
void AutoBlock(std::vector<PlantType> types, std::vector<Grid> grid_list);
TickRunner auto_blocker;

// *** Not In Queue
// 当三叶草种子可用且场上存在2列以左的气球僵尸时，种植三叶草将其消灭。结合TickRunner运行。
void UseBlover();
TickRunner blover_user;

// *** Not In Queue
// 只要允许，就在位置列表[pos_list]种植[type]植物。结合TickRunner使用。
void PrePlant(int type, std::vector<Grid> grid_list);
TickRunner pre_planter;

// *** Not In Queue
// 返回场上[row]行是否存在[wave]波刷新出的[type]僵尸，[row]为-1表示任意行，[type]为-1表示任意种类
bool IsExistZombieFromWave(int wave, int type, int row);

// *** Not In Queue
// 收尾操作
void EndingTheWave(int time, int wave);

// *** Not In Queue
// 等待直到[row]行的[type_list]种类僵尸全部移动到能啃食到[col]列南瓜头的位置时，种植倭瓜将其消灭
void WaitPlantSquash(int time, int wave, int row, int col, std::vector<int> type_list, int count);

// *** Not In Queue
// 在[wave]波，在{5, 6}和{2, 6}临时种植叶子保护伞消灭蹦极僵尸
void PlantTemporaryUmbrella(int wave);

// *** Not In Queue
// 在[wave]波的[time]厘秒，按照列表[grid_list]种植向日葵
void PlantSunflowers(int time, int wave, std::vector<Grid> grid_list);

// *** In Queue
// 尝试在位置列表[grid_list]种植并唤醒毁灭菇，[is_wake]为true表示同时唤醒
void TryPlantDoomShroom(std::vector<Grid> grid_list);

// *** Not Int Queue
// 有红眼巨人僵尸时的主要运阵操作
void ExistGiga();

// *** Not Int Queue
// 无红眼巨人僵尸时的主要运阵操作
void NotExistGiga();

// *** Not In Queue
// 跳帧运行，阵型受损时停止
void SkipTickToDamaged();

void Script()
{
    // SkipTick(-199, 9);
    // SkipTick(-199, 20);
    // 游戏倍速
    // SetGameSpeed(10);
    // 跳帧运行，阵型受损时停止
    // SkipTickToDamaged();

    // SetErrorMode(CONSOLE);

    // 脚本在游戏主界面和选择植物界面生效，按F12键结束运行
    OpenMultipleEffective(VK_F12, MAIN_UI_OR_FIGHT_UI);

    // SetZombiesPlus({ZOMBIE, CONEHEAD_ZOMBIE, BUCKETHEAD_ZOMBIE, POLE_VAULTING_ZOMBIE, FOOTBALL_ZOMBIE, ZOMBONI, JACK_IN_THE_BOX_ZOMBIE, POGO_ZOMBIE, BUNGEE_ZOMBIE, LADDER_ZOMBIE, BALLOON_ZOMBIE, SNORKEL_ZOMBIE}, INTERNAL);

    // 选择植物：咖啡豆、寒冰菇、模仿寒冰菇、睡莲叶、毁灭菇、南瓜头、倭瓜、三叶草、阳光菇、向日葵
    std::vector<int> card_list = {COFFEE_BEAN, ICE_SHROOM, M_ICE_SHROOM, LILY_PAD, DOOM_SHROOM, PUMPKIN, SQUASH, BLOVER, SUN_SHROOM, SUNFLOWER};

    if (GetZombieTypeList()[GIGA_GARGANTUAR]) {
        card_list[6] = PUFF_SHROOM;
        card_list[9] = SCAREDY_SHROOM;
        if (!GetZombieTypeList()[BALLOON_ZOMBIE])
            card_list[7] = FLOWER_POT;
    } else {
        if (GetZombieTypeList()[BUNGEE_ZOMBIE])
            card_list[8] = UMBRELLA_LEAF;
    }
    SelectCards(card_list);

    // 填充炮列表
    SetTime(-599, 1);
    pao_operator.resetPaoList({{3, 1}, {4, 1}, {3, 3}, {4, 3}});
    // 开始自动存冰
    ice_filler.start({{4, 5}, {1, 4}, {6, 4}, {1, 5}, {6, 5}});
    // 开始自动修补南瓜头
    plant_fixer.start(PUMPKIN, {{3, 6}, {4, 6}, {3, 5}, {4, 5}, {1, 4}, {6, 4}}, 1500);
    // 开始自动垫巨人僵尸
    auto_blocker.pushFunc([]() {
        AutoBlock({PUFF_SHROOM, FLOWER_POT, SCAREDY_SHROOM, SUN_SHROOM, BLOVER, UMBRELLA_LEAF, SUNFLOWER, PUMPKIN}, {{1, 6}, {6, 6}, {2, 6}, {5, 6}});
    });
    // 开始自动消灭2列以左的气球僵尸
    InsertTimeOperation(-599, 1, [=]() {
        if (GetSeedIndex(BLOVER) >= 0)
            blover_user.pushFunc(UseBlover);
    });

    // 主要运阵操作
    if (GetZombieTypeList()[GIGA_GARGANTUAR])
        ExistGiga();
    else
        NotExistGiga();
}
void AutoBlock(std::vector<PlantType> types, std::vector<Grid> grid_list)
{
    auto zombies = GetMainObject()->zombieArray();
    auto seeds = GetMainObject()->seedArray();
    const std::vector<int> state_list = {0, 13, 29, 31, 40, 44, 75, 76};
    std::vector<int> indices_seed;
    std::vector<int> indices_zombie;
    for (PlantType each : types) {
        if (each > IMITATOR)
            indices_seed.emplace_back(GetSeedIndex(each - (IMITATOR + 1), true));
        else
            indices_seed.emplace_back(GetSeedIndex(each, false));
    }
    for (Grid each : grid_list) {
        indices_zombie.clear();
        for (int index = 0; index < GetMainObject()->zombieTotal(); ++index) {
            if (!zombies[index].isDead() && !zombies[index].isDisappeared() && zombies[index].row() + 1 == each.row) {
                if (zombies[index].type() == POLE_VAULTING_ZOMBIE && (zombies[index].abscissa() > each.col * 80 - 51 && zombies[index].abscissa() < each.col * 80 + 40 && zombies[index].state() == 11)) {
                    if (GetPlantIndex(each.row, each.col) >= 0 || GetPlantIndex(each.row, each.col, FLOWER_POT) >= 0)
                        ShovelNotInQueue(each.row, each.col);
                    return;
                }
                if (((zombies[index].type() == GARGANTUAR || zombies[index].type() == GIGA_GARGANTUAR) && (zombies[index].abscissa() > each.col * 80 + 1 - 70 && zombies[index].abscissa() < each.col * 80 + 40 + 1 - 25)) || (zombies[index].type() == FOOTBALL_ZOMBIE && (zombies[index].abscissa() > each.col * 80 - 80 && zombies[index].abscissa() < each.col * 80 - 40 + 1 - 30)))
                    indices_zombie.emplace_back(index);
            }
        }
        for (int each_index : indices_zombie) {
            if (!(std::find(state_list.begin(), state_list.end(), zombies[each_index].state()) != state_list.end()))
                indices_zombie.clear();
        }
        if (indices_zombie.empty())
            continue;
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
void UseBlover()
{
    if (GetMainObject()->gameClock() % 10 != 0)
        return;
    auto seeds = GetMainObject()->seedArray();
    int index_clover_seed = GetSeedIndex(BLOVER);
    if (index_clover_seed < 0)
        return;
    auto zombies = GetMainObject()->zombieArray();
    if (seeds[index_clover_seed].isUsable()) {
        for (int index = 0; index < GetMainObject()->zombieTotal(); ++index) {
            if (zombies[index].isExist() && !zombies[index].isDisappeared() && !zombies[index].isDead() && zombies[index].type() == BALLOON_ZOMBIE && zombies[index].abscissa() <= 2 * 80) {
                ShovelNotInQueue(1, 1);
                CardNotInQueue(index_clover_seed + 1, {{1, 1}});
                break;
            }
        }
    }
}
void PrePlant(int type, std::vector<Grid> grid_list)
{
    if (GetMainObject()->gameClock() % 10 != 0)
        return;
    auto seeds = GetMainObject()->seedArray();
    auto zombies = GetMainObject()->zombieArray();
    int index_seed = type > IMITATOR ? GetSeedIndex(type - (IMITATOR + 1), true) : GetSeedIndex(type, false);
    for (auto each : grid_list) {
        for (int index = 0; index < GetMainObject()->zombieTotal(); ++index) {
            if (!zombies[index].isDead() && !zombies[index].isDisappeared() && zombies[index].row() + 1 == each.row) {
                if (((zombies[index].type() == GARGANTUAR || zombies[index].type() == GIGA_GARGANTUAR) && (zombies[index].abscissa() > each.col * 80 + 1 - 70 && zombies[index].abscissa() < each.col * 80 + 40 + 1)) || (zombies[index].type() == FOOTBALL_ZOMBIE && (zombies[index].abscissa() > each.col * 80 - 80 && zombies[index].abscissa() < each.col * 80 - 40 + 1 - 30)))
                    return;
            }
        }
        if (GetPlantIndex(each.row, each.col) < 0 && GetPlantIndex(each.row, each.col, FLOWER_POT) < 0 && Asm::getPlantRejectType(type, each.row - 1, each.col - 1) == Asm::NIL && seeds[index_seed].isUsable())
            CardNotInQueue(index_seed + 1, each.row, each.col);
    }
}
bool IsExistZombieFromWave(int wave, int type, int row)
{
    auto zombies = GetMainObject()->zombieArray();
    for (int index = 0; index < GetMainObject()->zombieTotal(); ++index) {
        if (!zombies[index].isDead() && !zombies[index].isDisappeared() && (zombies[index].type() == type || -1 == type) && zombies[index].existTime() == NowTime(wave) && (zombies[index].row() + 1 == row || -1 == row))
            return true;
    }
    return false;
}
void EndingTheWave(int time, int wave)
{
    InsertTimeOperation(time, wave, [=]() {
        if (IsExistZombieFromWave(wave, GARGANTUAR, -1) || IsExistZombieFromWave(wave, GIGA_GARGANTUAR, -1)) {
            SetTime(time, wave);
            pao_operator.recoverPao({{1, 8}, {6, 8}});
        }
    });
}
void WaitPlantSquash(int time, int wave, int row, int col, std::vector<int> type_list, int count = 1)
{
    if (count >= 3000)
        return;
    InsertTimeOperation(time, wave, [=]() {
        auto zombies = GetMainObject()->zombieArray();
        auto seeds = GetMainObject()->seedArray();
        std::vector<int> indices_zombie;
        bool is_opportunity;
        indices_zombie.clear();
        for (int index = 0; index < GetMainObject()->zombieTotal(); ++index) {
            if (!zombies[index].isDead() && !zombies[index].isDisappeared() && std::find(type_list.begin(), type_list.end(), zombies[index].type()) != type_list.end() && zombies[index].row() + 1 == row)
                indices_zombie.emplace_back(index);
        }
        is_opportunity = true;
        for (auto each : indices_zombie) {
            if (!(zombies[each].abscissa() < col * 80.0 - 10 + 30 + 1)) {
                is_opportunity = false;
                break;
            }
        }
        if (!seeds[GetSeedIndex(LILY_PAD)].isUsable() || !seeds[GetSeedIndex(SQUASH)].isUsable())
            is_opportunity = false;
        if (is_opportunity) {
            SetNowTime();
            if (row >= 3 && row <= 4) {
                Card(LILY_PAD, row, col);
                Card(SQUASH, row, col);
                Card(LILY_PAD, row, std::min(col + 1, 9));
                Card(SQUASH, row, std::min(col + 1, 9));
            }
            return;
        } else {
            WaitPlantSquash(time + 1, wave, row, col, type_list, count + 1);
        }
    });
}
void PlantTemporaryUmbrella(int wave)
{
    // 提前在下半场种植叶子保护伞
    InsertTimeOperation(374 - 751, wave, [=]() {
        if (GetPlantIndex(5, 6, UMBRELLA_LEAF) < 0) {
            SetTime(374 - 751, wave);
            Shovel(5, 6);
            Card(UMBRELLA_LEAF, 5, 6);
        }
    });
    InsertTimeOperation(0, wave, [=]() {
        // 以下位置刷出了蹦极僵尸时，在上半场种植叶子保护伞保护这些位置的植物
        std::vector<Grid> grid_list = {{1, 5}, {2, 5}, {3, 5}, {3, 6}};
        auto zombies = GetMainObject()->zombieArray();
        for (int index = 0; index < GetMainObject()->zombieTotal(); ++index) {
            if (!zombies[index].isDead() && !zombies[index].isDisappeared() && zombies[index].type() == BUNGEE_ZOMBIE) {
                for (auto each : grid_list) {
                    if (zombies[index].row() + 1 == each.row && INT(zombies[index].abscissa()) == each.col * 80 - 40) {
                        InsertTimeOperation(374, wave, [=]() {
                            if (GetPlantIndex(2, 6, UMBRELLA_LEAF) < 0) {
                                SetTime(374, wave);
                                Shovel(2, 6);
                                Card(UMBRELLA_LEAF, 2, 6);
                            }
                        });
                        return;
                    }
                }
            }
        }
    });
}
void PlantSunflowers(int time, int wave, std::vector<Grid> grid_list)
{
    int i = 0;
    for (auto each : grid_list) {
        InsertTimeOperation(time + i * 751, wave, [=]() {
            if (GetPlantIndex(each.row, each.col, SUNFLOWER) < 0) {
                SetNowTime();
                Shovel(each.row, each.col);
                if (each.row >= 3 && each.row <= 4)
                    Card(LILY_PAD, each.row, each.col);
                Card(SUNFLOWER, each.row, each.col);
            }
        });
        i++;
    }
}
void SkipTickToDamaged()
{
    // 启用20倍速
    // WriteMemory<bool>(true, 0x6A9EAB);
    // 启用10倍速
    SetGameSpeed(10);
    auto condition
        = [=]() {
              std::vector<Grid> plant_list = {{3, 1}, {4, 1}, {3, 3}, {4, 3}, {2, 5}, {5, 5}, {3, 6}, {4, 6}};
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
void TryPlantDoomShroom(std::vector<Grid> grid_list, bool is_wake)
{
    InsertOperation([=]() {
        for (auto each : grid_list) {
            if (Asm::getPlantRejectType(DOOM_SHROOM, each.row - 1, each.col - 1) == Asm::NIL || Asm::getPlantRejectType(LILY_PAD, each.row - 1, each.col - 1) == Asm::NIL) {
                SetNowTime();
                if (each.row >= 3 && each.row <= 4)
                    Card(LILY_PAD, each.row, each.col);
                Card(DOOM_SHROOM, each.row, each.col);
                if (is_wake)
                    Card(COFFEE_BEAN, each.row, each.col);
                break;
            }
        }
    });
}
void ExistGiga()
{
    // 开始预种植小喷菇
    pre_planter.pushFunc([]() {
        PrePlant(PUFF_SHROOM, {{2, 6}, {5, 6}, {1, 6}, {6, 6}});
    });

    // 主体节奏 ch4 I-PP|I-PP 1738|1738
    // wave1 N 首代
    SetTime(400 - 299, 1);
    TryPlantDoomShroom({{3, 9}, {4, 9}, {3, 8}, {4, 8}}, true);

    // wave2 PP 首代
    SetTime(729 - 373, 2);
    pao_operator.pao({{2, 8.6125}, {5, 8.6125}});

    // wave3, 4, 5, 6, 7, 8, 9, 12, 13, 14, 15, 16, 17, 18, 19 I-PP
    for (int wave : {3, 4, 5, 6, 7, 8, 9, 12, 13, 14, 15, 16, 17, 18, 19}) {
        SetTime(-200, wave);
        ice_filler.coffee();
        SetTime(1738 - 200 - 373, wave);
        pao_operator.recoverPao({{2, 8.7625}, {5, 8.7625}});
    }

    // wave10 N 首代
    SetTime(550 - 299, 10);
    TryPlantDoomShroom({{3, 8}, {4, 8}}, true);

    // wave11 PP 首代
    SetTime(729 - 373, 11);
    pao_operator.pao({{2, 8.6125}, {5, 8.6125}});

    // wave20 N
    SetTime(-600, 20);
    TryPlantDoomShroom({{3, 8}, {4, 8}}, false);
    SetTime(550 - 298, 20);
    Card(COFFEE_BEAN, {{3, 8}, {4, 8}});

    // wave9, 19 收尾操作
    for (int wave : {9, 19})
        EndingTheWave(2120 + 1738 - 200 - 373, wave);

    // wave20 收尾操作
    EndingTheWave(900 + 1738 - 200 - 373, 20);
    InsertTimeOperation(900 + 1738 - 200 + 3, 20, [=]() {
        SetTime(4258 - 373);
        if (IsExistZombieFromWave(20, GIGA_GARGANTUAR, 1))
            pao_operator.pao({{3, 8}, {5, 8}});
        else if (IsExistZombieFromWave(20, GIGA_GARGANTUAR, 6))
            pao_operator.pao({{2, 8}, {4, 8}});
        else if (IsExistZombieFromWave(20, GIGA_GARGANTUAR, 2))
            pao_operator.pao(5, 8);
        else if (IsExistZombieFromWave(20, GIGA_GARGANTUAR, 5))
            pao_operator.pao(2, 8);
    });
}
void NotExistGiga()
{

    // 种植向日葵
    PlantSunflowers(-599, 1, {{2, 6}, {5, 6}, {1, 6}, {6, 6}});
    if (!GetZombieTypeList()[GARGANTUAR] && !GetZombieTypeList()[DIGGER_ZOMBIE])
        PlantSunflowers(-599 + 6 * 751, 1, {{1, 1}, {2, 1}, {5, 1}, {6, 1}});

    // 主体节奏 C7i I-PP|I-PP|I-N|PP 1738|1738|1152|685
    // wave1 PP
    SetTime(638 - 373, 1);
    pao_operator.pao({{2, 8.5375}, {5, 8.5375}});

    // wave5, 14, 18 PP
    for (int wave : {5, 14, 18}) {
        SetTime(685 - 200 - 373, wave);
        pao_operator.pao({{2, 8.7625}, {5, 8.7625}});
    }

    // wave2, 3, 6, 7, 12, 15, 16 I-PP
    for (int wave : {2, 3, 6, 7, 12, 15, 16}) {
        SetTime(-200, wave);
        ice_filler.coffee();
        SetTime(1738 - 200 - 373, wave);
        pao_operator.pao({{2, 8.7625}, {5, 8.7625}});
    }

    // wave11 I-PP
    SetTime(-200, 11);
    ice_filler.coffee();
    SetTime(1754 - 200 - 373, 11);
    pao_operator.pao({{2, 8.7625}, {5, 8.7625}});

    // wave4, 8, 13, 17 I-N
    for (int wave : {4, 8, 13, 17}) {
        SetTime(-200, wave);
        ice_filler.coffee();
        SetTime(1152 - 200 - 298, wave);
        TryPlantDoomShroom({{3, 9}, {4, 9}, {3, 8}, {4, 8}}, true);
    }

    // wave9 PP
    InsertTimeOperation(706 - 200 - 373, 9, [=]() {
        SetTime(706 - 200 - 373, 9);
        if (IsExistZombieFromWave(9, GARGANTUAR, -1)) {
            pao_operator.pao({{2, 8.7625}, {5, 8.7625}});
        } else {
            if (IsExistZombieFromWave(9, -1, 3)) {
                pao_operator.pao({{1, 8.7625}, {5, 8.7625}});
                WaitPlantSquash(700, 9, 3, 6, {CONEHEAD_ZOMBIE, BUCKETHEAD_ZOMBIE, SNORKEL_ZOMBIE});
            } else if (IsExistZombieFromWave(9, -1, 4)) {
                pao_operator.pao({{2, 8.7625}, {6, 8.7625}});
                WaitPlantSquash(700, 9, 4, 6, {CONEHEAD_ZOMBIE, BUCKETHEAD_ZOMBIE, SNORKEL_ZOMBIE});
            } else {
                pao_operator.pao({{2, 8.7625}, {5, 8.7625}});
            }
        }
    });

    // wave19 I-PP
    SetTime(-200, 19);
    ice_filler.coffee();
    InsertTimeOperation(1754 - 200 - 373, 19, [=]() {
        SetTime(1754 - 200 - 373, 19);
        if (IsExistZombieFromWave(19, GARGANTUAR, -1)) {
            pao_operator.pao({{2, 8.7625}, {5, 8.7625}});
        } else {
            if (IsExistZombieFromWave(19, -1, 3)) {
                pao_operator.pao({{1, 8.7625}, {5, 8.7625}});
                Card(LILY_PAD, 3, 7);
                WaitPlantSquash(1754 - 200 - 373, 19, 3, 6, {CONEHEAD_ZOMBIE, BUCKETHEAD_ZOMBIE, SNORKEL_ZOMBIE});
            } else if (IsExistZombieFromWave(19, -1, 4)) {
                pao_operator.pao({{2, 8.7625}, {6, 8.7625}});
                Card(LILY_PAD, 4, 7);
                WaitPlantSquash(1754 - 200 - 373, 19, 4, 6, {CONEHEAD_ZOMBIE, BUCKETHEAD_ZOMBIE, SNORKEL_ZOMBIE});
            } else {
                pao_operator.pao({{2, 8.7625}, {5, 8.7625}});
            }
        }
    });

    // wave10 PP
    SetTime(776 - 373, 10);
    pao_operator.pao({{2, 8.45}, {5, 8.45}});

    // wave20 PP和收尾操作
    InsertTimeOperation(0, 20, [=]() {
        if (IsExistZombieFromWave(20, GARGANTUAR, -1)) {
            SetTime(776 - 373, 20);
            pao_operator.pao({{2, 8.45}, {5, 8.45}});
            if (IsExistZombieFromWave(20, GARGANTUAR, 1)) {
                SetTime(2500 + 776 - 373, 20);
                pao_operator.pao({{3, 8}, {5, 8}});
            } else if (IsExistZombieFromWave(20, GARGANTUAR, 6)) {
                SetTime(2500 + 776 - 373, 20);
                pao_operator.pao({{2, 8}, {4, 8}});
            } else if (IsExistZombieFromWave(20, GARGANTUAR, 2)) {
                SetTime(2500 + 776 - 373, 20);
                pao_operator.pao(5, 8);
            } else if (IsExistZombieFromWave(20, GARGANTUAR, 5)) {
                SetTime(2500 + 776 - 373, 20);
                pao_operator.pao(2, 8);
            }
        } else {
            SetTime(776 - 373, 20);
            if (IsExistZombieFromWave(20, -1, 3)) {
                pao_operator.pao({{1, 8.45}, {5, 8.45}});
                Card(LILY_PAD, 3, 7);
                WaitPlantSquash(776 - 373, 20, 3, 6, {CONEHEAD_ZOMBIE, BUCKETHEAD_ZOMBIE, SNORKEL_ZOMBIE});
            } else if (IsExistZombieFromWave(20, -1, 4)) {
                pao_operator.pao({{2, 8.45}, {6, 8.45}});
                Card(LILY_PAD, 4, 7);
                WaitPlantSquash(776 - 373, 20, 4, 6, {CONEHEAD_ZOMBIE, BUCKETHEAD_ZOMBIE, SNORKEL_ZOMBIE});
            } else {
                pao_operator.pao({{2, 8.45}, {5, 8.45}});
            }
        }
    });

    // wave9 收尾操作
    EndingTheWave(1854 + 706 - 200 - 373, 9);

    // wave19 收尾操作
    EndingTheWave(3592 - 373, 19);

    // wave10, 20 临时种植叶子保护伞应对蹦极僵尸
    for (int wave : {10, 20}) {
        if (GetZombieTypeList()[BUNGEE_ZOMBIE])
            PlantTemporaryUmbrella(wave);
    }
}