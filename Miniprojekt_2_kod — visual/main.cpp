#include <iostream>
#include <string>
#include <random>

#include "Heap.hpp"
#include "test.h"
#include "Zapis.hpp"

void testingHeap(const unsigned numOfHeaps, int size, int iteration);
void runTestsHeap(const unsigned numOfArrays);

int main(){
    test test;
    int num_of_numbers = 100;
    int min = 0;
    int max = 1000;
    std::string keys_file1 = "CSV/keys_file1.csv";
    std::string values_file1 = "CSV/values_file1.csv";
    int seed = 1;


    runTestsHeap(100);
}

void testingHeap(const unsigned numOfHeaps, int size, int iteration) {

    //Zapis plik_insert("PriorityQueue_insert.csv");
    //Zapis plik_extract_max("PriorityQueue_extract_max.csv");
    //Zapis plik_findMax("PriorityQueue_findMax.csv");
    //Zapis plik_modifyKey("PriorityQueue_modifyKey.csv");

    Zapis plik_insert("heap_insert.csv");
    Zapis plik_extractMax("heap_extract_max.csv");
    Zapis plik_findMax("heap_find_max.csv");
    Zapis plik_modifyKey("heap_modify_key.csv");
    Zapis plik_returnSize("heap_return_size.csv");

    cout << "Please wait..." << endl;

    Heap** heap = new Heap * [numOfHeaps];
    Heap** heapbackup = new Heap * [numOfHeaps];


    // Tworzymy numOfArrays priorytetowych kolejek
    for (int i = 0; i < numOfHeaps; ++i) {
        heap[i] = new Heap(4);
        heapbackup[i] = new Heap(4);
    }

    for (int i = 0; i < numOfHeaps; i++) {
        heap[i]->fillFromCSV("random_numbers.csv", "random_numbers_priority.csv", size);
        heapbackup[i]->fillFromCSV("random_numbers.csv", "random_numbers_priority.csv", size);
    }

    //    pQ[1]->display();
    //    cout << pQ[1]->returnSize() << endl;

    //insert
    std::random_device rd1;
    std::mt19937 gen1(rd1());
    std::uniform_int_distribution<> dis1(0, 500000);
    int losowa_liczba = dis1(gen1);

    auto begin = std::chrono::high_resolution_clock::now();
    for (unsigned i = 0; i < numOfHeaps; i++) {
        heap[i]->insert(losowa_liczba, 5);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    plik_insert.shot(iteration, elapsed.count() / numOfHeaps, size);

    //powrot do stanu poczatkowego
    for (int i = 0; i < numOfHeaps + 1; i++) {
        heap[i] = heapbackup[i];
    }

    //extract-max()
    auto begin2 = std::chrono::high_resolution_clock::now();
    for (unsigned i = 0; i < numOfHeaps; i++) {
        heap[i]->extractMax();
    }
    auto end2 = std::chrono::high_resolution_clock::now();
    auto elapsed2 = std::chrono::duration_cast<std::chrono::microseconds>(end2 - begin2);
    plik_extractMax.shot(iteration, elapsed2.count() / numOfHeaps, size);

    //powrot do stanu 
    delete[] heap;
    heap = new Heap * [numOfHeaps];
    for (int i = 0; i < numOfHeaps + 1; i++) {
        heap[i] = heapbackup[i];
    }



    //for (int i = 0; i < numOfHeaps; i++) {
    //    heap[i] = new Heap(4);
    //}
    //for (int i = 0; i < numOfHeaps; i++) {
    //    heap[i]->fillFromCSV("random_numbers.csv", "random_numbers_priority.csv", size);
    //}


    //find max
    auto begin3 = std::chrono::high_resolution_clock::now();
    for (unsigned i = 0; i < numOfHeaps; i++) {
        heap[i]->findMax();
    }
    auto end3 = std::chrono::high_resolution_clock::now();
    auto elapsed3 = std::chrono::duration_cast<std::chrono::microseconds>(end3 - begin3);
    plik_findMax.shot(iteration, elapsed3.count() / numOfHeaps, size);


    //modify key
    std::random_device rd2;
    std::mt19937 gen2(rd2());
    std::uniform_int_distribution<> dis2(0, size);
    losowa_liczba = dis2(gen2);

    int val = heap[0]->getNodeAt(losowa_liczba).getValue();
    auto begin4 = std::chrono::high_resolution_clock::now();
    for (unsigned i = 0; i < numOfHeaps; i++) {
        heap[i]->modifyKey(val, 1000);
    }
    auto end4 = std::chrono::high_resolution_clock::now();
    auto elapsed4 = std::chrono::duration_cast<std::chrono::microseconds>(end4 - begin4);
    plik_modifyKey.shot(iteration, elapsed4.count() / numOfHeaps, size);


    auto begin5 = std::chrono::high_resolution_clock::now();
    for (unsigned i = 0; i < numOfHeaps; i++) {
        heap[i]->returnSize();
    }
    auto end5 = std::chrono::high_resolution_clock::now();
    auto elapsed5 = std::chrono::duration_cast<std::chrono::microseconds>(end5 - begin5);
    plik_returnSize.shot(iteration, elapsed5.count() / numOfHeaps, size);


    for (int i = 0; i < numOfHeaps + 1; i++) {
        heap[i] = heapbackup[i];
    }
}

void runTestsHeap(const unsigned numOfArrays) {

    test::generateRandomNumbers(150000, 0, 100000, "random_numbers.csv", 5);
    test::generateRandomNumbers(150000, 0, 100000, "random_numbers_priority.csv", 3);

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
            testingHeap(numOfArrays, 1024, 1);
            testingHeap(numOfArrays, 2048, 2);
            testingHeap(numOfArrays, 4096, 3);
            testingHeap(numOfArrays, 8192, 4);
            testingHeap(numOfArrays, 16384, 5);
            testingHeap(numOfArrays, 32768, 6);
            testingHeap(numOfArrays, 65536, 7);
            testingHeap(numOfArrays, 131072, 8);
            //                testing(numOfArrays, 18000, 9);
            //                testing(numOfArrays, 20000, 10);
            break;
        }

        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    } while (choice3 != '0');
}