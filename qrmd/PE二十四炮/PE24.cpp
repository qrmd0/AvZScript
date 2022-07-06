/*
 * @Author: qrmd
 * @Date: 2022-05-02 22:23:43
 * @Last Modified by: qrmd
 * @Last Modified time: 2022-05-12 21:23:46
 * @Description: PE二十四炮 挂机全程
 */

#include "avz.h"

using namespace AvZ;
using namespace std;
struct ZombieAdd : public Zombie {
    // 僵尸动画编号
    uint16_t& animationCode()
    {
        return (uint16_t&)((uint8_t*)this)[0x118];
    }
};
struct AnimationAdd : public Animation {
    // 动画起始帧
    int& beginFrame()
    {
        return (int&)((uint8_t*)this)[0x18];
    }
};
// 游戏运行速度倍率
const vector<float> game_speeds = {0.1, 0.2, 0.5, 1.0, 2.0, 5.0, 10.0};
// 游戏运行速度倍率档位
int game_speed_gear = 3;
// 陆路高坚果自动修补操作类
PlantFixer tall_nut_fixer1;
// 水路高坚果自动修补操作类
PlantFixer tall_nut_fixer2;
// 大蒜自动修补操作类
PlantFixer garlic_fixer;
// 南瓜头自动修补操作类
PlantFixer pumpkin_fixer;
// 减压炮发射操作类
TickRunner press_reductioner;
// 种植玉米加农炮操作类
TickRunner cob_planter;
// 是否处于种植前场玉米加农炮的开局阶段
bool is_planting_frount_ground_cannon = false;
// 是否需要在第20波使用樱桃炸弹
bool is_need_cherry_bomb = false;
// 本轮累计刷出的红眼巨人僵尸数量
int the_number_of_have_refreshed_giga_gargantuar = 0;
namespace AvZ {
class TickPlanter : public TickRunner {
private:
    enum IfFailDo {
        // 放弃，不会再执行此操作
        ABANDON,
        // 推迟，下次仍会执行此操作
        DELAY,
        // 阻塞，跳过所有其他操作直到此操作被执行成功
        WAIT,
        // 如果仅因为位置被占用而失败，则铲除占位植物并重试，如果重试失败，则推迟
        SHOVEL_AND_TRY_AGAIN
    };
    // 种植操作数据
    struct Planting {
        // 种植的种子类型
        int type;
        // 种植的位置：{row, col}:[row]行[col]列
        Grid position;
        // 种植失败时的处理
        IfFailDo if_fail_do = DELAY;
    };
    // 优先队列
    std::vector<Planting> prior_plant_list;
    // 常规队列
    std::vector<Planting> routine_plant_list;
    // 种植操作队列向量
    std::vector<std::vector<Planting>> plant_list = {prior_plant_list, routine_plant_list};
    // 遍历种植操作队列的时间间隔
    int time_interval = 1;
    void run()
    {
        if (GetMainObject()->gameClock() % time_interval != 0)
            return;
        auto seeds = GetMainObject()->seedArray();
        for (int i = 0; i < 2; ++i) {
            for (int index = 0; index < this->plant_list[i].size(); index++) {
                auto it = plant_list[i][index];
                int plant_type = it.type > IMITATOR ? it.type - IMITATOR - 1 : it.type;
                int index_seed = it.type > IMITATOR ? GetSeedIndex(it.type - IMITATOR - 1, true) : GetSeedIndex(it.type);
                int sun_cost = *(int*)(0x69F2C0 + plant_type * 0x24);
                int present_sun = GetMainObject()->sun();
                int plant_reject_type = Asm::getPlantRejectType(plant_type, it.position.row - 1, it.position.col - 1);
                bool is_plant_successful = false;
                if (plant_reject_type == Asm::PlantReject::NIL && seeds[index_seed].isUsable() && present_sun >= sun_cost) {
                    CardNotInQueue(index_seed + 1, it.position.row, it.position.col);
                    if (!seeds[index_seed].isUsable()) {
                        is_plant_successful = true;
                        plant_list[i].erase(plant_list[i].begin() + index);
                    }
                }
                if (!is_plant_successful) {
                    switch (it.if_fail_do) {
                    case ABANDON:
                        plant_list[i].erase(plant_list[i].begin() + index);
                        break;
                    case WAIT:
                        return;
                        break;
                    case SHOVEL_AND_TRY_AGAIN:
                        if (plant_reject_type == Asm::PlantReject::NOT_HERE && seeds[index_seed].isUsable() && present_sun >= sun_cost) {
                            ShovelNotInQueue(it.position.row, it.position.col);
                            index--;
                        }
                        break;

                    default:
                        break;
                    }
                }
            }
        }
    }

public:
    // *** Not In Queue
    // 在种植操作队列尾部添加操作，如果这些操作失败则什么也不做
    void PlantNotInQuene(int type, std::vector<Grid> grid_list)
    {
        for (Grid each : grid_list) {
            Planting temp = {type, {each.row, each.col}, ABANDON};
            plant_list[1].emplace_back(temp);
        }
    }
    // *** Not In Queue
    // 在种植操作队列尾部添加操作，如果这些操作失败则将其保留在队列中
    void delayPlantNotInQuene(int type, std::vector<Grid> grid_list)
    {
        for (Grid each : grid_list) {
            Planting temp = {type, {each.row, each.col}, DELAY};
            plant_list[1].emplace_back(temp);
        }
    }
    // *** Not In Queue
    // 在种植操作队列尾部添加操作，如果这些操作仅因位置被占用而失败则铲除占位的植物重试，如果仍失败，操作被保留在队列中
    void shovelPlantNotInQuene(int type, std::vector<Grid> grid_list)
    {
        for (Grid each : grid_list) {
            Planting temp = {type, {each.row, each.col}, SHOVEL_AND_TRY_AGAIN};
            plant_list[0].emplace_back(temp);
        }
    }
    // *** Not In Queue
    // 在种植操作队列尾部添加操作，如果这些操作失败则暂停其他种植操作并将此操作保留
    void waitPlantNotInQuene(int type, std::vector<Grid> grid_list)
    {
        for (Grid each : grid_list) {
            Planting temp = {type, {each.row, each.col}, WAIT};
            plant_list[0].emplace_back(temp);
        }
    }
    // *** In Queue
    // 启动TickPlanter
    void start()
    {
        InsertOperation([=]() {
            pushFunc([=]() {
                run();
            });
        },
            "startTickPlanter");
    }
    // *** In Queue
    // 设置tick_planter遍历种植操作队列时间间隔，默认为1厘秒
    void setInterval(int _time)
    {
        InsertOperation([=]() {
            time_interval = _time;
        },
            "setInterval");
    }
};
TickPlanter tick_planter;
}
// 返回[wave]波首个出现的僵尸所在的行数，若场上不存在[wave]波刷出的僵尸，返回-1
int GetZombieRefreshRow(int wave);
// 在[pao_list]位置种植多个玉米加农炮，种植时铲除占位的植物，检测时间间隔为[time_interval]厘秒
void ShovelAndPlantCobCannons(std::vector<Grid> pao_list, int time_interval = 1);
// 发炮降低高坚果压力，触发条件为当高坚果前方一格存在的僵尸数量不小于3或其总血量大于1370(一只铁桶僵尸)
void PressReductionCob();
// 序号为[index_zombie]的僵尸在[time_length]厘秒内的位移预测
vector<float> GetZombieAbsccisas(int index_zombie, int time_length);
//在[wave]波发炮射击2行和5行消灭大部分僵尸，只留下最慢的一只领带僵尸。适用于六行场地
void SeparateLastZombie(int wave);
// 在[wave]波[time]厘秒，根据是否预判冰[is_iced]和场上僵尸类型进行守7列的反应炸
void ReactCob(int time, int wave, int is_iced);
// 在[wave]波[time]厘秒，补炸场上的白眼巨人僵尸
void CobGargantuar(int time, int wave);
// 当阳光数量不小于[start_sun]时，开始种植前场的玉米加农炮
void StartFrountCannonPlant(vector<Grid> cannon_list, int start_sun, int wave = 1);
// 常规炮操作 PPDDDD
void PPDDDD(int time, int wave);
// 常规炮操作 PPDD精准之舞
void PPDDJW(int time, int wave);
// 常规炮操作 PPI
void PPI(int time, int wave);
// 常规炮操作 PPSSDD
void PPSSDD(int time, int wave);
// 发炮射击生成于20波的从水面冒出的珊瑚僵尸，当[use_single_cannon]为true时使用一门炮，否则使用两门炮
void ShootCoralZombies(bool use_single_cannon);
// 返回场上处于就绪或装填状态的玉米加农炮数量
int GetNumberofCobCannonBeReady();
// 返回场上是否存在[type]类型的僵尸
bool GetIsExistZombie(int type = -1);
// 返回场上是否存在于[wave]波0厘秒刷出的僵尸
bool GetIsExistCurrentWaveZombie(int wave);
// 返回[wave]波是否刷出了红眼巨人僵尸
bool GetIsRefreshedGigaGargantuar(int wave);
// 在[wave]波[time]厘秒，如果陆路存在列表[zombie_types]中的僵尸，选择阳光消耗较低的植物放置在对应路的9列并在[shovel_time]厘秒后铲除
void PlantToBlockTheZombies(int time, int wave, vector<int> zombie_types, int row = 1, int shovel_time = 79);
// 在[wave]波[time]厘秒，不断尝试对[ice_shroom_positions]位置种植咖啡豆，直到咖啡豆种植成功为止
void RecoverAwakeIceShroom(int time, int wave, vector<Position> ice_shroom_positions = {{4, 9}, {3, 9}});
// 不刷出红眼巨人僵尸时，从[first_wave]波开始到[end_wave]波（含）的操作
void NoGigaGargantuar(int first_wave, int end_wave = 20);
// 刷出红眼巨人僵尸且刷出白眼巨人僵尸时，以[wave]波的[i]号操作为起始直到本轮结束的操作
void GigaGargantuarAndGargantuar(int i, int wave = 1, bool is_activation = false, bool is_transition = false, bool is_ending = false);
// 刷出红眼巨人僵尸且不刷出白眼巨人僵尸时，以[wave]波的[i]号操作为起始直到本轮结束的操作
void GigaGargantuarAndNoGargantuar(int i, int wave = 1, bool is_activation = false, bool is_transition = false, bool is_ending = false);
// 已完成0轮时的整轮操作
void Begin1();
// 已完成1轮时的整轮操作
void Begin2();
// 阵成型后的整轮操作
void RunThePlant();
void Script()
{
    is_need_cherry_bomb = false;
    the_number_of_have_refreshed_giga_gargantuar = 0;
    // ShowErrorNotInQueue("本脚本是从0轮开始的全程挂机脚本，无需手动控制。如果您目前有正在进行的生存无尽游戏，请确定本对话框后按“Q”键结束本脚本，将存档备份并删除，然后重新运行脚本并开始游戏。");
    OpenMultipleEffective('Q', AvZ::MAIN_UI_OR_FIGHT_UI);
    SetGameSpeed(game_speeds[game_speed_gear]);
    KeyConnect('A', [=]() {
        if (game_speed_gear > 0) {
            game_speed_gear -= 1;
            SetGameSpeed(game_speeds[game_speed_gear]);
        }
    });
    KeyConnect('D', [=]() {
        if (game_speed_gear < game_speeds.size() - 1) {
            game_speed_gear += 1;
            SetGameSpeed(game_speeds[game_speed_gear]);
        }
    });
    KeyConnect('S', [=]() {
        game_speed_gear = 3;
        SetGameSpeed(game_speeds[game_speed_gear]);
    });
    KeyConnect('W', [=]() {
        SkipTick(5999, 20);
    });
    int round = *reinterpret_cast<int*>(*reinterpret_cast<int*>(*reinterpret_cast<int*>(*reinterpret_cast<int*>(0x6A9EC0) + 0x768) + 0x160) + 0x6C);
    if (round == 0) {
        Begin1();
    } else if (round >= 1 && round <= 4) {
        Begin2();
    } else {
        RunThePlant();
    }
}

