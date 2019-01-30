#include <iostream>
#include "Food.h"
#pragma once

using namespace std;

class Shelf{
private:
	string name;
	Food *containedFood;
	int maxCapacity;
	int numberOfItems;
public:
   ~Shelf();
	Shelf(string, int);
	Shelf();
	Shelf(const Shelf&);
	Shelf & operator = (const Shelf &original);
	void AddFood(const Food *f);
	void ShowInventory() const;
	const Food* GetFoodList() const;
	unsigned int GetCapacity() const;
	unsigned int GetCount() const;
	const string GetName() const;

};