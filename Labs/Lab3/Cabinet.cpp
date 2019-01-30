#include "Cabinet.h"
#include <iomanip>
#include <ostream>

//Destructor
Cabinet::~Cabinet(){
 	delete[] containedShelves;
 	containedShelves = nullptr;
   }

//Constructors
Cabinet::Cabinet(string _name, int numberShelves){
	name = _name;
	maxShelves = numberShelves;
	currentShelves = 0;
	containedShelves = new Shelf[numberShelves];
}

Cabinet::Cabinet(){

}

//Copy constructor
Cabinet::Cabinet(const Cabinet &original){
	name = original.name;
	maxShelves = original.maxShelves;
	
	//Deep copy of containedShelves
	containedShelves = new Shelf[maxShelves];
	if(containedShelves != nullptr){
	   delete[] containedShelves;
	   for(int i = 0; i < currentShelves; i++){
	      containedShelves[i] = original.containedShelves[i];
	  }
	}
}

//Copy assignment operator
Cabinet & Cabinet::operator = (const Cabinet& original){
   name = original.name;
	maxShelves = original.maxShelves;
	currentShelves = original.currentShelves;
	
	//Deep copy of containedShelves[]
	containedShelves = new Shelf[maxShelves]; 
	if(containedShelves != nullptr){
	   containedShelves = new Shelf[maxShelves];
	   for(int i = 0; i < currentShelves; i++){
	      containedShelves[i] = original.containedShelves[i];
	  }
	}
    return *this;
}

//Adding a shelf object to a current Cabinet
void Cabinet::AddShelf(Shelf *shelfObj){
	containedShelves[currentShelves] = *shelfObj;
	currentShelves++;
}

//Printing the inventory of a shelf in a specified format
void Cabinet::ShowInventory(){
   cout << "Inventory of " << name << endl;
   for(int i = 0; i < currentShelves; i++){
      containedShelves[i].ShowInventory();
   }
   cout << fixed << setprecision(2) << "Average price of food: $" << GetAveragePrice();
}

//Calculate the avg price of all items in the Cabinet
float Cabinet::GetAveragePrice(){
	int numberItems = 0;
	float price = 0;
	
	//For each shelf in the cabinet, get the price of each Food object then
	//increment the numberItems, then divide the total price by numItems
	for(signed int i = 0; i < currentShelves; i++){
		const Food *items = containedShelves[i].GetFoodList();
		for(unsigned int j = 0; j < containedShelves[i].GetCount(); j++){
			price += items[j].getPrice();
			numberItems++;
		}
	}
	float avgPrice = price/numberItems;
	return avgPrice;
}