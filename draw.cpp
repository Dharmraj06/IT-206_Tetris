#include <stdio.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <windows.h>

#include "logic.h"
#include "tetriminos.h"
#include "draw.h"

using namespace std;

int Width = 10;
int Height = 20;
//enum tetro { I, J, L, O, S, T, Z };

tetro currentTetromino;
//int rnum = rand() % 7;

bool canPlace(int x, int y, const vector<vector<bool>> &shape, const vector<vector<bool>> &field)
{
    for (int i = 0; i < shape.size(); ++i)
    {
        for (int j = 0; j < shape[0].size(); ++j)
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

void control(const vector<vector<bool>> &shape, int &currentX, int &currentY, const vector<vector<bool>> &field, bool &gameOver)
{
    if (_kbhit())
    {
        char key = _getch();
        if (key == 'a' && canPlace(currentX - 1, currentY, shape, field))
        {
            cout << "left" << endl;
            currentX--;
        }
        else if (key == 'd' && canPlace(currentX + 1, currentY, shape, field))
        {
            cout << "right" << endl;
            currentX++;
        }
        else if (key == 's' )
        {
            cout << "down" << endl;
            currentY++;
        }
        else if (key == 'w')
        {
            // Handle rotation
        }
        else if (key == 'x' || key == 'X')
        {
            gameOver = true;
        }
    }
}