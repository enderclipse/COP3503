//
// Created by JOSHUA HADDAD on 2019-05-06.
//

#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <cmath>

using std::vector;
using std::string;
using std::map;
using std::cout;
using std::endl;

struct Gene {

    //Used to calculate how the trait will be passed on.
    float dominance_;

    //Gene traits
    float health_modifier_;
    float speed_modifier_;
    float energy_modifier_;

    //Gene identification;
    string identifier_;

    //Mixing
    static Gene MixGene(Gene&, Gene&);
    static float CalculateModifier(float, float, float, float);
};
class Creature {

    string name_;

    map<string,Gene> genes_;

    float health_;
    float speed_;
    float energy_;
    float strength_;
    float dexterity_;

    int x_;
    int y_;

public:
    Creature();
    Creature(int health, int speed, int energy);

    //Setters
    void SetLocation(int x, int y);
    void SetX(int x);
    void SetY(int y);


    //Getters
    int GetX();
    int GetY();
    bool CheckLocation(int x, int y);

    //Functionality
    Creature Reproduce(Creature&);
    void Move(int x, int y);
    void AddGene(string, Gene&);
    void Fight(Creature&);
    void Eat(float);
    bool CheckDeath();


    //Debugging and Display
    void PrintCreature();



};



