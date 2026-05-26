#ifndef PACKAGE_H
#define PACKAGE_H

#include <string>
#include "HistoryList.h"

class Package {
private:
    std::string receiptNumber;
    std::string originCity;
    std::string destinationCity;
    std::string currentCity;
    bool delivered;
    HistoryList history;

public:
    Package(const std::string& receiptNumber,
            const std::string& originCity,
            const std::string& destinationCity);

    std::string getReceiptNumber() const;
    std::string getOriginCity() const;
    std::string getDestinationCity() const;
    std::string getCurrentCity() const;
    bool isDelivered() const;

    void moveToCity(const std::string& cityName);
    void markDelivered();
    void displayTracking() const;
};

#endif
