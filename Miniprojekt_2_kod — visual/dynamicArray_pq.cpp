#include "dynamicArray_pq.h"

dynamicArray_PQ::dynamicArray_PQ(int capacity)
    : dynamicArrayCapacity_PQ(capacity),
    dynamicArrayPtr_PQ(new Element[capacity]),
    dynamicArraySize_PQ(0) {
    for (int i = 0; i < dynamicArrayCapacity_PQ; i++) {
        dynamicArrayPtr_PQ[i].value = 0;
        dynamicArrayPtr_PQ[i].priority = 0;
    }
}

dynamicArray_PQ::dynamicArray_PQ()
    : dynamicArraySize_PQ(0),
    dynamicArrayCapacity_PQ(0),
    dynamicArrayPtr_PQ(new Element[0]) {}

dynamicArray_PQ::~dynamicArray_PQ() {
    delete[] dynamicArrayPtr_PQ;
    dynamicArrayCapacity_PQ = 0;
    dynamicArraySize_PQ = 0;
    dynamicArrayPtr_PQ = nullptr;
}

void dynamicArray_PQ::increaseCapacity() {
    if (dynamicArraySize_PQ == dynamicArrayCapacity_PQ) {
        int newCapacity = dynamicArrayCapacity_PQ * 2;
        Element* newPtr = new Element[newCapacity];
        for (int i = 0; i < dynamicArraySize_PQ; ++i) {
            newPtr[i] = dynamicArrayPtr_PQ[i];
        }
        delete[] dynamicArrayPtr_PQ;
        dynamicArrayPtr_PQ = newPtr;
        dynamicArrayCapacity_PQ = newCapacity;
    }
}

void dynamicArray_PQ::decreaseCapacity() {
    if (dynamicArraySize_PQ < dynamicArrayCapacity_PQ / 4) {
        int newCapacity = dynamicArrayCapacity_PQ / 2;
        Element* newPtr = new Element[newCapacity];
        for (int i = 0; i < dynamicArraySize_PQ; ++i) {
            newPtr[i] = dynamicArrayPtr_PQ[i];
        }
        delete[] dynamicArrayPtr_PQ;
        dynamicArrayPtr_PQ = newPtr;
        dynamicArrayCapacity_PQ = newCapacity;
    }
}

int dynamicArray_PQ::getDynamicArraySize() const {
    return dynamicArraySize_PQ;
}

bool dynamicArray_PQ::isDynamicArrayEmpty() {
    return dynamicArraySize_PQ == 0;
}

Element dynamicArray_PQ::getDynamicArrayElementAt(int index) const {
    if (index < 0 || index >= dynamicArraySize_PQ) {
        std::cerr << "B³¹d: Indeks poza zakresem!" << std::endl;
        exit(EXIT_FAILURE);
    }
    return dynamicArrayPtr_PQ[index];
}

void dynamicArray_PQ::addBack(Element element) {
    increaseCapacity();
    dynamicArrayPtr_PQ[dynamicArraySize_PQ] = element;
    dynamicArraySize_PQ++;
}

void dynamicArray_PQ::add(int index, Element element) {
    if (index < 0) {
        std::cerr << "B³¹d: Niepoprawny indeks!" << std::endl;
        return;
    }

    if (index < dynamicArraySize_PQ) {
        increaseCapacity();
        for (int i = dynamicArraySize_PQ; i > index; i--) {
            dynamicArrayPtr_PQ[i] = dynamicArrayPtr_PQ[i - 1];
        }
        dynamicArrayPtr_PQ[index] = element;
        dynamicArraySize_PQ++;
    }
    else {
        increaseCapacity();
        dynamicArrayPtr_PQ[dynamicArraySize_PQ] = element;
        dynamicArraySize_PQ++;
    }
}

void dynamicArray_PQ::remove(int index) {
    if (index < 0 || index >= dynamicArraySize_PQ) {
        std::cerr << "B³¹d: Niepoprawny indeks!" << std::endl;
        return;
    }

    for (int i = index; i < dynamicArraySize_PQ - 1; ++i) {
        dynamicArrayPtr_PQ[i] = dynamicArrayPtr_PQ[i + 1];
    }
    dynamicArraySize_PQ--;

    decreaseCapacity();
}