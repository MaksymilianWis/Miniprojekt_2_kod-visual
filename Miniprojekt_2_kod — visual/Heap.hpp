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

    void insert(int key, int value);
    int extractMax();
    int findMax();
    void modifyKey(int value, int new_key);
    unsigned returnSize();


    void buildMaxHeap();
};