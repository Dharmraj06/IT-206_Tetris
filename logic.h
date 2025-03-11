#ifndef LOGIC_H
#define LOGIC_H

#include <vector>
using namespace std;

const int WIDTH = 10;
const int HEIGHT = 20;

enum tetro { L, O, I, S, Z, J, T };




vector<vector<bool>> get_tetromino(tetro curr_tetro);

vector<vector<bool>> rotate(tetro curr_tetro, int rnum);

int clear_lines(vector<vector<bool>> &grid);

void addtogrid(vector<vector<bool>> &grid, tetro curr_tetro);



int CurrX, CurrY;

#endif