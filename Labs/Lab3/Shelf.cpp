#include "Shelf.h"

//Constructor
Shelf::Shelf(string _name, int _maxCapacity){
	name = _name;
	containedFood = new Food[_maxCapacity];
	maxCapacity = _maxCapacity;
	numberOfItems = 0;
}

Shelf::Shelf(){
	
}

//Destructor
Shelf::~Shelf(){ 
   	delete[] containedFood;
   	containedFood = nullptr;
}

//Assignment overloader
Shelf & Shelf::operator = (const Shelf& original){
	name = original.name;
	maxCapacity = original.maxCapacity;
	numberOfItems = original.numberOfItems;

   //Deep copy of containedFood
   containedFood = new Food[numberOfItems];
	if(containedFood != nullptr){
		for(int i = 0; i < original.numberOfItems; i++){
			containedFood[i] = original.containedFood[i];
		}
	}
	return *this;
}

//Copy Constructor
Shelf::Shelf(const Shelf &original){
   name = original.name;
	maxCapacity = original.maxCapacity;
	numberOfItems = original.numberOfItems;
	containedFood = original.containedFood;
	
	//Deep copy of containedFood
   if(containedFood != nullptr){
      containedFood = new Food[maxCapacity];
      for(int i = 0; i < numberOfItems; i++){
         containedFood[i] = original.containedFood[i];
         }
   }
}

//Adding a Food object to the containedFood[] in a Shelf object
void Shelf::AddFood(const Food *f){
	containedFood[numberOfItems] = *f;
	numberOfItems++;
}

//Prints formatted contents of shelf
void Shelf::ShowInventory() const{
	cout << "Food in " << "" << name << "" << endl;
	
	//Loop through containedFood[] displaying each member Food
	for(int i = 0; i < numberOfItems; i++){
		containedFood[i].Display();
	}
	
	//endl after print is complete
	cout << endl;
}


//Getters
const Food* Shelf::GetFoodList() const{
	return containedFood;
}

unsigned int Shelf::GetCapacity() const{
	return maxCapacity;
}

unsigned int Shelf::GetCount() const{
	return numberOfItems;
}

const string Shelf::GetName() const{
	return name;
}