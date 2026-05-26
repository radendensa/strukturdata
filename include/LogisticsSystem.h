#ifndef LOGISTICS_SYSTEM_H
#define LOGISTICS_SYSTEM_H

#include <string>
#include "PackageQueue.h"
#include "RouteGraph.h"

struct PackageRecordNode {
    Package* package;
    PackageRecordNode* next;
};

struct HubQueueNode {
    std::string cityName;
    PackageQueue* queue;
    HubQueueNode* next;
};

class LogisticsSystem {
private:
    RouteGraph routeGraph;
    PackageRecordNode* firstPackageRecord;
    HubQueueNode* firstHubQueue;

    PackageQueue* getOrCreateQueue(const std::string& cityName);
    PackageQueue* findQueue(const std::string& cityName) const;
    Package* findPackage(const std::string& receiptNumber) const;
    void addPackageRecord(Package* package);
    void clearPackageRecords();
    void clearHubQueues();

public:
    LogisticsSystem();
    ~LogisticsSystem();

    void loadDefaultRoutes();
    void registerPackage();
    void dispatchPackage();
    void trackPackage() const;
    void displayAllQueues() const;
    void displayRoutes() const;
};

#endif
