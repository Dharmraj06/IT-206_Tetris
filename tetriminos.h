#ifndef TETRIMINOS_H
#define TETRIMINOS_H

#include <vector>
using namespace std;

enum tetro { I, O, S, T, Z, L, J };

class Tetromino {
public:
    vector<vector<bool>> get_tetromino(tetro curr_tetro);
    vector<vector<bool>> getRandomTetromino();

private:
    const vector<vector<vector<bool>>> TETROMINOS = {
        // I
        {{1, 1, 1, 1}},
        // J
        {{1, 0, 0}, {1, 1, 1}},
        // L
        {{0, 0, 1}, {1, 1, 1}},
        // O
        {{1, 1}, {1, 1}},
        // S
        {{0, 1, 1}, {1, 1, 0}},
        // T
        {{0, 1, 0}, {1, 1, 1}},
        // Z
        {{1, 1, 0}, {0, 1, 1}}
    };
};

#endif