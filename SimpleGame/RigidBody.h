//
// Created by JOSHUA HADDAD on 2019-04-10.
//

#pragma once
#include "Shape.h"
#include "Vec2.h"
#include "Force.h"
#include <vector>

using std::vector;


class RigidBody {
public:
    ShapeBody* shape_;

    //Forces
    vector<Force> forces_;
    Vec2 net_force_;

    //Linear
    Vec2 position_;
    Vec2 velocity_;
    Vec2 acceleration_;

    //Angular
    float orientation_;
    float angular_velocity_;
    float torque_;

public:
    explicit RigidBody(ShapeBody* shape);
    RigidBody() = default;
    void UpdatePhysics(float dt);

    //Forces
    vector<Force> GetForces();
    void CalculateNetForce();
    void AddForce(Force& force);
    void AddDrag(float scale_factor);
    void AddGravitational(RigidBody& partner);

    //Setters
    void SetX(float x);
    void SetY(float y);
    void SetVelocity(float x, float y);
    void SetAcceleration(Vec2 a);
    void SetOrientation(float radians);
    void SetAngularVelocity(float omega);
    void SetTorque(float torque);

    Vec2 GetPosition();
    Vec2* GetPositionPointer();
    ShapeBody* GetShape();
    Vec2 GetVelocity();
};

class ChargedBody : public RigidBody{
    ChargedBody(ShapeBody* shape, float charge);
    float charge_;

    //Forces
    void AddElectrical(ChargedBody& partner);
};

