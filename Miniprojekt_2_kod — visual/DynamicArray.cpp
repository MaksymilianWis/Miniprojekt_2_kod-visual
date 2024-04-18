#include "DynamicArray.hpp"

dynamicArray::dynamicArray(int capacity) : dynamicArrayCapacity(capacity), arrayNode_(new Node[capacity]) {
    // konstruktor z argumentem rozmiaru tablicy, pointer wskazuje na pocz�tek tej tablicy
    
    // flagi empty_ automatycznie ustawiane w konstruktorze node
}
dynamicArray::dynamicArray() : dynamicArraySize(0), dynamicArrayCapacity(0), arrayNode_(new Node[0])
{
    //konstruktor domy�lny
}
dynamicArray::~dynamicArray() {
    if (arrayNode_->isEmpty() == true) return;

    free(arrayNode_);
    dynamicArrayCapacity = 0;
    dynamicArraySize = 0;
    arrayNode_ = nullptr;
}

void dynamicArray::increaseCapacity() {
    // Sprawdzamy, czy tablica ma wystarczaj�c� pojemno��
    if (dynamicArraySize == dynamicArrayCapacity) {

        // Tworzymy nowy bufor o zwi�kszonej pojemno�ci
        Node* buffer = new Node[dynamicArrayCapacity * 2];

        // Kopiujemy istniej�ce elementy do nowego bufora
        for (int i = 0; i < dynamicArraySize + 1; i++) {
            buffer[i] = arrayNode_[i];
        }

        // Usuwamy stary bufor
        delete[] arrayNode_;

        // Przypisujemy nowy bufor do dynamicArrayPtr
        arrayNode_ = buffer;
        dynamicArrayCapacity *= 2;
    }
}

void dynamicArray::decreaseCapacity() {
    // Sprawdzamy, czy liczba element�w w tablicy spad�a poni�ej po�owy jej aktualnej pojemno�ci
    if (dynamicArraySize == (dynamicArrayCapacity / 2)) {

        // Tworzymy nowy bufor o zmniejszonej pojemno�ci
        Node* buffer = new Node[dynamicArrayCapacity / 2];

        // Kopiujemy istniej�ce elementy do nowego bufora
        for (int i = 0; i < dynamicArraySize + 1; ++i) {
            buffer[i] = arrayNode_[i];
        }

        // Usuwamy stary bufor
        delete[] arrayNode_;

        // Przypisujemy nowy bufor do dynamicArrayPtr
        arrayNode_ = buffer;
        dynamicArrayCapacity /= 2;
    }
}


int dynamicArray::getDynamicArraySize() const {
    return dynamicArraySize;
}

bool dynamicArray::isDynamicArrayEmpty() {
    return dynamicArraySize == 0;
}

int dynamicArray::getDynamicArrayValueAt(int index) {
    if (index < 0 || index >= dynamicArraySize) {
        cout << "B��d: Indeks poza zakresem!" << endl;
        exit(EXIT_FAILURE);
    }
    return arrayNode_[index].getValue();
}


int dynamicArray::getDynamicArrayKeyAt(int index) {
    return arrayNode_[index].getKey();
}

//int dynamicArray::findElement(int element) {
//    for (int i = 0; i < dynamicArraySize; i++) {
//        if (dynamicArrayPtr[i] == element) {
//            return i;
//        }
//    }
//    return -1;
//}

void dynamicArray::displayDynamicArrayWCapacity() {
    for (int i = 1; i < dynamicArrayCapacity + 1; i++) {
        cout << arrayNode_[i].getValue() << "\t"; // Wy�wietlamy warto�� na pozycji i
    }
    cout << endl;
}

void dynamicArray::displayDynamicArray() {  //wyswietlenie tablicy
    // Przechodzimy przez tablic� i wy�wietlamy jej zawarto��
    for (int i = 1; i < dynamicArraySize + 1; i++) {
        cout << arrayNode_[i].getValue() << "\t"; // Wy�wietlamy warto�� na pozycji i
    }
    cout << endl;
}

void dynamicArray::addBack(int key, int value) { // dodaje value w koniec tablicy
    increaseCapacity();
    dynamicArraySize++;
    arrayNode_[dynamicArraySize].OverwriteNodeKeyValue(key, value);
}

//void dynamicArray::add(int index, int element) {
//    if (index < 0) {
//        cout << "B��d: Niepoprawny indeks!" << endl;
//        return;
//    }
//
//    if (index < dynamicArraySize) {
//        increaseCapacity();
//        dynamicArraySize++;
//        for (int i = dynamicArraySize; i > index; i--) {
//            dynamicArrayPtr[i + 1] = dynamicArrayPtr[i];
//        }
//        dynamicArrayPtr[index + 1] = element;
//    }
//    else {
//        //gdy index jest wi�kszy ni� size, wstaw nowy element na pierwsz� woln� pozycj�
//        increaseCapacity();
//        addBack(element);
//    }
//}

//void dynamicArray::remove(int index) {
//    if (index < 0 || index > dynamicArraySize) {
//        cout << "B��d: Niepoprawny indeks!" << endl;
//        return;
//    }
//
//    // Usuwamy element na podanym indeksie
//    for (int i = index + 1; i < dynamicArraySize; ++i) {
//        dynamicArrayPtr[i] = dynamicArrayPtr[i + 1];
//    }
//    dynamicArraySize--;
//
//    decreaseCapacity();
//}

void dynamicArray::removeBack() {
    arrayNode_[dynamicArraySize].clearNode();
    dynamicArraySize--;
    decreaseCapacity();
}

//void dynamicArray::addFront(int element) {
//    increaseCapacity();
//    dynamicArraySize++;
//    for (int i = dynamicArraySize; i > 0; i--) {
//        dynamicArrayPtr[i] = dynamicArrayPtr[i - 1];
//    }
//    dynamicArrayPtr[1] = element;
//}

//void dynamicArray::removeFront() {
//    for (int i = 1; i < dynamicArraySize; i++) {
//        dynamicArrayPtr[i] = dynamicArrayPtr[i + 1];
//    }
//    dynamicArraySize--;
//    decreaseCapacity();
//}

void dynamicArray::swapNodes(int index1, int index2) {
    Node temp = arrayNode_[index1];

    arrayNode_[index1] = arrayNode_[index2];
    arrayNode_[index2] = temp;
}

void dynamicArray::fillFromArrayCSV(const std::string& filename, int maxElements) {
    // Otwieramy plik CSV
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Unable to open the file: " << filename << std::endl;
        return;
    }

    std::string line;
    int elementsAdded = 0;
    while (std::getline(file, line) && elementsAdded < maxElements) {
        std::istringstream iss(line);
        std::string value;
        while (std::getline(iss, value, ',') && elementsAdded < maxElements) {
            int element;
            try {
                // Konwertujemy warto�� z ci�gu znak�w na liczb� ca�kowit�
                element = std::stoi(value);
            }
            catch (const std::invalid_argument& e) {
                // Ignorujemy nieprawid�owe warto�ci
                continue;
            }
            // Dodajemy element do tablicy
            // cos jest poprostu offsetem �eby value != key // value nie ingeruje w badania
            int cos = 2;
            addBack(element, element+cos);
            elementsAdded++;
        }
    }

    // Zamykamy plik
    file.close();
}