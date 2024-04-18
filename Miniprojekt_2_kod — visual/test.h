#ifndef TABLICA_DYNAMICZNA_TEST_H
#define TABLICA_DYNAMICZNA_TEST_H

#include <string>
#include <chrono>

class test {
public:
    static void generateRandomNumbers(int numNumbers, int minValue, int maxValue, const std::string& filename, int seed);
};


#endif //TABLICA_DYNAMICZNA_TEST_H
