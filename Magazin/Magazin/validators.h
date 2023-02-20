#pragma once

#include "Produs.h"
#include <vector>
#include <string>

using std::string;
using std::vector;
class Validation {
	vector<string> errors;
public:
	Validation(vector<string> errorMs) :errors{ errorMs } {};

	string getErrors() {
		string Msg = "";
		for (const string e : errors) {
			Msg += e + "\n";
		}
		return Msg;
	}
};


class ProdusVal {
public:
	void valid(const Produs& p) {
		vector<string> errors;
		if (p.getNume().length() < 2)
			errors.push_back("Numele trebuie sa aiba cel putin 2 litere!");
		if (p.getProducator().length() < 2)
			errors.push_back("Numele Producatorului trebuie sa aiba cel putin 2 litere!");
		if (p.getPret() < 1 || p.getPret() > 10000)
			errors.push_back("Pretul trebuie sa fie intre 1 si 10000.");
		if (p.getTip().length() < 2)
			errors.push_back("Tipul trebuie sa aiba cel putin 2 litere!");

		if (errors.size() > 0)
			throw Validation(errors);
	}
};
