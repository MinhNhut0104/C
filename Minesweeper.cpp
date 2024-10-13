#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

const int WIDTH = 10;
const int HEIGHT = 10;
const int MINES = 10;


void InitializeBoard(vector<vector<char>>& board, vector<vector<bool>>& mines) {
    // Ðat tat ca cac o thanh '.'
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            board[i][j] = '.';  // Cac o chua mo
        }
    }

    // Ðat min ngau nhien
    srand(static_cast<unsigned>(time(0)));
    for (int m = 0; m < MINES;) {
        int x = rand() % WIDTH;
        int y = rand() % HEIGHT;
        if (!mines[y][x]) {
            mines[y][x] = true;  // Ðat min
            m++;
        }
    }

    // Tính so luong min xung quanh cac o
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (mines[i][j]) continue;

            int count = 0;
            for (int dx = -1; dx <= 1; dx++) {
                for (int dy = -1; dy <= 1; dy++) {
                    int nx = j + dx;
                    int ny = i + dy;
                    if (nx >= 0 && nx < WIDTH && ny >= 0 && ny < HEIGHT && mines[ny][nx]) {
                        count++;
                    }
                }
            }
            if (count > 0) {
                board[i][j] = count + '0';  // Hien thi so min xung quanh
            }
        }
    }
}

// Ham hien thi bang
void DisplayBoard(const vector<vector<char>>& board) {
    cout << "   ";
    for (int j = 0; j < WIDTH; j++)
        cout << j << " ";
    cout << endl;

    for (int i = 0; i < HEIGHT; i++) {
        cout << i << " | ";
        for (int j = 0; j < WIDTH; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

// Ham hien thi bang min khi tro choi ket thuc
void DisplayMines(const vector<vector<bool>>& mines) {
    cout << "Bang min:\n";
    cout << "   ";
    for (int j = 0; j < WIDTH; j++)
        cout << j << " ";
    cout << endl;

    for (int i = 0; i < HEIGHT; i++) {
        cout << i << " | ";
        for (int j = 0; j < WIDTH; j++) {
            cout << (mines[i][j] ? '*' : '.') << " ";
        }
        cout << endl;
    }
}

// Kiem tra o co min
bool PlayGame(vector<vector<char>>& board, const vector<vector<bool>>& mines, int x, int y) {
    if (mines[y][x]) {
        cout << "Game Over! Ban da cham vao min!" << endl;
        return false;
    }

    board[y][x] = ' ';  // Ðanh dau o da mo
    return true;
}


int main() {
    vector<vector<char>> board(HEIGHT, vector<char>(WIDTH));
    vector<vector<bool>> mines(HEIGHT, vector<bool>(WIDTH, false));

    InitializeBoard(board, mines);
    
    while (true) {
        DisplayBoard(board);
        int x, y;
        cout << "Nhap toa do (x y): ";
        cin >> x >> y;

        // Kiem tra toa do nhap vao
        if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) {
            cout << "Toa do khong hop le! Vui lòng thu lai." << endl;
            continue;
        }

        // Choi game
        if (!PlayGame(board, mines, x, y)) {
            DisplayMines(mines);  // Hien thi min khi ket thuc tro choi
            break;
        }
    }
    return 0;
}

