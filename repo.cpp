#include "repo.h"
#include <iostream>

int Repo::find_repo(int number, const string& name) {
	auto iterator = find_if(this->tentants.begin(),
		this->tentants.end(), [number, name](const Tentant& tentant) noexcept {
			if (tentant.get_number() == number && tentant.get_name() == name)
				return true;
			return false;
		});
	auto const poz = std::distance(this->tentants.begin(), iterator);

	if (iterator != this->tentants.end()) {
		return poz;
	}

	return -1;
}



void Repo::add_repo(const Tentant& tentant) {
	int number = tentant.get_number();
	const string& name = tentant.get_name();

	if (find_repo(number, name) == -1) {
		this->tentants.push_back(tentant);
	}
	else {
		throw RepoException("Tenant already exists!\n");
	}
}

void Repo::update_repo(const Tentant& new_tentant) {

	int number = new_tentant.get_number();
	const string& name = new_tentant.get_name();
	int index = find_repo(number, name);

	if (index != -1) {
		this->tentants[index] = new_tentant;
	}
	else {
		throw RepoException("Tenant doesn't exist!\n");
	}
}

void Repo::delete_repo(int number, const string& name) {
	int index = find_repo(number, name);
	if (index != -1) {
		auto prim = this->tentants.begin();
		this->tentants.erase(prim + index);
	}
	else {
		throw RepoException("Tenant doesn't exist!\n");
	}

}

const Tentant& Repo::get_tentant(int number, const string& name) {
	int index = find_repo(number, name);

	if (index != -1) {
		return this->tentants[index];
	}
	else {
		throw RepoException("Tenant doesn't exist!\n");
	}
}

const vector<Tentant>& Repo::get_all() const noexcept {
	return this->tentants;
}