#pragma once

#include <fstream>
#include <string>

class Zapis {
private:
	std::ofstream file_;
	std::string nazwa_pliku_;
public:
	Zapis(std::string nazwa_pliku);//otwieranie pliku preferowany tym .csv

	std::string shot(unsigned iteration, unsigned time, unsigned how_many_time);
};