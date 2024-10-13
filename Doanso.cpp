#include <iostream>
#include <cstdlib>  
#include <ctime>    

using namespace std;

int main() {
    srand(time(0));  

    int casinoNumber = rand() % 10 + 1;  
    int playerGuess;
    int attempts = 0;  
    int maxAttempts = 3;  

    cout << "Chao mung ban den voi Casino!\n";
    cout << "He thong da chon 1 den 100.\n";
    cout << "Ban co " << maxAttempts << " lan doan. Good luck!\n";

    do {
        cout << "Nhap so ban doan (1-10): ";
        cin >> playerGuess;
        attempts++;

        if (playerGuess < 1 || playerGuess > 10) {
            cout << "Laa chon không hop le, vui lòng chon so tu 1 den 100.\n";
            continue;
        }

        if (playerGuess > casinoNumber) {
            cout << "So ban doan lon hon so cua he thong!\n";
        } else if (playerGuess < casinoNumber) {
            cout << "So ban doan nho hon so cua he thong!\n";
        } else {
            cout << "Chuc mung! Ban da doan dung so sau " << attempts << " lan doan.\n";
            break;
        }

        if (attempts >= maxAttempts) {
            cout << "Ban da het luot doan. So cua he thong là " << casinoNumber << ". Good luck!\n";
            break;
        }

    } while (playerGuess != casinoNumber);

    return 0;
}
