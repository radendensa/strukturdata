#include <iostream>
#include "HistoryList.h"

HistoryList::HistoryList() {
    head = nullptr;
    tail = nullptr;
}

HistoryList::~HistoryList() {
    HistoryNode* current = head;

    while (current != nullptr) {
        HistoryNode* nodeToDelete = current;
        current = current->next;
        delete nodeToDelete;
    }
}

void HistoryList::addHistory(const std::string& cityName) {
    HistoryNode* newNode = new HistoryNode;
    newNode->cityName = cityName;
    newNode->next = nullptr;

    if (head == nullptr) {
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
}

void HistoryList::display() const {
    if (head == nullptr) {
        std::cout << "Belum ada histori perjalanan.\n";
        return;
    }

    HistoryNode* current = head;
    int step = 1;

    while (current != nullptr) {
        std::cout << step << ". " << current->cityName << "\n";
        current = current->next;
        step++;
    }
}

bool HistoryList::isEmpty() const {
    return head == nullptr;
}
