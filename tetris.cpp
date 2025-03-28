#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <windows.h>

using namespace std;

const int WIDTH = 20;
const int HEIGHT = 20;
int score = 0;
int highScore = 0;
time_t startTime;

const vector<vector<vector<bool>>> TETROMINOS = {
    {{1, 1, 1, 1}},
    {{1, 0, 0}, {1, 1, 1}},
    {{0, 0, 1}, {1, 1, 1}},
    {{1, 1}, {1, 1}},
    {{0, 1, 1}, {1, 1, 0}},
    {{0, 1, 0}, {1, 1, 1}},
    {{1, 1, 0}, {0, 1, 1}}};

vector<vector<int>> field(HEIGHT, vector<int>(WIDTH, 0));
int currentTetromino;
int currentRotation;
int currentX;
int currentY;

vector<int> tetrominoColors = {14, 12, 10, 9, 13, 11, 6};

void resetGame()
{
    field = vector<vector<int>>(HEIGHT, vector<int>(WIDTH, 0));
    currentTetromino = rand() % TETROMINOS.size();
    currentRotation = 0;
    currentX = WIDTH / 2 - 2;
    currentY = 0;
    score = 0;
    startTime = time(nullptr);
}

vector<vector<bool>> getCurrentShape()
{
    vector<vector<bool>> shape = TETROMINOS[currentTetromino];
    for (int r = 0; r < currentRotation; ++r)
    {
        vector<vector<bool>> rotated(shape[0].size(), vector<bool>(shape.size()));
        for (size_t i = 0; i < shape.size(); ++i)
            for (size_t j = 0; j < shape[0].size(); ++j)
                rotated[j][shape.size() - 1 - i] = shape[i][j];
        shape = rotated;
    }
    return shape;
}

bool canPlace(int x, int y, const vector<vector<bool>> &shape)
{
    for (size_t i = 0; i < shape.size(); ++i)
        for (size_t j = 0; j < shape[0].size(); ++j)
            if (shape[i][j] && (x + j < 0 || x + j >= WIDTH || y + i >= HEIGHT || (y + i >= 0 && field[y + i][x + j])))
                return false;
    return true;
}

void setColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void drawField()
{
    system("cls");
    vector<vector<int>> tempField = field;
    vector<vector<bool>> shape = getCurrentShape();
    for (size_t i = 0; i < shape.size(); ++i)
        for (size_t j = 0; j < shape[0].size(); ++j)
            if (shape[i][j] && currentY + i >= 0)
                tempField[currentY + i][currentX + j] = currentTetromino + 1;

    time_t currentTime = time(nullptr);
    int elapsedTime = static_cast<int>(currentTime - startTime);

    cout << "Score: " << score << "  High Score: " << highScore << "  Time: " << elapsedTime << "s\n";
    for (int y = 0; y < HEIGHT; ++y)
    {
        setColor(9);
        cout << "|";
        for (int x = 0; x < WIDTH; ++x)
        {
            if (tempField[y][x])
            {
                setColor(tetrominoColors[tempField[y][x] - 1]);
                cout << "\xDB";
            }
            else
            {
                setColor(7);
                cout << " ";
            }
        }
        setColor(9);
        cout << "|\n";
    }
    setColor(9);
    cout << "+" << string(WIDTH, '-') << "+\n";
    setColor(7);
}

void mergeTetromino()
{
    vector<vector<bool>> shape = getCurrentShape();
    for (size_t i = 0; i < shape.size(); ++i)
        for (size_t j = 0; j < shape[0].size(); ++j)
            if (shape[i][j])
                field[currentY + i][currentX + j] = currentTetromino + 1;
}

void clearLines()
{
    for (int y = HEIGHT - 1; y >= 0; --y)
    {
        bool full = true;
        for (int x = 0; x < WIDTH; ++x)
            if (!field[y][x])
            {
                full = false;
                break;
            }
        if (full)
        {
            for (int yy = y; yy > 0; --yy)
                field[yy] = field[yy - 1];
            field[0] = vector<int>(WIDTH, 0);
            score += 10;
            Beep(1000, 200);
            y++;
        }
    }
}
void hideCursor()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(consoleHandle, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}

bool gameLoop()
{
    resetGame();
    while (true)
    {
        drawField();
        if (GetAsyncKeyState(VK_LEFT) & 0x8000 && canPlace(currentX - 1, currentY, getCurrentShape()))
            currentX--;
        if (GetAsyncKeyState(VK_RIGHT) & 0x8000 && canPlace(currentX + 1, currentY, getCurrentShape()))
            currentX++;
        if (GetAsyncKeyState(VK_UP) & 0x8000)
        {
            currentRotation = (currentRotation + 1) % 4;
            if (!canPlace(currentX, currentY, getCurrentShape()))
                currentRotation = (currentRotation - 1 + 4) % 4;
        }
        if (GetAsyncKeyState(VK_DOWN) & 0x8000 && canPlace(currentX, currentY + 1, getCurrentShape()))
            currentY++;
        if (GetAsyncKeyState('X') & 0x8000 || GetAsyncKeyState('x') & 0x8000)
        {
            cout << "\nGAME OVER!\n";
            Beep(500, 500);
            break;
        }
        if (canPlace(currentX, currentY + 1, getCurrentShape()))
            currentY++;
        else
        {
            mergeTetromino();
            clearLines();
            currentTetromino = rand() % TETROMINOS.size();
            currentRotation = 0;
            currentX = WIDTH / 2 - 2;
            currentY = 0;
            if (!canPlace(currentX, currentY, getCurrentShape()))
            {
                setColor(12);
                cout << "\nGAME OVER!\n";
                Beep(500, 500);
                return false;
            }
        }
        Sleep(50);
    }
    return true;
}

int main()
{
    srand(static_cast<unsigned int>(time(nullptr)));

    while (true)
    {
        hideCursor();

        bool restart = gameLoop();
        if (score > highScore)
            highScore = score;

        setColor(12);
        cout << "\nYour Score: " << score << "  High Score: " << highScore << endl;
        setColor(7);

        cout << "Do you want to restart? (Y/N): ";
        char choice;
        cin >> choice;

        if (choice == 'n' || choice == 'N')
        {
            cout << "Final Score: " << score << "  High Score: " << highScore << endl;
            break;
        }
    }

    return 0;
}
