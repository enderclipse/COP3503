#include <iostream>
#pragma once
using std::string;

class Wheel{
   private:
      float mileage;
      string condition;
   public:
      Wheel();
      Wheel(string);
      float getMileage();
      float getMultiplier();
      string getCondition();
      void setMileage(int);
};