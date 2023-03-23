#include <iostream>
#include <vector>
#include <random>
#include <string>   

#include "Timer.h"
#include "Entity.h"
#include "Collision.h"

const int MAX_CIRCLES = 10;
const int MAX_CIRCLES_SETS = 2;
const float LOCATION_RANGE = 1000.0f; 
const float VELOCITY_RANGE = 5.0f;
const float SIMULATION_TIME = 10.0f;
const float SPEED = 30.0f;

Timer gTimer;


std::vector<Circle> gStaticCircles(MAX_CIRCLES / MAX_CIRCLES_SETS);
std::vector<Circle> gDynamicCircles(MAX_CIRCLES / MAX_CIRCLES_SETS);

void Initlise();
bool Simulate();

void Move(Circle* circles, uint32_t numCircles);


int main()
{
    //******* Initilise **********
    //****************************
    gTimer.Reset();

    Initlise();

    //******** Running ***********
    //****************************
    std::cout << "Starting Simulation" << std::endl;
    bool bIsRunning = true;
    while (bIsRunning)
    {
        gTimer.Tick();

        bIsRunning = Simulate();

        std::cout << gTimer.GetDeltaTime() << std::endl;
    }

    //******** Shutdown ***********
    //****************************
    
}

void Initlise()
{
    std::cout << "Initlising " << std::endl;

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<float> randLoc(-LOCATION_RANGE, LOCATION_RANGE); // TODO see what happens with float
    std::uniform_real_distribution<float> randVel(-VELOCITY_RANGE, VELOCITY_RANGE); // TODO see what happens with float

    int circleIndex = 0;
    for (auto& circle : gStaticCircles)
    {
        // Init data
        
        circle.Radius = 1.0f;
        circle.Location = { randLoc(mt), randLoc(mt)};
        circle.Velocity = { randVel(mt), randVel(mt)};
        
        
        circle.Name = "StaticCirlce: " + std::to_string(circleIndex);
        circle.HP = 100.0f;
        circle.Colour = { 1, 0, 0 }; // Red
        circle.type = EObjType::Static;


         circleIndex++;
    }

    for (auto& circle : gDynamicCircles)
    {
        // Init data
       
        circle.Radius = 1.0f;
        circle.Location = { randLoc(mt), randLoc(mt) };
        circle.Velocity = { randVel(mt), randVel(mt) };
       
        circle.Name = "DynamicCirlce: " + std::to_string(circleIndex);
        circle.HP = 100.0f;
        circle.Colour = { 0, 0, 1 }; // Blue
        circle.type = EObjType::Dynamic;


        circleIndex++;
    }
}

bool Simulate()
{
    if (gTimer.GetTime() <= SIMULATION_TIME)
    {
        // Move 
        Move(gDynamicCircles.data(), MAX_CIRCLES / MAX_CIRCLES_SETS);

        // Check Collision


        return true;
    }
    else
    {
        std::cout << "Finished Simulation" << std::endl;
        return false;
       
    }
}

void Move(Circle* circles, uint32_t numCircles)
{
    auto circlesEnd = circles + numCircles;
   
    while(circles != circlesEnd)
    {
        // Move the circle
        circles->Location += (SPEED * circles->Velocity) * gTimer.GetDeltaTime();
        ++circles;
    }
    
}
