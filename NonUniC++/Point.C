#include <iostream>

void print(int x){
	std::cout << x << std::endl;
}

int main(){
	int x = 10;
	int *p;
	p = &x;
	print(*p);
	x= 9;
	print(*p);
}