#pragma once

#include "Heap.hpp"
#include "DynamicArray.hpp"

Heap::Heap(unsigned capacity) : size_(capacity), capacity_(capacity), array_(new dynamicArray) {};
Heap::~Heap(){
    delete[] ptr_;
    ptr_ = nullptr;
}

void Heap::insert(int key, int value){
    // dodawanie na koniec
    array_->addBack(key, value);

    // porwawianie nie jezeli niewalsciwie umieszczony
    buildMaxHeap();
}

int Heap::extractMax(){
    int temp = array_->getDynamicArrayElementAt(0)
    return 0;
}

int Heap::findMax(){
    return 0;
}

void Heap::modifyKey(int element, int new_key){

}

unsigned Heap::returnSize(){
    return 0;
}

void Heap::maxHeapify(unsigned i){
    unsigned l = 2 * i;
    unsigned r = 2 * i + 1;

    unsigned largest = i;

    // szukanie większych synów niż rodzidziców
    // z lewa
    if (l < size_ && array_->getDynamicArrayKeyAt(l) > array_->getDynamicArrayKeyAt(i)) {
        largest = l;
    }
    // z prawa
    if (r < size_ && array_->getDynamicArrayKeyAt(l) > array_->getDynamicArrayKeyAt(largest)){
        largest = r;
    }


    // jezeli largest zostal zmieniony to swap
    if (largest != i){
        Node temp;

        array_->swapNodes(i, largest);

        // rekurencja
        maxHeapify(largest);
    }
}

    void Heap::buildMaxHeap(){
        // wywolanie maxHeapyfy od dolu(bez lisci) do gory
        for (unsigned i = size_/2; i > 0; i--)
        {
            maxHeapify(i);
        }
    }