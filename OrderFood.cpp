#include <iostream>
#include <vector>
#include <string>

// Lop FoodItem dai dien cho tung mon an trong thuc don
class FoodItem {
public:
    std::string name;  // Ten mon an
    double price;      // Gia cua mon an
    std::string description; // Mo ta ngan gon ve mon an
    
    // Ham khoi tao
    FoodItem(std::string n, double p, std::string desc) : name(n), price(p), description(desc) {}
    
    // Hien thi thong tin chi tiet cua mon an
    void display() const {
        std::cout << name << " - " << price << " VND\n";
        std::cout << description << "\n";
    }
};

// Lop Menu chua danh sach cac mon an
class Menu {
public:
    std::vector<FoodItem> items; // Danh sach cac mon an trong menu
    
    // Ham khoi tao va thiet lap menu
    Menu() {
        // Them cac mon an vao thuc don
        items.push_back(FoodItem("Pho Bo", 50000, "Pho bo truyen thong."));
        items.push_back(FoodItem("Bun Cha", 60000, "Bun cha Ha Noi."));
        items.push_back(FoodItem("Banh Mi", 25000, "Banh mi pate thom ngon."));
        items.push_back(FoodItem("Tra Sua", 30000, "Tra sua tran chau duong den."));
    }
    
    // Hien thi thuc don cho nguoi dung
    void displayMenu() const {
        std::cout << "===== MENU =====\n";
        for (int i = 0; i < items.size(); ++i) {
            std::cout << i + 1 << ". ";
            items[i].display();
            std::cout << "------------------\n";
        }
    }
    
    // Lay mon an dua tren so thu tu trong menu
    FoodItem getItem(int index) const {
        if (index >= 0 && index < items.size()) {
            return items[index];
        }
        return FoodItem("", 0.0, ""); // Neu nhap sai, tra ve mon an rong
    }
};

// Lop Order dai dien cho don dat hang
class Order {
public:
    std::vector<FoodItem> orderedItems; // Danh sach cac mon da duoc dat
    
    // Them mon an vao don hang
    void addItem(const FoodItem& item) {
        orderedItems.push_back(item);
    }

    // Tinh tong gia tri cua don hang
    double calculateTotal() const {
        double total = 0.0;
        for (const auto& item : orderedItems) {
            total += item.price;
        }
        return total;
    }
    
    // Hien thi don hang
    void displayOrder() const {
        std::cout << "===== DON HANG CUA BAN =====\n";
        for (const auto& item : orderedItems) {
            std::cout << item.name << " - " << item.price << " VND\n";
        }
        std::cout << "===========================\n";
    }
};

// Ham main
int main() {
    Menu menu;
    Order order;
    int choice;
    
    while (true) {
        menu.displayMenu();
        std::cout << "Nhap so thu tu mon an de dat (nhap 0 de thanh toan): ";
        std::cin >> choice;
        
        if (choice == 0) {
            break; // Ket thuc viec dat hang va di toi thanh toan
        }

        FoodItem selectedItem = menu.getItem(choice - 1);
        if (selectedItem.price > 0) {
            order.addItem(selectedItem);
            std::cout << "Da them " << selectedItem.name << " vao don hang.\n";
        } else {
            std::cout << "Lua chon khong hop le, vui long nhap lai.\n";
        }
    }
    
    // Hien thi don hang va tinh tong tien
    order.displayOrder();
    double total = order.calculateTotal();
    std::cout << "Tong gia tri don hang: " << total << " VND\n";
    std::cout << "Cam on da dat hang!\n";
    
    return 0;
}

