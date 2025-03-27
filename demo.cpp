#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <windows.h>

using namespace std;

const int WIDTH = 10;
const int HEIGHT = 20;

const vector<vector<vector<bool>>> TETROMINOS = {
    {{1, 1, 1, 1}},
    {{1, 1, 1}, {0, 1, 0}},
    {{1, 1, 0}, {0, 1, 1}},
    {{0, 1, 1}, {1, 1, 0}},
    {{1, 1, 1}, {1, 0, 0}},
    {{1, 1, 1}, {0, 0, 1}},
    {{1, 1}, {1, 1}}};

vector<vector<int>> field(HEIGHT, vector<int>(WIDTH, 0));
int currtetro = 0;
int currrotation = 0;
int currX = WIDTH / 2 - 2;
int currY = 0;
bool gameOver = false;
int score = 0;
int highscore = 0;

void setColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

vector<vector<bool>> getCurrentShape()
{

    vector<vector<bool>> shape = TETROMINOS[currtetro];
    for (int r = 0; r < currrotation; ++r)
    {

        vector<vector<bool>> rotated(shape[0].size(), vector<bool>(shape.size()));
        for (int i = 0; i < shape.size(); ++i)
        {

            for (int j = 0; j < shape[0].size(); ++j)
            {
                rotated[j][shape.size() - 1 - i] = shape[i][j];
            }
        }
        shape = rotated;
    }
    return shape;
}

void drawField()
{
    system("cls");
    vector<vector<int>> tempField = field;
    vector<vector<bool>> shape = getCurrentShape();
    for (size_t i = 0; i < shape.size(); ++i)
    {
        for (size_t j = 0; j < shape[0].size(); ++j)
        {
            if (shape[i][j] && currY + i >= 0)
            {
                tempField[currY + i][currX + j] = 1;
            }
        }
    }

    for (int y = 0; y < HEIGHT; ++y)
    {
        cout << "\033[34m|"; // Blue border
        for (int x = 0; x < WIDTH; ++x)
        {
            if (tempField[y][x])
            {
                setColor(14); // Yellow blocks
                cout << "#";
            }
            else
            {
                setColor(7); // White empty space
                cout << ".";
            }
        }
        cout << "\033[34m|\n"; // Blue border
    }
    cout << "\033[34m+" << string(WIDTH, '-') << "+\033[0m\n"; // Bottom border
}

bool canPlace(int x, int y, const vector<vector<bool>> &shape)
{
    for (size_t i = 0; i < shape.size(); ++i)
    {

        for (size_t j = 0; j < shape[0].size(); ++j)
        {

            if (shape[i][j])
            {
                if (x + j < 0 || x + j >= WIDTH || y + i >= HEIGHT || (y + i >= 0 && field[y + i][x + j]))
                {
                    return false;
                }
            }
        }
    }
    return true;
}

void addtogrid()
{
    vector<vector<bool>> shape = getCurrentShape();

    for (int i = 0; i < shape.size(); ++i)
    {

        for (int j = 0; j < shape[0].size(); ++j)
        {

            if (shape[i][j])
            {
                field[currY + i][currX + j] = 1;
            }
        }
    }
}

void clearLines()
{
    int linesCleared = 0;
    for (int y = HEIGHT - 1; y >= 0; --y)
    {
        bool full = true;
        for (int x = 0; x < WIDTH; ++x)
        {
            if (!field[y][x])
            {
                full = false;
                break;
            }
        }
        if (full)
        {
            linesCleared++;
            for (int y2 = y; y2 > 0; --y2)
            {
                field[y2] = field[y2 - 1];
            }
            field[0] = vector<int>(WIDTH, 0);
            y++;
        }
    }
    if (linesCleared > 0)
    {
        Beep(750, 300); // Play a beep sound when lines are cleared
    }
}

void control(const vector<vector<bool>> &shape)
{
    if (_kbhit())
    {
        char key = _getch();
        if (key == 'a' && canPlace(currX - 1, currY, shape))
        {
            currX--;
        }
        else if (key == 'd' && canPlace(currX + 1, currY, shape))
        {
            currX++;
        }
        else if (key == 'w')
        {
            currrotation = (currrotation + 1) % 4;
            if (!canPlace(currX, currY, getCurrentShape()))
            {
                currrotation = (currrotation - 1 + 4) % 4;
            }
        }
        else if (key == 's' && canPlace(currX, currY + 1, shape))
        {
            currY++;
        }
        else if (key == 'x' || key == 'X')
        {
            gameOver = true;
        }
    }
}

int main()
{
    srand(static_cast<int>(time(nullptr)));

    while (!gameOver)
    {
        vector<vector<bool>> shape = getCurrentShape();
        vector<vector<int>> tempfield = field;

        for (int i = 0; i < shape.size(); ++i)
        {
            for (int j = 0; j < shape[0].size(); ++j)
            {
                if (shape[i][j] && currY + i >= 0)
                {
                    tempfield[currY + i][currX + j] = 1;
                }
            }
        }

        drawField();

        control(shape);

        if (canPlace(currX, currY + 1, shape))
        {
            currY++;
        }
        else
        {
            addtogrid();
            clearLines();
            currtetro = rand() % TETROMINOS.size();
            currrotation = 0;
            currX = WIDTH / 2 - 2;
            currY = 0;

            if (!canPlace(currX, currY, getCurrentShape()))
            {
                cout << "Game Over!" << endl;
                cout << "WANT TO RESTART? PRESS Y" << endl
                     << "IF NOT PRESS N" << endl;
                char ch = _getch();
                if (ch == 'n' || ch == 'N')
                    break;
                else if (ch == 'y' || ch == 'Y')
                {
                    main();
                    score = 0;
                }
            }
        }
        highscore = max(highscore, score);

        cout << "Score: " << score << " Highscore: " << highscore << endl;
#ifdef _WIN32
        Sleep(150);
#else
        usleep(200000);
#endif
        system("cls");
#ifdef _WIN32
#endif
    }

    return 0;
}