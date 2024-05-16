#include "tests.h"
#include <sstream>
#include <fstream>

using namespace std;

void Tests::test_all() {
	test_validator();
	test_constructor_getters();
	test_copy_constructor();
	test_setters();
	// test_operators();
	test_comparison_operators();
	test_add_repo();
	test_find_repo();
	test_update_repo();
	test_delete_repo();
	test_get_tentant();
	test_get_all();
	test_add_service();
	test_update_service();
	test_delete_service();
	test_find_service();
	test_sort();
	test_filter();
	test_to_string();
	test_DTO();
	test_copy_DTO();
	test_get_DTO();
	test_notificare();
	test_add_notificare();
	test_find_notificare();
	test_generate_notificare();
	test_export_notificare();
	test_empty_notificare();
	test_add_notificare_srv();
	test_get_all_notificari();
	test_generate_notificare_srv();
	test_export_notificare_srv();
	test_empty_notificare_srv();
	test_get_notificare_size();
	test_raport();
	test_split();
	test_file();
	test_empty_file();
	test_set_path();
	test_repo_prob();
	test_bad_luck();
	test_undo_add();
	test_get_tentant_prob();
	test_update_repo_prob();
	test_find_repo_prob();
	test_add_repo_prob();
	test_delete_repo_prob();
	test_undo_delete();
	test_undo_update();
}

void Tests::test_validator() {
	Validator validator;
	Tentant test(1, "Andreea", 100, "bought");
	Tentant invalid{};

	validator.validate_tentant(test);
	try {
		validator.validate_tentant(invalid);
	}
	catch (ValidatorException& mesaj) {
		assert(mesaj.get_mesaj() == "Invalid number! \nInvalid name! \nInvalid surface! \nInvalid type! \n");
	}
}

void Tests::test_constructor_getters() {
	Tentant test_tentant{ 1, "Andreea", 100, "bought" };
	assert(test_tentant.get_number() == 1);
	assert(test_tentant.get_name() == "Andreea");
	assert(test_tentant.get_surface() == 100);
	assert(test_tentant.get_type() == "bought");

	Tentant test_implicit{};
	assert(test_implicit.get_number() == 0);
	assert(test_implicit.get_name().empty());
	assert(test_implicit.get_surface() == 0);
	assert(test_implicit.get_type().empty());
}

void Tests::test_copy_constructor() {
	Tentant test_tentant{ 1, "Andreea", 100, "bought" };
	Tentant test_copy(test_tentant);
	assert(test_copy.get_number() == 1);
	assert(test_copy.get_name() == "Andreea");
	assert(test_copy.get_surface() == 100);
	assert(test_copy.get_type() == "bought");
}

void Tests::test_setters() {
	Tentant tentant{ 1, "Andreea", 100, "bought" };
	tentant.set_number(2);
	assert(tentant.get_number() == 2);
	tentant.set_name("Diana");
	assert(tentant.get_name() == "Diana");
	tentant.set_surface(55);
	assert(tentant.get_surface() == 55);
	tentant.set_type("rented");
	assert(tentant.get_type() == "rented");
}
/*
void Tests::test_operators() {
	Tentant test1{ 1, "Andreea", 100, "bought" };
	assert(test1.operator==(test1));

	Tentant test2;
	test2.operator=(test1);
	assert(test2.get_number() == 1);
	assert(test2.get_name() == "Andreea");
	assert(test2.get_surface() == 100);
	assert(test2.get_type() == "bought");

	Tentant test3{ 3, "Ana", 200, "rented" };
	assert(test1.operator!=(test3));

	// reading and printinf
	Tentant test4{};
	istringstream input("4, Mihaela, 55, bought");
	input >> test4;
	assert(test4.get_number() == 4);
	assert(test4.get_name() == "Mihaela");
	assert(test4.get_surface() == 55);
	assert(test4.get_type() == "bought");

	ostringstream output;
	output << test4;
	string outp = output.str();
	assert(outp == "4, Mihaela, 55, bought\n");

}
*/

