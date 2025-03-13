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

struct Tetromino {
    int x, y, type, rotation;
    Tetromino(int t) : x(width / 2 - 1), y(0), type(t), rotation(0) {}      //Constructor
};

Tetromino *currentPiece;
bool gameOver = false;
int score = 0;

void InitBoard() {
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            board[i][j] = '.';
}

void PrintBoard() {
    system("cls");
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++)
            cout << board[i][j] << " ";
        cout << endl;
    }
    cout << "Score: " << score << endl;
}

bool CheckCollision(int x, int y, int rotation) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            int index = rotation * 4 + i * 4 + j;
            if (tetrominoes[currentPiece->type][0][index] == 'X') {
                int newX = x + j, newY = y + i;
                if (newX < 0 || newX >= width || newY >= height || (newY >= 0 && board[newY][newX] != '.'))
                    return true;
            }
        }
    }
    return false;
}

void PlacePiece() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            int index = currentPiece->rotation * 4 + i * 4 + j;
            if (tetrominoes[currentPiece->type][0][index] == 'X') {
                board[currentPiece->y + i][currentPiece->x + j] = 'X';
            }
        }
    }
}

void ClearLines() {
    for (int i = height - 1; i >= 0; i--) {
        bool full = true;
        for (int j = 0; j < width; j++) {
            if (board[i][j] == '.') {
                full = false;
                break;
            }
        }
        if (full) {
            for (int k = i; k > 0; k--)
                for (int j = 0; j < width; j++)
                    board[k][j] = board[k - 1][j];
            for (int j = 0; j < width; j++)
                board[0][j] = '.';
            score += 100;
            i++; 
        }
    }
}

void MovePiece(int dx, int dy, int rotation) {
    if (!CheckCollision(currentPiece->x + dx, currentPiece->y + dy, rotation)) {
        currentPiece->x += dx;
        currentPiece->y += dy;
        currentPiece->rotation = rotation;
    }
}

void DropPiece() {
    while (!CheckCollision(currentPiece->x, currentPiece->y + 1, currentPiece->rotation))
        currentPiece->y++;
    PlacePiece();
    ClearLines();
    delete currentPiece;
    currentPiece = new Tetromino(rand() % 7);
    if (CheckCollision(currentPiece->x, currentPiece->y, currentPiece->rotation))
        gameOver = true;
}

void HandleInput() {
    if (_kbhit()) {
        char ch = _getch();
        if (ch == 27) gameOver = true;
        else if (ch == 'a') MovePiece(-1, 0, currentPiece->rotation);
        else if (ch == 'd') MovePiece(1, 0, currentPiece->rotation);
        else if (ch == 's') MovePiece(0, 1, currentPiece->rotation);
        else if (ch == 'w') MovePiece(0, 0, (currentPiece->rotation + 1) % 4);
        else if (ch == ' ') DropPiece();
    }
}

void GameLoop() {
    currentPiece = new Tetromino(rand() % 7);
    while (!gameOver) {
        PrintBoard();
        HandleInput();
        Sleep(500);
        MovePiece(0, 1, currentPiece->rotation);
    }
    cout << "Game Over! Final Score: " << score << endl;
}

int main() {
    srand(time(0));
    InitBoard();
    GameLoop();
    return 0;
}