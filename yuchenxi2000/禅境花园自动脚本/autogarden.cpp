// 禅境花园自动脚本 by yuchenxi2000
// 进花园自动浇水/施肥/杀虫/放音乐/捡钱
//
// 功能开关：
// 按Q开关脚本；按M重置商店里金盏花购买日期；按P给你一株盆栽（可在弹出窗口中选择植物类型）；按G让所有植物立即长大（你可能要重新进一下花园）
// 按I显示所有植物编号，金盏花额外显示颜色代码；按U关闭安全模式，此时你可以通过按P得到任意编号的盆栽，但有崩溃风险
// 按R拯救你的花园，如果你按U得到了一颗非法植物，那么点击花园图标就会崩游戏，此时在主界面按R就能删掉所有编号不正常的植物
//
// 请无视VS Code的警告，脚本能正常编译。
// 定义DEBUG宏进入开发者模式，此时按D在命令行里输出盆栽信息，且按P时不会判断植物ID是否合法（可能导致崩溃！）。按T在花园里展示所有植物，共六大类植物，但不要在主玩存档使用，因为会覆盖你的所有植物！
#include <avz.h>
#include <windows.h>

// Constructable version of APvzStruct
class CPvzStruct {
public:
    template <typename T = CPvzStruct>
    __ANodiscard T& MRef(uintptr_t addr) noexcept {
        return (T&)((uint8_t*)this)[addr];
    }

    template <typename T = CPvzStruct>
    __ANodiscard T* MPtr(uintptr_t addr) noexcept {
        return *(T**)((uint8_t*)this + addr);
    }

    template <typename T = CPvzStruct*>
    __ANodiscard T MVal(uintptr_t addr) noexcept {
        return (T)((uint8_t*)this + addr);
    }

    // MRef<T>(0x1, 0x2, 0x3) 形式
    template <typename T = CPvzStruct, typename... Others>
    __ANodiscard T& MRef(uintptr_t first, Others... others) noexcept {
        return MPtr(first)->MRef<T>(others...);
    }

    template <typename T = CPvzStruct, typename... Others>
    __ANodiscard T* MPtr(uintptr_t first, Others... others) noexcept {
        return MPtr(first)->MPtr<T>(others...);
    }

    template <typename T = CPvzStruct*, typename... Others>
    __ANodiscard T MVal(uintptr_t first, Others... others) noexcept {
        return MPtr(first)->MVal<T>(others...);
    }

    template <typename T>
    void Write(const std::vector<T>& vec) {
        std::copy(vec.begin(), vec.end(), (T*)this);
    }

    template <typename T, typename Iter>
    void Write(Iter&& begin, Iter&& end) {
        std::copy(begin, end, (T*)this);
    }

    template <typename T>
    __ANodiscard auto Read(std::size_t size) {
        std::vector<T> vec(size);
        T* ptr = (T*)this;
        std::copy(ptr, ptr + size, vec.begin());
        return vec;
    }
};

bool IsPotIDValid(int potID) {
    // 这些是怎么玩都不会导致游戏崩溃的植物编号，包括可通过正常方法获得的，以及只能通过作弊调出来的
    // 一些放着不会崩溃，但是用手套/卖出会崩溃的植物不包括在内
    if (potID >= 0 && potID <= 52) {
        return true;
    }
    std::vector<int> discreteCases = {58,59,60,61,63,64,66,69,70,71,72,73,79,81,82,83,84,85,86,87,89,90,92,93,94,95};
    return std::find(discreteCases.begin(), discreteCases.end(), potID) != discreteCases.end();
}

// 花园花盆属性
struct APotPlant : public CPvzStruct {
protected:
    uint8_t _data[0x58];

public:
    APotPlant() {
        memset(_data, 0, sizeof(_data));
    }
    // 盆栽ID是否合法？
    bool HasValidID() {
        return IsPotIDValid(Type());
    }
    // 植物类型
    __ANodiscard int& Type() noexcept {
        return MRef<int>(0x0);
    }
    // 0：主花园
    // 1：蘑菇园
    // 3：水族馆
    __ANodiscard int& Location() noexcept {
        return MRef<int>(0x4);
    }
    __ANodiscard int& Col() noexcept {
        return MRef<int>(0x8);
    }
    __ANodiscard int& Row() noexcept {
        return MRef<int>(0xc);
    }
    // 盆栽植物朝向
    // 0：正常方向，向右
    // 1：向左
    __ANodiscard int& isReversed() noexcept {
        return MRef<int>(0x10);
    }
    // 金盏花颜色
    // 0：不是金盏花
    // 2：白色
    // 3：品红
    // 4：橙色
    // 5：粉色
    // 6：淡蓝
    // 7：红色
    // 8：蓝色
    // 9：紫色
    // 10：淡紫
    // 11：黄色
    // 12：绿色
    __ANodiscard int& Color() noexcept {
        return MRef<int>(0x20);
    }
    // 生长阶段
    // 0-3，从芽阶段到完全成熟
    __ANodiscard int& Age() noexcept {
        return MRef<int>(0x24);
    }
    // 浇了几次水
    __ANodiscard int& WaterCnt() noexcept {
        return MRef<int>(0x28);
    }
    // 一共要浇几次
    __ANodiscard int& MaxWaterCnt() noexcept {
        return MRef<int>(0x2c);
    }
    // 3：杀虫
    // 4：留声机
    __ANodiscard int& Requirement() noexcept {
        return MRef<int>(0x30);
    }
};

