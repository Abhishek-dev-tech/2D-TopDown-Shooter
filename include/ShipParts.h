#pragma once
#include "GameObject.h"
#include "Projectile.h"
#include "Enemy.h"

struct ShipInfo
{
public:
	enum type
	{
		Shooting,
		Sword
	};

	type shipType;
	int hitPoints;
	float AttackingSpeed;
};


class ShipParts : public GameObject
{
public:
	ShipParts(const char* texturesheet, Vector _pos, int shipType);
	void SetInfo();
	void Update(Enemy enemy);
	void Renderer();
	void Attack();
	void Shoot(Projectile& projectile);
	void AnimateShip();

	void SetOnAir(bool value);
	bool GetOnAir();
	void MouseButtonPressed();

	bool GetIsShoot();

private:
	struct ShipInfo shipInfo;

	bool onAir;
	bool mouseButtonPressed;
	bool targetLocked;
	bool isShoot;

	float angle;
};
