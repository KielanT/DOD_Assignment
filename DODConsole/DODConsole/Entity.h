#pragma once


struct Vector2 
{
	float X = 0.0f;
	float Y = 0.0f;

	

	Vector2& operator+=(const Vector2 v)
	{
		X += v.X;
		Y += v.Y;
		return *this;
	}
};

Vector2 operator*(const Vector2 v, const float f)
{
	return { v.X * f, v.Y * f };
}

Vector2 operator*(const float f, const Vector2 v)
{
	return { v.x * f, v.y * f };
}


struct Vector3
{
	float X = 0.0f;
	float Y = 0.0f;
	float Z = 0.0f;
};


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

