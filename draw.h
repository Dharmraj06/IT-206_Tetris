#ifndef DRAW_H
#define DRAW_H

#include <vector>
#include <conio.h>

using namespace std;

//enum tetro { I, J, L, O, S, T, Z };

extern int Width;
extern int Height;
//extern tetro currentTetromino;
extern int rnum;

bool canPlace(int x, int y, const vector<vector<bool>> &shape, const vector<vector<int>> &field);
void control(const vector<vector<bool>> &shape, int currentX, int currentY, const vector<vector<int>> &field);
using namespace std;

bool canPlace(int x, int y, const vector<vector<bool>> &shape, const vector<vector<bool>> &field);
void control(const vector<vector<bool>> &shape, int &currentX, int &currentY, const vector<vector<bool>> &field, bool &gameOver);

#endif