#ifndef KOLEJKA_PRIORYTETOWA_DYNAMICARRAY_H
#define KOLEJKA_PRIORYTETOWA_DYNAMICARRAY_H


#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <random>
#include <fstream>
#include <sstream>

using namespace std;

struct Element {
    int value;
    int priority;
};

class dynamicArray_PQ {
private:
    Element* dynamicArrayPtr_PQ;
    int dynamicArraySize_PQ;
    int dynamicArrayCapacity_PQ;

    void increaseCapacity();
    void decreaseCapacity();

public:
    dynamicArray_PQ(int capacity);
    dynamicArray_PQ();
    ~dynamicArray_PQ();

    int getDynamicArraySize() const;
    bool isDynamicArrayEmpty();
    Element getDynamicArrayElementAt(int index) const;


    void addBack(Element element);
    void add(int index, Element element);
    void remove(int index);
};


#endif //KOLEJKA_PRIORYTETOWA_DYNAMICARRAY_H