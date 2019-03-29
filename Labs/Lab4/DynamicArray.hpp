#include <iostream>
#pragma once

using namespace std;

template <typename T>
class DynamicArray{
private:
	unsigned int size;
	unsigned int capacity;
	T* array;

public:
	//Constructors
	DynamicArray();
	DynamicArray(int _capacity);

	//Destructor
	~DynamicArray();

	//Assignment operator
	DynamicArray<T>& operator= (const DynamicArray<T> &original);

	//Copy constructor
	DynamicArray(const DynamicArray &original);

	//Getters for array information
	unsigned int GetCapacity() const;
	unsigned int GetSize() const;
	const T* GetData() const;

	//Getters for contained array data
	const T& At(unsigned int index) const;
	T& At(unsigned int index);

	//Mutators
	void Add(const T &data);
	void Resize(unsigned int newSize);
	void Remove(unsigned int index);

	//Bracket operator overloading
	const T& operator[](unsigned int index) const;
	T& operator[](unsigned int index);
};

template <typename T>
DynamicArray<T>::DynamicArray(){
	size = 0;
	capacity = 1;
	array = new T[1];
}

template <typename T>
DynamicArray<T>::DynamicArray(int _capacity){
	size = 0;
	capacity = _capacity;
	array = new T[_capacity];
}

template <typename T>
DynamicArray<T>::~DynamicArray(){
	delete[] array;
}

template <typename T>
DynamicArray<T>& DynamicArray<T>::operator= (const DynamicArray<T> &original){
	array = new T[original.GetCapacity()];
	capacity = original.GetCapacity();
	size = original.GetSize();
	const T* copiedArray = original.GetData();

	delete[] original.array;

	for(unsigned int i = 0; i < original.GetCapacity(); i++){
		array[i] = copiedArray[i];
	}

	return *this;
}

template <typename T>
DynamicArray<T>::DynamicArray(const DynamicArray<T> &original){
	array = new T[original.GetCapacity()];
	capacity = original.GetCapacity();
	size = original.GetSize();
	for(unsigned int i = 0; i < original.GetCapacity(); i++){
		array[i] = original[i];
	}
}

template <typename T>
const T& DynamicArray<T>::operator[](unsigned int index) const{
	return array[index];
}

template <typename T>
T& DynamicArray<T>::operator[](unsigned int index){
	return array[index];
}

template <typename T>
unsigned int DynamicArray<T>::GetCapacity() const{
	return capacity;
}

template <typename T>
unsigned int DynamicArray<T>::GetSize() const{
	return size;
}

template <typename T>
const T* DynamicArray<T>::GetData() const{
	return array;
}

template <typename T>
const T& DynamicArray<T>::At(unsigned int index) const{
	return array[index];
}

template <typename T>
T& DynamicArray<T>::At(unsigned int index){
	if(index >= size){
		throw runtime_error("Error! Invalid Index");
	}
	return array[index];
}

template <typename T>
void DynamicArray<T>::Add(const T &data){
	if(size == capacity){
		Resize(size+1);
	}

	array[size] = data;
	size++;
}

template <typename T>
void DynamicArray<T>::Resize(unsigned int NewSize){
	cout << "Resizing... old capacity: " << GetCapacity() << " New Capacity: " << NewSize << endl;
	const T* copy = GetData();

	delete[] array;

	capacity = NewSize;
	array = new T[NewSize];

	for(unsigned int i = 0; i < size; i++){
		array[i] = copy[i];
		cout << "Copying " << copy[i] << endl;
	}

}

template <typename T>
void DynamicArray<T>::Remove(unsigned int index){
	unsigned int newCapacity = GetCapacity() - 1;

	if(index > GetSize()-1){
		throw runtime_error("Error! Invalid Index");
	}

	//unsigned int numberBefore = index;
	//unsigned int numberAfter = GetCapacity() - index;

	const T* copy = GetData();
	delete[] array;
	array = new T[newCapacity];

	unsigned int j = 0;
	for(unsigned int i = 0; i < GetCapacity(); i++){
		if(i == index){
			j++;
			continue;
		}
		array[i] = copy[j];
		j++;
	}
}


