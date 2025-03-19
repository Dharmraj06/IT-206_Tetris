#include <vector>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <windows.h>
#include "logic.h"
#include "tetriminos.h"

Logic::Logic(){
    // CurrX = 0;
    // CurrY = 0;
}
int score = 0;   

vector<vector<bool>> Logic::rotate(tetro curr_tetro, int rnum) {


    vector<vector<bool>> shape = get_tetromino(curr_tetro);
    if (rnum % 4 == 0)
        return shape;

    for (int r = 0; r < rnum % 4; ++r) {
        vector<vector<bool>> new_shape(shape[0].size(), vector<bool>(shape.size()));

        for (int i = 0; i < shape.size(); ++i) {
            for (int j = 0; j < shape[0].size(); ++j) {
                new_shape[j][shape.size() - 1 - i] = shape[i][j];
            }
        }

        shape = new_shape;
    }

    return shape;
}

int Logic::clear_lines(vector<vector<bool>> &grid) {
    

    for (int y = HEIGHT - 1; y >= 0; y--) {
        bool full = true;
        for (int x = WIDTH-1; x >= 0; x--) {
            if (!grid[y][x]) {
                full = false;
                break;
            }
        }
        if (full) {
            score=score+10;
            for (int yy = y; yy > 0; yy--) {
                grid[yy] = grid[yy - 1];
            }
            grid[0] = vector<bool>(WIDTH, 0);
            y++;
        }
    }

    return score;
}

void Logic::addtogrid(vector<vector<bool>> &grid, tetro curr_tetro, int CurrX, int CurrY) {


    vector<vector<bool>> shape = get_tetromino(curr_tetro);

    for (int i = 0; i < shape.size(); i++) {
        for (int j = 0; j < shape[0].size(); j++) {
            if (shape[i][j]) {
                grid[CurrX + i][CurrY + j] = 1;
            }
        }
    }
}

// bool Logic::canPlace(int x, int y, const vector<vector<bool>>& shape, const vector<vector<bool>>& field) {

//     for (int i = 0; i < shape.size(); ++i) {
//         for (int j = 0; j < shape[0].size(); ++j) {

//             if (shape[i][j])
//             {
//                 if (x + j < 0 || x + j >= WIDTH || y + i >= HEIGHT || (y + i >= 0 && field[y + i][x + j]))
//                 {
//                     return false;
//                 }
//             }
//         }
//     }

//     return true;
// }