bool unsafeMode = false;
bool plotPotID = false;

// 给禅境花园新增一株盆栽
void GivePotPlant(int plantType, int isReversed, int color = 0) {
#ifndef DEBUG
    // sanity check
    if (!unsafeMode && (!IsPotIDValid(plantType) || isReversed < 0 || isReversed > 1)) {
        return;
    }
#endif
    APotPlant potPlant;
    potPlant.Type() = plantType;
    potPlant.isReversed() = isReversed;
    potPlant.Color() = color;
    potPlant.MaxWaterCnt() = 3;
    // 我不知道0x81C地址处是什么，lmintlcx站里的地址表也没有，反正参数是这么传的，it just works
    asm volatile(
        "movl %[potPlantRef], %%edx;"
        "movl 0x6A9EC0, %%eax;"
        "movl 0x81C(%%eax), %%eax;"
        "pushl %%eax;"
        "movl $0x51D8C0, %%eax;"
        "call *%%eax;"
        :
        : [potPlantRef] "rm"(&potPlant)
        : ASaveAllRegister);
}

int & AGetPotPlantNum() {
    return AMRef<int>(0x6A9EC0, 0x82c, 0x350);
}

APotPlant * AGetPotPlantArray() {
    return AMVal<APotPlant *>(0x6A9EC0, 0x82c, 0x358);
}

bool AHasMusicPlayer() {
    return AMRef<bool>(0x6A9EC0, 0x82c, 0x200);
}

int AGetFertilizerNum() {
    return AMRef<int>(0x6A9EC0, 0x82c, 0x1F8) - 1000;
}

int AGetInsecticideNum() {
    return AMRef<int>(0x6A9EC0, 0x82c, 0x1FC) - 1000;
}

void ResetMarigoldBuyDate() {
    // 重置金盏花购买日期
    AMRef<int>(0x6A9EC0, 0x82c, 0x1E8) = 0;
    AMRef<int>(0x6A9EC0, 0x82c, 0x1EC) = 0;
    AMRef<int>(0x6A9EC0, 0x82c, 0x1F0) = 0;
}

// 我不明白宝开程序员的脑子想的什么
// 明明都是表示盆栽所在位置，为什么用不一样的enum？而且毫无规律
bool PotPlantLocationMatch(APotPlant & pot, int scene) {
    if (pot.Location() == 0 && scene == 7) {
        return true;
    }
    if (pot.Location() == 1 && scene == 6) {
        return true;
    }
    if (pot.Location() == 3 && scene == 8) {
        return true;
    }
    return false;
}

// 请无视VS Code的警告，它们能正常编译
void SelectTool(AMainObject* level, int toolType) {
    asm volatile(
        "movl %[level], %%ebx;"
        "movl %[toolType], %%edx;"
        "movl $0x411C10, %%eax;"
        "call *%%eax;"
        :
        : [toolType] "rm"(toolType), [level] "rm"(level)
        : ASaveAllRegister);
}

// 我搞不懂这几个函数有什么区别，因为它们貌似能实现同样的功能？都是使用工具。
// 现在只用了ollydbg调试，什么时候用IDA反汇编一下看看
void UseTool(AMainObject* level, int holdItem, int x, int y, int key) {
    asm volatile(
        "movl %[y], %%ecx;"
        "movl %[x], %%edx;"
        "pushl %[holdItem];"
        "pushl %[key];"
        "movl %[level], %%eax;"
        "movl $0x411060, %%edi;"
        "call *%%edi;"
        :
        : [key] "rm"(key), [y] "rm"(y), [x] "rm"(x), [level] "rm"(level), [holdItem] "rm"(holdItem)
        : ASaveAllRegister);
}

void UseTool_51F580(AMainObject* level, int holdItem, int x, int y, int key) {
    asm volatile(
        "movl %[holdItem], %%eax;"
        "pushl %[y];"
        "movl 0x6a9ec0, %%esi;"
        "movl 0x81c(%%esi), %%ecx;"
        "pushl %[x];"
        "movl $0x51F580, %%edx;"
        "call *%%edx;"
        :
        : [y] "rm"(y), [x] "rm"(x), [holdItem] "rm"(holdItem)
        : ASaveAllRegister);
}

