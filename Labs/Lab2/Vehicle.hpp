#include <iostream>
#include <vector>
#include <iomanip>
#include "Chassis.hpp"
#include "Wheel.hpp"

#pragma once

using std::cout;
using std::vector;
using std::endl;

class Vehicle{
private:
   float price;
   vector<Wheel> wheels;
   bool drivable;
public:
   Chassis chassis;
   Vehicle(Chassis);
   void addWheel(Wheel);
   void Display();
   bool isBuilt();
   void setPrice();
   void Drive(int);
   Chassis getChassis();
};