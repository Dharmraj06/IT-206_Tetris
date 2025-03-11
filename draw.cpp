#include<stdio.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <conio.h> 
#include <windows.h>
#include <iostream>

using namespace std;

int Width = 10;
int Height = 20;
int curr_tetro;
int rnum;
int CurrX;
int CurrY;
vector<vector<bool>> grid(Height, vector<bool>(Width, false));

void drawGrid()
{
    for (int y = 0; y < Height; ++y)
    {
        for (int x = 0; x < Width; ++x)
        {
            if (grid[y][x])
            {
                cout<< "#"; 
            }
            else
            {
                cout<< "."; 
            }
        }
        cout<<endl;
    }
}


void control()
{
    if (_kbhit())
        {
            char key = _getch();
            if (key == char(75) && canplace(CurrX
             - 1, CurrY, shape))
            {
                CurrX
            --;
            }
            else if (key == char(77) && canplace(CurrX
             + 1, CurrY, shape))
            {
                CurrX
            ++;
            }
            else if (key == char(72))
            {
                rnum = (rnum + 1) % 4;
                if (!canplace(CurrX
                , CurrY, get_tetromino(curr_tetro)))
                {
                    rnum = (rnum - 1 + 4) % 4; // Revert rotation if invalid
                }
            }
            
        }
}

bool canplace(int x, int y, const vector<vector<bool>>& shape, const vector<vector<int>>& field) {
    for (int i = 0; i < shape.size(); ++i) {
        for (int j = 0; j < shape[0].size(); ++j) {
            if (shape[i][j]) {
                if (x + j < 0 || x + j >= field[0].size() || y + i >= field.size() || (y + i >= 0 && field[y + i][x + j])) {
                    return false;
                }
            }
        }
    }
    return true;
}
// if the return value of the function canplace is true then call addtogrid