#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "UI.h"
#include <iostream>
using std::cout;
using std::endl;
void teste() {
	testProdus();
    testeRepo();
	testeService();
}

void start() {
	ProduseRepo repo;
	ProdusVal val;
	Magazin srv{ repo, val };
	Console ui{ srv };
	ui.run();
}

int main() {
	teste();
	start();

	_CrtDumpMemoryLeaks();
}