void UseTool_51EB70(AMainObject* level, int holdItem, int x, int y, int key) {
    asm volatile(
        "pushl %[holdItem];"
        "pushl %[y];"
        "pushl %[x];"
        "movl 0x6a9ec0, %%eax;"
        "movl 0x81c(%%eax), %%eax;"
        "movl $0x51eb70, %%ebx;"
        "call *%%ebx;"
        :
        : [y] "rm"(y), [x] "rm"(x), [holdItem] "rm"(holdItem)
        : ASaveAllRegister);
}

class AutoTool {
public:
    // 0: usable; 1: to be use; 2: cooling down
    int state;
    int toolID;
    int coolDown;
    int coolDownMax;
    int xi;
    int yi;
    bool enabled;
    static int lock;
    AutoTool(int toolID, int coolDownMax) : toolID(toolID), coolDownMax(coolDownMax) {
        enabled = true;
        state = 0;
        lock = 0;
    }
    void Switch() {
        enabled = !enabled;
    }
    void Reset() {
        state = 0;
        lock = 0;
        coolDown = 0;
    }
    void Start() {
        if (!enabled) {
            return;
        }
        if (state == 1) {
            int holdTool = AGetMainObject()->MouseAttribution()->Type();
            if (holdTool != 0) {
                UseTool_51EB70(AGetMainObject(), holdTool, xi, yi, 1);
                lock = 0;
                state = 2;
                coolDown = coolDownMax;
            } else {
                SelectTool(AGetMainObject(), toolID);
                AAsm::MouseMove(xi, yi);
            }
        } else if (state == 2) {
            if (coolDown == 0) {
                state = 0;
            } else {
                coolDown--;
            }
        }
    }
    bool isUsable() {
        return state == 0 && lock == 0;
    }
    bool Use(int xi, int yi) {
        if (!enabled) {
            return false;
        }
        if (isUsable()) {
            SelectTool(AGetMainObject(), toolID);
            // 单纯为了让PvZ有一帧的反应时间，不然会在错误的地方使用工具。
            // 发个假信息让PvZ以为我们把鼠标移动到给定位置
            AAsm::MouseMove(xi, yi);
            this->xi = xi;
            this->yi = yi;
            state = 1;
            lock = 1;
            return true;
        }
        return false;
    }
};

int AutoTool::lock = 0;

// 能在禅境花园里用的painter
class __MyABasicPainter : public __ABasicPainter, AOrderedBeforeExitHook<-1> {
public:
    virtual void _BeforeScript() override {}
    virtual void _ExitFight() override {
        // 由于AvZ内置的painter会卸载一个hook，因此我只能把它加回来。。说的就是你，aPainter
        __ABasicPainter::_BeforeScript();
    }
    virtual void _AfterInject() override {
        __ABasicPainter::_AfterInject();
        // AvZ不在禅境花园关卡加载脚本，只能这样了
        __ABasicPainter::_BeforeScript();
    }
    // 没这个第二次注入会崩溃，因为原本的painter加了个hook指向dll内部函数，第二次注入时先卸载原dll后加载新dll，卸载后游戏因为找不到hook的函数所以崩溃
    // 记得要继承AOrderedBeforeExitHook
    virtual void _BeforeExit() override {
        __ABasicPainter::_ExitFight();
    }
};

__MyABasicPainter _basicPainter;

