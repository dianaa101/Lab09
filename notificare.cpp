#include "notificare.h"
#include "exceptions.h"

void Notificare::add_notificare(const Tentant& tentant) {
	int number = tentant.get_number();
	const string& name = tentant.get_name();

	if (find_notificare(number, name) != -1) {
		throw NotificareException("Tenant already exists!\n");
	}
	else {
		this->notificare.push_back(tentant);
	}
}

int Notificare::find_notificare(int number, const string& name) {
	auto iterator = find_if(this->notificare.begin(),
		this->notificare.end(), [number, name](const Tentant& tentant) noexcept {
			if (tentant.get_number() == number && tentant.get_name() == name)
				return true;
			return false;
		});
	auto const poz = std::distance(this->notificare.begin(), iterator);

	if (iterator != this->notificare.end()) {
		return poz;
	}

	return -1;
}

void Notificare::empty_notificare() noexcept {
	this->notificare.clear();
}

void Notificare::generate_notificare(int nr_tentants, const vector<Tentant>& memory) {
	if (nr_tentants > memory.size()) {
		throw NotificareException("Not enough tenants in memory!\n");
	}
	empty_notificare();
	auto to_notificare = memory;
	shuffle(to_notificare.begin(), to_notificare.end(), std::default_random_engine(time(0)));

	while (nr_tentants && !to_notificare.empty()) {
		add_notificare(to_notificare.back());
		to_notificare.pop_back();
		nr_tentants--;
	}
}

const vector<Tentant>& Notificare::get_notificare() {
	return this->notificare;
}

void Notificare::export_notificare(const string& nume_fisier) {
	string filename = nume_fisier;
	auto poz = filename.find_first_of(".");

	if (poz < filename.size()) {
		auto file_extension = nume_fisier.substr(poz);
		if (file_extension != ".html") {
			filename = filename + ".html";
		}

	}
	else {
		filename += ".html";
	}

	std::ofstream fout(filename);
	fout << "<html>\n"
		"<body>\n"
		"<head>\n"
		"	<h3 style=\" font-family: 'Cascadia Mono',serif; color: #81A40D; \">Lista de notificari</h3>\n"
		"	</head>\n"
		"<style>\n"
		"	p {\n"
		"		color: #D7BDE2 ;\n"
		"		background-color: #A9CCE3 ;\n"
		"		border: 1px solid black; }\n"
		"	table,th,td{\n"
		"		border: 1px solid black;\n"
		"       font-size: 20px;\n" // Set the font size to 20px
		"	}\n"
		"	th{\n"
		"		color: RosyBrown;\n"
		"	}\n"
		"	body{\n"
		"		background-color: #FFEFD5 ;\n"
		"   }\n"
		"</style>\n";

	fout << "<table>\n"
		"\n"
		"		<th>Number</th>\n"
		"		<th>Name</th>\n"
		"       <th>Surface</th>\n"
		"		<th>Type</th>\n";

	for (const Tentant& tentant : get_notificare()) {
		fout << "<tr>\n";
		fout << "<th>" << tentant.get_number() << "</th>\n"
			<< "<th>" << tentant.get_name() << "</th>\n"
			<< "<th>" << tentant.get_surface() << "</th>\n"
			<< "<th>" << tentant.get_type() << "</th>\n"
			<< "</tr>\n";
	}

	fout << "</table>\n"
		"\n"
		"\n"
		"</body>\n"
		"</html>";

}