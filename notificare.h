#ifndef NOTIFICARE_H_
#define NOTIFICARE_H_

#include "domain.h"

#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include <fstream>

using std::vector;
using std::string;
using std::shuffle;

class Notificare {

private:
	vector<Tentant> notificare;

public:
	void add_notificare(const Tentant& tentant);

	int find_notificare(int number, const string& name);

	void empty_notificare() noexcept;

	const vector<Tentant>& get_notificare();

	void export_notificare(const string& nume_fisier);

	void generate_notificare(int nr_tentants, const vector<Tentant>& memory);
};

#endif