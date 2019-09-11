#include <iostream>
#include "SimulationDriver.h"

int main() {
    SimulationDriver testSim;
    Creature testCreature;
    testCreature.SetLocation(0,0);
    testSim.AddCreature(testCreature);

    testSim.PrintWorld();

    testSim.IterateWorld(6);
    cout << endl;
    testSim.PrintWorld();
    return 0;
}