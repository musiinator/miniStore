#pragma once
constexpr auto INITIAL_CAPACITY = 1;
#include <assert.h>

template<typename T>
class IteratorVector;

template<typename T>
class VectorDinamic {
private:
	T* elementele;
	int capacity;
	int length;

	void redim();
public:
	//constructor
	VectorDinamic();

	//copy constructor
	VectorDinamic(const VectorDinamic& ot);

	//asignement operator
	VectorDinamic& operator=(const VectorDinamic& ot);

	//destructor
	~VectorDinamic();

	//add element
	void adauga(T elem);
	//get element on poz
	T& get(int poz);
	//set element on poz
	void set(T elem, int poz);
	//get size
	int size();
	//stergere
	void sterge(int poz);







	friend class IteratorVector<T>;

	IteratorVector<T> begin();
	IteratorVector<T> end();
};

template<typename T>
VectorDinamic<T>::VectorDinamic() {
	this->elementele = new T[INITIAL_CAPACITY];
	this->length = 0;
	this->capacity = INITIAL_CAPACITY;
}

template<typename T>
VectorDinamic<T>::VectorDinamic(const VectorDinamic& ot) {
	
    this->elementele = new T[ot.capacity];

	for (int i = 0; i < ot.length; i++) {
		this->elementele[i] = ot.elementele[i];
	}
	this->length = ot.length;
	this->capacity = ot.capacity;
}

template<typename T>
VectorDinamic<T>& VectorDinamic<T>::operator=(const VectorDinamic& ot) {

	if (this == &ot) {
		return *this;
	}

	delete[] this->elementele;

	this->elementele = new T[ot.capacitate];
	for (int i = 0; i < ot.length; i++) {
		elementele[i] = ot.elementele[i];
	}
	this->length = ot.length;
	this->capacitate = ot.capacitate;
	return *this;
}

template<typename T>
void VectorDinamic<T>::redim() {
	int newCapacity = this->capacity * 2;
	T* newElems = new T[newCapacity];
	for (int i = 0; i < this->length; i++) {
		newElems[i] = this->elementele[i];
	}
	delete[] this->elementele;
	this->elementele = newElems;
	this->capacity = newCapacity;

}

template<typename T>
VectorDinamic<T>::~VectorDinamic() {
	delete[] this->elementele;
}

template<typename T>
void VectorDinamic<T>::adauga(T elem) {
	if (this->length == this->capacity)
		redim();
	this->elementele[this->length] = elem;
	this->length++;
}

template<typename T>
T& VectorDinamic<T>::get(int poz) {
	return this->elementele[poz];
}

template<typename T>
void VectorDinamic<T>::set(T elem, int poz) {
	this->elementele[poz] = elem;
}

template<typename T>
int VectorDinamic<T>::size() {
	return this->length;
}

template<typename T>
void VectorDinamic<T>::sterge(int i) {
	for (int j = i; j < length - 1; ++j) {
		elementele[j] = elementele[j + 1];
	}
	length--;
}











template<typename T>
class IteratorVector {
private:
	const VectorDinamic<T>& vec;
	int poz = 0;
public:
	IteratorVector(const VectorDinamic<T>& v) noexcept;
	IteratorVector(const VectorDinamic<T>& v, int poz) noexcept;
	bool valid() const;
	T& element() const;
	void next() noexcept;
	T& operator*() noexcept;
	IteratorVector& operator++();
	bool operator==(const IteratorVector& ot) noexcept;
	bool operator!=(const IteratorVector& ot) noexcept;
};




template<typename T>
IteratorVector<T> VectorDinamic<T>::begin() {
	return IteratorVector<T>(*this);
}
template<typename T>
IteratorVector<T> VectorDinamic<T>::end() {
	return IteratorVector<T>(*this, this->length);
}





template<typename T>
IteratorVector<T>::IteratorVector(const VectorDinamic<T>& v) noexcept :vec{ v } { };
template<typename T>
IteratorVector<T>::IteratorVector(const VectorDinamic<T>& v, int poz) noexcept :vec{ v }, poz{ poz }{};

template<typename T>
bool IteratorVector<T>::valid() const {
	return this->poz < this->vec.length;
}
template<typename T>
T& IteratorVector<T>::element() const {
	return this->vec.elementele[this->poz];
}
template<typename T>
void IteratorVector<T>::next() noexcept {
	this->poz++;
}

template<typename T>
T& IteratorVector<T>::operator*() noexcept {
	return this->element();
}

template<typename T>
IteratorVector<T>& IteratorVector<T>::operator++() {
	this->next();
	return *this;
}

template<typename T>
bool IteratorVector<T>::operator==(const IteratorVector& ot) noexcept {
	return this->poz == ot.poz;
}
template<typename T>
bool IteratorVector<T>::operator!=(const IteratorVector& ot) noexcept {
	return !(*this == ot);
}