#include "Vector.h"
#include "cmath"

Vector::Vector(float _x, float _y)
{
	x = _x;
	y = _y;
}

void Vector::SetAngle(float _angle)
{
	float length = GetLength();
	x = cos(_angle) * length;
	y = sin(_angle) * length;
}

float Vector::GetAngle()
{
	return atan2(y, x) ;
}

void Vector::SetLength(float _length)
{
	float _angle = GetAngle();
	x = cos(_angle) * _length;
	y = sin(_angle) * _length;
}

float Vector::Distance(Vector v1, Vector v2)
{
	float dx, dy;

	dx = v1.x - v2.x;
	
	dy = v1.y - v2.y;

	return sqrt(dx * dx + dy * dy);
}

float Vector::GetLength()
{
	return sqrt(x * x + y * y);
}

float Vector::GetX()
{
	return x;
}

float Vector::GetY()
{
	return y;
}

void Vector::SetX(float value)
{
	x = value;
}

void Vector::SetY(float value)
{
	y = value;
}

Vector Vector::operator+(Vector& other)
{
	return Vector(x + other.x, y + other.y);
}

Vector Vector::operator-(Vector& other)
{
	return Vector(x - other.x, y - other.y);
}

void Vector::AddTo(Vector& other)
{
	x += other.x;
	y += other.y;
}

void Vector::SubTo(Vector& other)
{
	x -= other.x;
	y -= other.y;
}

float Vector::lerp(float a, float b, float t)
{
	return (1.0 - t) * a + b * t;
}

