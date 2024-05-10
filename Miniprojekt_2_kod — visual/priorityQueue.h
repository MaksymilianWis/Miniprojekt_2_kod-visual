#ifndef KOLEJKA_PRIORYTETOWA_PRIORITYQUEUE_H
#define KOLEJKA_PRIORYTETOWA_PRIORITYQUEUE_H


#include "dynamicArray_pq.h"

class PriorityQueue {
private:
    dynamicArray_PQ elements;

public:
    PriorityQueue(int capacity = 10);
    void insert(int value, int priority);
    Element extractMax();
    Element findMax();
    void modifyKey(int value, int newPriority);
    int returnSize();
    void display() const;
    void fillFromCSV(const std::string& value_file_name, const std::string& priority_file_name, int n);
    Element getElementAt(int index) const;
};

#endif //KOLEJKA_PRIORYTETOWA_PRIORITYQUEUE_H
