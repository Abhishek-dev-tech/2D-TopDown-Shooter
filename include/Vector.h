#pragma once

class Vector
{

private:
	float x, y;
	float length;
	float angle;

public:
	Vector() = default;
	

	Vector(float _x, float _y);

	float GetX();
	float GetY();

	void SetX(float value);
	void SetY(float value);

	void SetAngle(float _angle);
	float GetAngle();
	float GetLength();
	void SetLength(float _length);

	Vector operator+(Vector& other);
	
	Vector operator-(Vector& other);

	void AddTo(Vector& other);

	void SubTo(Vector& other);

	float Distance(Vector v1, Vector v2);

	float lerp(float a, float b, float t);


};