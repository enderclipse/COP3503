//
// Created by JOSHUA HADDAD on 2019-04-10.
//

#include "Vec2.h"

Vec2::Vec2() {
    x_ = 0;
    y_ = 0;
    magnitude_ = 0;
    xDir_ = 0;
    yDir_ = 0;
}

Vec2::Vec2(float x, float y) {
    x_ = x;
    y_ = y;
    magnitude_ = sqrt(x*x+y*y);

    if(magnitude_ == 0){
        xDir_ = 0;
        yDir_ = 0;
    }
    else{
        xDir_ = (x/magnitude_);
        yDir_ = (y/magnitude_);
    }
}

bool Vec2::operator==(const Vec2 &rhs) {
    return(xDir_ == rhs.xDir_ && yDir_ == rhs.yDir_);
}

Vec2 Vec2::operator+(const Vec2 &rhs) {
    return Vec2(x_ + rhs.x_, y_ + rhs.y_);
}

Vec2 Vec2::operator-(const Vec2 &rhs) {
    return Vec2(x_ - rhs.x_, y_ - rhs.y_);
}

float Vec2::Cross(const Vec2 &rhs) {
    return (x_ * rhs.y_ - y_ * rhs.x_);
}

float Vec2::Dot(const Vec2 &rhs) {
    return (x_ * rhs.x_ + y_ * rhs.y_);
}

Vec2 Vec2::Cross(const Vec2 &lhs, float rhs) {
    return Vec2(rhs * lhs.y_, -rhs * lhs.x_);
}

Vec2 Vec2::Cross(float lhs, const Vec2 &rhs) {
    return Vec2(-lhs * rhs.y_, lhs * rhs.x_);
}

Vec2 Vec2::operator=(const Vec2 &rhs) {
    return Vec2(rhs.x_, rhs.y_);
}

void Vec2::operator+=(const Vec2 &rhs) {
    x_ += rhs.x_;
    y_ += rhs.y_;
    magnitude_ = sqrt(x_*x_+y_*y_);

    if(magnitude_ == 0){
        xDir_ = 0;
        yDir_ = 0;
    } else {
        xDir_ = x_/magnitude_;
        yDir_ = y_/magnitude_;
    }
}

Vec2 Vec2::operator*(float scalar) const{
    return Vec2(x_*scalar, y_*scalar);
}

float Vec2::GetX() const{
    return x_;
}

float Vec2::GetY() const{
    return y_;
}

float Vec2::GetMagnitude(){
    return magnitude_;
}

float Vec2::GetXDir(){
    return((x_ >= 0) ?  xDir_ : -xDir_);
}

float Vec2:: GetYDir(){
    return((y_ >= 0) ?  yDir_ : -yDir_);
}

void Vec2::Reset(float x, float y) {
    x_ = x;
    y_ = y;
    magnitude_ = sqrt(x*x+y*y);
    xDir_ = 0;
    yDir_ = 0;
    if(magnitude_ != 0){
        xDir_ = (x/magnitude_);
        yDir_ = (y/magnitude_);
    }
}

void Vec2::SetY(float y) {
    Reset(x_, y);
}

void Vec2::SetX(float x) {
    Reset(x, y_);
}

Vec2 Vec2::Direction(Vec2 &partner) {
    float x = partner.x_ - x_;
    float y = partner.y_ - y_;
    float mag = sqrt(x*x+y*y);
    return Vec2(x/mag, y/mag);
}

float Vec2::Distance(const Vec2 &pos_one, const Vec2& pos_two) {
    return sqrt(pow((pos_one.GetX()-pos_two.GetX()),2) + pow((pos_one.GetY()-pos_two.GetY()),2));
}




