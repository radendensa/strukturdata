#include <iostream>
#include <limits>
#include "LogisticsSystem.h"

void displayMenu() {
    std::cout << "\n=== Sistem Manajemen & Routing Paket Logistik ===\n";
    std::cout << "1. Registrasi paket\n";
    std::cout << "2. Dispatch paket\n";
    std::cout << "3. Lacak resi\n";
    std::cout << "4. Tampilkan antrean semua hub\n";
    std::cout << "5. Tampilkan graph rute\n";
    std::cout << "0. Keluar\n";
    std::cout << "Pilih menu: ";
}

int main() {
    LogisticsSystem system;
    system.loadDefaultRoutes();

    int choice = -1;

    do {
        displayMenu();
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                system.registerPackage();
                break;
            case 2:
                system.dispatchPackage();
                break;
            case 3:
                system.trackPackage();
                break;
            case 4:
                system.displayAllQueues();
                break;
            case 5:
                system.displayRoutes();
                break;
            case 0:
                std::cout << "Program selesai.\n";
                break;
            default:
                std::cout << "Pilihan tidak valid.\n";
                break;
        }
    } while (choice != 0);

    return 0;
}
