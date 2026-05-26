#ifndef HISTORY_LIST_H
#define HISTORY_LIST_H

#include <string>

struct HistoryNode {
    std::string cityName;
    HistoryNode* next;
};

class HistoryList {
private:
    HistoryNode* head;
    HistoryNode* tail;

public:
    HistoryList();
    ~HistoryList();

    void addHistory(const std::string& cityName);
    void display() const;
    bool isEmpty() const;
};

#endif
