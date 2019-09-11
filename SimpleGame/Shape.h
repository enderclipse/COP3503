//
// Created by JOSHUA HADDAD on 2019-04-10.
//

#pragma once
#include <iostream>
#include <math.h>
#include "Material.h"
#define _USE_MATH_DEFINES

using std::string;

struct MassData{
    float mass_;
    float inv_mass_;

    float inertia_;
    float inv_inertia_;

    MassData(){
        mass_ = 0;
        inv_mass_ = 0;
        inertia_ = 0;
        inv_inertia_ = 0;
    }
};

class ShapeBody {

protected:
    std::string type;
    MassData mass_information_;
    Material material_;

public:
    virtual float GetArea() = 0;
    virtual std::string GetType() = 0;
    void UpdateMassInfo();
    void SetMaterial(Material);
    void SetMass(float value);
    float GetMass();
    float GetInvMass();
    float GetInertia();
    float GetInvInertia();
};

class Circle : virtual public ShapeBody{
    float radius_;

public:
    Circle(float radius, Material material);
    float GetArea();
    string GetType();
};
class Rectangle : virtual public ShapeBody{
    float length_;
    float height_;

public:
    Rectangle(float length, float height, Material material);
    float GetArea();
    string GetType();

};


