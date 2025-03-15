#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include "draw.h"
#include "tetriminos.h"
#include "logic.h"

using namespace std;

void drawField(const vector<vector<bool>> &field)
{

    for (int y = 0; y < HEIGHT; ++y)
    {

        for (int x = 0; x < WIDTH; ++x)
        {

            if (field[y][x] == 0)
                std::cout << ".";
            else
                std::cout << "#";
        }
        std::cout << std::endl;
    }
}

int main()
{
    srand(time(0));
    vector<vector<bool>> field(HEIGHT, vector<bool>(WIDTH, 0));
    Logic logic;

    tetro currenttetro = static_cast<tetro>(rand() % 7);

    vector<vector<bool>> shape = get_tetromino(currenttetro);

    int currentX = WIDTH / 2 - shape[0].size() / 2;
    int currentY = 0;

    while (true)
    {
        vector<vector<bool>> tempField = field;
        system("cls");
        drawField(tempField);

        control(shape, currentX, currentY, tempField);

        if (!logic.canPlace(currentX, currentY, shape, field))
        {
            break;
        }

        for (int i = 0; i < shape.size(); ++i)
        {
            for (int j = 0; j < shape[0].size(); ++j)
            {
                if (shape[i][j] && currentY + i >= 0)
                {
                    tempField[currentY + i][currentX + j] = 1;
                }
            }
        }

        logic.addtogrid(field, currenttetro, currentX, currentY);

        currenttetro = static_cast<tetro>(rand() % 7);
        shape = get_tetromino(currenttetro);

        // currentX = WIDTH / 2 - shape[0].size() / 2;
        // currentY = 0;
       
    #ifdef _WIN32
        Sleep(200);
    #else
        usleep(200000); // 200 milliseconds
    #endif
        system("cls"); 
    }

    std::cout << "Game Over!" << std::endl;
    return 0;
}


    