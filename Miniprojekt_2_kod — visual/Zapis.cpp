#include "Zapis.hpp"

#include <string>
#include <fstream>
#include <iostream>


Zapis::Zapis(std::string nazwa_pliku) : nazwa_pliku_(nazwa_pliku) {
	file_.open(nazwa_pliku_);
	file_ << "pozycja;ilosc;czas ca³kowity(ms);czas/ilosc(ms)\n";
	file_.close();
};

std::string Zapis::shot(unsigned iteration, unsigned time, unsigned how_many_time) {
	//otwieranie w trybie nadpisywania (filepointer tak¿e ustawia sie na koniec pliku)
	file_.open(nazwa_pliku_, std::ios::app);
	double dtime = static_cast<double>(time);
	double dhow_many_time = static_cast<double>(how_many_time);

	if (file_.good() == false) {
		std::cout << "ERROR nie mozna otworzyc pliku " << nazwa_pliku_ << std::endl;
		return "";
	}

	file_ << iteration << ";" << how_many_time << ";" << time << ";" << dtime/dhow_many_time << "\n";

	file_.close();
	return "lp,ilosc,czas ca³kowity,czas/zapis\n" +
		std::to_string(iteration) + ";" + std::to_string(how_many_time) + ";" + std::to_string(time) + ";" + std::to_string(dtime / dhow_many_time) + "\n";;
}