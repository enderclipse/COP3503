//
// Created by JOSHUA HADDAD on 2019-04-11.
//

#include "Force.h"
#include <iostream>

using namespace std;

const float G = 6.67408 * pow(10, -11);
const float K = 8.99 * pow(10, 7);

Force::Force(Vec2 force) {
    force_.SetX(force.GetX());
    force_.SetY(force.GetY());

}

Vec2 Force::GetForceVector() {
    return force_;
}

Force Force::Gravity(float mass_one, float mass_two, Vec2 position_one, Vec2 position_two) {

    float r = pow(Vec2::Distance(position_one, position_two),2);

    if(mass_two == mass_one || r == 0)
        return {Vec2(0,0)};

    float magnitude = mass_one*mass_two*G/r;
    Vec2 direction = position_one.Direction(position_two);
    Vec2 force = direction * magnitude;

    return {force};
}

Force Force::Drag(Vec2& velocity, float area, float coefficient) {
    float drag = coefficient*pow(velocity.GetMagnitude(),2)*area/2;
    Vec2 direction = velocity * -1;
    return {direction*drag};
}

//This function is kind of wonky, the quadrants weren't working out how I thought they should
float Force::GetAngle() {
    float x = force_.GetX();
    float y = force_.GetY();
    if(x == 0 && y > 0)
        return 90;
    else if (x == 0 && y < 0)
        return 270;
    else if (y == 0 && x > 0)
        return 0;
    else if (y == 0 && x < 0)
        return 180;

    //In the second quadrant
    if(x < 0 && y < 0){
        return atan(y/x)*180/M_PI + 180;
    }

    //In the third quadrant
    if(x < 0 && y > 0){
        return 180+atan(y/x)*180/M_PI;
    }

    //In the first quadrant
    if(x > 0 && y < 0){
        return  -abs(atan(y/x)*180/M_PI);
    }

    //In the fourth
    if(x > 0 && y > 0){
        return atan(y/x)*180/M_PI;
    }
}

float Force::GetMagnitude() {
    return force_.GetMagnitude();
}

Force Force::Electrical(float charge_one, float charge_two, Vec2 position_one, Vec2 position_two) {
    float r = pow(Vec2::Distance(position_one, position_two),2);

    if(charge_one == charge_two || r == 0)
        return {Vec2(0,0)};

    float magnitude = charge_one*charge_two*K/r;
    Vec2 direction = position_one.Direction(position_two);
    Vec2 force = direction * magnitude;

    return {force};
}
