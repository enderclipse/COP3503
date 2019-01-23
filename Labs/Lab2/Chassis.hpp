#include <iostream>
#pragma once
using std::string;

class Chassis{
private:
   string size;
   unsigned int numWheelsNeeded;
public:
   string quality;
   Chassis();
   Chassis(string, string);
   Chassis(string);
   signed int getNumWheels();
   string getSize();
   int getQuality();
   string getQualityString();
};