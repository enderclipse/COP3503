//
// Created by JOSHUA HADDAD on 2019-04-10.
//

#pragma once


class Material {
    float density_;
    float restitution_;

public:
    Material();
    Material(float, float);
    float GetDensity();
    float GetRestitution();
    void SetDensity(float density);

};


