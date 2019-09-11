//
// Created by JOSHUA HADDAD on 2019-05-06.
//

#pragma once
#include <iostream>
#include <map>

using std::map;

struct Point{
    int x_;
    int y_;

    Point(int,int);

    inline bool operator<(const Point& p2) const;
};

class World {
    map<Point, int> world_tiles_;
    int length_;
    int height_;

public:

    //Generates a 50x50 space with randomly generated food
    World();

    //Generates a specified space with randomly generated food
    World(int, int);


    //Getters
    int GetFood(Point&);
    int GetLength();
    int GetHeight();

    //Display
    void PrintWorld();
};



