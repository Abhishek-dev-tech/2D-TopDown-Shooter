#pragma once
#include "GameObject.h"
#include "Collision.h"


class Projectile : public GameObject
{
public :
	Projectile(const char* texturesheet, Vector _pos);
	void Update();
	void Renderer();
	void SetActive(bool value);
	void SetReady(bool value);
	void SetProjectileAngle(float angle);
	void Reset();
	bool IsActive();
	bool IsReady();

private:

	Vector velocity;
	Vector accleration;

	bool active;
	bool ready;


};