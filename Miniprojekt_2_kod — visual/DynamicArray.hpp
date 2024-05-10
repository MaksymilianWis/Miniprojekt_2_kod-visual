#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <random>
#include <fstream>
#include <sstream>

#include "Node.hpp"

using namespace std;

class dynamicArray {
private:
    int dynamicArrayCapacity; //zmienna rozmiaru tablicy
    int dynamicArraySize; //iloœæ elementów w tablicy
    Node* arrayNode_; // od pozycji 0

    void increaseCapacity();
    void decreaseCapacity();
public:
    dynamicArray(); //konstruktor
    dynamicArray(int capacity); //konstruktor z argumentem
    ~dynamicArray(); //destruktor

    int getDynamicArraySize() const;
    bool isDynamicArrayEmpty();
    Node getDynamicArrayNodeAt(int index);

    void displayDynamicArray();
    void displayDynamicArrayWCapacity();
    void addBack(int key, int element);
    void removeBack();
    void swapNodes(int index1, int index2);

};