//
// Created by JOSHUA HADDAD on 2019-04-17.
//

#include "Collision.h"

bool Collision::CheckCollision(const FloatRect &body_one, const FloatRect &body_two) {
    return body_one.intersects(body_two);
}

bool Collision::CheckCollisionPerfect(const FloatRect &body_one, const FloatRect &body_two) {
    return false;
}
