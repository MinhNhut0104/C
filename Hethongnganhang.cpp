#include <iostream>

using namespace std;

class BankAccount {
private:
    string owner;
    double balance;

public:
    BankAccount(string name, double initialBalance) {
        owner = name;
        balance = initialBalance;
    }

    void checkBalance() {
        cout << "So du tai khoan cua ban la: $" << balance << endl;
    }

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Ban da gui $" << amount << " thanh cong.\n";
        } else {
            cout << "So tien gui phai lon hon 0.\n";
        }
    }

    void withdraw(double amount) {
        if (amount > 0) {
            if (amount <= balance) {
                balance -= amount;
                cout << "Ban da rut $" << amount << " thanh cong.\n";
            } else {
                cout << "So du khong du de rut so tien nay.\n";
            }
        } else {
            cout << "So tien rut phai lon hon 0.\n";
        }
    }

    string getOwner() {
        return owner;
    }
};

void displayMenu() {
    cout << "\n1. Kiem tra so du\n";
    cout << "2. Gui tien\n";
    cout << "3. Rut tien\n";
    cout << "4. Thoat\n";
    cout << "Chon mot tuy chon: ";
}

int main() {
    string name;
    double initialBalance;
    
    cout << "Chao mung ban den voi he thong ngan hang.\n";
    cout << "Nhap ten cua ban: ";
    getline(cin, name);
    
    cout << "Nhap so du ban dau cua ban: $";
    cin >> initialBalance;

    BankAccount account(name, initialBalance);

    int choice;
    double amount;

    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                account.checkBalance();
                break;
            case 2:
                cout << "Nhap so tien ban muon gui: $";
                cin >> amount;
                account.deposit(amount);
                break;
            case 3:
                cout << "Nhap so tien ban muon rut: $";
                cin >> amount;
                account.withdraw(amount);
                break;
            case 4:
                cout << "Cam on ban da su dung dich vu ngan hang. Tam biet!\n";
                break;
            default:
                cout << "Lua chon khong hop le. Vui long thu lai.\n";
                break;
        }
    } while (choice != 4);

    return 0;
}

