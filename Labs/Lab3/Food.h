#include <iostream>
#include <iomanip>
#pragma once

using namespace std;

class Food{
private:
	string type;
	string name;
	int expYear;
	float price;
	int calories;
public:
	Food(string, string, int, float, int);
	Food();
	void Display() const;
	string getYearTypeName() const;
	float getPrice() const;
};