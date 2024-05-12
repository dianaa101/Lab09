#include "domain.h"

#include <iostream>
#include <sstream>
using namespace std;

Tentant::Tentant() {
	this->number = 0;
	this->name = "";
	this->surface = 0;
	this->type = "";
}

// constructor
Tentant::Tentant(int number, const string& name, int surface, const string& type) {
	this->number = number;
	this->name = name;
	this->surface = surface;
	this->type = type;
}

// destructor
Tentant::~Tentant() = default;

// copie constructor
Tentant::Tentant(const Tentant& tentant) {
	this->number = tentant.number;
	this->name = tentant.name;
	this->surface = tentant.surface;
	this->type = tentant.type;
}

// getters

int Tentant::get_number() const noexcept {
	return this->number;
}

const string& Tentant::get_name() const noexcept {
	return this->name;
}

int Tentant::get_surface() const noexcept {
	return this->surface;
}

const string& Tentant::get_type() const noexcept {
	return this->type;
}

// setters


[[maybe_unused]] void Tentant::set_name(const string& new_name) {
	this->name = new_name;
}

[[maybe_unused]] void Tentant::set_number(int new_number) {
	this->number = new_number;
}

[[maybe_unused]] void Tentant::set_surface(int new_surface) {
	this->surface = new_surface;
}

[[maybe_unused]] void Tentant::set_type(const string& new_type) {
	this->type = new_type;
}

/// TO STRING PRINTARE
string Tentant::to_string_print() {
	return "\t\033[1;33mNumber: \033[0m" + to_string(this->number) + ";   \033[1;33mName: \033[0m" + this->name +
		";   \033[1;33mSurface: \033[0m" + to_string(this->surface) + ";   \033[1;33mType: \033[0m" + this->type + ".";
}

// operators
Tentant& Tentant::operator=(const Tentant& copy) = default;

bool Tentant::operator==(const Tentant& copy) noexcept {
	return this->number == copy.number && this->name == copy.name;
}

bool Tentant::operator!=(const Tentant& copy) noexcept {
	return !operator==(copy);
}


// comparing functions
bool cmp_number(const Tentant& t1, const Tentant& t2) {
	if (t1.get_number() < t2.get_number()) {
		return true;
	}
	return false;
}

bool cmp_name(const Tentant& t1, const Tentant& t2) {
	if (t1.get_name() < t2.get_name()) {
		return true;
	}
	return false;
}

bool cmp_surface(const Tentant& t1, const Tentant& t2) {
	if (t1.get_surface() < t2.get_surface()) {
		return true;
	}
	return false;
}

bool cmp_type(const Tentant& t1, const Tentant& t2) {
	if (t1.get_type() != t2.get_type()) {
		return t1.get_type() < t2.get_type();
	}
	return t1.get_number() < t2.get_number(); // To ensure a stable sort
}

bool cmp_type_surface(const Tentant& t1, const Tentant& t2) {
	if (t1.get_type() != t2.get_type()) {
		return t1.get_type() < t2.get_type();
	}
	else {
		return t1.get_surface() < t2.get_surface();
	}
}

vector<string> split(const string& input, char delimiter) {
	vector<string> result;
	stringstream stream(input);
	string item;
	while (std::getline(stream, item, delimiter)) {
		result.push_back(item);
	}
	return result;
}

std::istream& operator>>(std::istream& input, Tentant& tentant) {
	string linie;
	std::getline(input, linie);
	vector<string> tokens = split(linie, ',');

	if (tokens.size() != 4) {
		return input;
	}

	tentant.set_number(std::stoi(tokens[1]));
	tentant.set_name(tokens[0]);
	tentant.set_surface(std::stoi(tokens[1]));
	tentant.set_type(tokens[2]);

	return input;
}

std::ostream& operator<<(std::ostream& output, const Tentant& tentant) {
	output << tentant.get_number() << "," << tentant.get_name() << "," << tentant.get_surface() << "," << tentant.get_type() << "\n";
	return output;
}