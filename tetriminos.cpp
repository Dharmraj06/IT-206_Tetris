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


class Tetromino {
    public:
        
    };

    class I : public Tetromino {
    public:
        I() : Tetromino({{1, 1, 1, 1}}) {}
    };
    
    class J : public Tetromino {
    public:
        J() : Tetromino({{1, 0, 0}, {1, 1, 1}}) {}
    };
    
    class O : public Tetromino {
    public:
        O() : Tetromino({{1, 1}, {1, 1}}) {}
    };
    
    class L : public Tetromino {
    public:
        L() : Tetromino({{0, 0, 1}, {1, 1, 1}}) {}
    };
    
    class S : public Tetromino {
    public:
        S() : Tetromino({{0, 1, 1}, {1, 1, 0}}) {}
    };
    
    class Z : public Tetromino {
    public:
        Z() : Tetromino({{1, 1, 0}, {0, 1, 1}}) {}
    };
    
    class T : public Tetromino {
    public:
        T() : Tetromino({{0, 1, 0}, {1, 1, 1}}) {}
    };

    Tetromino *currentPiece = new Tetromino(rand() % 7);