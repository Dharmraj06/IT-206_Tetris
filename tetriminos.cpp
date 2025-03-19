#include <iostream>
#include <vector>
#include <conio.h>
#include <windows.h>
#include <ctime>
#include "tetriminos.h"
#include "logic.h"
#include <cstdlib>

using namespace std;

const int width = 10;
const int height = 20;

char board[height][width];

int currtetro = 0;

vector<vector<bool>> get_tetromino(tetro curr_tetro) {

    return TETROMINOS[curr_tetro];
}

vector<vector<bool>> getRandomTetromino() {

    srand(static_cast<unsigned int>(time(nullptr)));

    int index = rand() % TETROMINOS.size();
    return TETROMINOS[index];
}
