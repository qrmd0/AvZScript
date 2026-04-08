// 小游戏懒人合集 by yuchenxi2000
// 包含锤僵尸、宝石迷阵、宝石迷阵转转看
#include <avz.h>
#include <utility>
#include <algorithm>

// 实现拖拽操作（宝石迷阵）
void MouseDrag(int x_from, int y_from, int x_to, int y_to, int key = 1) {
    int curX = AGetPvzBase()->MouseWindow()->MouseAbscissa();
    int curY = AGetPvzBase()->MouseWindow()->MouseOrdinate();
    AAsm::MouseMove(x_from, y_from);
    AAsm::MouseDown(x_from, y_from, key);
    AAsm::MouseMove(x_to, y_to);
    AAsm::MouseUp(x_to, y_to, key);
    AAsm::MouseMove(curX, curY);
}

void ADragGrid(int row, float col, int row_dest, float col_dest) {
    int x = 0;
    int y = 0;
    int x_dest = 0;
    int y_dest = 0;
    col = int(col + 0.5);
    col_dest = int(col_dest + 0.5);
    AGridToCoordinate(row, col, x, y);
    AGridToCoordinate(row_dest, col_dest, x_dest, y_dest);
    // y += offset;
    MouseDrag(x, y, x_dest, y_dest);
}

// 宝石迷阵系列中自动升级植物
void UpgradePlantBeghouled() {
    int level_id = AGetPvzBase()->LevelId();
    if (level_id != AAsm::CHALLENGE_BEGHOULED && level_id != AAsm::CHALLENGE_BEGHOULED_TWIST) {
        return;
    }

    auto repeater = AGetMainObject()->SeedArray();
    auto fumeshroom = AGetMainObject()->SeedArray() + 1;
    auto tallnut = AGetMainObject()->SeedArray() + 2;
    int sun = AGetMainObject()->Sun();

    if (repeater->IsUsable()) {
        if (sun >= 1000) {
            ACard(1, 1, 9);
        }
    } else if (fumeshroom->IsUsable()) {
        if (sun >= 500) {
            ACard(2, 1, 9);
        }
    } else if (tallnut->IsUsable()) {
        if (sun >= 250) {
            ACard(3, 1, 9);
        }
    }
}

const int NRow = 5;
const int NCol = 8;

// 宝石迷阵系列的植物类型矩阵
class Board {
protected:
    int data[NRow][NCol];
public:
    void Fill() {
        memset(this->data, -1, sizeof(int) * NRow * NCol);
        for (auto && p : aAlivePlantFilter) {
            this->data[p.Row()][p.Col()] = p.Type();
        }
    }
    void Twist(int row, int col) {
        int tmp = this->data[row][col];
        this->data[row][col] = this->data[row + 1][col];
        this->data[row + 1][col] = this->data[row + 1][col + 1];
        this->data[row + 1][col + 1] = this->data[row][col + 1];
        this->data[row][col + 1] = tmp;
    }
    void UnTwist(int row, int col) {
        int tmp = this->data[row][col];
        this->data[row][col] = this->data[row][col + 1];
        this->data[row][col + 1] = this->data[row + 1][col + 1];
        this->data[row + 1][col + 1] = this->data[row + 1][col];
        this->data[row + 1][col] = tmp;
    }
    bool isValid(int row, int col) {
        int row_range_begin = row - 2 < 0 ? 0 : row - 2;
        int row_range_end = row + 2 >= NRow ? NRow - 2 : row + 1;
        int col_range_begin = col - 2 < 0 ? 0 : col - 2;
        int col_range_end = col + 2 >= NCol ? NCol - 2 : col + 1;
        for (int j = col_range_begin; j < col_range_end; j++) {
            if (this->data[row][j] == this->data[row][j + 1] && this->data[row][j] == this->data[row][j + 2] && this->data[row][j] >= 0) {
                return true;
            }
        }
        for (int i = row_range_begin; i < row_range_end; i++) {
            if (this->data[i][col] == this->data[i + 1][col] && this->data[i][col] == this->data[i + 2][col] && this->data[i][col] >= 0) {
                return true;
            }
        }
        return false;
    }
    bool isValidTwist(int row, int col) {
        int row_range_begin = row - 2 < 0 ? 0 : row - 2;
        int row_range_end = row + 3 >= NRow ? NRow - 2 : row + 2;
        int col_range_begin = col - 2 < 0 ? 0 : col - 2;
        int col_range_end = col + 3 >= NCol ? NCol - 2 : col + 2;
        for (int i = row; i < row + 2; i++) {
            for (int j = col_range_begin; j < col_range_end; j++) {
                if (this->data[i][j] == this->data[i][j + 1] && this->data[i][j] == this->data[i][j + 2] && this->data[i][j] >= 0) {
                    return true;
                }
            }
        }
        for (int i = row_range_begin; i < row_range_end; i++) {
            for (int j = col; j < col + 2; j++) {
                if (this->data[i][j] == this->data[i + 1][j] && this->data[i][j] == this->data[i + 2][j] && this->data[i][j] >= 0) {
                    return true;
                }
            }
        }
        return false;
    }
    void doValidMove() {
        // col direction
        for (int i = 0; i < NRow; i++) {
            for (int j = 0; j < NCol - 1; j++) {
                int tmp = this->data[i][j];
                this->data[i][j] = this->data[i][j + 1];
                this->data[i][j + 1] = tmp;
                if (this->isValid(i, j) || this->isValid(i, j + 1)) {
                    ADragGrid(i + 1, j + 1, i + 1, j + 2);
                    return;
                }
                this->data[i][j + 1] = this->data[i][j];
                this->data[i][j] = tmp;
            }
        }
        // row direction
        for (int i = 0; i < NRow - 1; i++) {
            for (int j = 0; j < NCol; j++) {
                int tmp = this->data[i][j];
                this->data[i][j] = this->data[i + 1][j];
                this->data[i + 1][j] = tmp;
                if (this->isValid(i, j) || this->isValid(i + 1, j)) {
                    ADragGrid(i + 1, j + 1, i + 2, j + 1);
                    return;
                }
                this->data[i + 1][j] = this->data[i][j];
                this->data[i][j] = tmp;
            }
        }
    }
    void doValidTwist() {
        for (int i = 0; i < NRow - 1; i++) {
            for (int j = 0; j < NCol - 1; j++) {
                this->Twist(i, j);
                if (this->isValidTwist(i, j)) {
                    AClickGrid(i + 1, j + 1);
                    return;
                }
                this->UnTwist(i, j);
            }
        }
    }
};

