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
//Node Heap::findNodeByValue(int value, int i = 0) {
//
//    unsigned l = 2 * i + 1; // Lewy syn
//    unsigned r = 2 * i + 2; // Prawy syn
//
//    // warunek krancowy
//    if (array_->getDynamicArrayNodeAt(i).isEmpty() or i >= array_->getDynamicArraySize()) {
//        cout << "pusty" << endl;
//        return Node();
//    }
//
//    // czy pod lewym synem?
//        if (array_->getDynamicArrayNodeAt(l).getValue() == value) {
//            return array_->getDynamicArrayNodeAt(l);
//        }
//            return findNodeByValue(value, l);
//        
//
//        if (array_->getDynamicArrayNodeAt(r).getValue() == value) {
//            return array_->getDynamicArrayNodeAt(r);
//        }
//            return findNodeByValue(value, r);
//
//    //std::cout << "ERROR nie znaleziono elementu o wartosci" << value << std::endl;
//}

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
        std::cout << "Nie znaleziono elementu o wartości " << value << "." << std::endl;
        return Node(); // Zwróć pusty węzeł
    }

    // Sprawdź wartość w bieżącym węźle
    if (array_->getDynamicArrayNodeAt(i).getValue() == value) {
        return array_->getDynamicArrayNodeAt(i); // Zwróć węzeł, jeśli wartość została znaleziona
    }

    // Rekurencyjnie poszukaj w lewym i prawym poddrzewie
    Node foundNode = findNodeByValue(value, l); // Przeszukaj lewe poddrzewo
    if (!foundNode.isEmpty()) {
        return foundNode; // Zwróć znaleziony węzeł
    }

    return findNodeByValue(value, r); // Przeszukaj prawe poddrzewo
}


void Heap::modifyKey(int value, int new_key){
    int i = 0;

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

void Heap::fillFromCSV(const std::string& filename_keys, const std::string& filename_values, int maxElements) {
    // Otwieramy plik CSV
    std::ifstream file1(filename_keys);
    std::ifstream file2(filename_values);
    if (!file1.is_open()) {
        std::cerr << "Unable to open the file: " << filename_keys << std::endl;
        return;
    }
    if (!file2.is_open()) {
        std::cerr << "Unable to open the file: " << filename_values << std::endl;
        return;
    }

    std::string line1;
    std::string line2;
    int elementsAdded = 0;
    while (std::getline(file1, line1) && elementsAdded < maxElements && std::getline(file2, line2)) {
        std::istringstream iss1(line1);
        std::string key;
        std::istringstream iss2(line2);
        std::string value;
        while (std::getline(iss1, key, ',') && (elementsAdded < maxElements) && std::getline(iss2, value, ',')) {
            int k;
            int v;
            try {
                // Konwertujemy wartość z ciągu znaków na liczbę całkowitą
                k = std::stoi(key);
                v = std::stoi(value);
            }
            catch (const std::invalid_argument& e) {
                // Ignorujemy nieprawidłowe wartości
                continue;
            }
            // Dodajemy element do tablicy
            insert(k, v);
            elementsAdded++;
        }
    }

    // Zamykamy pliki
    file1.close();
    file2.close();
}

Node Heap::getNodeAt(unsigned index) {
    return array_->getDynamicArrayNodeAt(index);
}