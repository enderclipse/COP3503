#include "Vehicle.hpp"

//Constructor for the vehicle, defines the price based on the chassis quality
Vehicle::Vehicle(Chassis _chassis){
	chassis = _chassis;
	drivable = false;
	price = 500 * _chassis.getQuality();
}

//Method to add a wheel to the car.  Checks if the max number of wheels are already added, if not adds and adjusts price
void Vehicle::addWheel(Wheel wheel){
   
   //Checking if the max wheels are added.  (signed int) because wheels.size() is unsigned and getNumWheels() returns signed int
	if(chassis.getNumWheels() != (signed int) wheels.size()){
		wheels.push_back(wheel);
		price *= wheel.getMultiplier();
	}
	
	//Max # of wheels added
	else{
		cout << "You’ve already added all the wheels!";
	}
}

//Method to display all information about the car
void Vehicle::Display(){
   
   //Vehicle Block
	cout << "Vehicle:\n\t";
	//Setting decimal precision
	std::cout << std::setprecision(1) << std::fixed;
	cout << "Price: " << price << "\n";

   //Chassis Block
	cout << "Chassis:\n\t";
	cout << "Size: " << chassis.getSize() << "\n\t";
	cout << "Quality: " << chassis.getQualityString() << "\n\t";
	cout << "Number of Wheels: " << wheels.size() << "\n";

   //Iterative printing of all the wheels with their info.
	for(unsigned int i = 0; i < wheels.size(); i++){
		cout << "Wheel " << i+1 << ":\n\t";
		cout << "Mileage Left: " << wheels[i].getMileage() << "\n\t";
		cout << "Condition: " << wheels[i].getCondition();
		if(i+1 < wheels.size())
		   cout << "\n";
		else{
		   cout << endl;
	   }
   }
   cout << endl;
}

//Checks if the Vehicle has all it's wheels.  No need to check Chassis as vehicle constructor requires a chassis
bool Vehicle::isBuilt(){
	if(chassis.getNumWheels() == (signed int) wheels.size())
		return true;
	else{
		return false;
	}
}

//Readjust method for the price for after driving.  Recalculates quality based on new tire price
void Vehicle::setPrice(){
	price = 500.0 * chassis.getQuality();
	for(unsigned int i = 0; i < wheels.size(); i++){
		price *= wheels[i].getMultiplier();
	}
}

//Drives the car an int # of miles (spec said int not float), if not drivable it does not drive, checks wheels for max mileage
//Drives based on max mileage, readjusts wheels and price.
void Vehicle::Drive(int miles){
   
   //Need more wheels!
	if(isBuilt() == false){
		cout << "Vehicle not built. Literally un-drivable" << endl;
	}
	
	//Car is drivable
	else {
	   
	   //Looking for the worst wheel as the limiting factor for mileage
		int indexWorstWheel = 0;
		for(unsigned int i = 0; i < wheels.size(); i++){
			if(wheels[i].getMileage() < wheels[indexWorstWheel].getMileage())
				indexWorstWheel = i;
		}
		
		//Setting max mileage based on which wheel has the least potential
		int maxMileage = wheels[indexWorstWheel].getMileage();
		
		//If the user wants to drive further than the max mileage the car breaks down and only travels the max mileage
		if(miles > maxMileage){
			cout << "Broke down! ";
		   std::cout << std::setprecision(1) << std::fixed;
			cout << "You've traveled " << (float)maxMileage << " miles!\n" << endl;
			for(unsigned int i = 0; i < wheels.size(); i++){
				wheels[i].setMileage(maxMileage);
			}
		}
		
		//If the miles driven is greater than the max mileage, the user drives that far.
		else{
		   std::cout << std::setprecision(1) << std::fixed;
			cout << "You've traveled " << (float) miles << " miles!\n" << endl;
			for(unsigned int i = 0; i < wheels.size(); i++){
				wheels[i].setMileage(miles);
		   }
		}
		
		//After driving, adjust price
		this -> setPrice();
	}
}

//Getter method for the chassis in the current vehicle.
Chassis Vehicle::getChassis(){
	return this -> chassis;
}