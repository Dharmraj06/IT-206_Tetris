#include <iostream>
#include <vector>
#include <conio.h>
#include <windows.h>
#include <ctime>

using namespace std;

const int width = 10;
const int height = 20;

char board[height][width];


class Tetromino {
    public:
        vector<vector<bool>> I() { return {{1, 1, 1, 1}}; }
        vector<vector<bool>> J() { return {{1, 0, 0}, {1, 1, 1}}; }
        vector<vector<bool>> O() { return {{1, 1}, {1, 1}}; }
        vector<vector<bool>> L() { return {{0, 0, 1}, {1, 1, 1}}; }
        vector<vector<bool>> S() { return {{0, 1, 1}, {1, 1, 0}}; }
        vector<vector<bool>> Z() { return {{1, 1, 0}, {0, 1, 1}}; }
        vector<vector<bool>> T() { return {{0, 1, 0}, {1, 1, 1}}; }
    };

    

    Tetromino *currentPiece = new Tetromino(rand() % 7);

    vector<vector<bool>> GetTetromino(int integer) {
        if (integer == 1) 
            {
                return {{1, 1, 1, 1}};
            }    
        if (integer == 2) 
            { 
                return {{1, 0, 0}, {1, 1, 1}};
            }
        if (integer == 3) 
            { 
                return {{1, 1}, {1, 1}};
            }
        if (integer == 4) 
            { 
                return {{0, 0, 1}, {1, 1, 1}};
            }
        if (integer == 5) 
            { 
                return {{0, 1, 1}, {1, 1, 0}};
            }
        if (integer == 6) 
            { 
                return {{1, 1, 0}, {0, 1, 1}};
            }
        if (integer == 7) 
            { 
                return {{0, 1, 0}, {1, 1, 1}};
            }
        return {};
    }
    
    vector<vector<bool>> getRandomTetromino() {
        srand(static_cast<unsigned int>(time(nullptr)));
        int index = rand() % Tetromino.size();
        return Tetromino[index];
    }

