#include "Zapis.hpp"
#include <fstream>
#include <iostream>

Zapis::Zapis(const std::string& filename) : filename(filename) {}

void Zapis::shot(int iteration, unsigned duration, int size) {

    file.open(filename, std::ios::out | std::ios::app);
    if (file.is_open()) {
        file << iteration << ";" << duration << ";" << size << "\n";
        file.close();
    }
    else {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
    }
}