#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <conio.h> // For _kbhit and _getch (Windows)
#include <windows.h>
// Game constants
const int WIDTH = 10;
const int HEIGHT = 20;

// Tetromino shapes (represented as 2D vectors of booleans)
const std::vector<std::vector<std::vector<bool>>> TETROMINOS = {
    // I
    {{1, 1, 1, 1}},
    // J
    {{1, 0, 0}, {1, 1, 1}},
    // L
    {{0, 0, 1}, {1, 1, 1}},
    // O
    {{1, 1}, {1, 1}},
    // S
    {{0, 1, 1}, {1, 1, 0}},
    // T
    {{0, 1, 0}, {1, 1, 1}},
    // Z
    {{1, 1, 0}, {0, 1, 1}}};

// Game state
std::vector<std::vector<int>> field(HEIGHT, std::vector<int>(WIDTH, 0));
int currentTetromino = 0;
int currentRotation = 0;
int currentX = WIDTH / 2 - 2;
int currentY = 0;

// Function to draw the game field
void drawField()
{
    for (int y = 0; y < HEIGHT; ++y)
    {
        for (int x = 0; x < WIDTH; ++x)
        {
            if (field[y][x])
            {
                std::cout << "#"; // Filled cell
            }
            else
            {
                std::cout << "."; // Empty cell
            }
        }
        std::cout << std::endl;
    }
}

// Function to get the current tetromino shape
std::vector<std::vector<bool>> getCurrentShape()
{
    std::vector<std::vector<bool>> shape = TETROMINOS[currentTetromino];
    for (int r = 0; r < currentRotation; ++r)
    {
        std::vector<std::vector<bool>> rotated(shape[0].size(), std::vector<bool>(shape.size()));
        for (size_t i = 0; i < shape.size(); ++i)
        {
            for (size_t j = 0; j < shape[0].size(); ++j)
            {
                rotated[j][shape.size() - 1 - i] = shape[i][j];
            }
        }
        shape = rotated;
    }
    return shape;
}

// Function to check if a tetromino can be placed at a given position
bool canPlace(int x, int y, const std::vector<std::vector<bool>> &shape)
{
    for (size_t i = 0; i < shape.size(); ++i)
    {
        for (size_t j = 0; j < shape[0].size(); ++j)
        {
            if (shape[i][j])
            {
                if (x + j < 0 || x + j >= WIDTH || y + i >= HEIGHT || (y + i >= 0 && field[y + i][x + j]))
                {
                    return false;
                }
            }
        }
    }
    return true;
}

// Function to merge the current tetromino into the field
void mergeTetromino()
{
    std::vector<std::vector<bool>> shape = getCurrentShape();
    for (size_t i = 0; i < shape.size(); ++i)
    {
        for (size_t j = 0; j < shape[0].size(); ++j)
        {
            if (shape[i][j])
            {
                field[currentY + i][currentX + j] = 1;
            }
        }
    }
}

// Function to clear completed lines
void clearLines()
{
    for (int y = HEIGHT - 1; y >= 0; --y)
    {
        bool full = true;
        for (int x = 0; x < WIDTH; ++x)
        {
            if (!field[y][x])
            {
                full = false;
                break;
            }
        }
        if (full)
        {
            for (int yy = y; yy > 0; --yy)
            {
                field[yy] = field[yy - 1];
            }
            field[0] = std::vector<int>(WIDTH, 0);
            y++; // Check the same line again
        }
    }
}

int main()
{
    srand(static_cast<unsigned int>(time(nullptr)));

    while (true)
    {
        // Draw the field and current tetromino
        std::vector<std::vector<bool>> shape = getCurrentShape();
        std::vector<std::vector<int>> tempField = field;
        
        for (size_t i = 0; i < shape.size(); ++i)
        {
            for (size_t j = 0; j < shape[0].size(); ++j)
            {
                if (shape[i][j] && currentY + i >= 0)
                {
                    tempField[currentY + i][currentX + j] = 1;
                }
            }
        }
        for (int y = 0; y < HEIGHT; ++y)
        {
            for (int x = 0; x < WIDTH; ++x)
            {
                if (tempField[y][x])
                {
                    std::cout << "#";
                }
                else
                {
                    std::cout << ".";
                }
            }
            std::cout << std::endl;
        }

        // Handle user input
        if (_kbhit())
        {
            char key = _getch();
            if (key == 'a' && canPlace(currentX - 1, currentY, shape))
            {
                currentX--;
            }
            else if (key == 'd' && canPlace(currentX + 1, currentY, shape))
            {
                currentX++;
            }
            else if (key == 'w')
            {
                currentRotation = (currentRotation + 1) % 4;
                if (!canPlace(currentX, currentY, getCurrentShape()))
                {
                    currentRotation = (currentRotation - 1 + 4) % 4; // Revert rotation if invalid
                }
            }
            else if (key == 's')
            {
                if (canPlace(currentX, currentY + 1, shape))
                {
                    currentY++;
                }
            }
        }
        
        // Move tetromino down
        if (canPlace(currentX, currentY + 1, shape))
        {
            currentY++;
        }
        else
        {
            mergeTetromino();
            clearLines();
            currentTetromino = rand() % TETROMINOS.size();
            currentRotation = 0;
            currentX = WIDTH / 2 - 2;
            currentY = 0;
            if (!canPlace(currentX, currentY, getCurrentShape()))
            {
                std::cout << "Game Over!" << std::endl;
                break;
            }
        }

// Simple delay (adjust for desired speed)
#ifdef _WIN32
        Sleep(200);
#else
        usleep(200000); // 200 milliseconds
#endif
        system("cls"); // Clear screen (Windows)
    }

    return 0;
}