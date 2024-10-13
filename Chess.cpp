#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // Them thu vien de dung std::max va std::min

enum PieceType { King, Queen, Rook, Bishop, Knight, Pawn, None };
enum Color { White, Black };

// Cau truc Piece dai dien cho mot quan co
struct Piece {
    PieceType type; // Loai quan co (King, Queen, etc.)
    Color color;    // Mau cua quan co (White hoac Black)
    
    Piece(PieceType t = None, Color c = White) : type(t), color(c) {}
};

const int BOARD_SIZE = 8; // Kich thuoc ban co vua

class Board; // Khai bao truoc lop Board

// Khai bao ham minimax truoc khi su dung no trong Game
int minimax(Board board, int depth, bool maximizingPlayer, int alpha, int beta);

// Lop Board dai dien cho ban co vua
class Board {
public:
    Piece board[BOARD_SIZE][BOARD_SIZE]; // Ban co gom mang 2 chieu chua cac quan co

    // Ham khoi tao, thiet lap ban co ban dau
    Board() {
        setupBoard(); // Goi ham thiet lap vi tri ban dau cua cac quan co
    }

    // Ham thiet lap vi tri cac quan co tren ban co
    void setupBoard() {
        // Thiet lap vi tri cac quan co trang
        board[0][0] = Piece(Rook, White);
        board[0][7] = Piece(Rook, White);
        board[0][1] = Piece(Knight, White);
        board[0][6] = Piece(Knight, White);
        board[0][2] = Piece(Bishop, White);
        board[0][5] = Piece(Bishop, White);
        board[0][3] = Piece(Queen, White);
        board[0][4] = Piece(King, White);
        
        // Thiet lap vi tri quan tot trang
        for (int i = 0; i < BOARD_SIZE; ++i) {
            board[1][i] = Piece(Pawn, White); // Hang 1 cho quan tot trang
            board[6][i] = Piece(Pawn, Black); // Hang 6 cho quan tot den
        }

        // Thiet lap vi tri cac quan co den
        board[7][0] = Piece(Rook, Black);
        board[7][7] = Piece(Rook, Black);
        board[7][1] = Piece(Knight, Black);
        board[7][6] = Piece(Knight, Black);
        board[7][2] = Piece(Bishop, Black);
        board[7][5] = Piece(Bishop, Black);
        board[7][3] = Piece(Queen, Black);
        board[7][4] = Piece(King, Black);

        // Thiet lap cac o con lai la o trong
        for (int i = 2; i < 6; ++i) {
            for (int j = 0; j < BOARD_SIZE; ++j) {
                board[i][j] = Piece(); // O trong
            }
        }
    }
    
    // Ham hien thi ban co
    void displayBoard() {
        for (int i = 0; i < BOARD_SIZE; ++i) {
            for (int j = 0; j < BOARD_SIZE; ++j) {
                if (board[i][j].type == None) {
                    std::cout << ". "; // Hien thi o trong la dau cham
                } else {
                    std::cout << getPieceSymbol(board[i][j]) << " "; // Hien thi ky hieu quan co
                }
            }
            std::cout << std::endl;
        }
    }

    // Ham tra ve ky hieu quan co dua tren loai va mau
    char getPieceSymbol(const Piece& piece) {
        if (piece.type == King) return (piece.color == White) ? 'K' : 'k';
        if (piece.type == Queen) return (piece.color == White) ? 'Q' : 'q';
        if (piece.type == Rook) return (piece.color == White) ? 'R' : 'r';
        if (piece.type == Bishop) return (piece.color == White) ? 'B' : 'b';
        if (piece.type == Knight) return (piece.color == White) ? 'N' : 'n';
        if (piece.type == Pawn) return (piece.color == White) ? 'P' : 'p';
        return '.'; // O trong
    }

    // Ham kiem tra dieu kien ket thuc tro choi (tam thoi tra ve false)
    bool isGameOver() {
        return false; // Mac dinh tro choi chua ket thuc
    }

    // Ham chuyen doi nuoc di thanh chuoi (vi du: e2 e4)
    std::string convertMove(int fromX, int fromY, int toX, int toY) {
        std::string move;
        move += (char)('a' + fromY); // Chuyen cot thanh ky tu
        move += std::to_string(fromX + 1); // Chuyen dong thanh so
        move += " ";
        move += (char)('a' + toY); // Chuyen cot dich thanh ky tu
        move += std::to_string(toX + 1); // Chuyen dong dich thanh so
        return move;
    }

