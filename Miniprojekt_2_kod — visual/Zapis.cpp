#include "Zapis.hpp"
#include <fstream>
#include <iostream>

Zapis::Zapis(const std::string& filename) : filename(filename) {}

void Zapis::shot(int iteration, unsigned duration, int size) {
    std::ofstream file(filename, std::ios::app);
    if (file.is_open()) {
        file << iteration << "," << duration << "," << size << std::endl;
        file.close();
    }
    else {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
    }
}