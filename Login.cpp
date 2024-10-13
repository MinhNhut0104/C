#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Ham dang ky nguoi dung moi
void Register() {
    string username, password;

    cout << "Dang ky tai khoan moi\n";
    cout << "Nhap ten nguoi dung: ";
    cin >> username;
    cout << "Nhap mat khau: ";
    cin >> password;

    // Mo file de ghi thong tin tai khoan
    ofstream file("accounts.txt", ios::app); // Mo file o che do them vao
    if (file.is_open()) {
        file << username << " " << password << endl; // Ghi ten nguoi dung va mat khau vao file
        file.close();
        cout << "Dang ky thanh cong!\n";
    } else {
        cout << "Loi khi mo file!\n";
    }
}

// Ham kiem tra dang nhap
bool Login() {
    string username, password, u, p;

    cout << "Dang nhap tai khoan\n";
    cout << "Nhap ten nguoi dung: ";
    cin >> username;
    cout << "Nhap mat khau: ";
    cin >> password;

    // Mo file de doc thong tin tai khoan
    ifstream file("accounts.txt");
    if (file.is_open()) {
        while (file >> u >> p) { // Doc lan luot tung dong trong file
            if (u == username && p == password) {
                file.close();
                return true; // Dang nhap thanh cong
            }
        }
        file.close();
    } else {
        cout << "Loi khi mo file!\n";
    }

    return false; // Dang nhap that bai
}

// Ham chinh
int main() {
    int choice;

    cout << "Chao mung den voi he thong\n";
    cout << "1. Dang ky\n";
    cout << "2. Dang nhap\n";
    cout << "Lua chon: ";
    cin >> choice;

    if (choice == 1) {
        Register();
        main(); // Sau khi dang ky xong, quay lai man hinh chinh
    } else if (choice == 2) {
        if (Login()) {
            cout << "Dang nhap thanh cong!\n";
        } else {
            cout << "Dang nhap that bai! Vui long kiem tra lai tai khoan va mat khau.\n";
        }
    } else {
        cout << "Lua chon khong hop le!\n";
    }

    return 0;
}

