#ifndef REPO_H_
#define REPO_H_

#include "domain.h"
#include "exceptions.h"

#include <vector>
#include <string>
#include <iterator>
#include <algorithm>
#include <map>
#include <utility>
#include <random>
#include <iostream>

using std::vector;
using std::string;
using std::find_if;
using std::make_pair;

class RepoAbs {
public:
	virtual void add_repo(const Tentant& tentant) = 0;
	virtual void update_repo(const Tentant& new_tentant) = 0;
	virtual void delete_repo(int number, const string& name) = 0;
	virtual int find_repo(int number, const string& name) = 0;
	virtual Tentant& get_tentant(int number, const string& name) = 0;
	virtual vector<Tentant>& get_all() = 0;

	virtual ~RepoAbs() = default;
};

class RepoProb : public RepoAbs {
private:
	float probabilitate;
	map<int, Tentant> elements;
	void det_luck();
	vector<Tentant> tentants;

public: 
	RepoProb() = default;
	explicit RepoProb(float probabilitate);
	
	void add_repo(const Tentant& tentant) override;
	void update_repo(const Tentant& new_tentant) override;
	void delete_repo(int number, const string& name) override;
	int find_repo(int number, const string& name) override;
	Tentant& get_tentant(int number, const string& name) override;
	vector<Tentant>& get_all() override;

	~RepoProb() = default;
};

class Repo : public RepoAbs {
private:
	// our vector
	vector<Tentant> tentants;

public:
	Repo() = default;

	explicit Repo(const vector<Tentant>& tentants) :tentants{ tentants } {};

	/* add tenants to the object list
	* 
	* param: tenant
	* throw exception if there is already an object equal with tenant
	*/

	virtual void add_repo(const Tentant& tentant);

	virtual void update_repo(const Tentant& new_tentant);

	/*
	* delets a tenant from the object list
	* params: - number
	*		  - name
	* throw exception if the tenant cannot be found
	*/

	virtual void delete_repo(int number, const string& name);

	/* find a tenant in the object list
	* param: - number
	*		 - name
	* returns: i != - 1 if the tenant exists
	*		   i = -1 if the tenant doesn't exist
	*/

	virtual int find_repo(int number, const string& name);

	/*
	* returns the tenant if it exists
	* throws exception if it doesn't
	*/

	virtual Tentant& get_tentant(int number, const string& name);

	/*
	* returns all the tenants
	*/
	virtual vector<Tentant>& get_all();

	virtual ~Repo() = default;
};

#endif
