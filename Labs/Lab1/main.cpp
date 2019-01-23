#include <iostream>
#include "Functions.hpp"

using std::cin;
using std::cout;
using std::endl;

int main(){
	int userInput;
	cout << "1. Quadratic Root\n2. Grade Calculator\n3. Credit Card Validator" << endl;
	try{
		cin >> userInput;
	}
	catch(int e){
		cout << "Please enter an int between 1 and 3" << endl;
		return 1;
	}

	if(userInput > 3 || userInput < 1){
		cout << "Please enter an int between 1 and 3" << endl;
		return 1;
	}

	if(userInput == 1){
		QuadraticRoot();
	}
	if(userInput == 2){
		GradeCalculator();
	}
	if(userInput == 3){
		CreditCardValidator();
	}

	return 0;

}