// 反正我只用画一段文字，直接化身CV工程师
static bool __isInPaintTickRunner = false;
void MyDraw(const AText& posText, int duration, float layer, DWORD _textColor = AArgb(0xff, 0, 0xff, 0xff)) {
    // 跳帧模式下，绘制无效
    if (__aGameControllor.isSkipTick() || duration <= 0)
        return;

    if (!_basicPainter.IsOpen3dAcceleration()) {
        aLogger->Warning("您尚未开启 3D 加速，无法使用绘制类");
        return;
    }
    if (posText.text.empty())
        return;
    std::wstring lineText;
    auto wText = AStrToWstr(posText.text);
    int fontSize = _basicPainter.fontSize;
    int width = 0;
    int totalWidth = 0;

    __ABasicPainter::TextInfo textInfo;

    // 对文本进行预处理
    // 遇到 \n 字符时换行
    for (auto&& ch : wText) {
        if (ch != '\n') {
            lineText.push_back(ch);
            width += ch > 0xff ? fontSize : fontSize / 2 + 1;
        } else {
            totalWidth = std::max(width, totalWidth);
            width = 0;
            textInfo.lines.push_back(std::move(lineText));
            lineText.clear();
        }
    }

    if (!lineText.empty()) {
        totalWidth = std::max(width, totalWidth);
        textInfo.lines.push_back(std::move(lineText));
        lineText.clear();
    }
    __ABasicPainter::DrawInfo info;
    int totalHeight = textInfo.lines.size() * _basicPainter.fontSize;

    // 绘制背景框必须在绘制文字之前
    // 不然背景框就会覆盖文字
    if (posText.isHasBkg) {
        // 绘制背景框
        __ABasicPainter::RectInfo rectInfo;
        rectInfo.rect.width = totalWidth;
        rectInfo.rect.height = totalHeight;
        rectInfo.rect.x = posText.x + totalWidth * _basicPainter.posDict[int(posText.pos)][0];
        rectInfo.rect.y = posText.y + totalHeight * _basicPainter.posDict[int(posText.pos)][1];
        DWORD _rectColor = AArgb(0xaf, 0, 0, 0);
        rectInfo.color = _rectColor;
        info.var = rectInfo;
        info.type = __ABasicPainter::RECT;
        do {
            info.duration = duration;
            if (__isInPaintTickRunner) {
                --info.duration;
                _basicPainter.Draw(info);
            }
            if (info.duration <= 0) {
                break;
            }
            if (info.duration == 1) {
                _basicPainter.singleTickQueue.emplace_back(std::move(info));
            } else {
                _basicPainter.multiTickQueue.emplace_back(std::move(info));
            }
        } while (false);
    }

    textInfo.color = _textColor;
    textInfo.x = posText.x + totalWidth * _basicPainter.posDict[int(posText.pos)][0];
    textInfo.y = posText.y + totalHeight * _basicPainter.posDict[int(posText.pos)][1];
    info.var = std::move(textInfo);
    info.type = __ABasicPainter::TEXT;
    do {
        info.duration = duration;
        if (__isInPaintTickRunner) {
            --info.duration;
            _basicPainter.Draw(info);
        }
        if (info.duration <= 0) {
            break;
        }
        if (info.duration == 1) {
            _basicPainter.singleTickQueue.emplace_back(std::move(info));
        } else {
            _basicPainter.multiTickQueue.emplace_back(std::move(info));
        }
    } while (false);
}

// 避免在同一个地方一直使用工具
class GardenPosCoolDown {
public:
    // 主花园有4行8列
    int main_garden[4][8];
    // 蘑菇园只有8个位置，行数固定为0，列数按照坑位的横坐标（x）大小进行排序，分别为0~7
    int mushroom_garden[8];
    // 水族馆只有8个位置，行数固定为0
    // 列数较复杂，以中间水平线分为上下两组，上面5个位置，编号0~4；下面3个，编号5~7。各组内部从左到右排序。
    int aquarium[8];
    GardenPosCoolDown() {
        Reset();
    }
    void Reset() {
        memset(main_garden, 0, 4 * 8 * sizeof(int));
        memset(mushroom_garden, 0, 8 * sizeof(int));
        memset(aquarium, 0, 8 * sizeof(int));
    }
    void Start() {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 8; j++) {
                if (main_garden[i][j] > 0) {
                    main_garden[i][j]--;
                }
            }
        }
        for (int j = 0; j < 8; j++) {
            if (mushroom_garden[j] > 0) {
                mushroom_garden[j]--;
            }
        }
        for (int j = 0; j < 8; j++) {
            if (aquarium[j] > 0) {
                aquarium[j]--;
            }
        }
    }
    int GetCoolDown(int row, int col) {
        int scene = AGetMainObject()->Scene();
        switch (scene)
        {
        case 7:
            return main_garden[row][col];
        
        case 6:
            return mushroom_garden[col];
        
        default:
            return aquarium[col];
        }
    }
    void SetCoolDown(int row, int col, int coolDown) {
        int scene = AGetMainObject()->Scene();
        switch (scene)
        {
        case 7:
            main_garden[row][col] = coolDown;
            break;
        
        case 6:
            mushroom_garden[col] = coolDown;
            break;
        
        default:
            aquarium[col] = coolDown;
        }
    }
};

GardenPosCoolDown garden_cooldown;

bool InGarden() {
    if (AGetPvzBase() == 0) {
        return false;
    }
    if (AGetPvzBase()->GameUi() != 3 || AGetPvzBase()->LevelId() != AAsm::CHALLENGE_ZEN_GARDEN) {
        return false;
    }
    if (AGetMainObject() == 0) {
        return false;
    }
    return true;
}

bool InShop() {
    auto pvzBase = AGetPvzBase();
    if (pvzBase == nullptr) {
        return false;
    }
    auto mouseWnd = pvzBase->MouseWindow();
    if (mouseWnd == nullptr) {
        return false;
    }
    auto topWnd = mouseWnd->TopWindow();
    if (topWnd == nullptr) {
        return false;
    }
    return topWnd->Type() == 4;
}

