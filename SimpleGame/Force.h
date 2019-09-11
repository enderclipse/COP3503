//
// Created by JOSHUA HADDAD on 2019-04-11.
//
#pragma once

#include "Vec2.h"

class Force {
    Vec2 force_;

public:
    Force(Vec2 force_);
    void SetPosition(Vec2* position);
    void SetOrientation(float degrees);
    Vec2 GetForceVector();
    static Force Gravity(float mass_one, float mass_two, Vec2 position_one, Vec2 position_two);
    static Force Electrical(float charge_one, float charge_two, Vec2 position_one, Vec2 position_two);
    static Force Drag(Vec2& velocity, float area, float coeffcient);
    float GetAngle();
    float GetMagnitude();

};


