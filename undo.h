#ifndef UNDO_H_
#define UNDO_H_

#include "domain.h"
#include "repo.h"

class UndoActiuni {
public:
	virtual void do_undo() = 0;
	virtual ~UndoActiuni() = default;
};

class UndoAdd : public UndoActiuni {
	const Tentant& added_tentant;
	RepoAbs& repo;

public:
	UndoAdd(RepoAbs& repo, const Tentant& tentant) : repo{ repo }, added_tentant{ tentant } {
	}

	void do_undo() override {
		this->repo.delete_repo(added_tentant.get_number(), added_tentant.get_name());
	}
};

class UndoDelete : public UndoActiuni {
	const Tentant& deleted_tentant;
	RepoAbs& repo;
public:
	UndoDelete(RepoAbs& repo, const Tentant& tentant) : repo{ repo }, deleted_tentant{ tentant } {
	}
	void do_undo() override {
		this->repo.add_repo(deleted_tentant);
	}
};

class UndoUpdate : public UndoActiuni {
	const Tentant& updated_tentant;
	RepoAbs& repo;
public:
	UndoUpdate(RepoAbs& repo, const Tentant& tentant) : repo{ repo }, updated_tentant{ tentant } {
	}
	void do_undo() override {
		this->repo.update_repo(updated_tentant);
	}
};

#endif