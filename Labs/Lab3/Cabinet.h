#include <iostream>
#include "Shelf.h"

using namespace std;

class Cabinet{
private:
	string name;
	Shelf *containedShelves;
	int maxShelves;
	int currentShelves;
public:
	~Cabinet();
	Cabinet();
	Cabinet & operator = (const Cabinet &original); 
	Cabinet(string, int);
	Cabinet(const Cabinet&);
	void AddShelf(Shelf*);
	float GetAveragePrice();
	void ShowInventory();
};