#include "tests.h"

using namespace std;

void Tests::test_all() {
	test_validator();
	test_constructor_getters();
	test_copy_constructor();
	test_setters();
	test_operators();
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
	test_get_DTO();
	test_notificare();
	test_add_notificare();
	test_find_notificare();
	test_generate_notificare();
	test_export_notificare();
	test_empty_notificare();
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
	tentant.set_name("Diana");
	assert(tentant.get_name() == "Diana");
}

void Tests::test_operators() {
	Tentant test1{ 1, "Andreea", 100, "bought" };
	assert(test1.operator==(test1));

	Tentant test2;
	test2.operator=(test1);
	assert(test2.get_number() == 1);
	assert(test2.get_name() == "Andreea");
	assert(test2.get_surface() == 100);
	assert(test2.get_type() == "bought");
}

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

void Tests::test_get_DTO() {
	DTO test{ "rented", 3 };
	assert(test.get_entity_type() == "rented");
	assert(test.get_count() == 3);
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
