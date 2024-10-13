#include <iostream>
#include <string>
#include <cstdlib> // Su dung cho ham rand()
#include <ctime>   // Su dung de lay thoi gian hien tai cho rand()

// Lop Rider (Nguoi di xe dap)
class Rider {
public:
    std::string name;  // Ten nguoi choi
    int speed;         // Toc do hien tai
    int stamina;       // The luc
    int distanceCovered; // Quang duong da di qua
    
    // Ham khoi tao
    Rider(std::string n, int spd, int stam) : name(n), speed(spd), stamina(stam), distanceCovered(0) {}
    
    // Ham di chuyen, quan ly su thay doi cua toc do va quang duong di
    void move() {
        if (stamina > 0) {
            int actualSpeed = speed + rand() % 5 - 2; // Toc do thuc te bi anh huong boi yeu to ngau nhien
            distanceCovered += actualSpeed;
            stamina--; // Giam the luc sau moi lan di chuyen
        }
    }

    // Ham hien thi thong tin cua Rider
    void displayStatus() {
        std::cout << name << ": Toc do = " << speed 
                  << " km/h, The luc = " << stamina 
                  << ", Quang duong da di = " << distanceCovered << " km\n";
    }
};

// Lop Game (Tro choi dua xe dap)
class Game {
public:
    Rider rider1; // Nguoi choi 1
    Rider rider2; // Nguoi choi 2
    const int totalDistance; // Quang duong can hoan thanh
    
    // Ham khoi tao
    Game(Rider r1, Rider r2, int distance) : rider1(r1), rider2(r2), totalDistance(distance) {
        srand(time(0)); // Thiet lap seed cho rand() de tao so ngau nhien moi
    }

    // Ham kiem tra xem ai da hoan thanh cuoc dua
    bool isRaceFinished() {
        if (rider1.distanceCovered >= totalDistance) {
            std::cout << rider1.name << " da chien thang!\n";
            return true;
        }
        if (rider2.distanceCovered >= totalDistance) {
            std::cout << rider2.name << " da chien thang!\n";
            return true;
        }
        return false;
    }

    // Ham chay cuoc dua
    void startRace() {
        std::cout << "Cuoc dua bat dau!\n";
        while (!isRaceFinished()) {
            rider1.move();
            rider2.move();
            rider1.displayStatus();
            rider2.displayStatus();
            std::cout << "==========================\n";
        }
        std::cout << "Cuoc dua ket thuc!\n";
    }
};

// Ham main
int main() {
    // Khoi tao hai Rider
    Rider r1("Rider 1", 10, 20); // Ten, Toc do ban dau, The luc
    Rider r2("Rider 2", 10, 18); 
    
    // Khoi tao tro choi voi quang duong dua 100km
    Game game(r1, r2, 100);
    
    // Bat dau cuoc dua
    game.startRace();

    return 0;
}

