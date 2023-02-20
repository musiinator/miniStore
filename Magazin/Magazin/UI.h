#pragma once
#include "Service.h"


class Console {
private:
	Magazin& srv;
public:
	Console(Magazin& srv) noexcept :srv{ srv } {};

	void printMeniu();
	void uiAdauga();
	void uiSterge();
	void uiCauta();
	void uiModifica();
	void uiFiltreaza();
	void uiSort();
	void printProduse();
	void run();
};