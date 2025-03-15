#ifndef LOGIC_H
#define LOGIC_H

#include <vector>
#include "tetriminos.h"
using namespace std;

const int WIDTH = 10;
const int HEIGHT = 20;

//enum tetro {  I,J,L,O,S,T,Z  };

class Logic {
    
public:
    Logic();

    vector<vector<bool>> rotate(tetro curr_tetro, int rnum);

    int clear_lines(vector<vector<bool>> &grid);

    void addtogrid(vector<vector<bool>> &grid, tetro curr_tetro, int CurrX, int CurrY);

    bool canPlace(int x, int y, const vector<vector<bool>>& shape, const vector<vector<bool>>& field);


private:
    //int CurrX, CurrY;

    tetro tetromino;
};

#endif