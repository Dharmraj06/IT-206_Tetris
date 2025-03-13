#include <iostream>
#include <vector>
#include <conio.h>
#include <windows.h>
#include <ctime>

using namespace std;

const int width = 10;
const int height = 20;

char board[height][width];

vector<vector<string>> tetrominoes = {
    {"..X...X...X...X."},    //I
    {".XX..XX........."},    //O
    {".X...XX...X....."},    //S
    {"..X..XX...X....."},    //T
    {".XX...XX........"},    //Z
    {".X...X...XX....."},    //L
    {"..X...X..XX....."}     //J
};