void PPDDDD(int time, int wave)
{
    SetTime(time - 376, wave);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    SetTime(time + 57 - 376, wave);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    SetTime(time + 57 + 110 - 376, wave);
    pao_operator.pao({{1, 8.8}, {5, 8.8}});
}
void PPDDJW(int time, int wave)
{
    SetTime(time - 373, wave);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    SetTime(time - 373 + 107, wave);
    pao_operator.pao({{1, 7.7}, {5, 7.7}});
}
void PPI(int time, int wave)
{
    SetTime(time - 376, wave);
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
    RecoverAwakeIceShroom(time - 298, wave);
}
void PPSSDD(int time, int wave)
{
    SetTime(time - 376, wave);
    pao_operator.pao({{2, 8.8}, {5, 8.8}, {2, 8.8}, {5, 8.8}});
    SetTime(time + 110 - 376, wave);
    pao_operator.pao({{1, 8.8}, {5, 8.8}});
}
void ShootCoralZombies(bool use_single_cannon)
{
    if (use_single_cannon) {
        // P
        SetTime(223 - 373, 20);
        pao_operator.pao(4, 7.5875);
    } else {
        // PP
        SetTime(223 - 373, 20);
        pao_operator.pao({{4, 7}, {4, 8.2}});
    }
}
int GetNumberofCobCannonBeReady()
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
bool GetIsExistZombie(int type)
{
    auto zombies = GetMainObject()->zombieArray();
    for (int index = 0; index < GetMainObject()->zombieTotal(); ++index) {
        if (!zombies[index].isDisappeared() && !zombies[index].isDead()) {
            if (type > 0) {
                if (zombies[index].type() == type) {
                    return true;
                }
            } else {
                return true;
            }
        }
    }
    return false;
}
bool GetIsExistCurrentWaveZombie(int wave)
{
    auto zombies = GetMainObject()->zombieArray();
    for (int index = 0; index < GetMainObject()->zombieTotal(); ++index) {
        if (!zombies[index].isDisappeared() && !zombies[index].isDead() && zombies[index].existTime() == NowTime(wave)) {
            return true;
        }
    }
    return false;
}

bool GetIsRefreshedGigaGargantuar(int wave)
{
    auto zombies = GetMainObject()->zombieArray();
    for (int index = 0; index < GetMainObject()->zombieTotal(); ++index) {
        if (zombies[index].type() == GIGA_GARGANTUAR && zombies[index].existTime() <= NowTime(wave) && !zombies[index].isDisappeared() && !zombies[index].isDead()) {
            return true;
        }
    }
    return false;
}