void Tests::test_comparison_operators() {
	Tentant test1{ 1, "John", 100, "rented" };
	Tentant test2{ 2, "Alice", 80, "owned" };

	// Test cmp_number
	assert(cmp_number(test1, test2) == true);
	assert(cmp_number(test2, test1) == false);

	// Test cmp_name
	assert(cmp_name(test1, test2) == false);
	assert(cmp_name(test2, test1) == true);

	// Test cmp_surface
	assert(cmp_surface(test1, test2) == false);
	assert(cmp_surface(test2, test1) == true);

	// Test cmp_type
	assert(cmp_type(test1, test2) == false);
	assert(cmp_type(test2, test1) == true);

	// Test cmp_type_surface
	assert(cmp_type_surface(test1, test2) == false);
	assert(cmp_type_surface(test2, test1) == true);

	Tentant test3{ 3, "Bob", 80, "owned" };
	Tentant test4{ 4, "Chris", 80, "rented" };

	assert(cmp_type(test2, test3) == true);
	assert(cmp_type(test2, test4) == true);

	assert(cmp_type_surface(test2, test3) == false);
	assert(cmp_type_surface(test2, test4) == true);
}

void Tests::test_DTO() {
	DTO test{ "rented", 3 };
	assert(test.get_count() == 3);
}

void Tests::test_copy_DTO() {
	DTO test{ "rented", 3 };
	DTO test_copy(test);
	assert(test_copy.get_count() == 3);
}

void Tests::test_get_DTO() {
	DTO test{ "rented", 3 };
	assert(test.get_entity_type() == "rented");
	assert(test.get_count() == 3);
}

void Tests::test_split() {
	string test = "1,Ana,50,rented";
	vector<string> result = split(test, ',');
	assert(result[0] == "1");
	assert(result[1] == "Ana");
	assert(result[2] == "50");
	assert(result[3] == "rented");
}

void Tests::test_add_repo() {
	vector<Tentant> tests;
	Repo repo(tests);
	Tentant test{ 1, "Andreea", 100, "bought" };

	repo.add_repo(test);
	try {
		repo.add_repo(test);
	}
	catch (RepoException& mesaj) {
		assert(mesaj.get_mesaj() == "Tenant already exists!\n");
	}

	assert(test.operator == (repo.get_tentant(1, "Andreea")));
}

void Tests::test_find_repo() {
	vector<Tentant> tests;
	Repo repo(tests);
	Tentant test{ 1, "Andreea", 100, "bought" };
	repo.add_repo(test);
	assert(repo.find_repo(1, "Andreea") == 0);
	assert(repo.find_repo(2, "Maria") == -1);
}

void Tests::test_update_repo() {
	vector<Tentant> tests;
	Repo repo(tests);
	Tentant test{ 1, "Andreea", 100, "bought" };
	repo.add_repo(test);

	Tentant newTenant{ 1, "Andreea", 200, "rented" };
	repo.update_repo(newTenant);

	// Verificăm dacă actualizarea s-a făcut cu succes
	assert(repo.find_repo(1, "Andreea") != -1);

	// Verificăm dacă aruncă excepția corespunzătoare când încercăm să actualizăm un chiriaș inexistent
	try {
		Tentant nonExistingTenant{ 2, "Maria", 300, "rented" };
		repo.update_repo(nonExistingTenant);
	}
	catch (RepoException& mesaj) {
		assert(mesaj.get_mesaj() == "Tenant doesn't exist!\n");
	}
}


void Tests::test_delete_repo() {
	vector<Tentant> tests;
	Repo repo(tests);
	Tentant test{ 1, "Andreea", 100, "bought" };
	repo.add_repo(test);
	repo.delete_repo(1, "Andreea");
	try {
		repo.delete_repo(1, "Andreea");
	}
	catch (RepoException& mesaj) {
		assert(mesaj.get_mesaj() == "Tenant doesn't exist!\n");
	}
}


