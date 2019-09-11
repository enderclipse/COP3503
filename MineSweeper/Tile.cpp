//
// Created by JOSHUA HADDAD on 2019-04-02.
//

#include "Tile.h"

//Set tile as not a mine
Tile::Tile() {
    is_mine_ = false;
}

//Set tile as a mine based on if true or false is passed
Tile::Tile(bool bomb) {
    is_mine_ = bomb;
}

//Getter and setter for mines
void Tile::SetMine() {
    is_mine_ = true;
}

bool Tile::CheckMine() {
    return is_mine_;
}


