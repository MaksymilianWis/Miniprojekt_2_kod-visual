#pragma once

#include "dynamicArray.hpp"


class Heap{
private:
    // liczone od 0
    dynamicArray* array_;


    void maxHeapify(unsigned i);
public:
    Heap(unsigned capacity);
    ~Heap();

    unsigned returnSize();

    void insert(int key, int value);
    int extractMax();
    Node getNodeAt(unsigned index);

    int findMax();
    Node findNodeByValue(int value, int i);

    void modifyKey(int value, int new_key);


    void buildMaxHeap();

    // szybkie przepisanie z pliku 
    void fillFromCSV(const std::string& filename_keys, const std::string& filename_values, int maxElements);
};