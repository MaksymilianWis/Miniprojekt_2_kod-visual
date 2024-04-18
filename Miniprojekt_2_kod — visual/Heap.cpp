#pragma once

#include "Heap.hpp"
#include "DynamicArray.hpp"

Heap::Heap(unsigned capacity) : array_(new dynamicArray) {};
Heap::~Heap(){
    delete[] array_;
    array_ = nullptr;
}

void Heap::insert(int key, int value){
    // dodawanie na koniec
    array_->addBack(key, value);

    // porwawianie nie jezeli niewalsciwie umieszczony
    buildMaxHeap();
}

int Heap::extractMax(){
    // skopiuj tymczasowo
    int temp = array_->getDynamicArrayNodeAt(0).getValue();

    // zamien miejscami nodes zamiast nadpisywac
    array_->swapNodes(0, array_->getDynamicArraySize());
    // usun ostatni czyli po swap bedzie to max
    array_->removeBack();

    buildMaxHeap();
    return temp;
}

int Heap::findMax(){
    return array_->getDynamicArrayNodeAt(0).getValue();
}

void Heap::modifyKey(int value, int new_key){
    int i = 0;

    // potrzebna metoda fina ktora zastapi ponizszy do while i bedzie wywolywana rekurencyjnie
    do {
        unsigned l = 2 * i + 1; // Lewy syn
        unsigned r = 2 * i + 2; // Prawy syn
        if (array_->getDynamicArrayNodeAt(l).getValue() >= value) {
            if (array_->getDynamicArrayNodeAt(l).getValue() == value) break;


        }
    } while (1);

    array_->getDynamicArrayNodeAt(value).OverwriteNodeKey(new_key);
}

unsigned Heap::returnSize(){
    return 0;
}

// liczone od 0
void Heap::maxHeapify(unsigned i) {
    unsigned l = 2 * i + 1; // Lewy syn
    unsigned r = 2 * i + 2; // Prawy syn

    unsigned largest = i;

    // Szukanie większych synów niż rodzic
    // Z lewej
    if (l < array_->getDynamicArraySize() && array_->getDynamicArrayKeyAt(l) > array_->getDynamicArrayKeyAt(i)) {
        largest = l;
    }
    // Z prawej
    if (r < array_->getDynamicArraySize() && array_->getDynamicArrayKeyAt(r) > array_->getDynamicArrayKeyAt(largest)) {
        largest = r;
    }

    // Jeżeli largest został zmieniony, to zamień
    if (largest != i) {
        array_->swapNodes(i, largest);
        // Rekurencja
        maxHeapify(largest);
    }
}

void Heap::buildMaxHeap() {
    // Wywołanie maxHeapify od dołu (bez liści) do góry
    for (unsigned i = (array_->getDynamicArraySize() / 2) - 1; i >= 0; i--) {
        maxHeapify(i);
    }
}