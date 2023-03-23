// DODTL.cpp: A program using the TL-Engine

#include <TL-Engine.h>	// TL-Engine include file and namespace
#include <vector>
#include <random>
#include "Timer.h"
#include "Entity.h"

using namespace tle;



const float CAM_SPEED = 500.0f;
const int MAX_CIRCLES = 10;
const int MAX_CIRCLES_SETS = 2;
const float LOCATION_RANGE = 1000.0f;
const float VELOCITY_RANGE = 5.0f;
const float SIMULATION_TIME = 10.0f;
const float SPEED = 30.0f;

Timer gTimer;

struct RenderedSphere
{
	std::string Name;
	IModel* Model;
};


std::vector<Circle> gStaticCircles(MAX_CIRCLES / MAX_CIRCLES_SETS);
std::vector<Circle> gDynamicCircles(MAX_CIRCLES / MAX_CIRCLES_SETS);
std::vector<IModel*> gStaticSpheres;
std::vector<RenderedSphere> gDynamicSpheres;

void Initlise(I3DEngine* engine);
void Move(Circle* circles, uint32_t numCircles);
void ControlCamera(I3DEngine* engine, ICamera* camera);

void main()
{
	// Create a 3D engine (using TLX engine here) and open a window for it
	I3DEngine* myEngine = New3DEngine( kTLX );
	myEngine->StartWindowed();

	// Add default folder for meshes and other media
	myEngine->AddMediaFolder( "D:\\Software\\Misc\\TL-Engine\\Media" );

	/**** Set up your scene here ****/
	ICamera* Camera;
	Camera = myEngine->CreateCamera(kManual, 0, 0, -3000);

	Initlise(myEngine);

	gTimer.Reset();

	// The main game loop, repeat until engine is stopped
	while (myEngine->IsRunning())
	{
		gTimer.Tick();

		// Draw the scene
		myEngine->DrawScene();

		/**** Update your scene each frame here ****/
		Move(gDynamicCircles.data(), MAX_CIRCLES / MAX_CIRCLES_SETS);

		ControlCamera(myEngine, Camera);
	}

	// Delete the 3D engine now we are finished with it
	myEngine->Delete();
}

void Initlise(I3DEngine* engine)
{
	IMesh* SphereMesh = engine->LoadMesh("Sphere.x");

	

	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> randLoc(-LOCATION_RANGE, LOCATION_RANGE); // TODO see what happens with float
	std::uniform_real_distribution<float> randVel(-VELOCITY_RANGE, VELOCITY_RANGE); // TODO see what happens with float

	int circleIndex = 0;
	for (auto& circle : gStaticCircles)
	{
		// Init data
		circle.Radius = 1.0f;
		circle.Location = { randLoc(mt), randLoc(mt) };
		circle.Velocity = { randVel(mt), randVel(mt) };


		circle.Name = "StaticCirlce: " + std::to_string(circleIndex);
		circle.HP = 100.0f;
		circle.Colour = { 1, 0, 0 }; // Red
		circle.type = EObjType::Static;

		IModel* SphereModel = SphereMesh->CreateModel(circle.Location.x, 0, 0);
		SphereModel->SetSkin("brick1.jpg");
		gStaticSpheres.push_back(SphereModel);

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



		RenderedSphere sphere;
		sphere.Name = circle.Name;
		sphere.Model = SphereMesh->CreateModel(circle.Location.x, circle.Location.y, 0);
		sphere.Model->SetSkin("CueMetal.jpg");

		gDynamicSpheres.push_back(sphere);

		circleIndex++;
	}
}


void Move(Circle* circles, uint32_t numCircles)
{
	auto circlesEnd = circles + numCircles;

	while (circles != circlesEnd)
	{
		// Move the circle
		circles->Location += (SPEED * circles->Velocity) * gTimer.GetDeltaTime();

		// TODO Move rendering to own thread / move to its own render function
		for (auto& sphere : gDynamicSpheres)
		{
			if (sphere.Name == circles->Name)
			{
				sphere.Model->SetPosition(circles->Location.x, circles->Location.y, 0);
				break;
			}
		}

		++circles;
	}

}


void ControlCamera(I3DEngine* engine, ICamera* camera)
{
	if (engine->KeyHeld(Key_W))
	{
		camera->MoveZ(CAM_SPEED * gTimer.GetDeltaTime());
	}
	if (engine->KeyHeld(Key_S))
	{
		camera->MoveZ(-CAM_SPEED * gTimer.GetDeltaTime());
	}
	if (engine->KeyHeld(Key_A))
	{
		camera->MoveX(-CAM_SPEED * gTimer.GetDeltaTime());
	}
	if (engine->KeyHeld(Key_D))
	{
		camera->MoveX(CAM_SPEED * gTimer.GetDeltaTime());
	}
}