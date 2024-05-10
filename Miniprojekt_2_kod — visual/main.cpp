#include <iostream>
#include <string>
#include <random>
#include <thread>

#include "Heap.hpp"
#include "test.h"
#include "Zapis.hpp"
#include "dynamicArray_pq.h"
#include "priorityQueue.h"

using std::operator""s;

void testingHeap(const unsigned numOfHeaps, int size, int iteration);
void runTestsHeap(const unsigned numOfArrays);

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

void testing(const unsigned numOfPQ, int size, int iteration) {

    Zapis plik_insert("PriorityQueue_insert.csv");
    Zapis plik_extract_max("PriorityQueue_extract_max.csv");
    Zapis plik_findMax("PriorityQueue_findMax.csv");
    Zapis plik_modifyKey("PriorityQueue_modifyKey.csv");
    Zapis plik_returnSize("PriorityQueue_returnSize.csv");

    cout << "Please wait..." << endl;
    //   PriorityQueue *pQ[numOfPQ];
    //   PriorityQueue *pQbackup[numOfPQ];

    PriorityQueue** pQ = new PriorityQueue * [numOfPQ];
    PriorityQueue** pQbackup = new PriorityQueue * [numOfPQ];


    // Tworzymy numOfArrays priorytetowych kolejek
    for (int i = 0; i < numOfPQ; ++i) {
        pQ[i] = new PriorityQueue;
        pQbackup[i] = new PriorityQueue;
    }

    for (int i = 0; i < numOfPQ; i++) {
        pQ[i]->fillFromCSV("random_numbers.csv", "random_numbers_priority.csv", size);
        pQbackup[i]->fillFromCSV("random_numbers.csv", "random_numbers_priority.csv", size);
    }

    //insert
    auto total_time = 0;
    for (unsigned i = 0; i < numOfPQ; i++) {
        std::random_device rd1;
        std::mt19937 gen1(rd1());
        std::uniform_int_distribution<> dis1(0, size);
        int losowa_liczba2 = dis1(gen1);

        auto start = std::chrono::high_resolution_clock::now();
        pQ[i]->insert(5, losowa_liczba2);
        auto end = std::chrono::high_resolution_clock::now();

        total_time += std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    }
    plik_insert.shot(iteration, total_time/numOfPQ, size);

    //powrot do stanu poczatkowego
    for (int i = 0; i < numOfPQ + 1; i++) {
        pQ[i] = pQbackup[i];
    }

    //extract-max()
    auto begin2 = std::chrono::high_resolution_clock::now();
    for (unsigned i = 0; i < numOfPQ; i++) {
        pQ[i]->extractMax();
    }
    auto end2 = std::chrono::high_resolution_clock::now();
    auto elapsed2 = std::chrono::duration_cast<std::chrono::microseconds>(end2 - begin2);
    plik_extract_max.shot(iteration, elapsed2.count() / numOfPQ, size);

    //powrot do stanu poczatkowego
    for (int i = 0; i < numOfPQ - 1; i++) {
        delete pQ[i];
    }
    for (int i = 0; i < numOfPQ; i++) {
        pQ[i] = new PriorityQueue;
    }
    for (int i = 0; i < numOfPQ; i++) {
        pQ[i]->fillFromCSV("random_numbers.csv", "random_numbers_priority.csv", size);
    }

    //find max
    auto begin3 = std::chrono::high_resolution_clock::now();
    for (unsigned i = 0; i < numOfPQ; i++) {
        pQ[i]->findMax();
    }
    auto end3 = std::chrono::high_resolution_clock::now();
    auto elapsed3 = std::chrono::duration_cast<std::chrono::microseconds>(end3 - begin3);
    plik_findMax.shot(iteration, elapsed3.count() / numOfPQ, size);

    //modify key
    auto total_time2 = 0;
    for (unsigned i = 0; i < numOfPQ; i++) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, size);
        int losowa_liczba = dis(gen);

        int val = pQ[0]->getElementAt(losowa_liczba).value;

        auto start = std::chrono::high_resolution_clock::now();
        pQ[i]->modifyKey(val, 1000);
        auto end = std::chrono::high_resolution_clock::now();

        total_time2 += std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    }
    double avg_time = total_time2 / numOfPQ;
    plik_modifyKey.shot(iteration, avg_time, size);

    //return size
    auto begin5 = std::chrono::high_resolution_clock::now();
    for (unsigned i = 0; i < numOfPQ; i++) {
        pQ[i]->returnSize();
    }
    auto end5 = std::chrono::high_resolution_clock::now();
    auto elapsed5 = std::chrono::duration_cast<std::chrono::nanoseconds>(end5 - begin5);
    plik_returnSize.shot(iteration, elapsed5.count() / numOfPQ, size);
    for (int i = 0; i < numOfPQ + 1; i++) {
        pQ[i] = pQbackup[i];
    }
}

