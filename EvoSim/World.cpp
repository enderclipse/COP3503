//
// Created by JOSHUA HADDAD on 2019-05-06.
//

#include "World.h"

World::World() {
    length_ = 50;
    height_ = 50;

    for(int i = 0; i < length_; i++){
        for(int j = 0; j < height_; j++){
            Point point = Point(i,j);
            int food = rand() % 10;

            //Make half the points contain no food
            if(food <= 5)
                food = 0;
            else{
                food %= 5;
            }

            world_tiles_.emplace(point, food);
        }
    }
}

World::World(int length, int height) {
    length_ = length;
    height_ = height;

    //For each x and y coordinate in the grid system
    for(int i = 0; i < length; i++){
        for(int j = 0; j < height; j++){
            Point point = Point(i,j);
            int food = rand() % 10;

            //Make half the points contain no food
            if(food <= 5)
                food = 0;
            else{
                food %= 5;
            }

            world_tiles_.emplace(point, food);
        }
    }
}

int World::GetFood(Point& p) {
    return world_tiles_[p];
}

int World::GetLength() {
    return length_;
}

int World::GetHeight() {
    return height_;
}

Point::Point(int x, int y) {
    x_ = x;
    y_ = y;
}

bool Point::operator<(const Point &p2) const {
    if (x_ != p2.x_) {
        return x_ < p2.x_;
    } else {
        return y_ < p2.y_;
    }
}
