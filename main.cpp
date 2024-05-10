#include "domain.h"
#include "repo.h"
#include "service.h"
#include "ui.h"
// #include "tests.h"

#define _CRTDBG_MAP_ALLOC

#include <iostream>
#include <crtdbg.h>
using namespace std;

void create() {
	// Tests tests;
	// tests.test_all();

	vector<Tentant> vector;
	Repo repo(vector);
	Validator validator;
	Notificare notificare;
	Service controller(repo, validator, notificare);
	Ui ui{ controller };

	ui.run();
}

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	create();
	_CrtDumpMemoryLeaks();
}