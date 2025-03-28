#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <windows.h>

using namespace std;

const int WIDTH = 10;
const int HEIGHT = 20;
int score = 0;
int highScore = 0;
time_t startTime;

const vector<vector<vector<bool>>> TETROMINOS = {
    {{1, 1, 1, 1}},

    {{1, 0, 0}, {1, 1, 1}},

    {{0, 0, 1}, {1, 1, 1}},

    {{1, 1}, {1, 1}},


    {{0, 1, 1}, {1, 1, 0}},

    {{0, 1, 0}, {1, 1, 1}},

    {{1, 1, 0}, {0, 1, 1}}
};

vector<vector<int>> field(HEIGHT, vector<int>(WIDTH, 0));

int currtetromino;
int currentrotation;
int currX;
int currY;

vector<int> tetrocolors = {14, 12, 10, 9, 13, 11, 6};



void resetGame() {

    field = vector<vector<int>>(HEIGHT, vector<int>(WIDTH, 0));

    currtetromino = rand() % TETROMINOS.size();

    currentrotation = 0;
    currX = WIDTH / 2 - 2;

    currY = 0;
    score = 0;

    startTime = time(nullptr);
}

vector<vector<bool>> getcurrentshape() {

    vector<vector<bool>> shape = TETROMINOS[currtetromino];

    for (int r = 0; r < currentrotation; r++) {

        vector<vector<bool>> rotated(shape[0].size(), vector<bool>(shape.size()));

        for (int i = 0; i < shape.size(); ++i){
            for (int j = 0; j < shape[0].size(); ++j){

                rotated[j][shape.size() - 1 - i] = shape[i][j];
            }
        }

        shape = rotated;
    }

    return shape;
}

bool canPlace(int x, int y, const vector<vector<bool>> &shape) {
    for (int i = 0; i < shape.size(); i++){

        for (int j = 0; j < shape[0].size(); j++){

            if (shape[i][j] && (x + j < 0 || x + j >= WIDTH || y + i >= HEIGHT || (y + i >= 0 && field[y + i][x + j])))
                return false;
        }
    }
    return true;
}

void setColor(int color) {

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);

}

void drawField() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD cursorPosition = {0, 0};
    SetConsoleCursorPosition(consoleHandle, cursorPosition);

    vector<vector<int>> tempfield = field;

    vector<vector<bool>> shape = getcurrentshape();


    for (int i = 0; i < shape.size(); i++){
        for (int j = 0; j < shape[0].size(); j++){

            if (shape[i][j] && currY + i >= 0)
                tempfield[currY + i][currX + j] = currtetromino + 1;
    
            }
        }

    time_t currentTime = time(nullptr);

    int elapsedTime = static_cast<int>(currentTime - startTime);

    cout << "Score: " << score << "  High Score: " << highScore << "  Time: " << elapsedTime << "s\n";

    for (int y = 0; y < HEIGHT; ++y) {

        setColor(9);
        cout << "|";

        for (int x = 0; x < WIDTH; ++x) {
            if (tempfield[y][x]) {

                setColor(tetrocolors[tempfield[y][x] - 1]);
                cout << "# ";

            } else {

                setColor(7);
                cout << ". ";
            }
        }

        setColor(9);
        cout << "|\n";
    }
    setColor(9);

    cout << "+" << string(WIDTH*2, '-') << "+\n";

    setColor(7);
}

void addtogrid() {

    vector<vector<bool>> shape = getcurrentshape();

    for (int i = 0; i < shape.size(); ++i)
    {
        for (int j = 0; j < shape[0].size(); ++j){

            if (shape[i][j])
            field[currY + i][currX + j] = currtetromino + 1;
        }

    }        
}

void clearLines() {

    for (int y = HEIGHT - 1; y >= 0; --y) {

        bool full = true;
        for (int x = 0; x < WIDTH; ++x){
            if (!field[y][x]) {
                full = false;
                break;
            }

        }

        if (full) {

            for (int yy = y; yy > 0; --yy)
                field[yy] = field[yy - 1];

            field[0] = vector<int>(WIDTH, 0);
            score += 100;

            Beep(1000, 200);
            y++;
        }
    }
}
void hideCursor() {

    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(consoleHandle, &cursorInfo);
    cursorInfo.bVisible = FALSE;  

    SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}

bool gameLoop() {
    resetGame();

    while (true) {

        drawField();

        if (GetAsyncKeyState(VK_LEFT) & 0x8000 && canPlace(currX - 1, currY, getcurrentshape()))
            currX--;

        if (GetAsyncKeyState(VK_RIGHT) & 0x8000 && canPlace(currX + 1, currY, getcurrentshape()))
            currX++;

        if (GetAsyncKeyState(VK_UP) & 0x8000) {

            currentrotation = (currentrotation + 1) % 4;

            if (!canPlace(currX, currY, getcurrentshape()))
                currentrotation = (currentrotation - 1 + 4) % 4;
        }
        if (GetAsyncKeyState(VK_DOWN) & 0x8000 && canPlace(currX, currY + 1, getcurrentshape()))
            currY++;

        if (GetAsyncKeyState('X') & 0x8000 || GetAsyncKeyState('x') & 0x8000) {
            cout << "\nGAME OVER!\n";
            Beep(500, 500);
            break;
        }

        //check if place or nto else move down
        if (canPlace(currX, currY + 1, getcurrentshape()))
            currY++;
        else {

            addtogrid();
            clearLines();
            currtetromino = rand() % TETROMINOS.size();

            currentrotation = 0;
            currX = WIDTH / 2 - 2;
            currY = 0;

            if (!canPlace(currX, currY, getcurrentshape())) {

                setColor(12);
                cout << "\nGAME OVER!\n";
                Beep(500, 500);
                return false;

            }
        }

        Sleep(150);
    }

    return true;
}

int main() {


    srand(static_cast<unsigned int>(time(nullptr)));
    system("cls");


    while (true) {
        hideCursor();

        bool restart = gameLoop();
        if (score > highScore)
            highScore = score;

        setColor(12);

        cout << "\nYour Score: " << score << "  High Score: " << highScore << endl;
        setColor(7);

        cout << "Do you want to restart? (Y/N): ";
        char choice;
        cin >> choice;
        
        if (choice == 'n' || choice == 'N') {
            cout << "Final Score: " << score << "  High Score: " << highScore << endl;
            break;
        }
    }

    return 0;
}
