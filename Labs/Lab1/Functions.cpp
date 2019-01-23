#include <iostream>
#include "Functions.hpp"

using std::cin;
using std::cout;
using std::endl;

//int main(){
	//return 0;
//}

void QuadraticRoot(){
	//Defining variables needed
    double a;
    double b;
    double c;

    //Prompting for and gathering input
    cout << "Enter a, b, c: ";
    cin >> a >> b >> c;

    //Calculating discriminate
    double discrim = b*b - 4*a*c;

    //If discrim is less than 0
    if(discrim < 0){
        cout << "The equation has no real roots." << endl;
    }

    //If discrim is greater than 0
    else if (discrim > 0){
        double r1 = (-b + sqrt(discrim))/(2*a);
        double r2 = (-b - sqrt(discrim))/(2*a);
        cout << "The equation has two roots: " << r1 << " and " << r2 << endl;
    }

    //If discrim is 0
    else{
        double r = -b/(2*a);
        cout << "The equation has one root: " << r << endl;
    }
}

void GradeCalculator(){
	//Needed variables
    int num;

    //Prompting for and storing input for number of students
    cout << "Enter the number of students: ";
    cin >> num;
    int scores[num];
    char grades[num];

    //Prompting for input of scores
    cout << "Enter " << num << " scores: ";

    int best = -1;

    //Finding the best score
    for (int i = 0; i < num; i++){
        cin >> scores[i];
        if(best < scores[i]){
            best = scores[i];
        }
    }

    //Assigning grades to each student
    for(int i = 0; i < num; i++){
        for(int i=0;i<num;i++) {
			if (scores[i] >= best - 10)
				grades[i] = 'A';
			else if (scores[i] >= best - 20)
				grades[i] = 'B';
			else if (scores[i] >= best - 30)
				grades[i] = 'C';
			else if (scores[i] >= best - 40)
				grades[i] = 'D';
			else grades[i] = 'F';
    }

        //Printing the students information
        cout << "Student " << i+1 << " - Score: " << scores[i] 
            << ", Letter: " << grades[i] << endl;
    }
}

void CreditCardValidator(){
	//Prompting for credit card number and taking it
    cout << "Enter a credit card number: ";
    long number;
    cin >> number;

    //I think this was a mistake in the source java code?
    cout << number << " is ";

    //Checking number and printing the corresponding 
    if(isValid(number))
        cout << "Credit card number is valid." << endl;
    else
        cout << "Credit card number is invalid." << endl;
}

bool isValid(long number){

    //Getting size of number
    int numSize = getSize(number);

    //Checking if number is of valid size
    if(numSize > 16 || numSize < 13) 
        return false;

    //Computing the sume of the even and odd places
    int sum = sumOfDoubleEvenPlace(number) + sumOfOddPlace(number);

    //Checking if prefixes are valid
    if(prefixMatched(number, 4)) 
        return true;
	if(prefixMatched(number, 5)) 
        return true;
	if(prefixMatched(number, 37)) 
        return true;
	if(prefixMatched(number, 6)) 
        return true;

    //Not valid
    return false;

}
int sumOfDoubleEvenPlace(long number){
    int sum = 0;
		
        //While loop to sum the even places.  Basically just a copy/paste from the java
		while(number > 0)
		{
			int digit = (int) ((number % 100) / 10);
			number /= 100;
			
			sum += getDigit(2 * digit);
		}
		
		return sum;
}

int getDigit(int number){

    //Basically just a copy/paste from the java
    return (number / 10) + (number % 10);
}
int sumOfOddPlace(long number){
    int sum = 0;

		//Basically just a copy/paste from the java
		while(number > 0)
		{
			int digit = (int) (number % 10);
			number /= 100;
			
			sum += getDigit(digit);
		}
		
		return sum;
}
bool prefixMatched(long number, int digit){
    //Basically just a copy/paste from the java
    return getPrefix(number, getSize(digit)) == digit;
}
int getSize(long number){
    //Basically just a copy/paste from the java
    int digitCount = 0;
		
		while(number > 0)
		{
			number /= 10;
			digitCount++;
		}
		
		return digitCount;
}
long getPrefix(long number, int numDigits){
    //Basically just a copy/paste from the java
    int numberSize = getSize(number);
		
		int decimalMovements = numberSize - numDigits;
		
		while(decimalMovements-- > 0)
		{
			number /= 10;
		}
		
		return number;
}