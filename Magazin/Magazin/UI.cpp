#pragma once
#include "UI.h"
#include "V3.h"
#include <iostream>
using namespace std;
void Console::printMeniu() {
	cout << "Comezile sunt:" << endl;
	cout << "1. Adauga produs" << endl;
	cout << "2. Sterge produs" << endl;
	cout << "3. Modificare produs" << endl;
	cout << "4. Cauta podus" << endl;
	cout << "5. Afisare produse" << endl;
    cout << "6. Filtreaza" << endl;
	cout << "7 .Sorteaza" << endl;
	cout << "8. Exit" << endl;
}

void Console::uiAdauga() {
	string nume, tip, producator;
	double pret;
	cout << "Introdu numele produsului:";
	getline(cin >> ws, nume);

	cout << "Introdu tipul produsului:";
	getline(cin >> ws, tip);

	cout << "Introdu producatorul produsului:";
	getline(cin >> ws, producator);

	cout << "Introdu pretul produsului:";
	cin >> pret;

	try {
		srv.adaugaProdus(nume, tip, producator, pret);
	}
	catch (RepoException& re) {
		cout << re.getErrors();
	}
	catch (Validation& ve) {
		cout << "Produsul nu este valid!" << endl;
		cout << ve.getErrors();
	}

}

void Console::uiSterge() {
	string nume, tip, producator;
	double pret;
	cout << "Introdu numele produsului:";
	getline(cin >> ws, nume);

	cout << "Introdu tipul produsului:";
	getline(cin >> ws, tip);

	cout << "Introdu producatorul produsului:";
	getline(cin >> ws, producator);

	cout << "Introdu pretul produsului:";
	cin >> pret;

	try {
		srv.stergeProdus(nume, tip, producator, pret);
	}
	catch (RepoException& re) {
		cout << re.getErrors();
	}
	catch (Validation& ve) {
		cout << "Produsul nu este valid!" << endl;
		cout << ve.getErrors();
	}
}

void Console::uiCauta() {
	string nume, tip;

	cout << "Introdu numele produsului:";
	getline(cin >> ws, nume);

	cout << "Introdu tipul produsului:";
	getline(cin >> ws, tip);

	Produs p = srv.cautaProdus(nume, tip);
	cout << "Produsul cautat este: " << endl;
	cout << "Nume: " << p.getNume() << "  Tip: " << p.getTip() << "  Producator: " << p.getProducator() << "  Pret: " << p.getPret() << endl;
}

void Console::uiModifica() {
	string nume, tip, producator;
	double pret;
	cout << "Introdu numele produsului:";
	getline(cin >> ws, nume);

	cout << "Introdu tipul produsului:";
	getline(cin >> ws, tip);

	cout << "Introdu producatorul produsului:";
	getline(cin >> ws, producator);

	cout << "Introdu pretul produsului:";
	cin >> pret;

	string nume_nou, tip_nou, producator_nou;
	double pret_nou;
	cout << "Introdu numele noului produs:";
	getline(cin >> ws, nume_nou);

	cout << "Introdu tipul noului produs:";
	getline(cin >> ws, tip_nou);

	cout << "Introdu producatorul noului produs:";
	getline(cin >> ws, producator_nou);

	cout << "Introdu pretul noului produs:";
	cin >> pret_nou;

	try {
		srv.modificaProdus(nume, tip, producator, pret, nume_nou, tip_nou, producator_nou, pret_nou);
	}
	catch (RepoException& re) {
		cout << re.getErrors();
	}
	catch (Validation& ve) {
		cout << "Produsul nu este valid!" << endl;
		cout << ve.getErrors();
	}
}

