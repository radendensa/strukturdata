#include <iostream>
#include "PackageQueue.h"

PackageQueue::PackageQueue() {
    front = nullptr;
    rear = nullptr;
    totalItems = 0;
}

PackageQueue::~PackageQueue() {
    while (!isEmpty()) {
        dequeue();
    }
}

void PackageQueue::enqueue(Package* package) {
    QueueNode* newNode = new QueueNode;
    newNode->package = package;
    newNode->next = nullptr;

    if (rear == nullptr) {
        front = newNode;
        rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }

    totalItems++;
}

Package* PackageQueue::dequeue() {
    if (front == nullptr) {
        return nullptr;
    }

    QueueNode* nodeToDelete = front;
    Package* package = nodeToDelete->package;

    front = front->next;
    if (front == nullptr) {
        rear = nullptr;
    }

    delete nodeToDelete;
    totalItems--;
    return package;
}

void PackageQueue::display() const {
    if (front == nullptr) {
        std::cout << "Antrean kosong.\n";
        return;
    }

    QueueNode* current = front;
    int position = 1;

    while (current != nullptr) {
        std::cout << position << ". Resi " << current->package->getReceiptNumber()
                  << " -> tujuan " << current->package->getDestinationCity() << "\n";
        current = current->next;
        position++;
    }
}

bool PackageQueue::isEmpty() const {
    return front == nullptr;
}

int PackageQueue::size() const {
    return totalItems;
}
