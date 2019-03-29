#include <iostream>
using namespace std;

template <typename T>
class ABQ{
private:
	unsigned int capacity;
	unsigned int size;
	float scaleFactor;
	T* arrayBasedQ;

public:
	ABQ();
	ABQ(int _capacity);
	ABQ(const ABQ &d);
	ABQ<T>& operator= (const ABQ<T> &d);
	~ABQ();

	void enqueue(T data);
	T dequeue();
	T peek();
	T* getData();

	unsigned int getSize();
	unsigned int getMaxCapacity();

	const T& operator[](unsigned int index) const;
	T& operator[](unsigned int index);

};

//Constructors
template <typename T>
ABQ<T>::ABQ(){
	scaleFactor = 2.0f;
	size = 0;
	capacity = 1;
	arrayBasedQ = new T[1];
}

template <typename T>
ABQ<T>::ABQ(int _capacity){
	capacity = _capacity;
	arrayBasedQ = new T[_capacity];
	size = 0;
	scaleFactor = 2.0f;
}

//Copy Constructor
template <typename T>
ABQ<T>::ABQ(const ABQ &d){
	capacity = d.capacity;
	size = d.size;
	scaleFactor = 2.0f;

	arrayBasedQ = new T[capacity];
	if(arrayBasedQ != nullptr){
		delete[] arrayBasedQ;
		for(int i = 0; i < capacity; i++){
			arrayBasedQ[i] = d[i];
		}
	}
}

//Assignment operator
template <typename T>
ABQ<T>& ABQ<T>::operator= (const ABQ<T> &d){
	capacity = d.getMaxCapacity();
	size = d.getSize();
	scaleFactor = 2.0f;

	arrayBasedQ = new T[capacity];

	if(arrayBasedQ != nullptr){
		delete[] arrayBasedQ;
		for(int i = 0; i < capacity; i++){
			arrayBasedQ[i] = d[i];
		}
	}
}

//Brackets operator
template <typename T>
const T& ABQ<T>::operator[](unsigned int index) const{
	return arrayBasedQ[index];
}

template <typename T>
T& ABQ<T>::operator[](unsigned int index){
	if(index >= size || size == 0){
		throw runtime_error("Error! Invalid index");
	}
	return arrayBasedQ[index];
}


//Destructor
template <typename T>
ABQ<T>::~ABQ(){
	delete[] arrayBasedQ;

}

template <typename T>
void ABQ<T>::enqueue(T data){
	if(getSize() == getMaxCapacity()){
		T* copiedData = getData();
		delete[] arrayBasedQ;
		capacity *= 2;
		arrayBasedQ = new T[capacity];
		for(unsigned int i = 0; i < getSize(); i++){
			arrayBasedQ[i] = copiedData[i];
		}
		delete[] copiedData;
		arrayBasedQ[size] = data;
	}

	else{
		arrayBasedQ[size] = data;
	}
	size++;
}

template <typename T>
T ABQ<T>::dequeue(){
	if(size == 0)
		throw -1;
	T* copy = getData();
	size--;
	T value = arrayBasedQ[0];
	float percentFull = (float)size/capacity;

	//If no resizing is needed do this
	if(percentFull >= 1/scaleFactor){
		delete[] arrayBasedQ;
		arrayBasedQ = new T[capacity];
		int j = 1;
		for(unsigned int i = 0; i < size; i++){
			arrayBasedQ[i] = copy[j];
			j++;
		}
	}

	//If need to resize do this
	else{
		delete[] arrayBasedQ;
		capacity = capacity/scaleFactor;
		arrayBasedQ = new T[capacity];

		int j = 1;
		for(unsigned int i = 0; i < size; i++){
			arrayBasedQ[i] = copy[j];
			j++;
		}
	}
	delete[] copy;
	return value;
}

template <typename T>
T ABQ<T>::peek(){
	if(size == 0){
		throw -1;
	}
	
	return arrayBasedQ[0];
}

template <typename T>
T* ABQ<T>::getData(){
	T* data = new T[capacity];
	for(unsigned int i = 0; i < size; i++){
		data[i] = arrayBasedQ[i];
	}
	return data;
}

template <typename T>
unsigned int ABQ<T>::getSize(){
	return size;
}

template <typename T>
unsigned int ABQ<T>::getMaxCapacity(){
	return capacity;
}

