#pragma once

#include "Heap.hpp"
#include "DynamicArray.hpp"

Heap::Heap(unsigned capacity) : array_(new dynamicArray(capacity)) {
};
Heap::~Heap(){
    delete array_;
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


// DO WERYFIKACJI
Node Heap::findNodeByValue(int value, int i = 0) {

    unsigned l = 2 * i + 1; // Lewy syn
    unsigned r = 2 * i + 2; // Prawy syn

    // czy pod lewym synem?
    if (value <= array_->getDynamicArrayNodeAt(l).getValue()) {
        
        if (array_->getDynamicArrayNodeAt(l).getValue() == value) return array_->getDynamicArrayNodeAt(l);
        
        return findNodeByValue(value, l);
    }

    if (value <= array_->getDynamicArrayNodeAt(r).getValue()) {

        if (array_->getDynamicArrayNodeAt(r).getValue() == value) return array_->getDynamicArrayNodeAt(r);

        return findNodeByValue(value, r);
    }

    std::cout << "ERROR nie znaleziono elementu o wartosci" << value << std::endl;
}

void Heap::modifyKey(int value, int new_key){
    int i = 0;

    // potrzebna metoda fina ktora zastapi ponizszy do while i bedzie wywolywana rekurencyjnie
    findNodeByValue(value).OverwriteNodeKey(new_key);
    // naprawianie heap (ustawianie zmienionego key w dobrym miejscu)
    buildMaxHeap();
}

unsigned Heap::returnSize(){
    return array_->getDynamicArraySize();
}

// liczone od 0
void Heap::maxHeapify(unsigned i) {
    unsigned l = 2 * i + 1; // Lewy syn
    unsigned r = 2 * i + 2; // Prawy syn

    unsigned largest = i;

    // Szukanie większych synów niż rodzic
    // Z lewej
    if (l < array_->getDynamicArraySize() && array_->getDynamicArrayNodeAt(l).getKey() > array_->getDynamicArrayNodeAt(i).getKey()) {
        largest = l;
    }
    // Z prawej
    if (r < array_->getDynamicArraySize() && array_->getDynamicArrayNodeAt(r).getKey() > array_->getDynamicArrayNodeAt(largest).getKey()) {
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
    for (int i = (array_->getDynamicArraySize() / 2) - 1; i >= 0; i--) {
        maxHeapify(i);
    }
}

void Heap::fillFromArrayCSV(const std::string& filename_keys, const std::string& filename_values, int maxElements) {
    array_->fillFromArrayCSV(filename_keys, filename_values, maxElements);
}