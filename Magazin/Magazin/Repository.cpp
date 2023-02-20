#include "Repository.h"
#include <assert.h>
//#include "gsl.h"

bool ProduseRepo::exista(const Produs& p) {
		IteratorVector<Produs> ic = this->lista_produse.begin();
		while (ic.valid())
		{
			if (ic.element().getNume() == p.getNume() && ic.element().getTip() == p.getTip())
				return true;
			ic.next();
		}
	
		return false;
}

const Produs& ProduseRepo::find(string nume, string tip) {
	for (int i = 0; i < this->lista_produse.size(); i++)
		if (this->lista_produse.get(i).getNume() == nume && this->lista_produse.get(i).getTip() == tip)
			return this->lista_produse.get(i);

	throw RepoException("Produsul cu numele " + nume + " si tip " + tip + " nu exista.");

}

void ProduseRepo::store(const Produs& p) {
	if (exista(p)) {
		throw RepoException("Produsul cu numele " + p.getNume() + " si tipul " + p.getTip() + " exista deja.");
	}
	this->lista_produse.adauga(p);
}

void ProduseRepo::remove(const Produs& p) {
	if (!exista(p)) {
		throw RepoException("Produsul cu numele " + p.getNume() + " si tipul " + p.getTip() + " nu exista.");
	}
	IteratorVector<Produs> ic = this->lista_produse.begin();
	int i = 0;
	while (ic.valid())
	{
		if (ic.element().getNume() == p.getNume() && ic.element().getTip() == p.getTip() && ic.element().getPret() == p.getPret() && ic.element().getProducator() == p.getProducator()) {
			this->lista_produse.sterge(i);
			break;
		}
		i++;
		ic.next();
	}
}

void ProduseRepo::modific(const Produs& p, const Produs& p_nou) {
	if (!exista(p)) {
		throw RepoException("Produsul cu numele " + p.getNume() + " si tipul " + p.getTip() + " nu exista.");
	}
	IteratorVector<Produs> ic = this->lista_produse.begin();
	int i = 0;
	while (ic.valid())
	{
		if (ic.element().getNume() == p.getNume() && ic.element().getTip() == p.getTip() && ic.element().getPret() == p.getPret() && ic.element().getProducator() == p.getProducator()) {
			this->lista_produse.set(p_nou, i);
			break;
		}
		i++;
	}
}

VectorDinamic<Produs>& ProduseRepo::getProduse() noexcept {
	return this->lista_produse;
}

void teststore() {
	ProduseRepo testr;
	Produs a{ "nume1", "tip1","prod1", 1.99 };
	testr.store(a);
	assert(testr.getProduse().size() == 1);

	Produs b{ "nume2", "tip2", "prod2", 5.99 };

	testr.store(b);
	assert(testr.getProduse().size() == 2);

	assert(testr.getProduse().get(1).getNume() == "nume2");

	try {
		testr.store(b);
		assert(false);
	}
	catch (RepoException) {
		assert(true);
	}

}

void testremove() {
	ProduseRepo testr;
	Produs a{ "nume1", "tip1","prod1", 1.99 };
	Produs b{ "nume2", "tip2", "prod2", 5.99 };
	Produs c{ "nume3", "tip3", "prod3", 4.11 };

	testr.store(a);
	testr.store(b);

	assert(testr.getProduse().size() == 2);

	testr.remove(a);

	assert(testr.getProduse().size() == 1);

	assert(testr.getProduse().get(0).getPret() == 5.99);

	try {
		testr.remove(c);
		assert(false);
	}
	catch (RepoException) {
		assert(true);
	}
}

void testmodific() {
	ProduseRepo testr;
	Produs a{ "nume1", "tip1","prod1", 1.99 };
	Produs b{ "nume2", "tip2", "prod2", 5.99 };
	Produs c{ "nume3", "tip3", "prod3", 4.11 };

	testr.store(a);
	testr.store(b);

	testr.modific(a, b);

	assert(testr.getProduse().get(1).getPret() == testr.getProduse().get(0).getPret());
	assert(testr.getProduse().get(1).getNume() == testr.getProduse().get(0).getNume());

	try {
		testr.modific(c, a);
		assert(false);
	}
	catch (RepoException) {
		assert(true);
	}
}

void testFind() {
	ProduseRepo testr;

	Produs a{ "nume1", "tip1","prod1", 1.99 };
	Produs b{ "nume2", "tip2", "prod2", 5.99 };
	Produs c{ "nume3","tip3", "prod3", 9.99 };
	testr.store(a);
	testr.store(b);

	assert(testr.exista(a));
	assert(!testr.exista(c));

	auto foundProdus = testr.find("nume1", "tip1");
	assert(foundProdus.getTip() == "tip1");
	assert(foundProdus.getPret() == 1.99);
	assert(foundProdus.getProducator() == "prod1");

	try {
		testr.find("nume5", "tip5");
		assert(false);
	}
	catch (RepoException& ve) {
		assert(ve.getErrors() == "Produsul cu numele nume5 si tip tip5 nu exista.");
	}

}

void testeRepo() {
	teststore();
	testremove();
	testmodific();
    testFind();
}