void Console::uiFiltreaza() {
	cout << "Criteriul de filtrare este (tip/pret):";
	string criteriu;
	cin >> criteriu;

	if (criteriu == "tip") {
		cout << "Tipul cautat este:" << endl;
		string searchedTip;
		cin >> searchedTip;

		VectorDinamic<Produs> produse = srv.filtrareTip(searchedTip);
		if (produse.size() == 0)
			cout << "Nu exista produse in lista!" << endl;
		else
			for (int i = 0; i < produse.size(); i++) {
				Produs produs = produse.get(i);
				//for (const auto& produs : produse) {
				cout << "Nume: " << produs.getNume() << "  Tip: " << produs.getTip() << "  Producator: " << produs.getProducator() << "  Pret: " << produs.getPret() << endl;
			}

	}
	else if (criteriu == "pret") {
		double pretStart, pretEnd;
		cout << "Limita inferioara a pretului este:" << endl;
		cin >> pretStart;
		cout << "Limita superioara a pretului este:" << endl;
		cin >> pretEnd;


		VectorDinamic<Produs> produse = srv.filtrarePret(pretStart, pretEnd);
		if (produse.size() == 0)
			cout << "Nu exista produse in lista!" << endl;
		else
			for (int i = 0; i < produse.size(); i++) {
				Produs produs = produse.get(i);
				//for (const auto& produs : produse) {
				cout << "Nume: " << produs.getNume() << "  Tip: " << produs.getTip() << "  Producator: " << produs.getProducator() << "  Pret: " << produs.getPret() << endl;
			}
	}

	else
		cout << "Nu se poate sorta dupa criteriul dat." << endl;

}

void Console::uiSort() {
	cout << "Criteriul de sortare este (pret/producator+nume):";
	string criteriu;
	cin >> criteriu;

	if (criteriu == "pret") {
		VectorDinamic<Produs> produse = srv.sortByPret();
		if (produse.size() == 0)
			cout << "Nu exista produse in lista!" << endl;
		else
			for (int i = 0; i < produse.size(); i++) {
				Produs produs = produse.get(i);
				//for (const auto& produs : produse) {
				cout << "Nume: " << produs.getNume() << "  Tip: " << produs.getTip() << "  Producator: " << produs.getProducator() << "  Pret: " << produs.getPret() << endl;
			}
	}
	else if (criteriu == "producator+nume") {
		VectorDinamic<Produs> produse = srv.sortByProdNume();
		if (produse.size() == 0)
			cout << "Nu exista produse in lista!" << endl;
		else
			for (int i = 0; i < produse.size(); i++) {
				Produs produs = produse.get(i);
				//for (const auto& produs : produse) {
				cout << "Nume: " << produs.getNume() << "  Tip: " << produs.getTip() << "  Producator: " << produs.getProducator() << "  Pret: " << produs.getPret() << endl;
			}
	}
	else
		cout << "Nu se poate sorta dupa criteriul dat." << endl;
}

void Console::printProduse() {
	VectorDinamic<Produs>& produse = srv.getproduse();
	if (produse.size() == 0)
		cout << "Nu exista produse in lista!" << endl;
	else 
		for (int i=0; i<produse.size(); i++) {
			Produs produs = produse.get(i);
		//for (const auto& produs : produse) {
			cout << "Nume: " << produs.getNume() << "  Tip: " << produs.getTip() << "  Producator: " << produs.getProducator() << "  Pret: " << produs.getPret() << endl;
		}

}

void Console::run() {
	constexpr int start = 1;
	int cmd = 6;
	while (start) {
		cout << endl;
		printMeniu();
		cout << "Introdu comanda:";
		cin >> cmd;
		if (cmd == 1) {
			uiAdauga();
		}
		else if (cmd == 2) {
			uiSterge();
		}
		else if (cmd == 3) {
			uiModifica();
		}
		else if (cmd == 4) {
			uiCauta();
		}
		else if(cmd == 5) {
			printProduse();
		}
		else if (cmd == 6) {
			uiFiltreaza();
		}
		else if (cmd == 7) {
			uiSort();
		}
		else if (cmd == 8) {
			break;
		}
	}
}