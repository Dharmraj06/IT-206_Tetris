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
 

vector<vector<bool>> Logic::rotate(tetro curr_tetro, int rnum) {
    vector<vector<bool>> shape = get_tetromino(curr_tetro);
    int rotations = ((rnum % 4) + 4) % 4;
    if (rotations == 0) {
        return shape;
    }
    vector<vector<bool>> current_shape = shape;
    for (int r=0; r<rotations; r++) {
        int rows = current_shape.size();       
        int cols = current_shape[0].size(); 
        vector<vector<bool>> new_shape(cols, vector<bool>(rows));
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                new_shape[j][rows - 1 - i] = current_shape[i][j];
            }
        }
        current_shape = new_shape;
    }
    return current_shape;
}

int Logic::clear_lines(vector<vector<bool>> &grid) {
    
    int score=0;
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
