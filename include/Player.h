#pragma once
#include "GameObject.h"
#include "Enemy.h"
#include "Projectile.h"

#include <vector>

class Player : public GameObject  
{
public:
	Player(const char* texturesheet, Vector _pos);

	Player() = default;

	void Update(Enemy enemies);
	void Renderer();
	void ShootProjectiles(Projectile &projectile);
	void AnimateShip();

private:

	Vector velocity;
	Vector accleration;

	float angle;
	
	bool targetLocked;

};
