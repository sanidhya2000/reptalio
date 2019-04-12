#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;
bool gameOver;
const int w = 30;
const int h = 30;
int x, y, grapeX, grapeY, score;
int tailX[120], tailY[120];
int nTail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;
void getData()
{
    gameOver = false;
    dir = STOP;
    x = w / 2;
    y = h / 2;
    grapeX = rand() % w;
    grapeY = rand() % h;
    score = 0;
}
void Draw()
{
    system("cls"); //system("clear");
    for (int i = 0; i < w+2; i++)
        cout << "*";
    cout << endl;
 
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            if (j == 0)
                cout << "*";
            if (i == y && j == x)
                cout << "@";
            else if (i == grapeY && j == grapeX)
                cout << "$";
            else
            {
                bool print = false;
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << "o";
                        print = true;
                    }
                }
                if (!print)
                    cout << " ";
            }
                 
 
            if (j == w - 1)
                cout << "*";
        }
        cout << endl;
    }
 
    for (int i = 0; i < w+2; i++)
        cout << "*";
    cout << endl;
    cout << "Score:" << score << endl;
}
void Input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'l':
            dir = LEFT;
            break;
        case 'r':
            dir = RIGHT;
            break;
        case 'u':
            dir = UP;
            break;
        case 'd':
            dir = DOWN;
            break;
        case 'x':
            gameOver = true;
            break;
        }
    }
}
void Logic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (dir)
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }
    //if (x > width || x < 0 || y > height || y < 0)
    //  gameOver = true;
    if (x >= w) x = 0; else if (x < 0) x = w - 1;
    if (y >= h) y = 0; else if (y < 0) y = h - 1;
 
    for (int i = 0; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;
 
    if (x == grapeX && y == grapeY)
    {
        score += 10;
        grapeX = rand() % w;
        grapeY = rand() % h;
        nTail++;
    }
}
int main()
{
    getData();
    while (!gameOver)
    {
        Draw();
        Input();
        Logic();
        Sleep(10); //sleep(10);
    }
    return 0;
}
