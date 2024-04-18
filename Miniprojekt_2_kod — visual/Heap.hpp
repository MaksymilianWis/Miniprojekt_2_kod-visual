#pragma once

#include "dynamicArray.hpp"


class Heap{
private:
    // liczone od 1
    dynamicArray* array_;
    unsigned size_;
    unsigned capacity_;


    void maxHeapify(unsigned i);
public:
    Heap(unsigned capacity);
    ~Heap();

    void insert(int key, int value);
    int extractMax();
    int findMax();
    void modifyKey(int element, int new_key);
    unsigned returnSize();


    void buildMaxHeap();
};