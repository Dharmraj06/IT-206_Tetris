#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include "draw.h"
#include "tetriminos.h"
#include "logic.h"
#include <conio.h>
using namespace std;

void drawField(const vector<vector<bool>> &field)
{

    for (int y = 0; y < HEIGHT; ++y)
    {

        for (int x = 0; x < WIDTH; ++x)
        {

            if (field[y][x] == 0)
                cout << ".";
            else
                cout << "#";
        }
        cout << endl;
    }
}

int main()
{
    srand(time(0));
    vector<vector<bool>> field(HEIGHT, vector<bool>(WIDTH, 0));
    Logic logic;

    tetro currenttetro = static_cast<tetro>(rand() % 7); // check meaning of this code

    vector<vector<bool>> shape = get_tetromino(currenttetro);

    int currentX = WIDTH / 2 - 2;
    int currentY = 0;
    bool gameOver = false;
    int score = 0;

    while (true)
    {
        vector<vector<bool>> tempField = field;
        system("cls");

        for (int i = 0; i < shape.size(); ++i)
        {
            for (int j = 0; j < shape[0].size(); ++j)
            {
                if (shape[i][j] && currentY + i >= 0)
                {
                    tempField[currentY + i][currentX + j] = 1;
                }
            }
        }

        drawField(tempField);

        cout << "tetromino: " << currenttetro << endl;
        cout << currentX << " " << currentY << endl;

        control(shape, currentX, currentY, field, gameOver);

        cout << currentX << " " << currentY << endl;

        if (gameOver)
        {
            cout << "Game Over!" << endl;
            cout << score << endl;
            break;
        }

        if (canPlace(currentX, currentY + 1, shape, field))
        {
            currentY++;
        }
        else
        {
            vector<vector<bool>> shape = get_tetromino(currenttetro);
            for (int i = 0; i < shape.size(); i++)
            {
                for (int j = 0; j < shape[0].size(); j++)
                {
                    if (shape[i][j])
                    {
                        field[currentX + i][currentY + j] = true;
                    }
                }
            }
            // logic.addtogrid(tempField, currenttetro, currentX, currentY);
            score += logic.clear_lines(field);
            cout << score << endl;

            currenttetro = static_cast<tetro>(rand() % TETROMINOS.size());

            shape = get_tetromino(currenttetro);
            currentX = WIDTH / 2 - 2;
            currentY = 0;

            if (!canPlace(currentX, currentY, shape, field))
            {
                cout << "Game Over!" << endl;
                break;
            }
        }

#ifdef _WIN32
        Sleep(200);
#else
        usleep(200000); // 200 milliseconds
#endif
        system("cls");
    }

    return 0;
}