// 适合花园的自动收集
class AGardenItemCollector : public AItemCollector, AOrderedAfterInjectHook<-1> {
public:
    void _Run() {
        if (InGarden() && AutoTool::lock == 0) {
            // 鼠标在返回按钮上的时候不要收集，不然崩给你看
            int curX = AGetPvzBase()->MouseWindow()->MouseAbscissa();
            int curY = AGetPvzBase()->MouseWindow()->MouseOrdinate();
            if (curY <= 36 && curX >= 627 && curX <= 791) {
                return;
            }
            AItemCollector::_Run();
        }
    }
    void Start() {
        ATickRunnerWithNoStart::_Start([this] { _Run(); }, ATickRunnerWithNoStart::AFTER_INJECT);
    }
    virtual void _AfterInject() override {
        Start();
    }
    virtual void _EnterFight() override {}
};

AGardenItemCollector garden_item_collector;

int GetPotNumInGarden(int gardenType) {
    int potNum = AGetPotPlantNum();
    APotPlant * potArray = AGetPotPlantArray();
    int cnt = 0;
    for (int i = 0; i < potNum; i++) {
        APotPlant & pot = potArray[i];
        if (pot.Location() == gardenType) {
            cnt++;
        }
    }
    return cnt;
}

APlant * FindPlantOnPot(APotPlant & pot) {
    if (!AGetMainObject()) {
        return nullptr;
    }
    // 必须是活的植物，否则会出错，表现为盆栽处于苗状态（age=0），浇水、施肥到age=1时，会不停施肥
    for (auto & plant : aAlivePlantFilter) {
        // 针对花盆盆栽进行特判
        // 不特判了，暂时无解，因为如果这样，那么盆栽为花盆时会不停浇水，目前没有好的办法
        // if (plant.Type() == AHP_33 && pot.Type() == AHP_33) {
        //     return &plant;
        // }
        if (plant.Type() != AHP_33 && plant.Row() == pot.Row() && plant.Col() == pot.Col()) {
            return &plant;
        }
    }
    return nullptr;
}

#ifdef DEBUG
// debug
void DebugPrintGarden(ALogger<AConsole> & logger) {
    int potNum = AGetPotPlantNum();
    APotPlant * potArray = AGetPotPlantArray();
    logger.Info("Garden pot plant info:");
    for (int i = 0; i < potNum; i++) {
        APotPlant & pot = potArray[i];
        APlant * plant = FindPlantOnPot(pot);
        if (plant) {
            logger.Info("pot {:d} in: {:d} at: {:d} {:d} reversed: {:d} state: {:d} requires: {:d} water: {:d}/{:d} color: {:d}", 
                pot.Type(), pot.Location(), pot.Row(), pot.Col(), 
                pot.isReversed(), plant->State(), pot.Requirement(),
                pot.WaterCnt(), pot.MaxWaterCnt(), pot.Color()
            );
        } else {
            logger.Info("pot {:d} in: {:d} at: {:d} {:d} reversed: {:d} requires: {:d} water: {:d}/{:d} color: {:d}", 
            pot.Type(), pot.Location(), pot.Row(), pot.Col(), 
            pot.isReversed(), pot.Requirement(),
            pot.WaterCnt(), pot.MaxWaterCnt(), pot.Color()
        );
        }
    }
    logger.Info("Has music player: {:d}", AHasMusicPlayer());
    logger.Info("Fertilizer: {:d}", AGetFertilizerNum());
    logger.Info("Insecticide: {:d}", AGetInsecticideNum());
    logger.Info("");
}
#endif

// 删除ID超出范围的植物
void RemoveInvalidPots() {
    int potNum = AGetPotPlantNum();
    APotPlant * potArray = AGetPotPlantArray();
    int idx = 0;
    int legalPotCnt = 0;
    while (idx < potNum) {
        APotPlant & pot = potArray[idx];
        if (pot.HasValidID()) {
            if (legalPotCnt < idx) {
                memcpy(potArray + legalPotCnt, potArray + idx, sizeof(APotPlant));
            }
            legalPotCnt++;
            idx++;
        } else {
            idx++;
        }
    }
    AGetPotPlantNum() = legalPotCnt;
}

AutoTool water_can(6, 0);  // 水壶
AutoTool fertilizer(7, 0);  // 肥料
AutoTool insecticide(8, 0);  // 杀虫剂
AutoTool music_player(9, 0);  // 留声机

#ifdef DEBUG
ALogger<AConsole> consoleLogger;
#endif

int selectedPotPlantType = 0;
int selectedPotPlantColor = 0;
bool selectedPotIsReversed = false;
bool userSelected = false;

// 控件 ID
#define IDC_EDIT_INPUT1   101
#define IDC_CHECK_OPTION  102
#define IDC_BTN_OK        103
#define IDC_BTN_CANCEL    104
#define IDC_EDIT_INPUT2   105
#define IDC_TEXT1         1001
#define IDC_TEXT2         1002