void Tests::test_get_tentant() {
	vector<Tentant> tests;
	Repo repo(tests);
	Tentant test{ 1, "Andreea", 100, "bought" };

	repo.add_repo(test);
	assert(test.operator == (repo.get_tentant(1, "Andreea")));
	try {
		repo.get_tentant(2, "Diana");
	}
	catch (RepoException& mesaj) {
		assert(mesaj.get_mesaj() == "Tenant doesn't exist!\n");
	}
}

void Tests::test_get_all() {
	vector<Tentant> tests;
	Repo repo(tests);
	Tentant tentant1(1, "Andreea", 100, "bought");
	Tentant tentant2(2, "Maria", 150, "rented");
	repo.add_repo(tentant1);
	repo.add_repo(tentant2);
	assert(repo.get_all().size() == 2);
}

void Tests::test_file() {
	Tentant test{ 1, "Andreea", 100, "bought" };
	Tentant test1{ 2, "Diana", 120, "rented" };

	FileRepo file("test_file.txt");
	file.add_repo(test);
	file.add_repo(test1);

	const vector<Tentant>& tentants = file.get_all();
	assert(file.get_all().size() == 2);

	file.empty_file();

}

void Tests::test_empty_file() {
	Tentant test{ 1, "Andreea", 100, "bought" };
	FileRepo file("test_file.txt");
	file.empty_file();
	file.add_repo(test);
	const vector<Tentant>& tentants = file.get_all();
	assert(tentants.size() == 1);

	file.empty_file();
	const vector<Tentant>& tentants1 = file.get_all();
	assert(tentants1.size() == 1);

	file.empty_file();

}

void Tests::test_set_path() {
	Tentant test{ 1, "Andreea", 100, "bought" };
	FileRepo file("test_file.txt");
	file.empty_file();

	file.add_repo(test);
	file.set_path("test_file1.txt");

	const vector<Tentant>& tentants = file.get_all();
	assert(tentants.size() == 1);

	file.empty_file();

	file.set_path("test_file.txt");
	file.empty_file();


}

/*
* Service
*/

void Tests::test_add_service() {
	vector<Tentant> tests;
	Repo repo(tests);
	Validator validator;
	Notificare notificare;
	Service service(repo, validator, notificare);
	service.add_service(1, "Andreea", 100, "bought");
	const vector<Tentant>& tentants = service.get_all();
	assert(tentants.size() == 1);

	try {
		service.add_service(1, "Andreea", 100, "bought");
	}
	catch (RepoException& mesaj) {
		assert(mesaj.get_mesaj() == "Tenant already exists!\n");
	}
}


void Tests::test_delete_service() {
	vector<Tentant> tests;
	Repo repo(tests);
	Validator validator;
	Notificare notificare;
	Service service(repo, validator, notificare);
	Tentant test{ 1, "Andreea", 100, "bought" };
	Tentant test1{ 2, "Diana", 120, "rented" };

	service.add_service(1, "Andreea", 100, "bought");

	const vector<Tentant>& tentants = service.get_all();

	assert(tentants.size() == 1);
	service.delete_service(1, "Andreea");
	assert(tentants.size() == 0);

	try {
		service.delete_service(1, "Andreea");
	}
	catch (RepoException& mesaj) {
		assert(mesaj.get_mesaj() == "Tenant doesn't exist!\n");
	}
}


void Tests::test_find_service() {
	vector<Tentant> tests;
	Repo repo(tests);
	Validator validator;
	Notificare notificare;
	Service service(repo, validator, notificare);
	Tentant test{ 1, "Andreea", 100, "bought" };

	service.add_service(1, "Andreea", 100, "bought");

	const vector<Tentant>& tentants = service.get_all();
	assert(tentants.size() == 1);

	assert(test.operator==(service.find_service(1, "Andreea")));
	try {
		service.find_service(2, "Diana");
	}
	catch (RepoException& mesaj) {
		assert(mesaj.get_mesaj() == "Tenant doesn't exist!\n");
	}

}

