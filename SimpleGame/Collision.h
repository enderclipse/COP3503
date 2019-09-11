//
// Created by JOSHUA HADDAD on 2019-04-17.
//

#pragma once

#include "Graphics.h"


class Collision {
public:
    static bool CheckCollision(const FloatRect& body_one, const FloatRect& body_two);
    static bool CheckCollisionPerfect(const FloatRect& body_one, const FloatRect& body_two);
};