void RecoverAwakeIceShroom(int time, int wave, vector<Position> ice_shroom_positions)
{
    InsertTimeOperation(time, wave, [=]() {
        auto seeds = GetMainObject()->seedArray();
        int index_coffee_bean_seed = GetSeedIndex(COFFEE_BEAN);
        auto plants = GetMainObject()->plantArray();
        for (Position pos : ice_shroom_positions) {
            if (seeds[index_coffee_bean_seed].isUsable() && GetPlantIndex(pos.row, pos.col, ICE_SHROOM) >= 0) {
                {
                    InsertGuard ig(false);
                    Card(COFFEE_BEAN, pos.row, pos.col);
                }
            }
        }
        if (seeds[index_coffee_bean_seed].isUsable()) {
            RecoverAwakeIceShroom(time + 1, wave, ice_shroom_positions);
        } else {
            return;
        }
    });
}
void NoGigaGargantuar(int first_wave, int end_wave)
{
    for (int wave = first_wave; wave <= end_wave; ++wave) {
        SetTime(295 + (341 - 295) * (wave == 10 || wave == 20) - 376, wave);
        pao_operator.pao({{2, 8.8}, {5, 8.8}});
        SetTime(295 + (341 - 295) * (wave == 10 || wave == 20) + 105 - 3 - 376, wave);
        pao_operator.pao({{2, 8.8}, {5, 8.8}});
        if (wave == 9 || wave == 19 || wave == 20) {
            InsertTimeOperation(601 * 2 - 200 - 373, wave, [=]() {
                if (GetIsExistCurrentWaveZombie(wave)) {
                    SetTime(601 * 2 - 200 - 373, wave);
                    pao_operator.pao({{2, 8.8}, {5, 8.8}});
                }
            });
        } else {
            InsertTimeOperation(601 * 2 - 200 - 373, wave, [=]() {
                if (GetRunningWave() == wave) {
                    SetTime(601 * 2 - 200 - 373, wave);
                    pao_operator.pao({{2, 8.8}, {5, 8.8}});
                }
            });
        }
    }
}
void GigaGargantuarAndGargantuar(int i, int wave, bool is_activation, bool is_transition, bool is_ending)
{
    if (is_ending) {
        InsertTimeOperation(341 + 57 + 110 + 1, wave, [=]() {
            switch (i % 3) {
            case 1:
                // (-PP)
                if (GetIsExistCurrentWaveZombie(wave)) {
                    SetTime(359 + 601 - 376, wave);
                    pao_operator.pao({{2, 8.8}, {5, 8.8}});
                }
                break;
            case 2:
                if (GetIsExistZombie(GIGA_GARGANTUAR)) {
                    PPI(295 + 601, wave);
                    // PPSS
                    SetTime(295 + 601 * 2 - 376, wave);
                    pao_operator.pao({{2, 8.8}, {5, 8.8}, {2, 8.8}, {5, 8.8}});
                } else {
                    // (-PP)
                    if (GetIsExistZombie()) {
                        SetTime(295 + 601 - 376, wave);
                        pao_operator.pao({{2, 8.8}, {5, 8.8}});
                    }
                }
                break;
            case 0:
                if (GetIsExistZombie(GIGA_GARGANTUAR)) {
                    if (GetIsRefreshedGigaGargantuar(wave)) {
                        PPSSDD(295 + 601, wave);
                    } else {
                        // PPSS
                        SetTime(295 + 601 - 376, wave);
                        pao_operator.pao({{2, 8.8}, {5, 8.8}, {2, 8.8}, {5, 8.8}});
                    }
                } else if (GetIsExistZombie(GARGANTUAR)) {
                    // PP
                    SetTime(295 + 601 - 376, wave);
                    pao_operator.pao({{2, 8.8}, {5, 8.8}});
                }
                InsertTimeOperation(359 + 601 * 2 - 373, wave, [=]() mutable {
                    // (-PP)
                    if (GetIsExistZombie()) {
                        SetTime(359 + 601 * 2 - 373, wave);
                        pao_operator.pao({{2, 8.8}, {5, 8.8}});
                    }
                });
                break;
            }
            InsertTimeOperation(601 + 745 - 223, wave, [=]() {
                if (wave == 9 || wave == 19) {
                    GigaGargantuarAndGargantuar(3, wave + 1, false, false, false);
                } else {
                    return;
                }
            });
        });
    } else if (is_activation) {
        InsertTimeOperation(341 + 57 + 110 + 1, wave, [=]() {
            switch (i % 3) {
            case 1:
                // PP
                SetTime(601 * 2 - 200 - 373, wave);
                pao_operator.pao({{2, 8.8}, {5, 8.8}});
                break;
            case 2:
                PlantToBlockTheZombies(777, wave, {GIGA_GARGANTUAR});
                PPI(601 * 2 - 200, wave);
                break;
            case 0:
                PPSSDD(377 + 399 + 106 * 2 - 1, wave);
                break;
            }
            GigaGargantuarAndGargantuar(i + 1, wave + 1, false, is_transition, false);
        });
    } else {
        InsertTimeOperation(295 - 376, wave, [=]() {
            InsertTimeOperation(0, wave, [=]() {
                auto zombies = GetMainObject()->zombieArray();
                for (int index = 0; index < GetMainObject()->zombieTotal(); ++index) {
                    if (zombies[index].type() == GIGA_GARGANTUAR && !zombies[index].isDisappeared() && !zombies[index].isDead() && zombies[index].existTime() == NowTime(wave)) {
                        the_number_of_have_refreshed_giga_gargantuar += 1;
                    }
                }
            });
            switch (i % 3) {
            case 1:
                if (is_transition) {
                    NoGigaGargantuar(wave, wave);
                } else {
                    PPDDJW(359, wave);
                }
                break;
            case 2:
                if (wave == 9 || wave == 19) {
                    PPI(295, wave);
                } else {
                    PlantToBlockTheZombies(191, wave, {DANCING_ZOMBIE, GIGA_GARGANTUAR});
                    PPI(377, wave);
                }
                break;
            case 0:
                if (wave == 10 || wave == 20) {
                    if (wave == 20 && is_need_cherry_bomb) {
                        // PADDDD
                        SetTime(341 - 376, wave);
                        pao_operator.pao(2, 8.8);
                        SetTime(341 - 100, wave);
                        Card(CHERRY_BOMB, 5, 9);
                        SetTime(341 + 57 - 376, wave);
                        pao_operator.pao({{2, 8.8}, {5, 8.8}});
                        SetTime(341 + 57 + 110 - 376, wave);
                        pao_operator.pao({{1, 8.8}, {5, 8.8}});
                    } else {
                        PPDDDD(341, wave);
                    }
                } else {
                    PPSSDD(295, wave);
                }
                break;
            }
        });
        InsertTimeOperation(341 + 57 + 110 + 1, wave, [=]() {
            if (GetRunningWave() == wave) {
                if (wave == 9 || wave == 19 || wave == 20) {
                    GigaGargantuarAndGargantuar(i + 1, wave, false, false, true);
                } else {
                    GigaGargantuarAndGargantuar(i + 1, wave, true, is_transition, false);
                }
            } else {
                if (i % 3 == 2 && (is_transition && !is_activation && !is_ending)) {
                    the_number_of_have_refreshed_giga_gargantuar = 0;
                    NoGigaGargantuar(wave + 1, 19);
                    GigaGargantuarAndGargantuar(3, 20, false, false, false);
                } else {
                    GigaGargantuarAndGargantuar(i + 1, wave + 1, false, the_number_of_have_refreshed_giga_gargantuar >= 50 && wave >= 10 && wave <= 17, false);
                }
            }
        });
    }
}
void GigaGargantuarAndNoGargantuar(int i, int wave, bool is_activation, bool is_transition, bool is_ending)
{
    if (is_ending) {
        InsertTimeOperation(341 + 57 + 110 + 1, wave, [=]() {
            switch (i % 2) {
            case 1:
                if (GetIsExistCurrentWaveZombie(wave)) {
                    PPSSDD(284 + 601, wave);
                }
                break;
            case 0:
                //(-PP)
                if (GetIsExistCurrentWaveZombie(wave)) {
                    SetTime(359 + 601 - 373, wave);
                    pao_operator.pao({{2, 8.8}, {5, 8.8}});
                }
                break;
            }
            InsertTimeOperation(601 + 745 - 223, wave, [=]() {
                if (wave == 9 || wave == 19) {
                    GigaGargantuarAndNoGargantuar(1, wave + 1, false, false, false);
                } else {
                    return;
                }
            });
        });
    } else if (is_activation) {
        InsertTimeOperation(341 + 57 + 110 + 1, wave, [=]() {
            switch (i % 2) {
            case 1:
                PPSSDD(601 * 2 - 200, wave);
                PlantToBlockTheZombies(777, wave, {GIGA_GARGANTUAR});
                break;
            case 0:
                SetTime(601 * 2 - 200 - 373, wave);
                pao_operator.pao({{2, 8.8}, {5, 8.8}});
                break;
            }
            GigaGargantuarAndNoGargantuar(i + 1, wave + 1, false, is_transition, false);
        });
    } else {
        InsertTimeOperation(284 - 376, wave, [=]() {
            InsertTimeOperation(0, wave, [=]() {
                auto zombies = GetMainObject()->zombieArray();
                for (int index = 0; index < GetMainObject()->zombieTotal(); ++index) {
                    if (zombies[index].type() == GIGA_GARGANTUAR && !zombies[index].isDisappeared() && !zombies[index].isDead() && zombies[index].existTime() == NowTime(wave)) {
                        the_number_of_have_refreshed_giga_gargantuar += 1;
                    }
                }
            });
            switch (i % 2) {
            case 1:
                if (wave == 10 || wave == 20) {
                    PPDDDD(341, wave);
                } else {
                    PPSSDD(284, wave);
                }
                break;
            case 0:
                SetTime(359 - 373, wave);
                pao_operator.pao({{2, 8.8}, {5, 8.8}});
                PlantToBlockTheZombies(191, wave, {DANCING_ZOMBIE});
                break;
            }
        });
        InsertTimeOperation(341 + 57 + 110 + 1, wave, [=]() {
            if (GetRunningWave() == wave) {
                if (wave == 9 || wave == 19 || wave == 20) {
                    GigaGargantuarAndNoGargantuar(i + 1, wave, false, false, true);
                } else {
                    GigaGargantuarAndNoGargantuar(i + 1, wave, true, is_transition, false);
                }
            } else {
                if (i % 2 == 0 && (is_transition && !is_activation && !is_ending)) {
                    the_number_of_have_refreshed_giga_gargantuar = 0;
                    NoGigaGargantuar(wave + 1, 19);
                    GigaGargantuarAndNoGargantuar(1, 20, false, false, false);
                } else {
                    GigaGargantuarAndNoGargantuar(i + 1, wave + 1, false, the_number_of_have_refreshed_giga_gargantuar >= 50 && wave >= 10 && wave <= 17, false);
                }
            }
        });
    }
}
int GetZombieRefreshRow(int wave)
{
    auto zombies = GetMainObject()->zombieArray();
    for (int index = 0; index < GetMainObject()->zombieTotal(); ++index) {
        if (!zombies[index].isDisappeared() && !zombies[index].isDead() && zombies[index].existTime() == NowTime(wave)) {
            return zombies[index].row() + 1;
        }
    }
    return -1;
}