void Tests::test_update_service() {
	vector<Tentant> tests;
	Repo repo(tests);
	Validator validator;
	Notificare notificare;
	Service service(repo, validator, notificare);
	Tentant tentant1{ 1, "Andreea", 100, "bought" };
	Tentant tentant2{ 2, "Maria", 200, "rented" };

	service.add_service(1, "Andreea", 100, "bought");

	service.update_service(1, "Andreea", 200, "rented");
	assert(tentant1.operator==(service.find_service(1, "Andreea")));


	try {
		service.update_service(1, "Maria", 200, "rented");
	}
	catch (RepoException& mesaj) {
		assert(mesaj.get_mesaj() == "Tenant doesn't exist!\n");
	}
}

void Tests::test_sort() {
	vector<Tentant> tests;
	Repo repo(tests);
	Validator validator;
	Notificare notificare;
	Service service(repo, validator, notificare);

	Tentant tentant1(1, "Andreea", 100, "bought");
	Tentant tentant2(2, "Maria", 200, "rented");
	Tentant tentant3(3, "John", 150, "owned");

	service.add_service(1, "Andreea", 100, "bought");
	service.add_service(2, "Maria", 200, "rented");
	service.add_service(3, "John", 150, "owned");

	// Test sorting by surface
	vector<Tentant> sortedBySurface = service.sort_surface();
	assert(sortedBySurface.size() == 3);
	assert(sortedBySurface[0] == tentant1);
	assert(sortedBySurface[1] == tentant3);
	assert(sortedBySurface[2] == tentant2);

	// Test sorting by type then surface
	vector<Tentant> sortedByTypeSurface = service.sort_type_surface();
	assert(sortedByTypeSurface.size() == 3);
	// Add assertions for the correct order based on type and surface

	// Test sorting by name
	vector<Tentant> sortedByName = service.sort_name();
	assert(sortedByName.size() == 3);
	// Add assertions for the correct order based on name
}


void Tests::test_filter() {
	vector<Tentant> tests;
	Repo repo(tests);
	Validator validator;
	Notificare notificare;
	Service service(repo, validator, notificare);
	Tentant tentant1(1, "Andreea", 100, "bought");
	Tentant tentant2(2, "Maria", 200, "rented");
	service.add_service(1, "Andreea", 100, "bought");
	service.add_service(2, "Maria", 200, "rented");

	vector<Tentant> filteredSurface = service.filter_surface(100);
	assert(tentant1 == filteredSurface[0]);

	vector<Tentant> filteredByType = service.filter_type("bought");
	assert(tentant1 == filteredByType[0]);

	vector<Tentant> filter_by_number = service.filter_number(1);
	assert(tentant1 == filter_by_number[0]);
}

void Tests::test_to_string() {
	Tentant test_tenant(1, "John", 100, "rented");
	assert(test_tenant.to_string_print() == "\t\033[1;33mNumber: \033[0m1;   \033[1;33mName: \033[0mJohn;   "
		"\033[1;33mSurface: \033[0m100;   \033[1;33mType: \033[0mrented.");
}

void Tests::test_notificare() {
	vector<Tentant> tests;
	Repo repo(tests);
	Validator validator;
	Notificare notificare;
	Service service(repo, validator, notificare);
	Tentant tentant1{ 1, "Andreea", 100, "bought" };
	Tentant tentant2{ 2, "Maria", 200, "rented" };
	service.add_service(1, "Andreea", 100, "bought");
	service.add_service(2, "Maria", 200, "rented");
	notificare.add_notificare(tentant1);
	notificare.add_notificare(tentant2);

	const vector<Tentant>& tentants = notificare.get_notificare();
	assert(tentants.size() == 2);

	notificare.empty_notificare();
	assert(tentants.size() == 0);

	notificare.generate_notificare(1, service.get_all());
	assert(tentants.size() == 1);
}

