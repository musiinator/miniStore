#include "Service.h"
#include <assert.h>
#include <functional>
#include <algorithm>
using std::sort;

void Magazin::adaugaProdus(string nume, string tip, string producator, double pret) {
	Produs p{ nume, tip, producator, pret };
	val.valid(p);
	repo.store(p);
}

void Magazin::stergeProdus(string nume, string tip, string producator, double pret) {
	Produs p{ nume, tip, producator, pret };
	val.valid(p);
	repo.remove(p);
}

const Produs& Magazin::cautaProdus(string nume, string tip) {
	return repo.find(nume, tip);
}

void Magazin::modificaProdus(string nume, string tip, string producator, double pret, string nume_nou, string tip_nou, string producator_nou, double pret_nou) {
	Produs p{ nume, tip, producator, pret };
	Produs p_nou(nume_nou, tip_nou, producator_nou, pret_nou);
	val.valid(p);
	val.valid(p_nou);
	repo.modific(p, p_nou);
}

VectorDinamic<Produs> Magazin::filter(function<bool(const Produs&)> fct) {
	VectorDinamic<Produs> filtered;
	//for (const auto& song : repo.getProduse()) {
	for (int i = 0; i < repo.getProduse().size(); i++){
		if (fct(repo.getProduse().get(i))) {
			string nume, tip, producator;
			double pret;
			nume = repo.getProduse().get(i).getNume();
			tip = repo.getProduse().get(i).getTip();
			producator = repo.getProduse().get(i).getProducator();
			pret = repo.getProduse().get(i).getPret();
			Produs p = { nume,tip,producator,pret };
			filtered.adauga(p);
		}
	}
	return filtered;
}

VectorDinamic<Produs> Magazin::filtrareTip(string tip) {
	return filter([tip](const Produs& m) {
		return m.getTip() == tip;
		});
}

VectorDinamic<Produs> Magazin::filtrarePret(double pretStart, double pretEnd) {
	return filter([=](const Produs& m) {
		return m.getPret() >= pretStart && m.getPret() <= pretEnd;
		});
}


VectorDinamic<Produs> Magazin::generalSort(bool(*maiMicF)(const Produs&, const Produs&)) {
	VectorDinamic<Produs> v{ repo.getProduse() };
	for (size_t i = 0; i < v.size(); i++) {
		for (size_t j = i + 1; j < v.size(); j++) {
			if (!maiMicF(v.get(i), v.get(j))) {
				//interschimbam
				Produs aux = v.get(i);
				v.set(v.get(j), i);
				v.set(aux, j);
			}
		}
	}
	return v;
}



VectorDinamic<Produs> Magazin::sortByPret() {
	return generalSort(cmpPret);
}

VectorDinamic<Produs> Magazin::sortByProdNume() {
	return generalSort(cmpProdNume);
}


VectorDinamic<Produs>& Magazin::getproduse() noexcept {
	return this->repo.getProduse();
}

void testadaugaProdus() {
	ProduseRepo testr;
	ProdusVal vl;
	Magazin tests{ testr, vl };

	tests.adaugaProdus("nume1", "tip1", "prod1", 1.99);
	tests.adaugaProdus("nume2", "tip2", "prod2", 5.99);
	tests.adaugaProdus("nume3", "tip3", "prod3", 9.99);

	assert(tests.getproduse().size() == 3);

	try {
		tests.adaugaProdus("Pictures of Home", "Deep Purple", "rock", 1.22);
		assert(true);
	}
	catch (Validation&) {
		assert(false);
	}

	try {
		tests.adaugaProdus("", "Deep Purple", "rock", 2.24);
		assert(false);
	}
	catch (Validation& ve) {
		assert(ve.getErrors() == "Numele trebuie sa aiba cel putin 2 litere!\n");
	}


	try {
		tests.adaugaProdus("Smoke on the Water", "", "rock", 2.24);
		assert(false);
	}
	catch (Validation&) {
		assert(true);
	}


	try {
		tests.adaugaProdus("High Hopes", "Pink Floyd", "rock", 12000);
		assert(false);
	}
	catch (Validation&) {
		assert(true);
	}

	try {
		tests.adaugaProdus("Child in Time", "Deep Purple", "", 16);
		assert(false);
	}
	catch (Validation&) {
		assert(true);
	}
}

void teststergeProdus() {
	ProduseRepo testr;
	ProdusVal vl;
	Magazin tests{ testr, vl };

	tests.adaugaProdus("nume1", "tip1", "prod1", 1.99);
	tests.adaugaProdus("nume2", "tip2", "prod2", 5.99);
	tests.adaugaProdus("nume3", "tip3", "prod3", 9.99);

	assert(tests.getproduse().size() == 3);

	tests.stergeProdus("nume1", "tip1", "prod1", 1.99);

	assert(tests.getproduse().size() == 2);

	assert(tests.getproduse().get(0).getPret() == 5.99);
}

