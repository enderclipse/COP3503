#include <iostream>
using namespace std;
template <typename T>
class ABS{
private:
	unsigned int size;
	unsigned int capacity;
	float scaleFactor;
	T* contents;

public:

	//Constructors
	ABS();

	ABS(int capacity);

	//Copy Constructor
	ABS(const ABS &d);

	//Assignment operator
	ABS &operator= (const ABS &d);

	//Destructor
	~ABS();

	//Mutators
	T push(T data);
	T pop();
	T peek();

	//Getters
	T* getData();
	unsigned int getSize();
	unsigned int getMaxCapacity();

	const T& operator[](unsigned int index) const;
	T& operator[](unsigned int index);
};

//Constructors
template <typename T>
ABS<T>::ABS(){
	size = 0;
	capacity = 1;
	contents = new T[1];
	scaleFactor = 2.0f;
}

template <typename T>
ABS<T>::ABS(int _capacity){
	size = 0;
	capacity = _capacity;
	contents = new T[_capacity];
	scaleFactor = 2.0f;
}

//Copy Constructor
template <typename T>
ABS<T>::ABS(const ABS<T> &original){
	capacity = original.getMaxCapacity();
	size = original.getSize();

	if(original.getSize() == 0)
		contents = new T[0];

	else{
		contents = new T[original.getMaxCapacity()];
		for(unsigned int i = 0; i < size; i++){
			contents[i] = original[i];
		}
	}
}

//Assignment operator
template <typename T>
ABS<T>& ABS<T>::operator= (const ABS<T> &original){
	capacity = original.getMaxCapacity();
	size = original.getSize();

	if(original.getSize() == 0)
		contents = new T[0];

	else{
		for(unsigned int i = 0; i < original.getSize(); i++){
			contents[i] = original[i];
		}
	}
}

template <typename T>
const T& ABS<T>::operator[](unsigned int index) const{
	return contents[index];
}

template <typename T>
T& ABS<T>::operator[](unsigned int index){
	if(index >= size || size == 0){
		//throw runtime_error("Error! Invalid index");
	}
	return contents[index];
}

//Destructor
template <typename T>
ABS<T>::~ABS(){
	delete[] contents;
}

template <typename T>
T ABS<T>::push(T data){
	if(getSize() == getMaxCapacity()){
		capacity *= 2;

		T* copyArray = getData();
		delete[] contents;
		contents = new T[capacity];

		for(unsigned int i = 0; i < size; i++){
			contents[i] = copyArray[i];
		}
		delete[] copyArray;
	}
	contents[size] = data;
	size++;
	return data;
}

template <typename T>
T ABS<T>::pop(){
	if(size == 0){
		throw -1;
	}
	size--;
	T value = contents[size];
	contents[size] = (T) NULL;
	float percentFull = (float)getSize()/getMaxCapacity();
	if(percentFull < 1/scaleFactor){
		T* copy = getData();
		capacity = capacity/scaleFactor;

		delete[] contents;
		contents = new T[capacity];
		for(unsigned int i = 0; i < size; i++){
			contents[i] = copy[i];
		}
		delete[] copy;
	}
	return value;
}

template <typename T>
T ABS<T>::peek(){
	if(size == 0){
		return -1;
	}
	else{
		return contents[size-1];
	}
}

template <typename T>
T* ABS<T>::getData(){
	T* data = new T[capacity];
	for(unsigned int i = 0; i < size; i++){
		data[i] = contents[i];
	}
	return data;
}

template <typename T>
const unsigned int ABS<T>::getSize(){
	return size;
}

template <typename T>
const unsigned int ABS<T>::getMaxCapacity(){
	return capacity;
}