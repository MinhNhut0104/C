#include <iostream>
#include <conio.h>
#include <windows.h>
#include <vector>

using namespace std;

// Khai bao cac bien toan cuc
bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
vector<int> tailX(100), tailY(100);
int nTail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

// Ham khoi tao tro choi
void Setup() {
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
}

// Ham ve tro choi
void Draw() {
    // Ðat con tro vi tri 0,0
    COORD coord = { 0, 0 };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

    // Ve khung trên
    for (int i = 0; i < width + 2; i++) 
        cout << "#";
    cout << endl;

    // Ve khung va cac phan tu trong tro choi
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0) 
                cout << "#"; // Khung bên trái
            if (i == y && j == x) 
                cout << "O"; // Ve ran
            else if (i == fruitY && j == fruitX) 
                cout << "F"; // Ve trái cây
            else {
                bool print = false;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        cout << "o"; // Ve duoi
                        print = true;
                    }
                }
                if (!print)
                    cout << " "; // Ve khoang trong de di chuyen
            }

            if (j == width - 1) 
                cout << "#"; // Khung bên phai
        }
        cout << endl;
    }

    // Ve khung duoi
    for (int i = 0; i < width + 2; i++) 
        cout << "#";
    cout << endl;

    cout << "Score: " << score << endl; // Hien thi diem
}

// Xu ly cac phim bam
void Input() {
    if (_kbhit()) { 
        switch (_getch()) {
            case 'a':
                dir = LEFT;
                break;
            case 'd':
                dir = RIGHT;
                break;
            case 'w':
                dir = UP;
                break;
            case 's':
                dir = DOWN;
                break;
            case 'x':
                gameOver = true; 
                break;
        }
    }
}

// Cap nhat trang thái trò choi
void Logic() {
    int prevX = tailX[0]; 
    int prevY = tailY[0];
    int prev2X, prev2Y;

    tailX[0] = x; 
    tailY[0] = y;

    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX; 
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    // Di chuyen theo huong
    switch (dir) {
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

    // Kiem tra va cham voi trái cây
    if (x == fruitX && y == fruitY) {
        score += 10; 
        fruitX = rand() % width; 
        fruitY = rand() % height;
        nTail++; 
    }

    // Kiem tra va cham voi tuong
    if (x >= width || x < 0 || y >= height || y < 0) {
        gameOver = true; 
    }

    // Kiem tra va cham voi chinh minh
    for (int i = 0; i < nTail; i++) {
        if (tailX[i] == x && tailY[i] == y) {
            gameOver = true; 
        }
    }
}


int main() {
    Setup(); 
    while (!gameOver) {
        Draw(); 
        Input(); 
        Logic(); // Cap nhat trang thai
        Sleep(100); // Cho truoc khi tiep tuc
    }
    return 0; 
}

