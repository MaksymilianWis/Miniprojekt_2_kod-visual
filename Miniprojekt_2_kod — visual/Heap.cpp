#pragma once

#include "Heap.hpp"
#include "DynamicArray.hpp"

// NODE
node::node() : key_(0), value_(0) {};
node::node(int key, int value) : key_(key), value_(value) {};

Heap::Heap(unsigned capacity) : size_(capacity), capacity_(capacity), ptr_(new node[capacity]) {};
Heap::~Heap(){
    delete[] ptr_;
    ptr_ = nullptr;
}

void Heap::insert(int element, int priority){

}

int Heap::extractMax(){
    return 0;
}

int Heap::findMax(){
    return 0;
}

void Heap::modifyKey(int element, int priority){

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
    if (l < size_ && ptr_[l].key_ > ptr_[i].key_){
        largest = l;
    }
    // z prawa
    if (r < size_ && ptr_[l].key_ > ptr_[largest].key_){
        largest = r;
    }


    // jezeli largest zostal zmieniony to swap
    if (largest != i){
        node temp;

        temp = ptr_[i];

        ptr_[i] = ptr_[largest];
        ptr_[largest] = temp;

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