// 窗口过程
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_CREATE: {
            // 文本（植物编号）
            CreateWindowExW(0, L"STATIC", L"输入植物编号", 
                WS_CHILD | WS_VISIBLE | SS_LEFT, 
                20, 10, 140, 20, 
                hWnd, (HMENU)IDC_TEXT1, __aig.hInstance, NULL);

            // 创建输入框（植物编号）
            CreateWindowExW(0, L"EDIT", L"",
                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
                20, 35, 140, 25,
                hWnd, (HMENU)IDC_EDIT_INPUT1, __aig.hInstance, NULL);
            
            // 文本（颜色）
            CreateWindowExW(0, L"STATIC", L"颜色代码", 
                WS_CHILD | WS_VISIBLE | SS_LEFT, 
                180, 10, 100, 20, 
                hWnd, (HMENU)IDC_TEXT2, __aig.hInstance, NULL);
            
            // 创建输入框（颜色）
            CreateWindowExW(0, L"EDIT", L"0",
                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
                180, 35, 100, 25,
                hWnd, (HMENU)IDC_EDIT_INPUT2, __aig.hInstance, NULL);

            // 创建复选框
            CreateWindowExW(0, L"BUTTON", L"是否反向？",
                WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
                20, 70, 140, 25,
                hWnd, (HMENU)IDC_CHECK_OPTION, __aig.hInstance, NULL);

            // 创建“确定”按钮
            CreateWindowExW(0, L"BUTTON", L"确定",
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                80, 110, 70, 25,
                hWnd, (HMENU)IDC_BTN_OK, __aig.hInstance, NULL);

            // 创建“取消”按钮
            CreateWindowExW(0, L"BUTTON", L"取消",
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                170, 110, 70, 25,
                hWnd, (HMENU)IDC_BTN_CANCEL, __aig.hInstance, NULL);
            break;
        }

        case WM_COMMAND: {
            int wmId = LOWORD(wParam);
            switch (wmId) {
                case IDC_BTN_OK: {
                    // 获取输入框中的文本：植物编号
                    wchar_t buffer1[256] = {0};
                    HWND hEdit1 = GetDlgItem(hWnd, IDC_EDIT_INPUT1);
                    GetWindowTextW(hEdit1, buffer1, 256);

                    // 获取输入框中的文本：颜色
                    wchar_t buffer2[256] = {0};
                    HWND hEdit2 = GetDlgItem(hWnd, IDC_EDIT_INPUT2);
                    GetWindowTextW(hEdit2, buffer2, 256);

                    // 获取复选框状态
                    HWND hCheck = GetDlgItem(hWnd, IDC_CHECK_OPTION);
                    BOOL isChecked = (SendMessage(hCheck, BM_GETCHECK, 0, 0) == BST_CHECKED);

                    // 获得输入内容
                    selectedPotIsReversed = isChecked;
                    try {
                        selectedPotPlantType = std::stoi(buffer1);
                        selectedPotPlantColor = std::stoi(buffer2);
                        userSelected = true;
                    } catch (std::invalid_argument const& ex) {
                        break;
                    } catch (std::out_of_range const& ex) {
                        break;
                    }

                    // 关闭窗口
                    DestroyWindow(hWnd);
                    break;
                }
                case IDC_BTN_CANCEL:
                    userSelected = false;
                    DestroyWindow(hWnd);
                    break;
            }
            break;
        }

        case WM_DESTROY:
            // 不要下面一行，不然无法第二次打开弹窗
            // PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
    return 0;
}

bool winClassRegistered = false;

