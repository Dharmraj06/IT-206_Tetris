#include <bits/stdc++.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <windows.h>

const int WIDTH = 10;
const int HEIGHT = 20;

using namespace std;

// rotate the tetromino
enum tetro
{
    L,
    O,
    I,
    S,
    Z,
    J,
    T
};

vector<vector<bool>> get_tetromino(tetro curr_tetro);

vector<vector<bool>> rotate(tetro curr_tetro, int rnum)
{

    vector<vector<bool>> shape = get_tetromino(curr_tetro); // Tetrominos will be accessed from the file itself and not the vector
    if (rnum % 4 == 0)
        return shape;

    for (int r = 0; r < rnum % 4; ++r)
    {
        vector<vector<bool>> new_shape(shape[0].size(), vector<bool>(shape.size()));
        for (int i = 0; i < shape.size(); ++i)
        {
            for (int j = 0; j < shape[0].size(); ++j)
            {
                new_shape[j][shape.size() - 1 - i] = shape[i][j];
            }
        }
        shape = new_shape;
    }

    return shape;
}

//checks and clears the lines which are full
int clear_lines(vector<vector<bool>> &grid)
{
    int score = 0;
    for (int y = HEIGHT - 1; y >= 0; y--)
    {
        bool full = true;
        for (int x = 0; x < WIDTH; x--)
        {
            if (!grid[y][x])
            {
                full = false;
                break;
            }
        }
        if (full)
        {
            score++;
            for (int yy = y; yy > 0; yy--)
            {
                grid[yy] = grid[yy - 1];
            }
            grid[0] = vector<bool>(WIDTH, 0);
            y++;
        }
    }

    return score;
}

int CurrX, CurrY;
//when the tetromino is placed
void addtogrid(vector<vector<bool>> &grid, tetro curr_tetro)
{

    vector<vector<bool>> shape = get_tetromino(curr_tetro);
    for (int i = 0; i < shape.size(); i++)
    {
        for (int j = 0; j < shape[0].size(); j++)
        {
            if (shape[i][j])
            {
                grid[CurrX + i][CurrY + j] = 1;
            }
        }
    }
}
