#include <iostream>
#include <string>
#include <random>
#include <thread>

#include "Heap.hpp"
#include "test.h"
#include "Zapis.hpp"

using std::operator""s;

void testingHeap(const unsigned numOfHeaps, int size, int iteration);
void runTestsHeap(const unsigned numOfArrays);

int main(){
    unsigned numOfArrays = 100;
    //std::string keys_file1 = "CSV/keys_file1.csv";
    //std::string values_file1 = "CSV/values_file1.csv";

    //Heap *heap = new Heap;
    //heap->fillFromCSV("random_numbers.csv", "random_numbers_priority.csv", size);

    //cout << heap->findNodeByValue(67307, 0).getValue() << "TUUUUUUU" << endl;

    runTestsHeap(numOfArrays);
    //testingHeap(numOfArrays, 1000, 1);
    //testingHeap(numOfArrays, 2000, 2);
    //testingHeap(numOfArrays, 4000, 3);
    //testingHeap(numOfArrays, 8000, 4);
    //testingHeap(numOfArrays, 16000, 5);
    //testingHeap(numOfArrays, 32000, 6);
    //testingHeap(numOfArrays, 64000, 7);
    //testingHeap(numOfArrays, 128000, 8);


}

void testingHeap(const unsigned numOfHeaps, int size, int iteration) {

    Zapis plik_insert("CSV/heap_insert.csv");
    Zapis plik_extractMax("CSV/heap_extract_max.csv");
    Zapis plik_findMax("CSV/heap_find_max.csv");
    Zapis plik_modifyKey("CSV/heap_modify_key.csv");
    Zapis plik_returnSize("CSV/heap_return_size.csv");

    cout << "Please wait..." << endl;

    Heap* heap1 = new Heap[numOfHeaps];
    Heap* heap2 = new Heap[numOfHeaps];
    Heap* heap3 = new Heap[numOfHeaps];
    Heap* heap4 = new Heap[numOfHeaps];
    Heap* heap5 = new Heap[numOfHeaps];

    for (int i = 0; i < numOfHeaps; i++) {
        heap1[i].fillFromCSV("CSV/random_numbers.csv", "CSV/random_numbers_priority.csv", size);
        heap2[i].fillFromCSV("CSV/random_numbers.csv", "CSV/random_numbers_priority.csv", size);
        heap3[i].fillFromCSV("CSV/random_numbers.csv", "CSV/random_numbers_priority.csv", size);
        heap4[i].fillFromCSV("CSV/random_numbers.csv", "CSV/random_numbers_priority.csv", size);
        heap5[i].fillFromCSV("CSV/random_numbers.csv", "CSV/random_numbers_priority.csv", size);
    }
    //heap1->printHeap(0);

    //insert
    std::random_device rd1;
    std::mt19937 gen1(rd1());
    std::uniform_int_distribution<> dis1(0, 500000);
    int losowa_liczba = dis1(gen1);
    
    auto begin = std::chrono::high_resolution_clock::now();
    for (unsigned i = 0; i < numOfHeaps; i++) {
        heap1[i].insert(losowa_liczba, 5);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    plik_insert.shot(iteration, elapsed.count() / numOfHeaps, size);

    //extract-max()
    auto begin2 = std::chrono::high_resolution_clock::now();
    for (unsigned i = 0; i < numOfHeaps; i++) {
        heap2[i].extractMax();
    }
    auto end2 = std::chrono::high_resolution_clock::now();
    auto elapsed2 = std::chrono::duration_cast<std::chrono::microseconds>(end2 - begin2);
    plik_extractMax.shot(iteration, elapsed2.count() / numOfHeaps, size);


    //find max
    auto begin3 = std::chrono::high_resolution_clock::now();
    for (unsigned i = 0; i < numOfHeaps; i++) {
        heap3[i].findMax();
    }
    auto end3 = std::chrono::high_resolution_clock::now();
    auto elapsed3 = std::chrono::duration_cast<std::chrono::microseconds>(end3 - begin3);
    plik_findMax.shot(iteration, elapsed3.count() / numOfHeaps, size);


    //modify key
    std::random_device rd2;
    std::mt19937 gen2(rd2());
    std::uniform_int_distribution<> dis2(0, size);
    losowa_liczba = dis2(gen2);

    int val = heap4[0].getNodeAt(losowa_liczba).getValue();
    auto begin4 = std::chrono::high_resolution_clock::now();
    for (unsigned i = 0; i < numOfHeaps; i++) {
        heap4[i].modifyKey(val, 1000);
    }
    auto end4 = std::chrono::high_resolution_clock::now();
    auto elapsed4 = std::chrono::duration_cast<std::chrono::microseconds>(end4 - begin4);
    plik_modifyKey.shot(iteration, elapsed4.count() / numOfHeaps, size);


    auto begin5 = std::chrono::high_resolution_clock::now();
    for (unsigned i = 0; i < numOfHeaps; i++) {
        heap5[i].returnSize();
    }
    auto end5 = std::chrono::high_resolution_clock::now();
    auto elapsed5 = std::chrono::duration_cast<std::chrono::microseconds>(end5 - begin5);
    plik_returnSize.shot(iteration, elapsed5.count() / numOfHeaps, size);


    //for (int i = 0; i < numOfHeaps; i++) {
    //    heap[i] = heapbackup[i];
    //}

    // usuwanie
    //for (int i = 0; i < numOfHeaps; i++) {
    //    delete[] heap[i];
    //}
    //delete[] heap;

    //for (int i = 0; i < numOfHeaps; i++) {
    //    delete[] heapbackup[i];
    //}
    //delete[] heapbackup;

    //heap = nullptr;
    //heapbackup = nullptr;
}

void runTestsHeap(const unsigned numOfArrays) {

    test::generateRandomNumbers(150000, 0, 100000, "CSV/random_numbers.csv", 5);
    test::generateRandomNumbers(150000, 0, 100000, "CSV/random_numbers_priority.csv", 3);

    char choice3;
    do {
        cout << "1. array_2k" << endl;
        cout << "2. array_4k" << endl;
        cout << "3. array_6k" << endl;
        cout << "4. array_8k" << endl;
        cout << "5. array_10k" << endl;
        cout << "6. array_12k" << endl;
        cout << "7. array_14k" << endl;
        cout << "8. array_16k" << endl;
        cout << "9. array_18k" << endl;
        cout << "X. array_20k" << endl;
        cout << "A. Test all" << endl;
        cout << "0. Exit" << endl;



        cin >> choice3;
        switch (choice3) {
        case '0':
            cout << "Exiting..." << endl;
            break;
        case '1':
        {
            testingHeap(numOfArrays, 2000, 1);
            break;
        }
        case '2':
        {
            testingHeap(numOfArrays, 4000, 2);
            break;
        }
        case '3':
        {
            testingHeap(numOfArrays, 6000, 3);
            break;
        }
        case '4':
        {
            testingHeap(numOfArrays, 8000, 4);
            break;
        }
        case '5':
        {
            testingHeap(numOfArrays, 10000, 5);
            break;
        }
        case '6':
        {
            testingHeap(numOfArrays, 12000, 6);
            break;
        }
        case '7':
        {
            testingHeap(numOfArrays, 14000, 7);
            break;
        }
        case '8':
        {
            testingHeap(numOfArrays, 16000, 8);
            break;
        }
        case '9':
        {
            testingHeap(numOfArrays, 18000, 9);
            break;
        }
        case 'X':
        {
            testingHeap(numOfArrays, 20000, 10);
            break;
        }
        case 'A':
        {
            testingHeap(numOfArrays, 1000, 1);
            testingHeap(numOfArrays, 2000, 2);
            testingHeap(numOfArrays, 4000, 3);
            testingHeap(numOfArrays, 8000, 4);
            testingHeap(numOfArrays, 16000, 5);
            testingHeap(numOfArrays, 32000, 6);
            testingHeap(numOfArrays, 64000, 7);
            testingHeap(numOfArrays, 128000, 8);
            //testingHeap(numOfArrays, 1024, 1);
            //testingHeap(numOfArrays, 2048, 2);
            //testingHeap(numOfArrays, 4096, 3);
            //testingHeap(numOfArrays, 8192, 4);
            //testingHeap(numOfArrays, 16384, 5);
            //testingHeap(numOfArrays, 32768, 6);
            //testingHeap(numOfArrays, 65536, 7);
            //testingHeap(numOfArrays, 131072, 8);
                            //testing(numOfArrays, 18000, 9);
                            //testing(numOfArrays, 20000, 10);
            break;
        }

        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    } while (choice3 != '0');
}