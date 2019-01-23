#include "Vehicle.hpp"
#include "Wheel.hpp"
#include <iostream>

int main(){
    Wheel plainWheel;

    Chassis plainChassis("medium"); //Works as intended

    Vehicle firstCar(plainChassis); //Works as intended

    cout << plainChassis.quality;
    cout << plainChassis.getSize();


}