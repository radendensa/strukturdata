#include <iostream>
#include "Package.h"

Package::Package(const std::string& receiptNumber,
                 const std::string& originCity,
                 const std::string& destinationCity) {
    this->receiptNumber = receiptNumber;
    this->originCity = originCity;
    this->destinationCity = destinationCity;
    this->currentCity = originCity;
    this->delivered = false;

    // Kota asal langsung masuk histori sebagai titik awal perjalanan.
    history.addHistory(originCity);
}

std::string Package::getReceiptNumber() const {
    return receiptNumber;
}

std::string Package::getOriginCity() const {
    return originCity;
}

std::string Package::getDestinationCity() const {
    return destinationCity;
}

std::string Package::getCurrentCity() const {
    return currentCity;
}

bool Package::isDelivered() const {
    return delivered;
}

void Package::moveToCity(const std::string& cityName) {
    currentCity = cityName;
    history.addHistory(cityName);
}

void Package::markDelivered() {
    delivered = true;
}

void Package::displayTracking() const {
    std::cout << "Nomor resi     : " << receiptNumber << "\n";
    std::cout << "Kota asal      : " << originCity << "\n";
    std::cout << "Kota tujuan    : " << destinationCity << "\n";
    std::cout << "Posisi saat ini: " << currentCity << "\n";
    std::cout << "Status         : " << (delivered ? "Sudah sampai" : "Dalam perjalanan") << "\n";
    std::cout << "Histori perjalanan:\n";
    history.display();
}
