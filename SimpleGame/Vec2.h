//
// Created by JOSHUA HADDAD on 2019-04-10.
//

#pragma once
#include <math.h>

class Vec2 {
    float x_;
    float y_;
    float xDir_;
    float yDir_;
    float magnitude_;


public:
    Vec2();
    Vec2(float, float);
    bool operator== (const Vec2& rhs);
    Vec2 operator+ (const Vec2& rhs);
    Vec2 operator-(const Vec2& rhs);
    Vec2 operator=(const Vec2& rhs);
    Vec2 operator*(float scalar) const;
    void operator+=(const Vec2& rhs);
    float Cross(const Vec2& rhs);
    Vec2 Cross(const Vec2& lhs, float rhs);
    Vec2 Cross(float lhs, const Vec2& rhs);
    float Dot(const Vec2& rhs);
    float GetX() const;
    float GetY() const;
    float GetMagnitude();
    float GetXDir();
    float GetYDir();
    void Reset(float, float);
    void SetY(float y);
    void SetX(float x);
    Vec2 Direction(Vec2& partner);

    static float Distance(const Vec2& pos_one, const Vec2& pos_two);

};



