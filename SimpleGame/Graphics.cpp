//
// Created by JOSHUA HADDAD on 2019-04-10.
//

#include "Graphics.h"

Graphics::Graphics(Texture texture) {
    sprite_.setTexture(texture);

}

Graphics::Graphics(Texture* tex){
    sprite_.setTexture(*tex);
}

void Graphics::SetPosition(Vec2 pos) {
    sprite_.setPosition(pos.GetX(),pos.GetY());
}

Sprite* Graphics::GetSprite() {
    Sprite* ptr = &sprite_;
    return ptr;
}

void Graphics::SetOrientation(float angle) {
    sprite_.setRotation(angle);
}

void Graphics::SetOrigin(Vec2 origin){
    sprite_.setOrigin(origin.GetX(), origin.GetY());
}

void Graphics::SetScale(float x, float y) {
    sprite_.setScale(x,y);
}
