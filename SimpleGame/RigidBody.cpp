//
// Created by JOSHUA HADDAD on 2019-04-10.
//
#include "RigidBody.h"

RigidBody::RigidBody(ShapeBody* shape) {

    vector<Force> all_forces_;
    net_force_ = Vec2();

    shape_ = shape;
    position_ = Vec2();

    velocity_ = Vec2();
    acceleration_ = Vec2();

    orientation_ = 0;
    angular_velocity_ = 0;
    torque_ = 0;


}

void RigidBody::UpdatePhysics(float dt) {
    //Calculate position
    float max_speed = 100;

    //Calculate new acceleration and velocity
    CalculateNetForce();
    Vec2 force = net_force_*shape_->GetInvMass();
    acceleration_ += force;
    velocity_ += acceleration_*(dt*100);
    position_ += velocity_*(dt*5);

    if(abs(velocity_.GetX()) > max_speed){
        velocity_.GetX() > 0 ? velocity_.SetX(max_speed) : velocity_.SetX(-max_speed);
    }
    if(abs(velocity_.GetY()) > max_speed){
        velocity_.GetY() > 0 ? velocity_.SetY(max_speed) : velocity_.SetY(-max_speed);
    }


    //Calculate rotation

    //Set force = 0 and acceleration to 0;
    forces_.clear();
    net_force_.Reset(0,0);
    acceleration_.Reset(0,0);
}

void RigidBody::SetVelocity(float x, float y) {
    velocity_.Reset(x,y);
}

void RigidBody::SetAcceleration(Vec2 a) {
    acceleration_.Reset(a.GetX(), a.GetY());
}

void RigidBody::SetOrientation(float radians) {
    orientation_ = radians;
}

void RigidBody::SetAngularVelocity(float omega) {
    angular_velocity_ = omega;
}

void RigidBody::SetTorque(float torque) {
    torque_ = torque;
}

void RigidBody::AddForce(Force& force) {
    forces_.push_back(force);
}

Vec2 RigidBody::GetPosition() {
    return position_;
}

void RigidBody::AddDrag(float scale_factor) {
    Force drag_force = Force::Drag(velocity_, shape_->GetArea(), scale_factor);
    AddForce(drag_force);

}

void RigidBody::SetX(float x) {
    position_.SetX(x);
}

void RigidBody::SetY(float y) {
    position_.SetY(y);
}

void RigidBody::AddGravitational(RigidBody& partner) {
    Force gravity = Force::Gravity(shape_->GetMass(), partner.shape_->GetMass(), position_, partner.GetPosition());
    AddForce(gravity);
}

ShapeBody *RigidBody::GetShape() {
    return shape_;
}

Vec2* RigidBody::GetPositionPointer() {
    Vec2* ptr = &position_;
    return ptr;
}

void RigidBody::CalculateNetForce() {
    for(Force force : forces_){
        net_force_ += force.GetForceVector();
    }
}

vector<Force> RigidBody::GetForces() {
    return forces_;
}

Vec2 RigidBody::GetVelocity() {
    return velocity_;
}

void ChargedBody::AddElectrical(ChargedBody& partner) {
    Force electrical = Force::Electrical(charge_, partner.charge_, position_, partner.GetPosition());
    AddForce(electrical);
}

ChargedBody::ChargedBody(ShapeBody *shape, float charge) : RigidBody(shape) {
    charge_ = charge;
}
