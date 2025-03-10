#include<stdio.h>

using namespace std;

int Width = 10;
int Height = 20;

class grid()
{
    for (int i = 0; i < Height; i++) {
        for (int j = 0; j < Width; j++) {
            
            if (i == 0 || i == height - 1 || j == 0 || j == width - 1) {
                cout << "#";
            } else {
                cout << " ";
            }
        }
        cout << endl;
    }

}