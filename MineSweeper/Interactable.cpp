//
// Created by JOSHUA HADDAD on 2019-04-03.
//

#include "Interactable.h"

//Interactables will handle all the sprite loading

//Set the texture, sprite, if bomb, if revealed, if flagged, and number of mines around Interactable to 0
Interactable::Interactable(Texture _texture) {
    texture_ = _texture;
    texture_.setSmooth(true);
    sprite_.setTexture(texture_);
    is_bomb_ = false;
    is_revealed_ = false;
    is_flagged_ = false;
    number_adjacent_mines_ = 0;
}

//Getters
Sprite Interactable::GetSprite() {
    return sprite_;
}

int Interactable::GetMineCount() {
    return number_adjacent_mines_;
}

bool Interactable::CheckForMine() {
    return is_bomb_;
}

bool Interactable::CheckForReveal() {
    return is_revealed_;
}

bool Interactable::IsFlagged() {
    return is_flagged_;
}


//Setters
void Interactable::SetPosition(float x, float y) {
    sprite_.setPosition(x,y);
}

void Interactable::SetTexture(Texture* _texture){
    texture_ = *_texture;
}


void Interactable::SetReveal(bool condition){
    is_revealed_ = condition;
}

void Interactable::SetMine(bool bomb){
    is_bomb_ = bomb;
}

//Sets the rectangle of the digits.png texture to the number provided 0-9, 10 is -.
void Interactable::ShiftDigits(int number) {
    sprite_.setTextureRect(IntRect(number*21,0,21,32));
}

//Adds a pointer to an adjacent tile
void Interactable::SetAdjacent(Interactable* adjacent) {
    adjacent_tiles_.push_back(adjacent);
}

void Interactable::IncrementMineCount() {
    number_adjacent_mines_++;
}

void Interactable::Flag() {
    is_flagged_ = !is_flagged_;
}


//Reveals all spaces which have no adjacent mines recursively
void Interactable::RecursiveReveal(int& number_of_mines) {

    //Set reveal to true
    is_revealed_ = true;

    //Check if the tile being recursively revealed has flag, if so remove it and increment number of mines
    if(is_flagged_){
        is_flagged_ = false;
        number_of_mines++;
    }

    //For each adjacent tile, recursive reveal the ones which have 0 adjacent mines and are not revealed
    for(Interactable* adjacent : adjacent_tiles_){

        //If adjacent mine is nullptr (edges) do move to next
        if(adjacent == nullptr){
            continue;
        }

        //If adjacent tile has no mines and is not already revelead, recursive reveal it
        if(adjacent->number_adjacent_mines_ == 0 && !adjacent->is_revealed_){
            adjacent->RecursiveReveal(number_of_mines);
        }

        //If adjacent tile has mines near it and is flagged, remove the flag and increment the mine count
        if(adjacent->number_adjacent_mines_ != 0 && adjacent->IsFlagged()){
            number_of_mines++;
            adjacent->Flag();
        }

        //Reveal the adjacent mine and set it to have no flag
        adjacent->is_flagged_ = false;
        adjacent->is_revealed_ = true;

    }
}




