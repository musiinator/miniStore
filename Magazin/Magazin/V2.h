#pragma once
#pragma warning (disable: 26446)
#pragma warning (disable: 26458)
#pragma warning (disable: 26455)
#include <exception>

template <typename Type>
class DynamicVectorIterator;

template <typename Type>
class DynamicVector {
private:
	unsigned length;
	unsigned capacity;
	Type* elements;
	void redim();
public:
	// Dynamic Vector Default Constructor
	DynamicVector();
	// Dynamic Vector Class Constructor
	DynamicVector(unsigned capacity);
	// Copy Constructor
	DynamicVector(const DynamicVector& ot);
	// Dynamic Vector Class Move Constructor
	DynamicVector(DynamicVector&&) = default;
	// Dynamic Vector Class Copy Assignment Operators
	DynamicVector& operator=(const DynamicVector&) = default;
	// Dynamic Vector Class Move Assignment Operators
	DynamicVector& operator=(DynamicVector&&) = default;
	// Dynamic Vector Class Destructor
	~DynamicVector() {};

	// Returns the size
	unsigned size() const noexcept;
	// Returns the element at position i
	const Type& at(unsigned i) const;
	// Sets the value of the element at position i and returns the old value
	void assign(const Type& e, unsigned i);
	// Emplaces the element at the last position
	void push_back(const Type& e);
	// Inserts the element at a given position
	void insert(const Type& e, unsigned i);
	// Removes the element at the given position and returns the old value
	void remove(unsigned i);
	// Returns true if the vector is empty and false otherwise
	bool empty();
	// Verifies if a element is in the vector
	unsigned search(const Type& e) noexcept;
	// Returns the iterator of the Dynamic Vector
	DynamicVectorIterator<Type> iterator();
};

template <typename Type>
void DynamicVector<Type>::redim() {
	auto newElements = new Type[capacity * 2];
	for (unsigned i = 0; i < length; ++i) {
		newElements[i] = elements[i];
	}
	capacity += capacity;
	elements = newElements;
}

template <typename Type>
DynamicVector<Type>::DynamicVector() {
	this->capacity = INITIAL_CAPACITY;
	this->length = 0;
	this->elements = new Type[INITIAL_CAPACITY];
}

template <typename Type>
DynamicVector<Type>::DynamicVector(unsigned capacity) {
	this->capacity = capacity;
	length = 0;
	elements = new Type[capacity];
}

template <typename Type>
unsigned DynamicVector<Type>::size() const noexcept {
	return length;
}

template <typename Type>
const Type& DynamicVector<Type>::at(unsigned i) const {
	//if (i >= length) {
//		throw exception("Invalid position!");
	//}
	return elements[i];
}

template <typename Type>
void DynamicVector<Type>::push_back(const Type& e) {
	if (length == capacity) {
		redim();
	}
	elements[length] = e;
	++length;
}

template <typename Type>
void DynamicVector<Type>::insert(const Type& e, unsigned i) {
	if (i > length) {
		throw std::exception("Invalid position!");
	}
	if (length == capacity) {
		redim();
	}
	for (unsigned j = length; j > i; --j) {
		elements[j] = elements[j - 1];
	}
	elements[i] = e;
	++length;
}

template <typename Type>
void DynamicVector<Type>::assign(const Type& e, unsigned i) {
	if (i >= length) {
		throw std::exception("Invalid position!");
	}
	elements[i] = e;
}

template <typename Type>
void DynamicVector<Type>::remove(unsigned i) {
	if (i >= length) {
		throw std::exception("Invalid position!");
	}
	for (unsigned j = i; j < length - 1; ++j) {
		elements[j] = elements[j + 1];
	}
	length--;
}

template <typename Type>
bool DynamicVector<Type>::empty() {
	return length == 0;
}

template <typename Type>
unsigned DynamicVector<Type>::search(const Type& e) noexcept {
	unsigned i = 0;
	while (i < length) {
		if (elements[i] == e) {
			break;
		}
		++i;
	}
	return i;
}


template <typename Type>
DynamicVectorIterator<Type> DynamicVector<Type>::iterator() {
	return DynamicVectorIterator<Type>(*this);
}

template <typename Type>
class DynamicVectorIterator {

private:
	// Dynamic Vector Iterator Constructor
	DynamicVectorIterator(const DynamicVector<Type>&);
	const DynamicVector<Type>& v;
	unsigned curent;

public:
	// Sets the Iterator at the first position
	void begin();
	// Sets the Iterator to the next position
	void next();
	// Verifies if the Iterator is valid
	bool valid() const;
	// Returns the value of the element that the Iterator refers to
	Type element() const;
};

template <typename Type>
DynamicVectorIterator<Type>::DynamicVectorIterator(const DynamicVector<Type>& _v) : v(_v) {
	curent = 0;
}

template <typename Type>
void DynamicVectorIterator<Type>::begin() {
	curent = 0;
}

template <typename Type>
bool DynamicVectorIterator<Type>::valid() const {
	return curent < v.size();
}

template <typename Type>
Type DynamicVectorIterator<Type>::element() const {
	return v[curent];
}

template <typename Type>
void DynamicVectorIterator<Type>::next() {
	++curent;
}