    // Lay tat ca cac nuoc di co the cua mot nguoi choi
    std::vector<std::string> getAllPossibleMoves(Color player) {
        std::vector<std::string> moves;
        
        for (int i = 0; i < BOARD_SIZE; ++i) {
            for (int j = 0; j < BOARD_SIZE; ++j) {
                if (board[i][j].color == player) {
                    // Lay cac nuoc di cho quan Tot
                    if (board[i][j].type == Pawn) {
                        if (player == White) {
                            if (i + 1 < BOARD_SIZE && board[i + 1][j].type == None) {
                                moves.push_back(convertMove(i, j, i + 1, j)); // Di thang 1 o
                            }
                        } else {
                            if (i - 1 >= 0 && board[i - 1][j].type == None) {
                                moves.push_back(convertMove(i, j, i - 1, j)); // Di thang 1 o
                            }
                        }
                    }

                    // Lay cac nuoc di cho quan Xe
                    if (board[i][j].type == Rook) {
                        // Di chuyen theo hang ngang
                        for (int x = i + 1; x < BOARD_SIZE && board[x][j].type == None; ++x) {
                            moves.push_back(convertMove(i, j, x, j));
                        }
                        for (int x = i - 1; x >= 0 && board[x][j].type == None; --x) {
                            moves.push_back(convertMove(i, j, x, j));
                        }
                        // Di chuyen theo cot doc
                        for (int y = j + 1; y < BOARD_SIZE && board[i][y].type == None; ++y) {
                            moves.push_back(convertMove(i, j, i, y));
                        }
                        for (int y = j - 1; y >= 0 && board[i][y].type == None; --y) {
                            moves.push_back(convertMove(i, j, i, y));
                        }
                    }

                    // Thêm các quân c? khác (Knight, Bishop, Queen, King) tuong t?
                }
            }
        }
        
        return moves;
    }

    // Ham thuc hien nuoc di
    void makeMove(const std::string& move) {
        int fromX = move[1] - '1'; // Toa do dong bat dau
        int fromY = move[0] - 'a'; // Toa do cot bat dau
        int toX = move[4] - '1';   // Toa do dong ket thuc
        int toY = move[3] - 'a';   // Toa do cot ket thuc

        if (board[fromX][fromY].type != None) {
            // Di chuyen quan co toi vi tri moi
            board[toX][toY] = board[fromX][fromY];
            board[fromX][fromY] = Piece(); // Lam trong vi tri cu
        } else {
            std::cout << "Nuoc di khong hop le!" << std::endl;
        }
    }

    // Ham danh gia ban co (tam thoi tra ve 0)
    int evaluate() {
        return 0; // Thay the bang logic danh gia thuc te
    }
};

// Lop Game dai dien cho mot tro choi vua
class Game {
    Board board;              // Ban co
    Color currentPlayer;      // Nguoi choi hien tai

public:
    // Ham khoi tao, nguoi choi trang di truoc
    Game() : currentPlayer(White) {}

    // Ham bat dau choi
    void play() {
        while (true) {
            board.displayBoard(); // Hien thi ban co
            if (currentPlayer == White) {
                playerMove();      // Nguoi choi trang di
            } else {
                aiMove();          // AI di chuyen
            }
            if (board.isGameOver()) break;
            switchPlayer();        // Doi luot choi
        }
    }

    // Ham doi nguoi choi
    void switchPlayer() {
        currentPlayer = (currentPlayer == White) ? Black : White;
    }

    // Ham xu ly nuoc di cua nguoi choi
    void playerMove() {
        std::cout << "Nhap nuoc di (dinh dang: e2 e4): ";
        std::string move;
        std::getline(std::cin, move);
        board.makeMove(move);
    }

    // Ham xu ly nuoc di cua AI
    void aiMove() {
        std::cout << "AI dang di chuyen..." << std::endl;
        std::vector<std::string> possibleMoves = board.getAllPossibleMoves(Black);
        if (possibleMoves.empty()) {
            std::cout << "AI khong co nuoc di!" << std::endl;
            return;
        }

        int bestEval = -9999;
        std::string bestMove;
        for (const std::string& move : possibleMoves) {
            Board newBoard = board;
            newBoard.makeMove(move);
            int eval = minimax(newBoard, 3, false, -10000, 10000);
            if (eval > bestEval) {
                bestEval = eval;
                bestMove = move;
            }
        }
        board.makeMove(bestMove);
    }
};

// Ham thuat toan Minimax de AI tinh toan nuoc di
int minimax(Board board, int depth, bool maximizingPlayer, int alpha, int beta) {
    if (depth == 0 || board.isGameOver()) {
        return board.evaluate(); // Ham danh gia ban co
    }

    if (maximizingPlayer) {
        int maxEval = -9999;
        for (auto move : board.getAllPossibleMoves(White)) {
            Board newBoard = board;
            newBoard.makeMove(move);
            int eval = minimax(newBoard, depth - 1, false, alpha, beta);
            maxEval = std::max(maxEval, eval);
            alpha = std::max(alpha, eval);
            if (beta <= alpha) break; // Cat tia alpha-beta
        }
        return maxEval;
    } else {
        int minEval = 9999;
        for (auto move : board.getAllPossibleMoves(Black)) {
            Board newBoard = board;
            newBoard.makeMove(move);
            int eval = minimax(newBoard, depth - 1, true, alpha, beta);
            minEval = std::min(minEval, eval);
            beta = std::min(beta, eval);
            if (beta <= alpha) break; // Cat tia alpha-beta
        }
        return minEval;
    }
}


int main() {
    Game game;
    game.play();
    return 0;
}

