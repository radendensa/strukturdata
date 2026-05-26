#ifndef PACKAGE_QUEUE_H
#define PACKAGE_QUEUE_H

#include "Package.h"

struct QueueNode {
    Package* package;
    QueueNode* next;
};

class PackageQueue {
private:
    QueueNode* front;
    QueueNode* rear;
    int totalItems;

public:
    PackageQueue();
    ~PackageQueue();

    void enqueue(Package* package);
    Package* dequeue();
    void display() const;
    bool isEmpty() const;
    int size() const;
};

#endif