int ShowPotSelectDialog() {
    if (!winClassRegistered) {
        // 注册窗口类
        WNDCLASSEXW wc = {0};
        wc.cbSize        = sizeof(WNDCLASSEXW);
        wc.lpfnWndProc   = WndProc;
        wc.hInstance     = __aig.hInstance;
        wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
        wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
        wc.lpszClassName = L"AGGivePotDialogClass";
        if (!RegisterClassExW(&wc)) {
            // MessageBoxW(NULL, L"窗口类注册失败！", L"错误", MB_ICONERROR);
            return 0;
        }
        winClassRegistered = true;
    }

    int width = 320;
    int height = 180;
    int x = CW_USEDEFAULT;
    int y = CW_USEDEFAULT;
    HWND hParentWnd = AGetPvzBase()->Hwnd();
    if (hParentWnd) {
        RECT rcParent;
        GetWindowRect(hParentWnd, &rcParent);
        int parentWidth = rcParent.right - rcParent.left;
        int parentHeight = rcParent.bottom - rcParent.top;
        x = rcParent.left + (parentWidth - width) / 2;
        y = rcParent.top + (parentHeight - height) / 2;
    }

    // 创建窗口
    HWND hWnd = CreateWindowExW(
        0, L"AGGivePotDialogClass", L"",
        WS_OVERLAPPED | WS_CAPTION | WS_VISIBLE | WS_SYSMENU,
        x, y, width, height,
        NULL, NULL, __aig.hInstance, NULL
    );

    if (!hWnd) {
        // MessageBoxW(NULL, L"窗口创建失败！", L"错误", MB_ICONERROR);
        return 0;
    }

    // 消息循环
    MSG msg;
    while (GetMessageW(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
        if (!IsWindow(hWnd)) break;
    }
    return 1;
}

// 脚本自动设置盆栽，演示作用。不要在自己主玩存档使用！它会删除所有原有盆栽！
#ifdef DEBUG
bool demoWhitePot = false;
void SetPotPlantForDemo() {
    static int demoID = 0;
    const int demoNum = 6;
    std::vector<int> demoScene = {0, 1, 0, 0, 0, 0};
    std::vector<std::vector<int>> demoPots = {
        // 正常可获得盆栽（非蘑菇园）
        {0, 1, 2, 3, 4, 5, 6, 7, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, -1, 32, 11, 34, 35, 36, 37, 38, 39},
        // 正常可获得盆栽（蘑菇园）
        {8, 9, 10, 12, 13, 14, 15, 31},
        // 正常无法获得，但表现正常，包括所有紫卡，模仿者，两种特殊坚果，花盆等
        {33, 40, 41, 42, 43, 44, 45, 46, 47, -1, 48, 49, 51, 52, 72, 85, -1, -1, -1, -1, -1, -1, -1, -1, -1, 50, -1, 59},
        // 都表现为一颗不停开花的小花，但用手套拿会出现僵尸
        {58, 60, 61, 63, 64, 66, 67, 69, 70, 71, 73, 79},
        // 不能用手套移动，会崩溃
        {98, 111, 124, 150, 163, 176, 189, -1, 202, -1, -1, -1, -1, -1, -1, -1, 228, 241, -1, 254, -1, 267},
    };
    if (demoID == demoNum - 1) {  // 全不同颜色金盏花变种
        AGetPotPlantNum() = 0;
        APotPlant * potArray = AGetPotPlantArray();
        int potCnt = 0;
        for (int color = 0; color < 13; color++) {
            GivePotPlant(38, 0, color);
            APotPlant & pot = potArray[potCnt];
            pot.Location() = 0;
            pot.Row() = potCnt / 8;
            pot.Col() = potCnt % 8;
            pot.Age() = 3;
            potCnt++;
        }
    } else {
        AGetPotPlantNum() = 0;
        APotPlant * potArray = AGetPotPlantArray();
        int potCnt = 0;
        int pos = 0;
        for (auto potID : demoPots[demoID]) {
            if (potID >= 0) {
                GivePotPlant(potID, 0, demoWhitePot);
                APotPlant & pot = potArray[potCnt];
                pot.Location() = demoScene[demoID];
                pot.Row() = pos / 8;
                pot.Col() = pos % 8;
                pot.Age() = 3;
                potCnt++;
            }
            pos++;
        }
    }
    demoID = (demoID + 1) % demoNum;
}
#endif

void GardenInit() {
    // 脚本开关（按Q）
    AConnect('Q', [] () {
        water_can.Switch();
        music_player.Switch();
        fertilizer.Switch();
        insecticide.Switch();
    }, 0, ATickRunner::AFTER_INJECT);
    // 重置金盏花购买日期
    AConnect('M', [] () {
        ResetMarigoldBuyDate();
    }, 0, ATickRunner::AFTER_INJECT);
    // 给我一盆指定的植物
    AConnect('P', [] () {
        // 判断花园是否满了？得到盆栽默认放在主花园，如果满了，再放会崩溃
        if (GetPotNumInGarden(0) >= 32) {
            MessageBoxW(NULL, L"你的花园已经满了！请先移除一些盆栽", L"AutoGarden", NULL);
            return;
        }
        // 显示一个对话框
        int status = ShowPotSelectDialog();
        if (status && userSelected) {
            GivePotPlant(selectedPotPlantType, selectedPotIsReversed, selectedPotPlantColor);
        }
    }, 0, ATickRunner::AFTER_INJECT);
    // 所有植物立即长大，你可能需要退出花园然后重进来看到效果
    AConnect('G', [] () {
        int potNum = AGetPotPlantNum();
        APotPlant * potArray = AGetPotPlantArray();
        for (int i = 0; i < potNum; i++) {
            APotPlant & pot = potArray[i];
            pot.Age() = 3;
        }
    }, 0, ATickRunner::AFTER_INJECT);
    // 救救我的存档！如果花园里有无效植物编号的盆栽，进花园游戏会崩溃，这个快捷键能删除这些有问题的植物
    AConnect('R', [] () {
        RemoveInvalidPots();
    }, 0, ATickRunner::AFTER_INJECT);
    // 画盆栽编号
    AConnect('I', [] () {
        plotPotID = !plotPotID;
    }, 0, ATickRunner::AFTER_INJECT);
#ifdef DEBUG
    // debug print
    AConnect('D', [] () {
        DebugPrintGarden(consoleLogger);
    }, 0, ATickRunner::AFTER_INJECT);
    // demo
    AConnect('T', [] () {
        SetPotPlantForDemo();
    }, 0, ATickRunner::AFTER_INJECT);
    // demo pot color
    AConnect('W', [] () {
        demoWhitePot = !demoWhitePot;
    }, 0, ATickRunner::AFTER_INJECT);
#else
    // 不安全模式，此时可以获得任意编号的盆栽，注意不要把游戏玩崩溃了喵。
    AConnect('U', [] () {
        unsafeMode = !unsafeMode;
    }, 0, ATickRunner::AFTER_INJECT);
#endif
}

void GardenFinalize() {
    // 这个是避免再次注入时，由于窗口类已经注册，导致无法弹出窗口
    if (winClassRegistered) {
        UnregisterClassW(L"AGGivePotDialogClass", __aig.hInstance);
    }
}

AOnAfterInject(GardenInit());

AOnBeforeExit(GardenFinalize());

void Garden() {
    // avoid crash
    if (!InGarden()) {
        return;
    }
    // 切换场景后进行重置
    static int prev_scene = 0;
    int scene = AGetMainObject()->Scene();
    if (scene != prev_scene) {
        garden_cooldown.Reset();
        water_can.Reset();
        music_player.Reset();
        fertilizer.Reset();
        insecticide.Reset();
        prev_scene = scene;
    }

    // 在商店时暂时停止
    bool inShop = InShop();
    if (!inShop) {
        garden_cooldown.Start();
        water_can.Start();
        music_player.Start();
        fertilizer.Start();
        insecticide.Start();
    }

    // 画一行字告诉你脚本开关状态
    if (water_can.enabled) {
        MyDraw(AText("AutoGarden on", 10, 570), 1, 0.0);
    } else {
        MyDraw(AText("AutoGarden off", 10, 570), 1, 0.0);
    }
    // 红色警告：调试模式，以及不安全模式！
#ifdef DEBUG
    MyDraw(AText("DEBUG MODE", 320, 570), 1, 0.0, AArgb(0xff, 0xff, 0x00, 0x00));
#else
    if (unsafeMode) {
        MyDraw(AText("UNSAFE MODE", 320, 570), 1, 0.0, AArgb(0xff, 0xff, 0x00, 0x00));
    }
#endif

    // 一些游戏内数据
    int potNum = AGetPotPlantNum();
    APotPlant * potArray = AGetPotPlantArray();

    // 状态：0：未浇水；43：已浇水；44：需要留声机/除虫；45：完成留声机/除虫
    for (int i = 0; i < potNum; i++) {
        APotPlant & pot = potArray[i];
        if (PotPlantLocationMatch(pot, scene)) {
            // 找到对应的植物
            APlant * plant_ptr = FindPlantOnPot(pot);
            if (plant_ptr) {
                APlant & plant = *plant_ptr;
                if (plotPotID && !inShop) {
                    // 对于金盏花，额外输出颜色代码
                    if (pot.Type() == 38) {
                        MyDraw(AText(std::to_string(pot.Type()) + "," + std::to_string(pot.Color()), plant.Abscissa(), plant.Ordinate()), 1, 0.0);
                    } else {
                        MyDraw(AText(std::to_string(pot.Type()), plant.Abscissa(), plant.Ordinate()), 1, 0.0);
                    }
                }
                if (!plant.IsSleeping() && garden_cooldown.GetCoolDown(pot.Row(), pot.Col()) == 0) {
                    // 坐标
                    int xi = plant.Abscissa() + plant.HurtWidth() / 2;
                    int yi = plant.Ordinate() + plant.HurtHeight() / 2;
                    if (plant.State() == 44) {
                        if (pot.Requirement() == 4 && AHasMusicPlayer()) {  // 需要留声机
                            if (music_player.Use(xi, yi)) {
                                garden_cooldown.SetCoolDown(pot.Row(), pot.Col(), 200);
                            }
                        } else if (pot.Requirement() == 3 && AGetInsecticideNum() > 0) {  // 需要杀虫
                            if (insecticide.Use(xi, yi)) {
                                garden_cooldown.SetCoolDown(pot.Row(), pot.Col(), 200);
                            }
                        } else if (pot.Requirement() == 0 && AGetFertilizerNum() > 0) {  // 需要肥料
                            if (fertilizer.Use(xi, yi)) {
                                garden_cooldown.SetCoolDown(pot.Row(), pot.Col(), 200);
                            }
                        }
                    } else if (plant.State() == 0) {  // 需要浇水
                        if (water_can.Use(xi, yi)) {
                            garden_cooldown.SetCoolDown(plant.Row(), plant.Col(), 200);
                        }
                    }
                }
            }
        }
    }
}

AOnAfterTick(Garden());

void AScript() {
    // 必须要有，不然退出花园重进脚本有概率失效
    ASetReloadMode(AReloadMode::MAIN_UI_OR_FIGHT_UI);
}
