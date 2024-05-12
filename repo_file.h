#ifndef REPO_FILE_H_
#define REPO_FILE_H_

#include "repo.h"

class FileRepo : public Repo {
private:
	string nume_fisier;
	void load_from_file();
	void save_to_file();

public:

	explicit FileRepo(const string& nume_fisier);

	[[maybe_unused]] void set_path(const string& nume_fisier) {
		this->nume_fisier = nume_fisier;
	}

	void empty_file();

	void add_repo(const Tentant& tentant) override {
		Repo::add_repo(tentant);
		save_to_file();
	}

	void update_repo(const Tentant& new_tentant) override {
		Repo::update_repo(new_tentant);
		save_to_file();
	}

	void delete_repo(int number, const string& name) override {
		Repo::delete_repo(number, name);
		save_to_file();
	}

	~FileRepo() override = default;
};

#endif