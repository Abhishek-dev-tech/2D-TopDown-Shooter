#include "Projectile.h"
#include <iostream>


Projectile::Projectile(const char* texturesheet, Vector _pos)
	:GameObject(texturesheet, _pos)
{
	accleration.SetX(5);
	accleration.SetY(5);
	
	SetReady(true);
}

void Projectile::Update()
{

	if (active)
	{
		SetPos(GetPos() - accleration);

		if (GetPos().GetX() > 800 || GetPos().GetX() < 0 || GetPos().GetY() > 600 || GetPos().GetY() < 0)
		{
			active = false;
		}
	}
	else
	{
		ready = true;

		velocity.SetX(0);
		velocity.SetY(0);

		
		SetPos(Vector(400, 300));

		SetScale(Vector(0, 0));
	}
}

void Projectile::SetProjectileAngle(float angle)
{
	accleration.SetAngle(angle);
}

void Projectile::Reset()
{
	active = false;
}


void Projectile::Renderer()
{
	RenderEx(accleration.GetAngle());
	
}

bool Projectile::IsActive()
{
	return active;
}

void Projectile::SetActive(bool value)
{
	active = value;
}

bool Projectile::IsReady()
{
	return ready;
}

void Projectile::SetReady(bool value)
{
	ready = value;
}