#include "repo_file.h"
#include <fstream>

FileRepo::FileRepo(const string& nume_fisier) {
	this->nume_fisier = nume_fisier;
	load_from_file();
}

void FileRepo::load_from_file() {
	std::ifstream fin(this->nume_fisier);
	Tentant tentant{};
	Tentant previous_tentant{};

	while (fin >> tentant) {
		if (tentant != previous_tentant) {
			add_repo(tentant);
		}
		previous_tentant = tentant;
	}
}

void FileRepo::save_to_file() {
	std::ofstream fout(this->nume_fisier);

	for (const auto& tentant : this->get_all()) {
		fout << tentant;
	}

	fout.close();
}

void FileRepo::empty_file() {
	std::ofstream fout(this->nume_fisier);
	fout << "";
	fout.close();
}