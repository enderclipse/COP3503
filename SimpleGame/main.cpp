
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Graphics.h"
#include "Shape.h"
#include "RigidBody.h"
#include "Vec2.h"
#include "Force.h"
#include "ResourceManager.h"
#include "Collision.h"
#include <cmath>

using namespace std;
using sf::RenderWindow;

int main()
{
    ResourceManager resources;
    resources.AddTexture("stars", "./assets/stars.png");
    resources.AddTexture("vector" , "./assets/vector.png");
    resources.AddTexture("box", "./assets/boxSprite.png");

    RenderWindow window(sf::VideoMode(1980, 1080), "Physics!");

    vector<Graphics> items;
    vector<RigidBody> bodies;

    //Loading space texture and scaling to fit the screen
    Texture space;
    space.loadFromFile("./assets/stars.png");
    Sprite background;
    background.setTexture(*resources.GetTexture("stars"));
    background.setScale(1,1);
    background.scale(2.1,2.2);


    //Testing force display
    vector<Graphics> force_vectors;


    int mass[10] = {1,1,1,1,21474, 100000,100000,100000,100000,100000};
    bool draw_arrows = false;
    for(unsigned int i = 0; i < 6; i++){
        auto iron = new Material(mass[i], 0.05);
        ShapeBody* shape = new Rectangle(10,10, *iron);

        shape->SetMass(mass[i]);
        RigidBody object = RigidBody(shape);
        object.position_.Reset(rand() % 1960, rand() % 1080);

        Graphics game_item = Graphics(resources.GetTexture("box"));
        game_item.GetSprite()->setScale(.5,.5);
        game_item.GetSprite()->scale(.25,.25);
        game_item.GetSprite()->setOrigin(502.0/2,502.0/2);
        game_item.GetSprite()->setPosition(rand() % 1960, rand() % 1080);

        items.push_back(game_item);
        bodies.push_back(object);
    }

    //vector_test.SetPosition(bodies.at(0)->GetPositionPointer());

    Clock clock;

    while (window.isOpen())
    {
        Time time = clock.getElapsedTime();
        float dt = time.asSeconds();
        clock.restart();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == Event::KeyReleased){
                if(event.key.code == Keyboard::Q){
                    draw_arrows = !draw_arrows;
                }
            }
        }

        //Spawn a body at the mouse location
        if(sf::Mouse::isButtonPressed(Mouse::Left)){
            Material i = Material(mass[1], 0.05);
            ShapeBody* shape = new Rectangle(10,10,i);
            shape->SetMass(mass[7]);
            RigidBody* object = new RigidBody(shape);
            object->position_.Reset(Mouse::getPosition(window).x, Mouse::getPosition(window).y);
            Graphics game_item = Graphics(resources.GetTexture("box"));
            game_item.GetSprite()->setScale(.5,.5);
            game_item.GetSprite()->scale(.25,.25);
            game_item.GetSprite()->setOrigin(502/2,502/2);
            game_item.GetSprite()->setPosition(Mouse::getPosition(window).x, Mouse::getPosition(window).y);

            items.push_back(game_item);
            bodies.push_back(*object);
        }
        if(sf::Keyboard::isKeyPressed(Keyboard::Space)){
            bodies.at(0).SetVelocity(0,0);
            bodies.at(0).SetAcceleration(Vec2(0,0));
        }
        if(sf::Keyboard::isKeyPressed(Keyboard::D)){
            bodies.at(0).SetVelocity(40,0);
        }
        if(sf::Keyboard::isKeyPressed(Keyboard::A)){
            bodies.at(0).SetVelocity(-40,0);

        }
        if(sf::Keyboard::isKeyPressed(Keyboard::S)){
            bodies.at(0).SetVelocity(0,40);
        }
        if(sf::Keyboard::isKeyPressed(Keyboard::W)){
            bodies.at(0).SetVelocity(0,-40);
        }



        window.clear(Color(255,255,255));
        window.draw(background);

        //Rigid body to rigid body interactions
        for(unsigned int i = 0; i < bodies.size(); i++){
            for(unsigned int j = 0; j < bodies.size(); j++){
                if(abs(bodies.at(0).velocity_.GetX()) > .001 || abs(bodies.at(0).velocity_.GetY()) > 0.01)
                    bodies.at(i).AddDrag(.0000001);
                if(i == j){
                    continue;
                }
                FloatRect bound_one = items.at(j).GetSprite()->getGlobalBounds();
                FloatRect bound_two = items.at(i).GetSprite()->getGlobalBounds();

                if(Collision::CheckCollision(bound_one, bound_two)){
                    //Make a closer check for collision as this is not good for rotated objects

                }

                else{
                }

            }
        }

        //Interactions involving one rigid body
        //Make it so arrow stops once the tip hits the block that causes the force
        for(unsigned int i = 0; i < bodies.size(); i++){

            //Get force arrows
            if(i==0){
                for(Force force : bodies.at(i).GetForces()){
                    Graphics* arrow = new Graphics(resources.GetTexture("vector"));
                    float scale = force.GetMagnitude();
                    if(scale > 1){
                        scale = .25;
                    }
                    arrow->SetScale(.025+scale,.1+scale);
                    arrow->SetOrigin(Vec2(512.0/2,0));
                    arrow->SetPosition(bodies.at(i).GetPosition());
                    arrow->SetOrientation(270+force.GetAngle());
                    force_vectors.push_back(*arrow);
                }
            }

            //Draw force arrows
            if(draw_arrows) {
                for (Graphics x : force_vectors) {
                    window.draw(*x.GetSprite());
                }
            }

            //Update physics
            bodies.at(i).UpdatePhysics(dt);


            //Looping around the screen
            if(bodies.at(i).GetPosition().GetX() < 0){
                bodies.at(i).SetX(1959);
            }
            else if(bodies.at(i).GetPosition().GetX() > 1960){
                bodies.at(i).SetX(1);
            }
            if(bodies.at(i).GetPosition().GetY() < 0){
                bodies.at(i).SetY(1079);
            }
            else if(bodies.at(i).GetPosition().GetY() > 1080){
                bodies.at(i).SetY(1);
            }


            items.at(i).SetPosition(bodies.at(i).GetPosition());
            //items.at(i).GetSprite()->setRotation(items.at(i).GetSprite()->getRotation() + .01);
            window.draw(*items.at(i).GetSprite());
            force_vectors.clear();
        }

        window.display();

    }

    return 0;
}