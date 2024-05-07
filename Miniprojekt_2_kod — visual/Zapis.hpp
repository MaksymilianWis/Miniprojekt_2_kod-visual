#pragma once

#include <fstream>
#include <string>

class Zapis {
public:
    // Konstruktor przyjmuj¹cy nazwê pliku
    Zapis(const std::string& filename);

    // Metoda do zapisu danych do pliku CSV
    void shot(int iteration, unsigned duration, int size);

private:
    std::string filename; // Nazwa pliku
};