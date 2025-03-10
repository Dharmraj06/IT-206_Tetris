#include<stdio.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <conio.h> 
#include <windows.h>

using namespace std;

int Width = 10;
int Height = 20;
int currentTetromino;
int rnum;
int currentX;
int currentY;

void drawField()
{
    for (int y = 0; y < Height; ++y)
    {
        for (int x = 0; x < Width; ++x)
        {
            if (field[y][x])
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
            if (key == char(75) && canPlace(currentX - 1, currentY, shape))
            {
                currentX--;
            }
            else if (key == char(77) && canPlace(currentX + 1, currentY, shape))
            {
                currentX++;
            }
            else if (key == char(72))
            {
                rnum = (rnum + 1) % 4;
                if (!canPlace(currentX, currentY, get_tetromino(curr_tetro))
                {
                    rnum = (rnum - 1 + 4) % 4; // Revert rotation if invalid
                }
            }
            
        }
}

bool canPlace(int x, int y, const vector<vector<bool>>& shape, const vector<vector<int>>& field) {
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
