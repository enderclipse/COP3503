//
// Created by JOSHUA HADDAD on 2019-05-06.
//

#include "SimulationDriver.h"

void SimulationDriver::SetWorld(int length, int width) {
    world_ = World(length, width);
}

void SimulationDriver::AddCreature(Creature& creature) {
    creatures_.push_back(creature);
    number_of_creatures_++;
}

//TODO Refactor to use a map of points to creatures
void SimulationDriver::IterateWorld(int number_iterations) {

    while(number_iterations != -1){
        for(int i = 0; i < number_of_creatures_; i++){
            Creature& entity = creatures_.at(i);
            int x_direction = 1;
            int y_direction = 1;
            entity.Move(x_direction, y_direction);

            //Move the creature
            if(entity.GetX() > world_.GetLength())
                entity.SetX(world_.GetLength());

            else if(entity.GetX() < 0)
                entity.SetX(0);

            if(entity.GetY() > world_.GetHeight())
                entity.SetY(world_.GetHeight());

            else if(entity.GetY() < 0)
                entity.SetY(0);

            //Eat if possible

            //Check for other creatures and fight if other creature is on tile


        }

        number_iterations--;
    }
}

void SimulationDriver::PrintWorld() {
    for(int i = 0; i < world_.GetHeight(); i++){
        for(int j = 0; j < world_.GetLength(); j++){
            Point space = Point(j,i);
            for(Creature creature : creatures_){
                if(creature.CheckLocation(j,i)) {
                    cout << "C";
                    continue;
                }
            }

            if(world_.GetFood(space) == 0)
                cout << "-";
            else {
                cout << world_.GetFood(space);
            }
        }
        cout << endl;
    }
}
