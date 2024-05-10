#pragma once

#include "dynamicArray.hpp"


class Heap{
private:
    // liczone od 0
    dynamicArray* array_;


    void heapifyUp();
    void heapifyDown();

    unsigned getParentIndex(unsigned index);
    bool hasParent(unsigned index);
    bool hasLeftChild(unsigned index);
    bool hasRightChild(unsigned index);
public:
    Heap();
    Heap(unsigned capacity);
    ~Heap();

    unsigned returnSize();

    void insert(int key, int value);
    int extractMax();
    Node getNodeAt(unsigned index);

    int findMax();
    Node findNodeByValue(int value, int i); // i predefiniowane jako i=0

    void modifyKey(int value, int new_key);

    void buildMaxHeap();


    // szybkie przepisanie z pliku 
    void fillFromCSV(const std::string& value_file_name, const std::string& priority_file_name, int n);
    void printHeap(unsigned i);
};