#include <bits/stdc++.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <windows.h>

const int WIDTH = 10;
const int HEIGHT = 20;

using namespace std;

// merge tetromino
// can the shape of the tetromino be placed or not

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
    if(rnum%4 == 0)return shape;

    for (int r = 0; r < rnum%4; ++r)
    {
        vector<vector<bool>>new_shape(shape[0].size(), vector<bool>(shape.size()));
        for (size_t i = 0; i < shape.size(); ++i)
        {
            for (size_t j = 0; j < shape[0].size(); ++j)
            {
            new_shape[j][shape.size() - 1 - i] = shape[i][j];
            }
        }
        shape =new_shape;
    }

    return shape;
}

int clear_lines(vector<vector<int>> grid)
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
            grid[0] = vector<int>(WIDTH, 0);
            y++;
        }
    }

    return score;
}