void ShovelAndPlantCobCannons(std::vector<Grid> cannon_list, int time_interval)
{
    if (GetMainObject()->gameClock() % time_interval != 0)
        return;
    auto seeds = GetMainObject()->seedArray();
    for (Grid each : cannon_list) {
        int present_sun = GetMainObject()->sun();
        int sun_cost = *(int*)(0x69F2C0 + COB_CANNON * 0x24) + *(int*)(0x69F2C0 + KERNEL_PULT * 0x24) * 2;
        // 在生存无尽模式中，场上每存在一个紫卡植物，其种植花费阳光数增加50
        auto plants = GetMainObject()->plantArray();
        for (int index = 0; index < GetMainObject()->plantTotal(); ++index) {
            if (plants[index].type() == COB_CANNON) {
                sun_cost += 50;
            }
        }
        int sun_down_bound = sun_cost + 300;
        int index_cob_cannon_seed = GetSeedIndex(COB_CANNON);
        bool is_usable_cob_cannon_seed = seeds[index_cob_cannon_seed].isUsable();
        int remaining_cd_cob_cannon = 5000 - seeds[index_cob_cannon_seed].cd();
        int index_kernel_pult_seed = GetSeedIndex(KERNEL_PULT);
        bool is_usable_kernel_pult_seed = seeds[index_kernel_pult_seed].isUsable();
        if (GetPlantIndex(each.row, each.col, COB_CANNON) < 0) {
            if (GetPlantIndex(each.row, each.col, KERNEL_PULT) < 0) {
                if (present_sun >= sun_down_bound && (remaining_cd_cob_cannon < 750 || is_usable_cob_cannon_seed) && is_usable_kernel_pult_seed) {
                    if (GetPlantIndex(each.row, each.col) >= 0) {
                        ShovelNotInQueue(each.row, each.col);
                    }
                    CardNotInQueue(index_kernel_pult_seed + 1, each.row, each.col);
                }
            } else {
                if (is_usable_kernel_pult_seed) {
                    if (GetPlantIndex(each.row, each.col + 1) >= 0) {
                        ShovelNotInQueue(each.row, each.col + 1);
                    }
                    CardNotInQueue(index_kernel_pult_seed + 1, each.row, each.col + 1);
                    CardNotInQueue(index_cob_cannon_seed + 1, each.row, each.col);
                }
            }
            break;
        }
    }
}
void PressReductionCob()
{
    if (GetMainObject()->gameClock() % 377 != 0)
        return;
    auto zombies = GetMainObject()->zombieArray();
    int zombies_num_in_the_row_2 = 0;
    int zombies_num_in_the_row_3 = 0;
    int zombies_num_in_the_row_5 = 0;
    int zombies_hp_in_the_row_2 = 0;
    int zombies_hp_in_the_row_3 = 0;
    int zombies_hp_in_the_row_5 = 0;
    for (int index = 0; index < GetMainObject()->zombieTotal(); ++index) {
        if (!zombies[index].isDisappeared() && !zombies[index].isDead() && zombies[index].row() + 1 == 2 && zombies[index].abscissa() <= 8 * 80.0) {
            zombies_num_in_the_row_2++;
            zombies_hp_in_the_row_2 += zombies[index].hp() + zombies[index].oneHp() + zombies[index].twoHp() / 5;
        }
    }
    for (int index = 0; index < GetMainObject()->zombieTotal(); ++index) {
        if (!zombies[index].isDisappeared() && !zombies[index].isDead() && zombies[index].row() + 1 == 3 && zombies[index].abscissa() <= 765) {
            zombies_num_in_the_row_3++;
            zombies_hp_in_the_row_3 += zombies[index].hp() + zombies[index].oneHp() + zombies[index].twoHp() / 5;
        }
    }
    for (int index = 0; index < GetMainObject()->zombieTotal(); ++index) {
        if (!zombies[index].isDisappeared() && !zombies[index].isDead() && zombies[index].row() + 1 == 5 && zombies[index].abscissa() <= 8 * 80.0) {
            zombies_num_in_the_row_5++;
            zombies_hp_in_the_row_5 += zombies[index].hp() + zombies[index].oneHp() + zombies[index].twoHp() / 5;
        }
    }
    int index_ready_pao = -1;
    auto plants = GetMainObject()->plantArray();
    for (int index = 0; index < GetMainObject()->plantTotal(); ++index) {
        if (plants[index].type() == COB_CANNON && plants[index].state() == 37) {
            index_ready_pao = index;
            break;
        }
    }
    if (index_ready_pao >= 0) {
        if (zombies_num_in_the_row_2 >= 3 || zombies_hp_in_the_row_2 > 1370 || zombies_num_in_the_row_3 >= 3 || zombies_hp_in_the_row_3 > 1370) {
            SafeClick();
            Asm::shootPao(80 * 8, 55 + 85 * 2, index_ready_pao);
            SafeClick();
        } else if (zombies_num_in_the_row_5 >= 3 || zombies_hp_in_the_row_5 > 1370) {
            SafeClick();
            Asm::shootPao(80 * 7, 55 + 85 * 5, index_ready_pao);
            SafeClick();
        }
    }
}
vector<float> GetZombieAbsccisas(int index_zombie, int time_length)
{
    vector<float> zombie_walk_a = {-9.8, -8.4, -7, -5.6, -4.1, -2.7, -1.3, 0, 1.4, 2.8, 4.2, 5.7, 7.1, 7.9, 8.8, 9.7, 10.5, 10.6, 10.8, 10.9, 11, 11, 11, 11, 11, 13.4, 15.8, 18.1, 20.5, 22.8, 25.2, 27.6, 29.9, 31.1, 32.3, 33.5, 34.6, 35.9, 37, 38.2, 39.4, 39.5, 39.6, 39.7, 39.8, 39.9, 40};
    vector<float> zombie_walk_b = {-9.8, -8.5, -7.3, -6, -4.7, -3.4, -2.1, -0.9, 0.3, 1.6, 2.8, 4.1, 5.4, 6.7, 8, 9.2, 10.5, 10.6, 10.7, 10.7, 10.8, 10.8, 10.9, 11, 12.8, 14.5, 16.3, 18.1, 19.9, 21.6, 23.4, 25.2, 27, 28.8, 30.5, 32.3, 34, 35.9, 37.6, 39.4, 39.5, 39.5, 39.6, 39.8, 39.9, 39.9, 40};
    vector<float> zombie_dance = {-9.8, -9.4, -8.9, -8.4, -7.9, -7.5, -7, -6.5, -6.1, -5.6, -5.1, -4.7, -4.2, -3.7, -3.3, -2.8, -2.3, -1.8, -1.4, -0.9, -0.4, 0, 0.3, 0.8, 1.3, 1.8, 2.2, 2.6, 3.1, 3.6, 4.1, 4.6, 5, 5.5, 6, 6.5, 6.9, 7.3, 7.8, 8.3, 8.8, 9.3, 9.7, 10.2, 10.7, 11.1, 11.6, 12.1, 12.6, 13};
    SafePtr<ZombieAdd> zombies = (ZombieAdd*)(GetMainObject()->zombieArray());
    SafePtr<AnimationAdd> animations = (AnimationAdd*)(GetPvzBase()->animationMain()->animationOffset()->animationArray());
    int index_animation = zombies[index_zombie].animationCode();
    int begin_frame = animations[index_animation].beginFrame();
    vector<float> zombie_walk;
    switch (begin_frame) {
    case 44:
        zombie_walk.assign(zombie_walk_a.begin(), zombie_walk_a.end());
        break;
    case 91:
        zombie_walk.assign(zombie_walk_b.begin(), zombie_walk_b.end());
        break;
    case 454:
        zombie_walk.assign(zombie_dance.begin(), zombie_dance.end());
        break;
    default:
        break;
    }
    float total_movement = zombie_walk.back() - zombie_walk.front();
    int frame_number = zombie_walk.size();
    float zombie_speed = zombies[index_zombie].speed();
    float frame_speed = zombie_speed * 47 * frame_number * 0.01 / total_movement;
    float circulation_rate = animations[index_animation].circulationRate();
    float circulation_rate_change = zombie_speed * 47 * 0.01 / total_movement;
    float zombie_abscissa = zombies[index_zombie].abscissa();
    vector<float> result;
    result.emplace_back(zombie_abscissa);
    int index_present_frame = 0;
    float present_movement = 0;
    for (int time = 0; time < time_length; ++time) {
        index_present_frame = (int)(circulation_rate * (frame_number - 1) + 1);
        present_movement = frame_speed * (zombie_walk[index_present_frame] - zombie_walk[index_present_frame - 1]);
        zombie_abscissa -= present_movement;
        result.emplace_back(zombie_abscissa);
        circulation_rate += circulation_rate_change;
        circulation_rate = circulation_rate > 1 ? circulation_rate - 1 : circulation_rate;
    }
    return result;
}
void SeparateLastZombie(int wave)
{
    InsertTimeOperation(0, wave, [=]() {
        struct ZombieEnterMovement {
            int index;
            int row;
            vector<float> absccisas;
            int enter_time;
        };
        vector<ZombieEnterMovement> zombie_enter_movements;
        auto zombies = GetMainObject()->zombieArray();
        ZombieEnterMovement temp = {};
        for (int index = 0; index < GetMainObject()->zombieTotal(); ++index) {
            if (!zombies[index].isDisappeared() && !zombies[index].isDead() && zombies[index].existTime() == NowTime(wave) && (zombies[index].type() == ZOMBIE || zombies[index].type() == CONEHEAD_ZOMBIE || zombies[index].type() == BUCKETHEAD_ZOMBIE || zombies[index].type() == SCREEN_DOOR_ZOMBIE)) {
                temp.index = index;
                temp.row = zombies[index].row() + 1;
                temp.absccisas = GetZombieAbsccisas(index, 820);
                for (int t = 0; t <= 820; ++t) {
                    if (temp.absccisas[t] < 765) {
                        temp.enter_time = t;
                        break;
                    }
                }
                zombie_enter_movements.emplace_back(temp);
            }
        }
        int max_enter_time = zombie_enter_movements[0].enter_time;
        for (int i = 0; i < zombie_enter_movements.size(); ++i) {
            if (zombie_enter_movements[i].enter_time > max_enter_time) {
                max_enter_time = zombie_enter_movements[i].enter_time;
            }
        }
        if (max_enter_time > 373) {
            SetTime(max_enter_time - 1 - 373, wave);
            pao_operator.pao({{2, 8.8}, {5, 8.8}});
        } else {
            //灰烬的作用范围是圆，所以对本行、上行、和下行的能打击到的僵尸的横坐标范围不同，因此选择最右僵尸时，应根据其(横坐标+落点行炮距-本行炮距)判断
            const int cannon_left_length_of_zombie_at_up_row = 71;
            const int cannon_left_length_of_zombie_at_the_row = 79;
            const int cannon_left_length_of_zombie_at_down_row = 78;
            float max_absccisa = 0;
            float cannon_left_length_of_zombie_offset = 0;
            float cannon_drop_absccisa = 0;
            for (int i = 0; i < zombie_enter_movements.size(); ++i) {
                if (zombie_enter_movements[i].row == 1 || zombie_enter_movements[i].row == 4) {
                    cannon_left_length_of_zombie_offset = cannon_left_length_of_zombie_at_the_row - cannon_left_length_of_zombie_at_up_row;
                } else if (zombie_enter_movements[i].row == 2 || zombie_enter_movements[i].row == 5) {
                    cannon_left_length_of_zombie_offset = 0;
                } else if (zombie_enter_movements[i].row == 3 || zombie_enter_movements[i].row == 6) {
                    cannon_left_length_of_zombie_offset = cannon_left_length_of_zombie_at_the_row - cannon_left_length_of_zombie_at_down_row;
                }
                if (zombie_enter_movements[i].absccisas[373] + cannon_left_length_of_zombie_offset > max_absccisa) {
                    max_absccisa = zombie_enter_movements[i].absccisas[373] + cannon_left_length_of_zombie_offset;
                    cannon_drop_absccisa = max_absccisa - cannon_left_length_of_zombie_at_the_row + 7 - 1;
                }
            }
            SetTime(0, wave);
            pao_operator.recoverPao({{2, cannon_drop_absccisa / 80}, {5, cannon_drop_absccisa / 80}});
        }
    });
}
void Begin1()
{
    SelectCards({SUNFLOWER, M_SUNFLOWER, TWIN_SUNFLOWER, POTATO_MINE, GARLIC, TALL_NUT, LILY_PAD, KERNEL_PULT, COB_CANNON, SNOW_PEA});
    SetTime(-1799, 1);
    tick_planter.start();
    press_reductioner.pushFunc(PressReductionCob);
    // wave 1 智能土豆地雷，陆路后场的向日葵
    InsertTimeOperation(-1799, 1, [=]() {
        tick_planter.delayPlantNotInQuene(SUNFLOWER, {{1, 1}, {2, 1}, {1, 2}, {2, 2}});
        tick_planter.delayPlantNotInQuene(M_SUNFLOWER, {{5, 1}, {6, 1}, {5, 2}, {6, 2}});
    });
    InsertTimeOperation(0, 1, [=]() {
        tick_planter.waitPlantNotInQuene(POTATO_MINE, {{GetZombieRefreshRow(1), 5}});
    });
    // wave 2 智能土豆地雷
    InsertTimeOperation(0, 2, [=]() {
        tick_planter.waitPlantNotInQuene(POTATO_MINE, {{GetZombieRefreshRow(2), 4}});
        tick_planter.delayPlantNotInQuene(SUNFLOWER, {{1, 3}, {2, 3}});
        tick_planter.delayPlantNotInQuene(M_SUNFLOWER, {{5, 3}, {6, 3}});
    });
    // wave 3, 4 智能大蒜、土豆地雷、寒冰射手、高坚果
    InsertTimeOperation(0, 3, [=]() {
        int zombie_row = GetZombieRefreshRow(3);
        int garlic_row = zombie_row <= 2 ? 1 : 6;
        int snow_pea_row = zombie_row <= 2 ? 2 : 5;
        tick_planter.waitPlantNotInQuene(GARLIC, {{garlic_row, 9}});
        InsertTimeOperation(500, 3, [=]() {
            tick_planter.waitPlantNotInQuene(TALL_NUT, {{snow_pea_row, 7}});
        });
        InsertTimeOperation(900, 3, [=]() {
            tick_planter.waitPlantNotInQuene(SNOW_PEA, {{snow_pea_row, 6}});
        });
        InsertTimeOperation(0, 4, [=]() {
            tick_planter.waitPlantNotInQuene(GARLIC, {{garlic_row == 6 ? 1 : 6, 9}});
            tick_planter.waitPlantNotInQuene(TALL_NUT, {{snow_pea_row == 5 ? 2 : 5, 7}});
            tick_planter.waitPlantNotInQuene(SNOW_PEA, {{snow_pea_row == 5 ? 2 : 5, 6}});
        });
    });
    // wave 4 边路向日葵、睡莲叶
    InsertTimeOperation(1, 4, [=]() {
        tick_planter.delayPlantNotInQuene(SUNFLOWER, {{1, 4}, {1, 5}, {1, 6}, {1, 7}, {1, 8}, {2, 4}, {2, 5}, {4, 3}});
        tick_planter.delayPlantNotInQuene(M_SUNFLOWER, {{6, 4}, {6, 5}, {6, 6}, {6, 7}, {6, 8}, {5, 4}, {5, 5}, {4, 4}});
        tick_planter.delayPlantNotInQuene(LILY_PAD, {{4, 8}, {3, 7}, {4, 7}, {3, 6}, {4, 6}, {5, 6}, {3, 5}, {4, 5}, {4, 3}, {4, 4}, {3, 1}, {3, 2}, {4, 1}, {4, 2}, {3, 3}, {3, 4}});
    });
    // wave 5 水路大蒜、南瓜头、寒冰射手、向日葵
    InsertTimeOperation(1, 5, [=]() {
        tick_planter.waitPlantNotInQuene(LILY_PAD, {{4, 9}});
        tick_planter.waitPlantNotInQuene(GARLIC, {{4, 9}});
        tick_planter.waitPlantNotInQuene(LILY_PAD, {{3, 9}});
        tick_planter.waitPlantNotInQuene(TALL_NUT, {{3, 9}});
        tick_planter.waitPlantNotInQuene(LILY_PAD, {{3, 8}});
        tick_planter.waitPlantNotInQuene(SNOW_PEA, {{3, 8}});
        tick_planter.delayPlantNotInQuene(SUNFLOWER, {{3, 7}, {3, 6}, {3, 5}, {3, 4}, {3, 3}});
        tick_planter.delayPlantNotInQuene(M_SUNFLOWER, {{4, 8}, {4, 7}, {4, 6}, {4, 5}});
    });
    // wave 6 开启高坚果和大蒜修补
    InsertTimeOperation(0, 6, [=]() {
        SetTime(0, 6);
        tall_nut_fixer1.start(TALL_NUT, {{2, 7}, {5, 7}}, 1800);
        tall_nut_fixer2.start(TALL_NUT, {{3, 9}}, 2500);
        garlic_fixer.start(GARLIC, {{1, 9}, {4, 9}, {6, 9}}, 80);
    });
    // wave 7 玉米加农炮、双子向日葵
    InsertTimeOperation(0, 7, [=]() {
        tick_planter.delayPlantNotInQuene(TWIN_SUNFLOWER, {{1, 7}, {3, 7}, {4, 7}, {4, 8}, {6, 7}});
        tick_planter.delayPlantNotInQuene(COB_CANNON, {{3, 1}, {4, 1}, {3, 3}, {4, 3}});
        cob_planter.pushFunc([]() {
            ShovelAndPlantCobCannons({{3, 1}, {4, 1}, {3, 3}, {4, 3}, {1, 1}, {2, 1}, {5, 1}, {6, 1}});
        });
    });
    // wave 19 拖收尾
    InsertTimeOperation(0, 19, [=]() {
        SetTime(0, 19);
        Shovel({{2, 6}, {3, 8}, {5, 6}});
        tick_planter.delayPlantNotInQuene(SUNFLOWER, {{2, 6}, {3, 8}});
        tick_planter.delayPlantNotInQuene(M_SUNFLOWER, {{5, 6}});
        tick_planter.delayPlantNotInQuene(TWIN_SUNFLOWER, {{3, 8}});
        press_reductioner.stop();
        pao_operator.autoGetPaoList();
        SeparateLastZombie(19);
        SetTime(4500 - 200 - 373, 19);
        pao_operator.autoGetPaoList();
        pao_operator.pao({{2, 8.8}, {5, 8.8}});
    });
    // wave 20 炮消珊瑚、拖收尾
    SetTime(223 - 373, 20);
    pao_operator.autoGetPaoList();
    pao_operator.pao(4, 7.5875);
    SetTime(0, 20);
    pao_operator.autoGetPaoList();
    SeparateLastZombie(20);
    SetTime(5500 - 200 - 373, 20);
    pao_operator.autoGetPaoList();
    pao_operator.pao({{2, 8.8}, {5, 8.8}});
}
void ReactCob(int time, int wave, int is_iced)
{
    // 各类型僵尸威胁7列普通植物的最早时间
    const vector<int> zombies_not_iced_all_killed_time = {1300, 1200, 1300, 800, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1000, 893, 1300, 640, 549, 729, 376, 376, 1300, 1300, 500, 546, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300};
    // 98厘秒冰时各类型僵尸威胁7列普通植物的最早时间
    const vector<int> zombies_iced_all_killed_time = {2400, 2300, 2400, 1800, 2400, 2400, 2400, 2400, 2400, 2400, 2400, 2100, 893, 2400, 1000, 949, 1570, 376, 900, 2400, 2400, 1200, 886, 2400, 2400, 2400, 2400, 2400, 2400, 2400, 2400, 2400, 2400};
    InsertTimeOperation(time, wave, [=]() {
        vector<int> zombies_all_killed_time = zombies_not_iced_all_killed_time;
        if (is_iced) {
            zombies_all_killed_time = zombies_iced_all_killed_time;
        }
        int activation_time = *max_element(zombies_all_killed_time.begin(), zombies_all_killed_time.end());
        bool is_exist_gargantuar_in_the_up_ground = false;
        bool is_exist_gargantuar_in_the_down_ground = false;
        auto zombies = GetMainObject()->zombieArray();
        for (int index = 0; index < GetMainObject()->zombieTotal(); ++index) {
            if (!zombies[index].isDisappeared() && !zombies[index].isDead() && zombies[index].existTime() == NowTime(wave)) {
                if (zombies_all_killed_time[zombies[index].type()] < activation_time) {
                    activation_time = zombies_all_killed_time[zombies[index].type()];
                }
                if (zombies[index].type() == GARGANTUAR) {
                    if (zombies[index].row() + 1 <= 2) {
                        is_exist_gargantuar_in_the_up_ground = true;
                    }
                    if (zombies[index].row() + 1 >= 5) {
                        is_exist_gargantuar_in_the_down_ground = true;
                    }
                }
            }
        }
        SetTime(activation_time - 376, wave);
        pao_operator.autoGetPaoList();
        pao_operator.pao({{2, 8.48}, {5, 8.48}});
        if (is_exist_gargantuar_in_the_up_ground) {
            if (!is_iced || (is_iced && activation_time >= 98 + 400)) {
                pao_operator.pao(2, 8.48);
            }
        }
        if (is_exist_gargantuar_in_the_down_ground) {
            if (!is_iced || (is_iced && activation_time >= 98 + 400)) {
                pao_operator.pao(5, 8.48);
            }
        }
        InsertTimeOperation(max(activation_time + 1, 401), wave, [=]() {
            if (wave == 9 || wave == 19 | wave == 20) {
                auto zombies = GetMainObject()->zombieArray();
                for (int index = 0; index < GetMainObject()->zombieTotal(); ++index) {
                    if (!zombies[index].isDisappeared() && !zombies[index].isDead() && zombies[index].existTime() == NowTime(wave)) {
                        ReactCob(max(activation_time + 1, 401), wave, is_iced);
                        break;
                    }
                }
                return;
            } else {
                if (GetRunningWave() == wave) {
                    ReactCob(max(activation_time + 1, 401), wave, is_iced);
                } else {
                    return;
                }
            }
        });
    });
}
void CobGargantuar(int time, int wave)
{
    InsertTimeOperation(max(0, time - 373), wave, [=]() {
        bool is_exist_gargantuar_in_the_up_ground = false;
        bool is_exist_gargantuar_in_the_down_ground = false;
        auto zombies = GetMainObject()->zombieArray();
        for (int index = 0; index < GetMainObject()->zombieTotal(); ++index) {
            if (!zombies[index].isDisappeared() && !zombies[index].isDead() && zombies[index].existTime() == NowTime(wave)) {
                if (zombies[index].type() == GARGANTUAR) {
                    if (zombies[index].row() + 1 <= 2) {
                        is_exist_gargantuar_in_the_up_ground = true;
                    }
                    if (zombies[index].row() + 1 >= 5) {
                        is_exist_gargantuar_in_the_down_ground = true;
                    }
                }
            }
        }
        if (is_exist_gargantuar_in_the_up_ground) {
            SetTime(time - 373, wave);
            pao_operator.pao(2, 8.8);
        }
        if (is_exist_gargantuar_in_the_down_ground) {
            SetTime(time - 373, wave);
            pao_operator.pao(5, 8.8);
        }
    });
}

