#pragma once
#include "GameObject.h"
#include "Projectile.h"
#include "Enemy.h"
#include"vector"

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
	void Renderer(std::vector<ShipParts> shipParts);
	void Attack();
	void Shoot(Projectile& projectile);
	void AnimateShip();

	void SetOnAir(bool value);
	bool GetOnAir();
	void MouseButtonPressed();

	bool GetIsShoot();
	void DrawLine(std::vector<ShipParts> shipParts);


private:
	struct ShipInfo shipInfo;

	bool onAir;
	bool mouseButtonPressed;
	bool targetLocked;
	bool isShoot;
	bool stopShip;

	float angle;

	int smallestDistance, smallestDistanceIndex;

	std::vector<int> DistancesBetweenShipsParts;
};
