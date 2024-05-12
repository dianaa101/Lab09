#ifndef SERVICE_H_
#define SERVICE_H_

#include "validator.h" 
#include "notificare.h"
#include "undo.h"
#include "repo_file.h"

#include <string>
#include <vector>
#include <functional>
#include <map>
#include <random>
#include <algorithm>
#include <memory>


using std::string;
using std::vector;
using std::function;
using std::map;
using std::copy_if;
using std::shuffle;
using std::unique_ptr;


class Service {
    RepoAbs& repo;
    Validator& validator;
    Notificare& notificare;
    std::vector < unique_ptr<UndoActiuni>> undo_actiuni;


public:

    void undo(); 

    const vector<Tentant>& get_all_notifications() noexcept;

    int get_notificare_size();

    void add_notificare_srv(int number, const string& name, const vector<Tentant>& filtered);

    void generate_notificare_srv(int nr_tentants);

    void export_notificare_srv(const string& nume);

    void empty_notificare_srv();

    map<string, DTO> raport() noexcept;

    Service(RepoAbs& repo, Validator& validator, Notificare& notificare) noexcept : repo{ repo }, validator{ validator }, notificare{ notificare } {
    }

    //nu putem lasa sa se faca copie
    Service(const Service& copy) = delete;

    /*
    * Add a tenant
    * Throws exception if it already exists or if validation fails
    */
    void add_service(int number, const string& name, int surface, const string& type);
    void update_service(int number, const string& name, int surface, const string& type);
    
    /*
    * Deletes a tenant
    * Throws exception if the tenant doesn't exist
    */
    void delete_service(int number, const string& name);

    /*
    * Finds a tenant by a number and name
    * Throws exception if tenant doesn't exist
    */
    const Tentant& find_service(int number, const string& name);
    const vector<Tentant>& get_all() noexcept;

    /*
    * Filters by surface
    */
    vector<Tentant> filter_surface(int number);
    /*
    * Filters the type
    */
    vector<Tentant> filter_type(const string& name);
    vector<Tentant> filter_number(int number);

    vector<Tentant> sort_type_surface();

    vector<Tentant> sort_name();



    /*
    * Sorts by surface
    */
    vector<Tentant> sort_surface();
};

#endif // SERVICE_H