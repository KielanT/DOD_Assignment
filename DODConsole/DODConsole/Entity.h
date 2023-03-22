#pragma once

//******************************************************
//****** Basic Structs for containing floats
//****** Vectors without the vector code
//******************************************************

struct Vector2 
{
	float X = 0.0f;
	float Y = 0.0f;
};

struct Vector3
{
	float X = 0.0f;
	float Y = 0.0f;
	float Z = 0.0f;
};

//******************************************************
//******************************************************

enum class EObjType
{
	// Does not move
	Static = 0,

	// Moves
	Dynamic,
};

struct Circle 
{
	// Basic Data
	float Radius;
	Vector2 Location;
	Vector2 Velocity;

	// Additional Data
	std::string Name;
	float HP;
	Vector3 Colour;

	// Extra Data
	EObjType type;

};

