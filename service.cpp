#include "service.h"

void Service::undo() {
	if (undo_actiuni.empty()) {
		throw RepoException("Nothing left to undo!\n");
	}
	undo_actiuni.back()->do_undo();
	undo_actiuni.pop_back();
}

const vector<Tentant>& Service::get_all_notifications() noexcept {
	return notificare.get_notificare();
}

void Service::generate_notificare_srv(int nr_tentants) {
	notificare.generate_notificare(nr_tentants, repo.get_all());
}

void Service::export_notificare_srv(const string& nume) {
	notificare.export_notificare(nume);
}

void Service::empty_notificare_srv() {
	notificare.empty_notificare();
}

void Service::add_notificare_srv(int number, const string& name, const vector<Tentant>& filtered) {
	auto gasit = repo.find_repo(number, name);
	if (gasit >= 0) {
		auto tentant = repo.get_tentant(number, name);
		notificare.add_notificare(tentant);
	}

	else if (gasit == -1) {
		auto to_add = filtered;
		std::shuffle(to_add.begin(), to_add.end(), std::default_random_engine(time(0)));
		if (filtered.size() >= 1) {
			notificare.add_notificare(to_add.back());
		}
		else {
			throw RepoException("Tenant doesn't exist!\n");
		}
	}

}


int Service::get_notificare_size() {
	return notificare.get_notificare().size();
}

map<string, DTO> Service::raport() noexcept {
	map<string, DTO> raport;
	auto tentants = repo.get_all();

	for (const auto& tentant : tentants) {
		DTO type(tentant.get_type());
		raport[tentant.get_type()] = type;
	}

	for (const auto& tentant : tentants) {
		int nr = raport[tentant.get_type()].get_count() + 1;
		DTO val(tentant.get_type(), nr);
		raport[tentant.get_type()] = val;
	}
	return raport;
}



void Service::add_service(int number, const string& name, int surface, const string& type) {
	Tentant tentant{ number, name, surface, type };

	validator.validate_tentant(tentant);
	repo.add_repo(tentant);
	undo_actiuni.push_back(std::make_unique<UndoAdd>(repo, tentant));

}


 void Service::update_service(int number, const string& name, int surface, const string& type) {
	Tentant tentant{ number, name, surface, type };
	Tentant previous_tentant = repo.get_tentant(number, name);

	validator.validate_tentant(tentant);
	repo.update_repo(tentant);
	undo_actiuni.push_back(std::make_unique<UndoUpdate>(repo, previous_tentant));

 }

void Service::delete_service(int number, const string& name) {
	Tentant copie = repo.get_tentant(number, name);
	repo.delete_repo(number, name);
	undo_actiuni.push_back(std::make_unique<UndoDelete>(repo, copie));
}

const Tentant& Service::find_service(int number, const string& name) {
	return repo.get_tentant(number, name);
}

const vector<Tentant>& Service::get_all() noexcept {
	return this->repo.get_all();
}

vector<Tentant> Service::filter_surface(int surface) {
	vector <Tentant> filtered;

	const auto all_tentants = repo.get_all();
	copy_if(repo.get_all().begin(), repo.get_all().end(), std::back_inserter(filtered),
		[surface](const Tentant& tentant) noexcept {
			return tentant.get_surface() == surface;
		});
	return filtered;
}

vector<Tentant> Service::filter_type(const string& type) {
	vector <Tentant> filtered;

	const auto all_tentants = repo.get_all();
	copy_if(repo.get_all().begin(), repo.get_all().end(), std::back_inserter(filtered),
		[type](const Tentant& tentant) noexcept {
			return tentant.get_type() == type;
		});
	return filtered;
}

vector<Tentant> Service::filter_number(int number) {
	vector <Tentant> filtered;

	const auto all_tentants = repo.get_all();
	copy_if(repo.get_all().begin(), repo.get_all().end(), std::back_inserter(filtered),
		[number](const Tentant& tentant) noexcept {
			return tentant.get_number() == number;
		});
	return filtered;
}

vector<Tentant> Service::sort_type_surface() {
	auto sorted = repo.get_all();
	std::sort(sorted.begin(), sorted.end(), cmp_type_surface);
	return sorted;
}

vector<Tentant> Service::sort_surface() {
	auto sorted = repo.get_all();
	std::sort(sorted.begin(), sorted.end(), cmp_surface);
	return sorted;
}

vector<Tentant> Service::sort_name() {
	auto sorted = repo.get_all();
	std::sort(sorted.begin(), sorted.end(), cmp_name);
	return sorted;
}