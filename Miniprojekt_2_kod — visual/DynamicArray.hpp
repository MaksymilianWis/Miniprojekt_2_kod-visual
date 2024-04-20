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
    int dynamicArrayCapacity = 0; //zmienna rozmiaru tablicy
    int dynamicArraySize = 0; //iloœæ elementów w tablicy
    Node* arrayNode_;

    void increaseCapacity();
    void decreaseCapacity();
public:
    dynamicArray(); //konstruktor
    dynamicArray(int capacity); //konstruktor z argumentem
    ~dynamicArray(); //destruktor

    int getDynamicArraySize() const;
    bool isDynamicArrayEmpty();
    //int getDynamicArrayValueAt(int index);
    //int getDynamicArrayKeyAt(int index);
    Node getDynamicArrayNodeAt(int index);
    //int findElement(int element);

    void displayDynamicArray();
    void displayDynamicArrayWCapacity();
    //void add(int index, int element);
    void addBack(int key, int element);
    //void addFront(int item);
    //void remove(int index);
    void removeBack();
    //void removeFront();
    void swapNodes(int index1, int index2);

    void fillFromArrayCSV(const std::string& filename_keys, const std::string& filename_values, int maxElements);
};