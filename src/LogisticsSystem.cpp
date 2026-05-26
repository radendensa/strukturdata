#include <iostream>
#include <limits>
#include "LogisticsSystem.h"

LogisticsSystem::LogisticsSystem() {
    firstPackageRecord = nullptr;
    firstHubQueue = nullptr;
}

LogisticsSystem::~LogisticsSystem() {
    clearHubQueues();
    clearPackageRecords();
}

void LogisticsSystem::loadDefaultRoutes() {
    routeGraph.addRoute("Jakarta", "Bandung", 150);
    routeGraph.addRoute("Jakarta", "Semarang", 450);
    routeGraph.addRoute("Bandung", "Yogyakarta", 390);
    routeGraph.addRoute("Semarang", "Surabaya", 350);
    routeGraph.addRoute("Yogyakarta", "Surabaya", 330);
    routeGraph.addRoute("Surabaya", "Denpasar", 430);
    routeGraph.addRoute("Bandung", "Cirebon", 130);
    routeGraph.addRoute("Cirebon", "Semarang", 240);
}

PackageQueue* LogisticsSystem::findQueue(const std::string& cityName) const {
    HubQueueNode* current = firstHubQueue;

    while (current != nullptr) {
        if (current->cityName == cityName) {
            return current->queue;
        }
        current = current->next;
    }

    return nullptr;
}

PackageQueue* LogisticsSystem::getOrCreateQueue(const std::string& cityName) {
    PackageQueue* existingQueue = findQueue(cityName);
    if (existingQueue != nullptr) {
        return existingQueue;
    }

    HubQueueNode* newHub = new HubQueueNode;
    newHub->cityName = cityName;
    newHub->queue = new PackageQueue;
    newHub->next = firstHubQueue;
    firstHubQueue = newHub;

    return newHub->queue;
}

Package* LogisticsSystem::findPackage(const std::string& receiptNumber) const {
    PackageRecordNode* current = firstPackageRecord;

    while (current != nullptr) {
        if (current->package->getReceiptNumber() == receiptNumber) {
            return current->package;
        }
        current = current->next;
    }

    return nullptr;
}

void LogisticsSystem::addPackageRecord(Package* package) {
    PackageRecordNode* newRecord = new PackageRecordNode;
    newRecord->package = package;
    newRecord->next = firstPackageRecord;
    firstPackageRecord = newRecord;
}

void LogisticsSystem::registerPackage() {
    std::string receiptNumber;
    std::string originCity;
    std::string destinationCity;

    std::cout << "Masukkan nomor resi   : ";
    std::getline(std::cin, receiptNumber);
    std::cout << "Masukkan kota asal    : ";
    std::getline(std::cin, originCity);
    std::cout << "Masukkan kota tujuan  : ";
    std::getline(std::cin, destinationCity);

    if (receiptNumber.empty() || originCity.empty() || destinationCity.empty()) {
        std::cout << "Input tidak boleh kosong.\n";
        return;
    }

    if (findPackage(receiptNumber) != nullptr) {
        std::cout << "Nomor resi sudah terdaftar.\n";
        return;
    }

    if (!routeGraph.hasCity(originCity) || !routeGraph.hasCity(destinationCity)) {
        std::cout << "Kota asal atau tujuan belum ada di graph rute.\n";
        return;
    }

    Package* newPackage = new Package(receiptNumber, originCity, destinationCity);
    addPackageRecord(newPackage);
    getOrCreateQueue(originCity)->enqueue(newPackage);

    std::cout << "Paket berhasil diregistrasi dan masuk antrean " << originCity << ".\n";
}

void LogisticsSystem::dispatchPackage() {
    std::string currentCity;
    std::cout << "Dispatch dari kota: ";
    std::getline(std::cin, currentCity);

    PackageQueue* queue = findQueue(currentCity);
    if (queue == nullptr || queue->isEmpty()) {
        std::cout << "Tidak ada paket dalam antrean kota " << currentCity << ".\n";
        return;
    }

    Package* package = queue->dequeue();

    if (package->isDelivered()) {
        std::cout << "Paket " << package->getReceiptNumber() << " sudah sampai sebelumnya.\n";
        return;
    }

    if (package->getCurrentCity() == package->getDestinationCity()) {
        package->markDelivered();
        std::cout << "Paket " << package->getReceiptNumber() << " sudah berada di kota tujuan.\n";
        return;
    }

    std::string nextCity;
    int distance = 0;
    bool routeFound = routeGraph.findNextCity(package->getCurrentCity(),
                                              package->getDestinationCity(),
                                              nextCity,
                                              distance);

    if (!routeFound) {
        std::cout << "Tidak ada rute dari " << package->getCurrentCity()
                  << " menuju " << package->getDestinationCity() << ".\n";
        getOrCreateQueue(package->getCurrentCity())->enqueue(package);
        return;
    }

    package->moveToCity(nextCity);

    if (nextCity == package->getDestinationCity()) {
        package->markDelivered();
        std::cout << "Paket " << package->getReceiptNumber() << " dikirim ke "
                  << nextCity << " (" << distance << " km) dan sudah sampai tujuan.\n";
    } else {
        getOrCreateQueue(nextCity)->enqueue(package);
        std::cout << "Paket " << package->getReceiptNumber() << " dikirim dari "
                  << currentCity << " ke " << nextCity << " (" << distance << " km).\n";
    }
}

void LogisticsSystem::trackPackage() const {
    std::string receiptNumber;
    std::cout << "Masukkan nomor resi: ";
    std::getline(std::cin, receiptNumber);

    Package* package = findPackage(receiptNumber);
    if (package == nullptr) {
        std::cout << "Paket dengan resi " << receiptNumber << " tidak ditemukan.\n";
        return;
    }

    package->displayTracking();
}

void LogisticsSystem::displayAllQueues() const {
    if (firstHubQueue == nullptr) {
        std::cout << "Belum ada antrean hub.\n";
        return;
    }

    HubQueueNode* current = firstHubQueue;
    while (current != nullptr) {
        std::cout << "\nHub " << current->cityName << " (" << current->queue->size() << " paket)\n";
        current->queue->display();
        current = current->next;
    }
}

void LogisticsSystem::displayRoutes() const {
    routeGraph.displayGraph();
}

void LogisticsSystem::clearPackageRecords() {
    PackageRecordNode* current = firstPackageRecord;

    while (current != nullptr) {
        PackageRecordNode* recordToDelete = current;
        current = current->next;
        delete recordToDelete->package;
        delete recordToDelete;
    }

    firstPackageRecord = nullptr;
}

void LogisticsSystem::clearHubQueues() {
    HubQueueNode* current = firstHubQueue;

    while (current != nullptr) {
        HubQueueNode* hubToDelete = current;
        current = current->next;
        delete hubToDelete->queue;
        delete hubToDelete;
    }

    firstHubQueue = nullptr;
}