void Tests::test_add_notificare() {
	vector<Tentant> tests;
	Repo repo(tests);
	Validator validator;
	Notificare notificare;
	Service service(repo, validator, notificare);
	Tentant tentant1{ 1, "Andreea", 100, "bought" };
	Tentant tentant2{ 2, "Maria", 200, "rented" };
	service.add_service(1, "Andreea", 100, "bought");
	service.add_service(2, "Maria", 200, "rented");
	notificare.add_notificare(tentant1);
	notificare.add_notificare(tentant2);
	const vector<Tentant>& tentants = notificare.get_notificare();
	assert(tentants.size() == 2);

	try {
		notificare.add_notificare(tentant1);
	}
	catch (NotificareException& mesaj) {
		assert(mesaj.get_mesaj() == "Tenant already exists!\n");
	}
}

void Tests::test_find_notificare() {
	vector<Tentant> tests;
	Repo repo(tests);
	Validator validator;
	Notificare notificare;
	Service service(repo, validator, notificare);
	Tentant tentant1{ 1, "Andreea", 100, "bought" };
	service.add_service(1, "Andreea", 100, "bought");
	notificare.add_notificare(tentant1);
	assert(notificare.find_notificare(1, "Andreea") == 0);
	assert(notificare.find_notificare(2, "Diana") == -1);
}

void Tests::test_generate_notificare() {
	vector<Tentant> tests;
	Repo repo(tests);
	Validator validator;
	Notificare notificare;
	Service service(repo, validator, notificare);
	Tentant tentant1{ 1, "Andreea", 100, "bought" };
	Tentant tentant2{ 2, "Maria", 200, "rented" };

	service.add_service(1, "Andreea", 100, "bought");
	service.add_service(2, "Maria", 200, "rented");

	notificare.generate_notificare(1, service.get_all());
	const vector<Tentant>& tentants = notificare.get_notificare();
	assert(tentants.size() == 1);

	try {
		notificare.generate_notificare(3, service.get_all());
	}
	catch (NotificareException& mesaj) {
		assert(mesaj.get_mesaj() == "Not enough tenants in memory!\n");
	}
}

void Tests::test_export_notificare() {
	vector<Tentant> tests;
	Repo repo(tests);
	Validator validator;
	Notificare notificare;
	Service service(repo, validator, notificare);
	Tentant tentant1{ 1, "Andreea", 100, "bought" };
	Tentant tentant2{ 2, "Maria", 200, "rented" };

	service.add_service(1, "Andreea", 100, "bought");
	service.add_service(2, "Maria", 200, "rented");

	notificare.generate_notificare(1, service.get_all());
	notificare.export_notificare("notificare1");

	notificare.export_notificare("notificare1.html");
}

void Tests::test_empty_notificare() {
	vector<Tentant> tests;
	Repo repo(tests);
	Validator validator;
	Notificare notificare;
	Service service(repo, validator, notificare);
	Tentant tentant1{ 1, "Andreea", 100, "bought" };
	Tentant tentant2{ 2, "Maria", 200, "rented" };

	service.add_service(1, "Andreea", 100, "bought");
	service.add_service(2, "Maria", 200, "rented");

	notificare.generate_notificare(1, service.get_all());
	notificare.empty_notificare();

	const vector<Tentant>& tentants = notificare.get_notificare();
	assert(tentants.size() == 0);
}

void Tests::test_get_all_notificari() {
	vector<Tentant> tests;
	Repo repo(tests);
	Validator validator;
	Notificare notificare;
	Service service(repo, validator, notificare);
	Tentant tentant1{ 1, "Andreea", 100, "bought" };
	Tentant tentant2{ 2, "Maria", 200, "rented" };

	service.add_service(1, "Andreea", 100, "bought");
	service.add_service(2, "Maria", 200, "rented");

	notificare.generate_notificare(1, service.get_all());
	const vector<Tentant>& tentants = service.get_all_notifications();
	assert(tentants.size() == 1);
}

