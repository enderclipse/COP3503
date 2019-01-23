#include "Wheel.hpp"

//Default Wheel Constructor
Wheel::Wheel(){
   condition = "fair";
   mileage = 10000.0;
}

//Constructor for a wheel that is of specified condition
Wheel::Wheel(string _condition){
	condition = _condition;
	if(_condition == "poor"){
		mileage = 5000.0;
	}
	else if(_condition == "fair"){
		mileage = 10000.0;
	}
	else if(_condition == "good"){
		mileage = 20000.0;
	}
}


//Accessors
float Wheel::getMileage(){
	return this -> mileage;
}

string Wheel::getCondition(){
   return this -> condition;   
}

float Wheel::getMultiplier(){
	if(condition == "poor"){
		return 1.5;
	}
	else if(condition == "fair"){
		return 1.8;
	}
	else if(condition == "good"){
		return 2.2;
	}
	return 1;
}

//Mutators

//Sets the mielage based on how many miles are driven.  Miles left - Miles driven = new miles
void Wheel::setMileage(int milesDriven){
	this -> mileage -= milesDriven;
	if(mileage > 50000.0){
		condition = "good";
	}
	else if(mileage < 10000.0){
		condition = "poor";
	}
	else if(mileage > 20000.0 && mileage < 50000.0 ){
		condition = "fair";
	}
}