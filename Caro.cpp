#include <iostream>
using namespace std;

const int SIZE = 3; // Kich thuoc ban co 3x3

// Ham hien thi ban co
void displayBoard(char board[SIZE][SIZE]) {
    cout << "  0 1 2\n";
    for (int i = 0; i < SIZE; i++) {
        cout << i << " ";
        for (int j = 0; j < SIZE; j++) {
            cout << board[i][j];
            if (j < SIZE - 1) cout << "|";
        }
        cout << endl;
        if (i < SIZE - 1) cout << "  -----\n";
    }
}

// Ham kiem tra ket qua
char checkWin(char board[SIZE][SIZE]) {
    // Kiem tra hang ngang
    for (int i = 0; i < SIZE; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ')
            return board[i][0];
    }

    // Kiem tra hang doc
    for (int j = 0; j < SIZE; j++) {
        if (board[0][j] == board[1][j] && board[1][j] == board[2][j] && board[0][j] != ' ')
            return board[0][j];
    }

    // Kiem tra duong cheo
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ')
        return board[0][0];
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ')
        return board[0][2];

    // Kiem tra hoa (neu khong con o trong nao)
    bool draw = true;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == ' ')
                draw = false;
        }
    }

    if (draw) return 'D'; // D cho draw (hoa)
    
    return ' '; // Khong co ai thang va van con o trong
}

// Ham kiem tra neu co the thang o buoc tiep theo
bool canWinNextMove(char board[SIZE][SIZE], char player, int &x, int &y) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == ' ') {
                // Danh thu vao o nay
                board[i][j] = player;
                if (checkWin(board) == player) {
                    x = j;  // Tr?c x là c?t
                    y = i;  // Tr?c y là hàng
                    board[i][j] = ' '; // Huy nuoc danh thu
                    return true;
                }
                board[i][j] = ' '; // Huy nuoc danh thu
            }
        }
    }
    return false;
}

// Ham de may tinh choi nuoc di
void computerMove(char board[SIZE][SIZE]) {
    int x, y;

    // Uu tien nuoc di thang cho may tinh
    if (canWinNextMove(board, 'O', x, y)) {
        board[y][x] = 'O';
        cout << "May di nuoc tai (" << x << ", " << y << ") de thang\n";
        return;
    }

    // Chan nuoc di thang cua nguoi choi
    if (canWinNextMove(board, 'X', x, y)) {
        board[y][x] = 'O';
        cout << "May di nuoc tai (" << x << ", " << y << ") de chan nguoi choi thang\n";
        return;
    }

    // Neu khong co nuoc thang hoac chan, di nuoc ngau nhien
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = 'O';
                cout << "May di nuoc tai (" << j << ", " << i << ")\n";
                return;
            }
        }
    }
}


int main() {
    char board[SIZE][SIZE] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}}; // Khoi tao ban co rong
    char currentPlayer = 'X'; // Nguoi choi dau tien la 'X'
    int x, y;

    while (true) {
        displayBoard(board); // Hien thi ban co

        if (currentPlayer == 'X') {
            // Nguoi choi di
            cout << "Nguoi choi " << currentPlayer << ", nhap toa do (x y): ";
            cin >> x >> y;

            // Kiem tra toa do hop le
            if (y < 0 || y >= SIZE || x < 0 || x >= SIZE || board[y][x] != ' ') {
                cout << "Toa do khong hop le, vui long nhap lai!\n";
                continue;
            }

            // Danh dau tren ban co
            board[y][x] = currentPlayer;
        } else {
            // May tinh di nuoc
            computerMove(board);
        }

        // Kiem tra ket qua sau moi nuoc di
        char result = checkWin(board);
        if (result == 'X' || result == 'O') {
            displayBoard(board);
            cout << "Nguoi choi " << result << " thang!\n";
            break;
        } else if (result == 'D') {
            displayBoard(board);
            cout << "Tran dau hoa!\n";
            break;
        }

        // Chuyen luot choi
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }

    return 0;
}

