#ifndef LOGIC_H
#define LOGIC_H

#include <vector>
#include "tetriminos.h"
using namespace std;

const int WIDTH = 10;
const int HEIGHT = 20;

enum tetro { I, O, S, T, Z, L, J };

class Logic {
    
public:
    Logic();

    vector<vector<bool>> rotate(tetro curr_tetro, int rnum);

    int clear_lines(vector<vector<bool>> &grid);

    void addtogrid(vector<vector<bool>> &grid, tetro curr_tetro);

    bool canPlace(int x, int y, const vector<vector<bool>>& shape, const vector<vector<int>>& field);


private:
    int CurrX, CurrY;

    Tetromino tetromino;
};

#endif