void testcautaProdus() {
	ProduseRepo testr;
	ProdusVal vl;
	Magazin tests{ testr, vl };

	tests.adaugaProdus("nume1", "tip1", "prod1", 1.99);
	tests.adaugaProdus("nume2", "tip2", "prod2", 5.99);
	tests.adaugaProdus("nume3", "tip3", "prod3", 9.99);

	assert(tests.cautaProdus("nume1", "tip1").getPret() == 1.99);
	assert(tests.cautaProdus("nume2", "tip2").getPret() == 5.99);
	assert(tests.cautaProdus("nume3", "tip3").getPret() == 9.99);
}

void testmodificareProdus() {
	ProduseRepo testr;
	ProdusVal vl;
	Magazin tests{ testr, vl };

	tests.adaugaProdus("nume1", "tip1", "prod1", 1.99);
	tests.adaugaProdus("nume2", "tip2", "prod2", 5.99);

	tests.modificaProdus("nume1", "tip1", "prod1", 1.99, "nume2", "tip2", "prod2", 5.99);

	assert(tests.getproduse().get(1).getPret() == tests.getproduse().get(0).getPret());
	assert(tests.getproduse().get(1).getNume() == tests.getproduse().get(0).getNume());
}

void testFilterService() {
	ProduseRepo testRepo;
	ProdusVal vl;
	Magazin testService{ testRepo, vl };

	testService.adaugaProdus("Pasarea Calandrinon", "Phoenix", "folk-rock", 3.42);
	testService.adaugaProdus("Baba Novak", "Phoenix", "folk-rock", 8.31);
	testService.adaugaProdus("Apocalipsa", "Phoenix", "folk-rock", 5.27);
	testService.adaugaProdus("Fantanile", "Alternosfera", "alternative rock", 4.52);
	testService.adaugaProdus("Ploile Nu Vin", "Alternosfera", "alternative rock", 3.45);
	testService.adaugaProdus("Padure Verde", "Via Daca", "maybe folk", 3.2);

	VectorDinamic<Produs> melodiiFolkRock = testService.filtrareTip("Phoenix");
	assert(melodiiFolkRock.size() == 3);
	VectorDinamic<Produs> melodiiHeavyMetal = testService.filtrareTip("heavy metal");
	assert(melodiiHeavyMetal.size() == 0);


	VectorDinamic<Produs> melodii1 = testService.filtrarePret(2.15, 3.44);
	assert(melodii1.size() == 2);
	VectorDinamic<Produs> melodii2 = testService.filtrarePret(9, 10);
	assert(melodii2.size() == 0);

}

void testSortService() {

	ProduseRepo testRepo;
	ProdusVal vl;
	Magazin testService{ testRepo, vl };

	testService.adaugaProdus("Pasarea Calandrinon", "Phoenix", "folk-rock", 3.42);
	testService.adaugaProdus("Baba Novak", "Phoenix", "folk-rock", 8.31);
	testService.adaugaProdus("Apocalipsa", "Phoenix", "folk-rock", 5.27);
	testService.adaugaProdus("Fantanile", "Alternosfera", "alternative rock", 4.52);
	testService.adaugaProdus("Ploile Nu Vin", "Alternosfera", "alternative rock", 3.45);
	testService.adaugaProdus("Padure Verde", "Via Daca", "maybe folk", 3.2);

	VectorDinamic<Produs> sortedByDurata = testService.sortByPret();
	assert(sortedByDurata.get(0).getNume() == "Padure Verde");
	assert(sortedByDurata.get(1).getNume() == "Pasarea Calandrinon");
	assert(sortedByDurata.get(2).getNume() == "Ploile Nu Vin");
	assert(sortedByDurata.get(5).getNume() == "Baba Novak");

	VectorDinamic<Produs> sortedByArtistSong = testService.sortByProdNume();
	assert(sortedByArtistSong.get(0).getTip() == "Alternosfera");
	assert(sortedByArtistSong.get(0).getNume() == "Fantanile");

	assert(sortedByArtistSong.get(2).getTip() == "Phoenix");
	assert(sortedByArtistSong.get(2).getNume() == "Apocalipsa");

	assert(sortedByArtistSong.get(5).getTip() == "Via Daca");
	assert(sortedByArtistSong.get(5).getNume() == "Padure Verde");

}

void testeService() {
	testadaugaProdus();
	teststergeProdus();
	testcautaProdus();
	testmodificareProdus();
	testSortService();
	testFilterService();
}
