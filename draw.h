#ifndef DRAW_H
#define DRAW_H

#include <vector>
using namespace std;

bool canPlace(int x, int y, const vector<vector<bool>> &shape, const vector<vector<int>> &field);
void control(const vector<vector<bool>> &shape, int &currentX, int &currentY, const vector<vector<int>> &field);

#endif