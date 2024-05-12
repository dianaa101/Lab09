#include "repo.h"
#include <iostream>

RepoProb::RepoProb(float probabilitate) {
	this->probabilitate = probabilitate;
	elements.clear();
}

void RepoProb::add_repo(const Tentant& tentant) {
	det_luck();
	elements.insert(make_pair(elements.size(), tentant));
}

void RepoProb::update_repo(const Tentant& new_tentant) {
	det_luck(); 
	for (auto it = elements.begin(); it != elements.end(); ++it) {
		if (it->second.get_number() == new_tentant.get_number() && it->second.get_name() == new_tentant.get_name()) {
			it->second = new_tentant;
			return;
		}
	}
}

void RepoProb::delete_repo(int number, const string& name) {
	det_luck();
	for (auto it = elements.begin(); it != elements.end(); ++it) {
		if (it->second.get_number() == number && it->second.get_name() == name) {
			elements.erase(it);
			return;
		}
	}
}

Tentant& RepoProb::get_tentant(int number, const string& name) {
	det_luck();
	for (auto it = elements.begin(); it != elements.end(); ++it) {
		if (it->second.get_number() == number && it->second.get_name() == name) {
			return it->second;
		}
	}
	throw RepoException("Tenant doesn't exist!\n");
}

vector<Tentant>& RepoProb::get_all() {
	det_luck();
	tentants.clear();
	for (auto it = elements.begin(); it != elements.end(); ++it) {
		tentants.push_back(it->second);
	}
	return tentants;
}

void RepoProb::det_luck() {
	auto prb = int(probabilitate * 10);
	int nr = rand() % 10;
	if (nr <= prb) {
		return;
	}
	throw BadLuckException("No luck!\n");
}

int RepoProb::find_repo(int number, const string& name) {
	det_luck();
	for (auto it = elements.begin(); it != elements.end(); ++it) {
		if (it->second.get_number() == number && it->second.get_name() == name) {
			return it->first;
		}
	}
	return -1;
}


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

Tentant& Repo::get_tentant(int number, const string& name) {
	const int index = find_repo(number, name);

	if (index != -1) {
		return this->tentants[index];
	}
	else {
		throw RepoException("Tenant doesn't exist!\n");
	}
}

vector<Tentant>& Repo::get_all() {
	return this->tentants;
}