#include <iostream>

void ArrayEq(int arrayOne[], int arrayTwo[], int size){
	bool equal = true;
	for(int i = 0; i < size; i++){
		if(arrayOne[i] != arrayTwo[i]){
			equal = false;
		}
	}

	std::cout << equal << std::endl;
}

int main(){
	int size = 3;
	int one[size];
	int two[size];
	one[0] = 1;
	one[1] = 2;
	one[2] = 3;
	two[0] = 1;
	two[1] = 2;
	two[2] = 3;
	ArrayEq(one, two, size);
}

