#include "GameObject.h"
#include "Player.h"

#include <iostream>

Player::Player(const char* texturesheet, Vector _pos)
	:GameObject(texturesheet, _pos)
{
}

void Player::Update(Enemy enemy)
{

	if (enemy.IsActive())
		targetLocked = true;
	else
		targetLocked = false;

	angle = atan2(enemy.GetPos().GetY() - enemy.GetRect().h / 2 - GetPos().GetY(),
		enemy.GetPos().GetX() - enemy.GetRect().w / 2 - GetPos().GetX());//lerp(angle, atan2(closestTarget.GetPos().GetY() - closestTarget.GetRect().h / 2 - GetPos().GetY(),
		//closestTarget.GetPos().GetX() - closestTarget.GetRect().w / 2 - GetPos().GetX()), .5);

	float scale = lerp(GetScale().GetX(), 0.35, 0.1);

	SetScale(Vector(scale, scale));
}



void Player::ShootProjectiles(Projectile &projectile)
{
	if (targetLocked)
	{
		projectile.SetPos(Vector(GetPos().GetX() + GetRect().w / 2 + cos(angle) * GetRect().h / 2
			, GetPos().GetY() + GetRect().h / 2 + sin(angle) * GetRect().h / 2));

		projectile.SetActive(true);
		projectile.SetReady(false);

		projectile.SetProjectileAngle(angle);

		projectile.SetScale(Vector(1, 1));

		AnimateShip();
	}
}

void Player::AnimateShip()
{
	float scale = lerp(GetScale().GetX(), 0.475, 1);

	SetScale(Vector(scale, scale));
}


void Player::Renderer()
{
	RenderEx(angle);
}

