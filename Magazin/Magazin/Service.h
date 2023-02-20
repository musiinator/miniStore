#pragma once
#include "Repository.h"
#include "V3.h"
#include "validators.h"
#include <functional>
using std::function;

class Magazin {
private:
	ProduseRepo& repo;
	ProdusVal& val;

	VectorDinamic<Produs> filter(function<bool(const Produs&)> fct);
	
	VectorDinamic<Produs> generalSort(bool(*maiMicF)(const Produs&, const Produs&));

public:
	Magazin(ProduseRepo& produseR, ProdusVal& val) noexcept :repo{ produseR }, val{ val } {};
    
	Magazin(const Magazin& o) = delete;

	void adaugaProdus(string nume, string tip, string producator, double pret);

	void stergeProdus(string nume, string tip, string producator, double pret);

	const Produs& cautaProdus(string nume, string tip);

	void modificaProdus(string nume, string tip, string producator, double pret, string nume_nou, string tip_nou, string producator_nou, double pret_nou);

	VectorDinamic<Produs>& getproduse() noexcept ;

	VectorDinamic<Produs> filtrareTip(string tip);

	VectorDinamic<Produs> filtrarePret(double pretStart, double pretEnd);

	VectorDinamic<Produs> sortByPret();

	VectorDinamic<Produs> sortByProdNume();
};

void testeService();