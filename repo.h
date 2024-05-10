#ifndef REPO_H_
#define REPO_H_

#include "domain.h"
#include "exceptions.h"

#include <vector>
#include <string>
#include <iterator>

using std::vector;
using std::string;
using std::find_if;

class Repo {
private:
	// our vector
	vector<Tentant> tentants;

public:
	explicit Repo(const vector<Tentant>& tentants) :tentants{ tentants } {};

	/* add tenants to the object list
	* 
	* param: tenant
	* throw exception if there is already an object equal with tenant
	*/

	void add_repo(const Tentant& tentant);

	void update_repo(const Tentant& new_tentant);

	/*
	* delets a tenant from the object list
	* params: - number
	*		  - name
	* throw exception if the tenant cannot be found
	*/

	void delete_repo(int number, const string& name);

	/* find a tenant in the object list
	* param: - number
	*		 - name
	* returns: i != - 1 if the tenant exists
	*		   i = -1 if the tenant doesn't exist
	*/

	int find_repo(int number, const string& name);

	/*
	* returns the tenant if it exists
	* throws exception if it doesn't
	*/

	const Tentant& get_tentant(int number, const string& name);

	/*
	* returns all the tenants
	*/
	[[nodiscard]] const vector<Tentant>& get_all() const noexcept;

};

#endif
