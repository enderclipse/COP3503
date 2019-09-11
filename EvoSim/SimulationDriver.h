//
// Created by JOSHUA HADDAD on 2019-05-06.
//

#pragma once
#include "Creature.h"
#include "World.h"

class SimulationDriver {

    World world_;
    vector<Point, Creature> creatures_;
    int number_of_creatures_ = 0;

public:
    void SetWorld(int length, int width);
    void AddCreature(Creature&);
    void IterateWorld(int number_iterations);
    void PrintWorld();
};