void PlantToBlockTheZombies(int time, int wave, vector<int> zombie_types, int row, int shovel_time)
{
    InsertTimeOperation(time, wave, [=]() {
        auto zombies = GetMainObject()->zombieArray();
        bool is_exist_the_zombie = false;
        for (int index = 0; index < GetMainObject()->zombieTotal(); ++index) {
            if (zombies[index].row() == row - 1 && !zombies[index].isDisappeared() && !zombies[index].isDead()) {
                for (int type : zombie_types) {
                    if (zombies[index].type() == type) {
                        is_exist_the_zombie = true;
                        goto END;
                    }
                }
            }
        }
    END:
        auto seeds = GetMainObject()->seedArray();
        int index_seeds[] = {GetSeedIndex(PUFF_SHROOM), GetSeedIndex(PUFF_SHROOM, true), GetSeedIndex(SUN_SHROOM), GetSeedIndex(FLOWER_POT), GetSeedIndex(SCAREDY_SHROOM), GetSeedIndex(SUNFLOWER), GetSeedIndex(GARLIC), GetSeedIndex(FUME_SHROOM), GetSeedIndex(KERNEL_PULT), GetSeedIndex(CABBAGE_PULT)};
        if (is_exist_the_zombie) {
            for (int index : index_seeds) {
                if (index < 0) {
                    continue;
                }
                if (seeds[index].isUsable()) {
                    SetTime(time, wave);
                    Card(index + 1, row, 9);
                    SetTime(time + shovel_time, wave);
                    Shovel(row, 9);
                    break;
                }
            }
        }
        switch (row) {
        case 1:
            PlantToBlockTheZombies(time, wave, zombie_types, 2, shovel_time);
            break;
        case 2:
            PlantToBlockTheZombies(time, wave, zombie_types, 5, shovel_time);
            break;
        case 5:
            PlantToBlockTheZombies(time, wave, zombie_types, 6, shovel_time);
            break;
        default:
            return;
            break;
        }
    });
}
void StartFrountCannonPlant(vector<Grid> cannon_list, int start_sun, int wave)
{
    InsertTimeOperation(-200, wave, [=]() mutable {
        if (GetPlantIndex(6, 5, COB_CANNON) >= 0 && GetPlantIndex(2, 7, COB_CANNON) < 0 && GetMainObject()->sun() < start_sun && cob_planter.getStatus() == RUNNING) {
            cob_planter.pause();
            ice_filler.stop();
        } else if (GetPlantIndex(6, 5, COB_CANNON) >= 0 && GetMainObject()->sun() >= start_sun && cob_planter.getStatus() != RUNNING) {

            is_planting_frount_ground_cannon = true;
            SetTime(-200, wave);
            pumpkin_fixer.resetFixList({{3, 9}, {4, 9}});
            ice_filler.stop();
            ice_filler.start({{4, 9}});
            ShovelNotInQueue(1, 7, true);
            ShovelNotInQueue(2, 7, true);
            ShovelNotInQueue(5, 7, true);
            ShovelNotInQueue(6, 7, true);
            if (cob_planter.getStatus() == PAUSED) {
                cob_planter.goOn();
            } else if (cob_planter.getStatus() == STOPPED) {
                cob_planter.pushFunc([=]() {
                    ShovelAndPlantCobCannons(cannon_list);
                });
            }

        } else if ((GetPlantIndex(2, 7, COB_CANNON) >= 0 || GetPlantIndex(6, 5, COB_CANNON) < 0) && cob_planter.getStatus() != RUNNING) {
            cob_planter.pushFunc([=]() {
                ShovelAndPlantCobCannons(cannon_list);
            });
        }
    });
    if (wave + 1 <= 20) {
        StartFrountCannonPlant(cannon_list, start_sun, wave + 1);
    } else {
        return;
    }
}
void Begin2()
{
    if (GetPlantIndex(2, 7, COB_CANNON) >= 0) {
        SelectCards({PUMPKIN, KERNEL_PULT, COB_CANNON, PUFF_SHROOM, M_PUFF_SHROOM, SUN_SHROOM, FLOWER_POT, SCAREDY_SHROOM, SUNFLOWER, GARLIC});
    } else {
        SelectCards({KERNEL_PULT, COB_CANNON, COFFEE_BEAN, ICE_SHROOM, M_ICE_SHROOM, PUMPKIN, PUFF_SHROOM, FLOWER_POT, SUNFLOWER, TWIN_SUNFLOWER});
    }
    InsertTimeOperation(-599, 1, [=]() mutable {
        if (GetPlantIndex(2, 7, COB_CANNON) >= 0) {
            is_planting_frount_ground_cannon = true;
        }

        if (!is_planting_frount_ground_cannon) {
            SetTime(-599, 1);
            Shovel({{1, 8}, {6, 8}, {1, 9}, {6, 9}});
            tick_planter.start();
            ice_filler.start({{2, 7}, {5, 7}});
            pumpkin_fixer.start(PUMPKIN, {{4, 9}, {3, 9}, {1, 7}, {6, 7}, {2, 7}, {5, 7}}, 1300);
            if ((GetPlantIndex(2, 7, ICE_SHROOM) < 0 && GetPlantIndex(2, 7, IMITATOR) < 0)) {
                ShovelNotInQueue(2, 7);
            }
            if (GetPlantIndex(5, 7, ICE_SHROOM) < 0 && GetPlantIndex(5, 7, IMITATOR) < 0) {
                ShovelNotInQueue(5, 7);
            }
            if (GetPlantIndex(4, 9, TWIN_SUNFLOWER) < 0) {
                ShovelNotInQueue(4, 9);
                tick_planter.delayPlantNotInQuene(SUNFLOWER, {{4, 9}});
                tick_planter.delayPlantNotInQuene(TWIN_SUNFLOWER, {{4, 9}});
            }
            if (GetPlantIndex(3, 9, TWIN_SUNFLOWER) < 0) {
                ShovelNotInQueue(3, 9);
                tick_planter.delayPlantNotInQuene(SUNFLOWER, {{3, 9}});
                tick_planter.delayPlantNotInQuene(TWIN_SUNFLOWER, {{3, 9}});
            }
        } else {
            pumpkin_fixer.start(PUMPKIN, {{4, 9}, {3, 9}}, 1300);
        }
    });
    StartFrountCannonPlant({{3, 1}, {4, 1}, {3, 3}, {4, 3}, {1, 1}, {2, 1}, {5, 1}, {6, 1}, {1, 3}, {2, 3}, {5, 3}, {6, 3}, {1, 5}, {2, 5}, {3, 5}, {4, 5}, {5, 5}, {6, 5}, {2, 7}, {5, 7}, {1, 7}, {6, 7}, {3, 7}, {4, 7}}, 8000);
    // 非20波
    for (wave : {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19}) {
        InsertTimeOperation(-200, wave, [=]() {
            if (is_planting_frount_ground_cannon) {
                if (wave == 10) {
                    PlantToBlockTheZombies(231, wave, {DANCING_ZOMBIE}, 1, 79);
                    SetTime(398 - 376, wave);
                    pao_operator.autoGetPaoList();
                    pao_operator.pao({{2, 8.75}, {5, 8.75}});
                } else {
                    PlantToBlockTheZombies(191, wave, {DANCING_ZOMBIE}, 1, 79);
                    SetTime(377 - 376, wave);
                    pao_operator.autoGetPaoList();
                    pao_operator.pao({{2, 8.8}, {5, 8.8}});
                }
                CobGargantuar(373, wave);
                InsertTimeOperation(1202 - 200 - 373, wave, [=]() {
                    bool is_exist_zombie = false;
                    auto zombies = GetMainObject()->zombieArray();
                    for (int index = 0; index < GetMainObject()->zombieTotal(); ++index) {
                        if (!zombies[index].isDisappeared() && !zombies[index].isDead()) {
                            is_exist_zombie = true;
                            break;
                        }
                    }
                    if (GetRunningWave() == wave || wave == 9 || wave == 19) {
                        SetTime(1202 - 200 - 373, wave);
                        pao_operator.autoGetPaoList();
                        pao_operator.pao({{2, 8.8}, {5, 8.8}});
                    }
                });
            } else {
                bool is_used_ice = false;
                if (GetPlantIndex(2, 7, ICE_SHROOM) >= 0 || GetPlantIndex(5, 7, ICE_SHROOM) >= 0) {
                    SetTime(-200, wave);
                    ice_filler.coffee();
                    is_used_ice = true;
                }
                ReactCob(0, wave, is_used_ice);
                if (!is_used_ice) {
                    PlantToBlockTheZombies(191, wave, {DANCING_ZOMBIE}, 1, 79);
                }
            }
        });
    }
    // 20波
    for (wave : {20}) {
        // 炮消珊瑚
        SetTime(223 - 373, wave);
        pao_operator.autoGetPaoList();
        pao_operator.pao(4, 7.5875);
        CobGargantuar(373, wave);
        SetTime(398 - 376, wave);
        pao_operator.autoGetPaoList();
        pao_operator.pao({{2, 8.75}, {5, 8.75}});
        PlantToBlockTheZombies(231, wave, {DANCING_ZOMBIE}, 1, 79);
        InsertTimeOperation(0, wave, [=]() {
            if (is_planting_frount_ground_cannon) {
                SetTime(1089 - 373, wave);
                pao_operator.autoGetPaoList();
                pao_operator.pao({{2, 8.8}, {5, 8.8}});
            } else {
                SeparateLastZombie(wave);
                SetTime(5500 - 200 - 373, wave);
                pao_operator.autoGetPaoList();
                pao_operator.pao({{2, 8.8}, {5, 8.8}});
            }
        });
    }
}
void RunThePlant()
{
    if (GetZombieTypeList()[GIGA_GARGANTUAR]) {
        if (GetZombieTypeList()[GARGANTUAR]) {
            SelectCards({ICE_SHROOM, M_ICE_SHROOM, COFFEE_BEAN, CHERRY_BOMB, PUFF_SHROOM, SUN_SHROOM, SCAREDY_SHROOM, FLOWER_POT, PUMPKIN, WALL_NUT});
        } else {
            SelectCards({WALL_NUT, PUMPKIN, PUFF_SHROOM, M_PUFF_SHROOM, SUN_SHROOM, SCAREDY_SHROOM, FLOWER_POT, SUNFLOWER, GARLIC, FUME_SHROOM});
        }
    } else {
        SelectCards({WALL_NUT, PUMPKIN, LILY_PAD, ICE_SHROOM, CHERRY_BOMB, SQUASH, PUFF_SHROOM, M_PUFF_SHROOM, SUN_SHROOM, FLOWER_POT});
    }
    // 20波是否需要使用樱桃炸弹
    is_need_cherry_bomb = false;
    // 本轮累计刷出的红眼巨人僵尸数量
    the_number_of_have_refreshed_giga_gargantuar = 0;
    SetTime(-599, 1);
    InsertOperation([=]() {
        if (GetPlantIndex(4, 9, ICE_SHROOM) < 0) {
            ShovelNotInQueue(4, 9);
        }
    });
    ice_filler.start({{4, 9}, {3, 9}});
    plant_fixer.start(PUMPKIN, {{3, 9}, {4, 9}}, 1200);
    pao_operator.resetPaoList({{1, 1}, {6, 1}, {1, 3}, {6, 3}, {1, 5}, {6, 5}, {1, 7}, {6, 7}, {2, 1}, {5, 1}, {2, 3}, {5, 3}, {2, 5}, {5, 5}, {2, 7}, {5, 7}, {3, 1}, {4, 1}, {3, 3}, {4, 3}, {3, 5}, {4, 5}, {3, 7}, {4, 7}});

    if (GetZombieTypeList()[GIGA_GARGANTUAR]) {
        if (GetZombieTypeList()[GARGANTUAR]) {
            GigaGargantuarAndGargantuar(1);
        } else {
            GigaGargantuarAndNoGargantuar(1);
        }
    } else {
        NoGigaGargantuar(1);
    }
    // 炮消珊瑚
    InsertTimeOperation(223 - 373, 20, [=]() {
        is_need_cherry_bomb = GetNumberofCobCannonBeReady() < 8 ? true : false;
        ShootCoralZombies(is_need_cherry_bomb);
    });
}