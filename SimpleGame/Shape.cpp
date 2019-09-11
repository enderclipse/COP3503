//
// Created by JOSHUA HADDAD on 2019-04-10.
//

#include "Shape.h"

Circle::Circle(float radius, Material material) {
    radius_ = radius;
    material_ = material;
    UpdateMassInfo();

}

float Circle::GetArea() {
    return (float) M_PI * radius_ * radius_;
}

string Circle::GetType() {
    return "Circle";
}

Rectangle::Rectangle(float length, float height, Material material) {
    length_ = length;
    height_ = height;
    material_ = material;
    UpdateMassInfo();

}

float Rectangle::GetArea() {
    return length_*height_;
}

string Rectangle::GetType() {
    return "Square";
}

void ShapeBody::UpdateMassInfo() {
    mass_information_.mass_ = material_.GetDensity() * GetArea();
    mass_information_.inv_mass_ = 1/mass_information_.mass_;
    mass_information_.inertia_ = 0;
    mass_information_.inv_inertia_ = 0;
}

void ShapeBody::SetMaterial(Material material) {
    material_ = material;
    UpdateMassInfo();
}

float ShapeBody::GetMass() {
    return mass_information_.mass_;
}

float ShapeBody::GetInvMass() {
    return mass_information_.inv_mass_;
}

float ShapeBody::GetInertia() {
    return mass_information_.inertia_;
}

float ShapeBody::GetInvInertia() {
    return mass_information_.inv_inertia_;
}

void ShapeBody::SetMass(float value) {
    material_.SetDensity(value);
    UpdateMassInfo();
}

