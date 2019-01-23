#include "Chassis.hpp"

//Default constructor for the Chassis as defined by the spec
Chassis::Chassis(){
	size = (string) "medium";
	quality = (string) "fair";
	numWheelsNeeded = 4;
}

//Chassis constructor for defining both a size and quality for the vehicle
Chassis::Chassis(string _size, string _quality){
	size = _size;
	quality = _quality;
	if(size == "small")
		numWheelsNeeded = 3;
	else if(size == "medium"){
		numWheelsNeeded = 4;
	}
	else if(size == "large"){
		numWheelsNeeded = 6;
	}
}

//Chassis constructor for size specified only.
Chassis::Chassis(string _size){
	size = _size;
	quality = "fair";
	if(_size == "small")
		numWheelsNeeded = 3;
	else if(_size == "medium"){
		numWheelsNeeded = 4;
	}
	else if(_size == "large"){
		numWheelsNeeded = 6;

	}
}

//Accessors
signed int Chassis::getNumWheels(){
	return this -> numWheelsNeeded;
}
string Chassis::getSize(){
   return this -> size;   
}

string Chassis::getQualityString(){
   return this -> quality;
}

//Multiplier for the price calculation
int Chassis::getQuality(){
	if(quality == "poor"){
		return 5;
	}
	else if(quality == "fair"){
		return 8;
	}
	else if(quality == "good"){
		return 12;
	}
	return 1;
}