#pragma once
#include "GameObject.h"
#include "Enemy.h"
#include "Projectile.h"
#include "ObjectSpawner.h"

#include <vector>

class Player : public GameObject  
{
public:
	Player(const char* texturesheet, Vector _pos);

	Player() = default;

	void Update(ObjectSpawner& objectSpawner);
	void HandleEvents(SDL_Event event);
	void Renderer();
	void ShootProjectiles(Projectile &projectile);
	void TakeDamage();

private:

	Vector velocity;
	Vector accleration;

	float angle;
	float maxTime, previousTime;
	float maxVelocity;

	bool mouseButtonPressed;
};
