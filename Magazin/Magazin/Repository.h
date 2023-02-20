#pragma once
#include "Produs.h"
#include "V3.h"
#include <vector>
using std::vector;

class RepoException {
private:
	string errors;
public:
	RepoException(string errors) :errors{ errors } {};
	string getErrors() {
		return this->errors;
	}
};

class ProduseRepo {
private:
	//vector<Produs> lista_produse;

	VectorDinamic<Produs> lista_produse;
public:
	ProduseRepo() = default;

	ProduseRepo(const ProduseRepo& o) = delete;

	void store(const Produs& p);

	void remove(const Produs& p);

	void modific(const Produs& p, const Produs& p_nou);

	VectorDinamic<Produs>& getProduse() noexcept ;

	const Produs& find(string nume, string tip);

	bool exista(const Produs& p);
};

void testeRepo();