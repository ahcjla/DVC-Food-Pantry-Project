// Programmer: Rachael Karim
// Programmer's ID: 0136068

#ifndef DynamicArray_H
#define DynamicArray_H

#include <string>
using namespace std;

#include <cassert>

template <typename T>
class DynamicArray
{
	T* value;  // T datatype CAP capacity
	int cap;
	T dummy = T();

public:
	DynamicArray(int = 2); // Constructor // default = 2
	DynamicArray(const DynamicArray<T>&);  // copy constructor
	~DynamicArray() { delete[] value; } // destructor
	DynamicArray<T>& operator = (const DynamicArray<T>&); // assignment operator
	int capacity() const { return cap; }
	void capacity(int); // capacity setter
	T operator[] (int) const; // getter
	T& operator[] (int); // setter
};


//constructor
template <typename T>
DynamicArray<T>::DynamicArray(int cap)
{
	this->cap = cap;
	value = new T[cap];
	dummy = T();
}

//copy constructor
template <typename T>
DynamicArray<T>::DynamicArray(const DynamicArray<T>& original) {
	cap = original.cap; // copy of capacity
	value = new T[cap]; // new object for new array

	for (int i = 0; i < cap; i++) {
		value[i] = original.value[i]; // copy array
	}
}

//assignment operator
template <typename T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray<T>&original) {
	if (this != &original) {
		delete[] value;

		cap = original.cap;
		value = new T[cap];
		for (int i = 0; i < cap; i++) {
			value[i] = original.value[i];
		}
	}
	return *this;
}

// capacity setter
template <typename T>
void DynamicArray<T>::capacity(int cap) {
	T* temp = new T[cap];
	
	int limit = (cap < this->cap ? cap : this->cap);

	for (int i = 0; i < limit; i++)
		temp[i] = value[i];

	for (int i = limit; i < cap; i++)
		temp[i] = T();

	delete[] value;
	value = temp;
	this->cap = cap;
}

//getter
template <typename T>
T DynamicArray<T>::operator[](int index) const {
	if (index < 0) return dummy;
	if (index >= cap) return dummy;
	return value[index];
}

//setter
template <typename T>
T& DynamicArray<T>::operator[](int index) {
	if (index < 0) return dummy;
	if (index >= cap) capacity(2 * index);
	return value[index];
}

#endif // header_h