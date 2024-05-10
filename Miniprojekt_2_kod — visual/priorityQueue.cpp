#include "priorityQueue.h"

#include <iostream>

using namespace std;

PriorityQueue::PriorityQueue(int capacity) : elements(capacity) {}

void PriorityQueue::insert(int value, int priority) {
    Element newElement = { value, priority };
    elements.addBack(newElement);
}

Element PriorityQueue::extractMax() {
    if (elements.isDynamicArrayEmpty()) {
        cout << "Kolejka jest pusta." << endl;
        return { -1, -1 };
    }

    int maxIndex = 0;
    for (int i = 1; i < elements.getDynamicArraySize(); ++i) {
        if (elements.getDynamicArrayElementAt(i).priority > elements.getDynamicArrayElementAt(maxIndex).priority) {
            maxIndex = i;
        }
    }

    Element maxElement = elements.getDynamicArrayElementAt(maxIndex);
    elements.remove(maxIndex);
    return maxElement;
}

Element PriorityQueue::findMax() {
    if (elements.isDynamicArrayEmpty()) {
        cout << "Kolejka jest pusta." << endl;
        return { -1, -1 };
    }

    int maxIndex = 0;
    for (int i = 1; i < elements.getDynamicArraySize(); ++i) {
        if (elements.getDynamicArrayElementAt(i).priority > elements.getDynamicArrayElementAt(maxIndex).priority) {
            maxIndex = i;
        }
    }

    return elements.getDynamicArrayElementAt(maxIndex);
}

void PriorityQueue::modifyKey(int value, int newPriority) {
    int index = -1;
    for (int i = 0; i < elements.getDynamicArraySize(); ++i) {
        if (elements.getDynamicArrayElementAt(i).value == value) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "Element o podanej wartosci nie istnieje w kolejce." << endl;
        return;
    }

    Element modifiedElement = elements.getDynamicArrayElementAt(index);
    modifiedElement.priority = newPriority;
    elements.remove(index);
    elements.add(index, modifiedElement);
}

int PriorityQueue::returnSize() {
    return elements.getDynamicArraySize();
}

void PriorityQueue::display() const {
    std::cout << "Elementy w kolejce priorytetowej:\n";
    for (int i = 0; i < elements.getDynamicArraySize(); ++i) {
        std::cout << "Wartosc: " << elements.getDynamicArrayElementAt(i).value << " (Priorytet: " << elements.getDynamicArrayElementAt(i).priority << ")\n";
    }
}

void PriorityQueue::fillFromCSV(const std::string& value_file_name, const std::string& priority_file_name, int n) {
    // Otwarcie plików CSV
    std::ifstream valueFile(value_file_name);
    std::ifstream priorityFile(priority_file_name);

    if (!valueFile.is_open()) {
        std::cerr << "Nie mo¿na otworzyæ pliku wartoœci do odczytu." << std::endl;
        return;
    }

    if (!priorityFile.is_open()) {
        std::cerr << "Nie mo¿na otworzyæ pliku priorytetów do odczytu." << std::endl;
        return;
    }

    std::string valueLine;
    std::string priorityLine;

    for (int i = 0; i < n; ++i) {
        if (std::getline(valueFile, valueLine) && std::getline(priorityFile, priorityLine)) {
            // Konwersja wartoœci i priorytetów z ci¹gów tekstowych na liczby
            int value = std::stoi(valueLine);
            int priority = std::stoi(priorityLine);

            // Dodawanie do kolejki priorytetowej
            insert(value, priority);
        }
        else {
            std::cerr << "Wyst¹pi³ b³¹d podczas odczytu danych." << std::endl;
            break; // Jeœli jeden z plików ma mniej linii ni¿ oczekiwano, przerywamy pêtlê
        }
    }

    // Zamkniêcie plików
    valueFile.close();
    priorityFile.close();
}


Element PriorityQueue::getElementAt(int index) const {
    if (index < 0 || index >= elements.getDynamicArraySize()) {
        throw std::out_of_range("Indeks poza zakresem!");
    }
    return elements.getDynamicArrayElementAt(index);
}
