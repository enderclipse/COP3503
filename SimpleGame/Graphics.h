#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Vec2.h"

using namespace std;
using namespace sf;

#pragma once

class Graphics {
public:
    Sprite sprite_;
    Texture texture_;

public:
    Graphics(Texture texture);
    Graphics(Texture* tex);
    void SetPosition(Vec2 pos);
    Sprite* GetSprite();
    void SetOrientation(float angle);
    void SetOrigin(Vec2);
    void SetScale(float x, float y);
    void Scale(float factor);
};