void runTests(const unsigned numOfArrays) {

    test::generateRandomNumbers(150000, 0, 100000, "random_numbers.csv", 5);
    test::generateRandomNumbers(150000, 0, 500000, "random_numbers_priority.csv", 3);

    char choice3;
    do {
        cout << "1. array_1k" << endl;
        cout << "2. array_2k" << endl;
        cout << "3. array_4k" << endl;
        cout << "4. array_8k" << endl;
        cout << "5. array_16k" << endl;
        cout << "6. array_32k" << endl;
        cout << "7. array_64k" << endl;
        cout << "8. array_128k" << endl;
        cout << "9. array_256k" << endl;
        cout << "A. Test all" << endl;
        cout << "0. Exit" << endl;



        cin >> choice3;
        switch (choice3) {
        case '0':
            cout << "Exiting..." << endl;
            break;
        case '1':
        {
            testing(numOfArrays, 1000, 1);
            break;
        }
        case '2':
        {
            testing(numOfArrays, 2000, 2);
            break;
        }
        case '3':
        {
            testing(numOfArrays, 4000, 3);
            break;
        }
        case '4':
        {
            testing(numOfArrays, 8000, 4);
            break;
        }
        case '5':
        {
            testing(numOfArrays, 16000, 5);
            break;
        }
        case '6':
        {
            testing(numOfArrays, 32000, 6);
            break;
        }
        case '7':
        {
            testing(numOfArrays, 64000, 7);
            break;
        }
        case '8':
        {
            testing(numOfArrays, 128000, 8);
            break;
        }
        case '9':
        {
            testing(numOfArrays, 256000, 9);
            break;
        }
        case 'A':
        {
            testing(numOfArrays, 1000, 1);
            testing(numOfArrays, 2000, 2);
            testing(numOfArrays, 4000, 3);
            testing(numOfArrays, 8000, 4);
            testing(numOfArrays, 16000, 5);
            testing(numOfArrays, 32000, 6);
            testing(numOfArrays, 64000, 7);
            testing(numOfArrays, 128000, 8);
            break;
        }

        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    } while (choice3 != '0');
}


int main() {
    char choice;
    do {
        cout << "Menu:" << endl;
        cout << "1. Test Dynamic Array" << endl;
        cout << "2. Test Heap" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: " << endl;
        cin >> choice;

        switch (choice) {
        case '1':
            cout << "Running tests..." << endl;
            cout << "Please choose the number of priority queues, " << endl;
            int numOfArrays;
            cin >> numOfArrays;
            cout << "Please wait..." << endl;
            runTests(numOfArrays);
            break;
        case '2':
            cout << "Running tests..." << endl;
            cout << "Please choose the number of priority queues, " << endl;
            int numOfArrays2;
            cin >> numOfArrays2;
            cout << "Please wait..." << endl;
            runTestsHeap(numOfArrays2);
            break;
        case '3':
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }

    } while (choice != '3');

    return 0;


}