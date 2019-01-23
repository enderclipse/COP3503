#include <iostream>

//Defining useful function shortcuts
using std::cout;
using std::cin;
using std::endl;

//Defining all prototypes for defining
bool isValid(long number);
int sumOfDoubleEvenPlace(long number);
int getDigit(int number);
int sumOfOddPlace(long number);
bool prefixMatched(long number, int digit);
int getSize(long number);
long getPrefix(long number, int numDigits);

int main(){

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