void Tests::test_add_notificare_srv() {
	vector<Tentant> tests;
	Repo repo(tests);
	Validator validator;
	Notificare notificare;
	Service service(repo, validator, notificare);
	Tentant tentant1{ 1, "Andreea", 100, "bought" };
	Tentant tentant2{ 2, "Maria", 200, "rented" };

	service.add_service(1, "Andreea", 100, "bought");
	service.add_service(2, "Maria", 200, "rented");

	service.add_notificare_srv(1, "Andreea", {});

	const vector<Tentant>& tentants = notificare.get_notificare();

	assert(tentants.size() == 1);

	try {
		service.add_notificare_srv(2, "Diana", {});
	}
	catch (RepoException& mesaj) {
		assert(mesaj.get_mesaj() == "Tenant doesn't exist!\n");
	}

	auto filtru = service.filter_type("rented");
	service.add_notificare_srv(3, "Diana", filtru);
	assert(tentants.size() == 2);
}

void Tests::test_generate_notificare_srv() {
	vector<Tentant> tests;
	Repo repo(tests);
	Validator validator;
	Notificare notificare;
	Service service(repo, validator, notificare);
	Tentant tentant1{ 1, "Andreea", 100, "bought" };
	Tentant tentant2{ 2, "Maria", 200, "rented" };

	service.add_service(1, "Andreea", 100, "bought");
	service.add_service(2, "Maria", 200, "rented");

	service.generate_notificare_srv(1);
	const vector<Tentant>& tentants = notificare.get_notificare();
	assert(tentants.size() == 1);
}

void Tests::test_export_notificare_srv() {
	vector<Tentant> tests;
	Repo repo(tests);
	Validator validator;
	Notificare notificare;
	Service service(repo, validator, notificare);
	Tentant tentant1{ 1, "Andreea", 100, "bought" };
	Tentant tentant2{ 2, "Maria", 200, "rented" };

	service.add_service(1, "Andreea", 100, "bought");
	service.add_service(2, "Maria", 200, "rented");

	service.generate_notificare_srv(1);
	service.export_notificare_srv("notificare.txt");
}

void Tests::test_empty_notificare_srv() {
	vector<Tentant> tests;
	Repo repo(tests);
	Validator validator;
	Notificare notificare;
	Service service(repo, validator, notificare);
	Tentant tentant1{ 1, "Andreea", 100, "bought" };
	Tentant tentant2{ 2, "Maria", 200, "rented" };

	service.add_service(1, "Andreea", 100, "bought");
	service.add_service(2, "Maria", 200, "rented");

	service.generate_notificare_srv(1);
	service.empty_notificare_srv();

	const vector<Tentant>& tentants = notificare.get_notificare();
	assert(tentants.size() == 0);
}

void Tests::test_get_notificare_size() {
	vector<Tentant> tests;
	Repo repo(tests);
	Validator validator;
	Notificare notificare;
	Service service(repo, validator, notificare);
	Tentant tentant1{ 1, "Andreea", 100, "bought" };
	Tentant tentant2{ 2, "Maria", 200, "rented" };

	service.add_service(1, "Andreea", 100, "bought");
	service.add_service(2, "Maria", 200, "rented");

	service.generate_notificare_srv(1);
	assert(service.get_notificare_size() == 1);
}

void Tests::test_raport() {
	vector<Tentant> tests;
	Repo repo(tests);
	Validator validator;
	Notificare notificare;
	Service service(repo, validator, notificare);
	Tentant tentant1{ 1, "Andreea", 100, "bought" };
	Tentant tentant2{ 2, "Maria", 200, "rented" };

	service.add_service(1, "Andreea", 100, "bought");
	service.add_service(2, "Maria", 200, "rented");

	map<string, DTO> raport = service.raport();
	assert(raport["rented"].get_count() == 1);
	assert(raport["bought"].get_count() == 1);
}

/* 
* Repo Prob
*/

void Tests::test_repo_prob() {
	RepoProb repo(1);
	Tentant test{ 1, "Andreea", 100, "bought" };
	Tentant test1{ 2, "Maria", 200, "rented" };

	repo.add_repo(test);
	repo.add_repo(test1);

	const vector<Tentant>& tentants = repo.get_all();
	assert(tentants.size() == 2);

	repo.update_repo(test1);
	assert(tentants[1].get_surface() == 200);

	repo.delete_repo(1, "Andreea");
	const vector<Tentant>& tentants1 = repo.get_all();
	assert(tentants1.size() == 1);
}

