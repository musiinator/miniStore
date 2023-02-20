#pragma once
#include <string>
#include <iostream>
using std::string;
using std::cout;
using std::endl;
class Produs {
private:
	string nume;
	string tip;
	string producator;
	double pret;
public:
	Produs() = default;
	Produs(string nume, string tip, string producator, double pret) :nume{ nume }, tip{ tip }, producator{ producator }, pret{ pret }{};
    
	Produs(const Produs& o) :nume{ o.nume }, tip{ o.tip }, producator{ o.producator }, pret{ o.pret }{
		//cout << "[PRODUS] Copy constructor called." << endl;
	}

	//Produs& operator=(const Produs&) = default;

	string getNume() const;
	string getTip() const;
	string getProducator() const;
	double getPret() const noexcept;

	void setNume(string nume2);
	void setTip(string tip2);
	void setProducator(string producator2);
	void setPret(double pret2) noexcept;

	bool operator==(const Produs& other) noexcept {
		return this->nume == other.nume && this->pret == other.pret && this->producator == other.producator && this->tip == other.tip;
	}
};

bool cmpPret(const Produs& m1, const Produs& m2);

bool cmpProdNume(const Produs& m1, const Produs& m2);

void testProdus();
