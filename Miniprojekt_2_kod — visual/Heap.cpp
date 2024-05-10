#pragma once

#include "Heap.hpp"
#include "DynamicArray.hpp"
#include "iostream"

Heap::Heap() : array_(new dynamicArray(2)) {};
Heap::Heap(unsigned capacity) : array_(new dynamicArray(capacity)) {};
Heap::~Heap(){
    delete array_;
    array_ = nullptr;
}

void Heap::insert(int key, int value){
    // dodawanie na koniec
    array_->addBack(key, value);
    
    // naprawianie heap
    heapifyUp();
}

int Heap::extractMax(){
    // skopiuj tymczasowo
    int temp = array_->getDynamicArrayNodeAt(0).getValue();

    // zamien miejscami nodes zamiast nadpisywac
    array_->swapNodes(0, array_->getDynamicArraySize());
    // usun ostatni czyli po swap bedzie to max
    array_->removeBack();

    //buildMaxHeap();
    heapifyDown();
    return temp;
}

int Heap::findMax(){
    return array_->getDynamicArrayNodeAt(0).getValue();
}

Node Heap::findNodeByValue(int value, int i = 0) {

    unsigned l = 2 * i + 1; // Lewy syn
    unsigned r = 2 * i + 2; // Prawy syn

    // Sprawdź czy kopiec jest pusty
    if (array_->isDynamicArrayEmpty()) {
        std::cout << "Kopiec jest pusty." << std::endl;
        return Node(); // Zwróć pusty węzeł
    }

    // Jeśli indeks przekracza rozmiar kopca, zwróć pusty węzeł
    if (i >= array_->getDynamicArraySize()) {
        //std::cout << "Nie znaleziono elementu o wartości " << value << "." << std::endl;
        return Node(); // Zwróć pusty węzeł
    }

    // Sprawdź wartość w bieżącym węźle
    int out = array_->getDynamicArrayNodeAt(i).getValue();
    if (array_->getDynamicArrayNodeAt(i).getValue() == value) {
        return array_->getDynamicArrayNodeAt(i); // Zwróć węzeł, jeśli wartość została znaleziona
    }
    //std::cout << array_->getDynamicArrayNodeAt(i).getKey() << " " << array_->getDynamicArrayNodeAt(i).getValue() << std::endl;

    // Rekurencyjnie poszukaj w lewym i prawym poddrzewie
    Node foundNode = findNodeByValue(value, l); // Przeszukaj lewe poddrzewo

    if (!foundNode.isEmpty()) {
        return foundNode; // Zwróć znaleziony węzeł
    }

    foundNode = findNodeByValue(value, r);// przeszukaj prawe

    return foundNode;
}


void Heap::modifyKey(int value, int new_key){
    int i = 0;

    findNodeByValue(value).OverwriteNodeKey(new_key);
    //std::cout << findNodeByValue(value).getValue() << std::endl;

    // naprawianie heap (ustawianie zmienionego key w dobrym miejscu)
    heapifyUp();
}

unsigned Heap::returnSize(){
    return array_->getDynamicArraySize();
}


void Heap::heapifyUp() {
    int index = this->returnSize() - 1;
    while (hasParent(index) && this->getNodeAt(getParentIndex(index)).getKey() < this->getNodeAt(index).getKey())
    {
        array_->swapNodes(index, getParentIndex(index));
        index = getParentIndex(index);
    }
}

void Heap::heapifyDown() {
    int index = 0;
    unsigned l, r, smaller = 0;
    while (hasLeftChild(index)) {
        l = 2 * index + 1; // Lewy syn
        r = 2 * index + 2; // Prawy syn

        smaller = l;
        if(hasRightChild(index) && r > l) {
            smaller = r;
        }

        if (getNodeAt(index).getKey() > getNodeAt(smaller).getKey()) {
            break;
        }
        else {
            array_->swapNodes(index, smaller);
        }
        index = smaller;
    }
}

unsigned Heap::getParentIndex(unsigned index) {
    return (index - 1) / 2;
}

bool Heap::hasParent(unsigned index) {
    if (index != 0) return 1;
    return 0;
}

bool Heap::hasLeftChild(unsigned index) {
    unsigned l = 2 * index + 1; // Lewy syn
    unsigned r = 2 * index + 2; // Prawy syn
    if((array_->getDynamicArraySize() - 1) < l) return 0;
    if (array_->getDynamicArrayNodeAt(l).isEmpty() == true) return 0;
    return 1;
}
bool Heap::hasRightChild(unsigned index) {
    unsigned l = 2 * index + 1; // Lewy syn
    unsigned r = 2 * index + 2; // Prawy syn
    if ((array_->getDynamicArraySize() - 1) < r) return 0;
    if (array_->getDynamicArrayNodeAt(r).isEmpty() == true) return 0;
    return 1;
}

void Heap::fillFromCSV(const std::string& value_file_name, const std::string& priority_file_name, int n) {
    // Otwarcie plików CSV
    std::ifstream valueFile(value_file_name);
    std::ifstream priorityFile(priority_file_name);

    if (!valueFile.is_open()) {
        std::cerr << "Nie można otworzyć pliku wartości do odczytu." << std::endl;
        return;
    }

    if (!priorityFile.is_open()) {
        std::cerr << "Nie można otworzyć pliku priorytetów do odczytu." << std::endl;
        return;
    }

    std::string valueLine;
    std::string priorityLine;

    for (int i = 0; i < n; ++i) {
        if (std::getline(valueFile, valueLine) && std::getline(priorityFile, priorityLine)) {
            // Konwersja wartości i priorytetów z ciągów tekstowych na liczby
            int value = std::stoi(valueLine);
            int priority = std::stoi(priorityLine);

            // Dodawanie do kolejki priorytetowej
            insert(priority, value);
        }
        else {
            std::cerr << "Wystąpił błąd podczas odczytu danych." << std::endl;
            break; // Jeśli jeden z plików ma mniej linii niż oczekiwano, przerywamy pętlę
        }
    }

    // Zamknięcie plików
    valueFile.close();
    priorityFile.close();
}

Node Heap::getNodeAt(unsigned index) {
    return array_->getDynamicArrayNodeAt(index);
}

void Heap::printHeap(unsigned i = 0) {
    unsigned l = 2 * i + 1; // Lewy syn
    unsigned r = 2 * i + 2; // Prawy syn

    if(i==0) std::cout << "the key of node " << i << " is " << this->getNodeAt(i).getKey() << " value " << this->getNodeAt(i).getValue() << std::endl;

    if ( l >= this->returnSize()) return;

    printHeap(l);
    std::cout << "the key of node " << l << " is " << this->getNodeAt(l).getKey() << " value " << this->getNodeAt(l).getValue() << std::endl;

    if (r >= this->returnSize()) return;

    printHeap(r);
    std::cout << "the key of node " << r << " is " << this->getNodeAt(r).getKey() << " value " << this->getNodeAt(r).getValue() << std::endl;

}