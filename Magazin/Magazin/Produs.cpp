#include "Produs.h"
#include <assert.h>

string Produs::getNume() const {
	return this->nume;
}

string Produs::getTip() const {
	return this->tip;
}

string Produs::getProducator() const {
	return this->producator;
}

double Produs::getPret() const noexcept {
	return this->pret;
}

void Produs::setNume(string nume2) {
	this->nume = nume2;
}

void Produs::setTip(string tip2) {
	this->tip = tip2;
}

void Produs::setProducator(string producator2) {
	this->producator = producator2;
}

void Produs::setPret(double pret2) noexcept {
	this->pret = pret2;
}


bool cmpPret(const Produs& m1, const Produs& m2) {
	return m1.getPret() < m2.getPret();
}

bool cmpProdNume(const Produs& m1, const Produs& m2) {
	if (m1.getProducator() == m2.getProducator())
		return m1.getNume() < m2.getNume();
	else
		return m1.getProducator() < m2.getProducator();
}


void testGS() {
	Produs a{ "salam", "mezel","sibiu", 10.99 };
	assert(a.getNume() == "salam");
	assert(a.getTip() == "mezel");
	assert(a.getProducator() == "sibiu");
	assert(a.getPret() == 10.99);

	Produs b{ "pateu", "conserva","sadu", 8.75 };
	assert(b.getNume() == "pateu");
	assert(b.getTip() == "conserva");
	assert(b.getProducator() == "sadu");
	assert(b.getPret() == 8.75);

	b.setNume("nume");
	b.setTip("tip");
	b.setProducator("producator");
	b.setPret(8.75);

	assert(b.getNume() == "nume");
	assert(b.getTip() == "tip");
	assert(b.getProducator() == "producator");
	assert(b.getPret() == 8.75);
}

void testProdus() {
	testGS();
}