void Tests::test_bad_luck() {
	RepoProb repo(0);
	Tentant test{ 1, "Andreea", 100, "bought" };

	try {
		repo.add_repo(test);
	}
	catch (BadLuckException& mesaj) {
		assert(mesaj.get_mesaj() == "No luck!\n");
	}

}

void Tests::test_add_repo_prob() {
	RepoProb repo(1);
	Tentant test{ 1, "Andreea", 100, "bought" };

	repo.add_repo(test);

	assert(repo.get_all().size() == 1);
}

void Tests::test_update_repo_prob() {
	vector<Tentant> teste;
	RepoProb repo(1);
	Tentant test{ 1, "Andreea", 100, "bought" };
	Tentant test1{ 2, "Diana", 150, "bought" };
	Tentant test2{ 3, "Ana", 160, "rented" };


	repo.add_repo(test);
	repo.update_repo(test1);

	assert(repo.find_repo(2, "Diana") == 0);

	const vector<Tentant> tentants = repo.get_all();
	assert(tentants.size() == 1);
}

void Tests::test_find_repo_prob() {
	RepoProb repo(1);
	Tentant test{ 1, "Andreea", 100, "bought" };
	repo.add_repo(test);
	assert(repo.find_repo(1, "Andreea") == 0);
	assert(repo.find_repo(2, "Diana") == -1);
}

void Tests::test_delete_repo_prob() {
	RepoProb repo(1);
	Tentant test{ 1, "Andreea", 100, "bought" };

	repo.add_repo(test);
	repo.delete_repo(1, "Andreea");

	assert(repo.get_all().size() == 0);
}

void Tests::test_get_tentant_prob() {
	RepoProb repo(1);
	Tentant test{ 1, "Andreea", 100, "bought" };

	repo.add_repo(test);
	assert(test.operator == (repo.get_tentant(1, "Andreea")));
	try {
		repo.get_tentant(2, "Diana");
	}
	catch (RepoException& mesaj) {
		assert(mesaj.get_mesaj() == "Tentant doesn't exist!\n");
	}
}

/*
* UNDO
*/

void Tests::test_undo_add() {
	FileRepo repo("test_service.txt");
	Validator validator;
	Notificare notificare;
	Service service(repo, validator, notificare);

	repo.empty_file();

	service.add_service(1, "Diana", 100, "rented");
	service.undo();
	const vector<Tentant>& tentants = service.get_all();

	try {
		service.undo();
	}
	catch (RepoException& mesaj) {
		assert(mesaj.get_mesaj() == "Nothing left to undo!\n");
	}

	repo.empty_file();
}

void Tests::test_undo_update() {
	FileRepo repo("test_service.txt");
	Validator validator;
	Notificare notificare;
	Service service(repo, validator, notificare);

	repo.empty_file();

	service.add_service(1, "Diana", 100, "rented");
	service.update_service(1, "Diana", 200, "bought");
	service.undo();
	const vector<Tentant>& tentants = service.get_all();
	assert(tentants.size() == 1);

	Tentant updated = service.find_service(1, "Diana");
	assert(updated.get_surface() == 100);
	assert(updated.get_type() == "rented");

	repo.empty_file();
}

void Tests::test_undo_delete() {
	FileRepo repo("test_service.txt");
	Validator validator;
	Notificare notificare;
	Service service(repo, validator, notificare);

	repo.empty_file();

	service.add_service(1, "Diana", 100, "rented");
	service.delete_service(1, "Diana");

	const vector<Tentant>& tentants = service.get_all();

	assert(tentants.size() == 0);

	service.undo();
	const vector<Tentant>& tentants1 = service.get_all();
	assert(tentants1.size() == 1);

	repo.empty_file();
}