Board board;

// 宝石迷阵主函数
void Beghouled() {
    if (AGetPvzBase()->LevelId() != AAsm::CHALLENGE_BEGHOULED) {
        return;
    }
    if (!aAlivePlantFilter.Count()) {
        return;
    }
    board.Fill();
    board.doValidMove();
}

// 宝石迷阵转转看主函数
void BeghouledTwist() {
    if (AGetPvzBase()->LevelId() != AAsm::CHALLENGE_BEGHOULED_TWIST) {
        return;
    }
    if (!aAlivePlantFilter.Count()) {
        return;
    }
    board.Fill();
    board.doValidTwist();
}

// 锤僵尸主函数
void WhackZombie() {
    if (AGetPvzBase()->LevelId() != AAsm::CHALLENGE_WHACK_A_ZOMBIE) {
        return;
    }
    if (AGetMainObject()->Wave() <= 0) {
        return;
    }
    for (auto && z : aAliveZombieFilter) {
        // consoleLogger.Info("{:d} {:d} {:d}", z.Index(), z.State(), z.StateCountdown());
        // 在此之前（50~20）僵尸无法被伤害
        if (z.StateCountdown() <= 19) {
            int x = int(z.Abscissa() + z.HurtWidth() / 2);
            int y = int(z.Ordinate() + z.HurtHeight() / 2);
            AAsm::MouseClick(x, y, 1);
        }
    }
    // 自动种墓碑苔藓
    auto grave_buster = AGetMainObject()->SeedArray() + AGetSeedIndex(AGRAVE_BUSTER);
    if (AGetMainObject()->Sun() >= AGetSeedSunVal(grave_buster) && grave_buster->IsUsable()) {
        auto grave_lst = AGetGraves();
        std::sort(grave_lst.begin(), grave_lst.end(), [] (const AGrid & a, const AGrid & b) {return a.col < b.col;});
        ACard(AGRAVE_BUSTER, grave_lst);
    }
}

// 修复锤僵尸模式不能自动收集的bug
class AItemCollectorFixed : public AItemCollector {
    // __ADeleteCopyAndMove(AItemCollectorFixed)
public:
    void Start() {
        ATickRunnerWithNoStart::_Start([this] { _Run(); }, ONLY_FIGHT);
    }
protected:
    void _Run() {
        // if (AGetMainObject()->GameClock() % _timeInterval != 0 || //
        //     AGetMainObject()->MouseAttribution()->Type() != 0)
        //     return;

        // fix by yuchenxi: not working on "whack a zombie" level, because hammer (type 7) is on mouse
        if (AGetMainObject()->GameClock() % _timeInterval != 0)
            return;
        int mouseItem = AGetMainObject()->MouseAttribution()->Type();
        if (mouseItem != 0 && mouseItem != 7)
            return;

        AItem* collectItem = nullptr;
        for (auto& item : aAliveItemFilter) {
            if (!_types[item.Type()])
                continue;
            collectItem = &item;
            if (ARangeIn(item.Type(), {4, 5, 6})) // 优先采集阳光
                break;
        }
        if (!collectItem) // 没有要收集的物品
            return;

        float itemX = collectItem->Abscissa();
        float itemY = collectItem->Ordinate();
        if (itemX >= 0.0 && itemY >= 70) {
            AAsm::ReleaseMouse();
            int x = static_cast<int>(itemX + 30);
            int y = static_cast<int>(itemY + 30);
            ALeftClick(x, y);
            AAsm::ReleaseMouse();
        }
    }
    virtual void _EnterFight() override {
        Start();
    }
};

ATickRunner whack_zombie_runner;
ATickRunner beghouled_runner;
ATickRunner twist_runner;
ATickRunner upgrade_runner;
AItemCollectorFixed aItemCollectorFixed;

void AScript() {
    ASetReloadMode(AReloadMode::MAIN_UI_OR_FIGHT_UI);

    whack_zombie_runner.Start(WhackZombie);
    beghouled_runner.Start(Beghouled);
    twist_runner.Start(BeghouledTwist);
    upgrade_runner.Start(UpgradePlantBeghouled);

    // fix the bug on AItemCollector
    aItemCollector.Stop();
    aItemCollectorFixed.Start();
}
