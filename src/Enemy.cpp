#include "Enemy.h"
#include "iostream"

Enemy::Enemy(const char* texturesheet, Vector _pos, int enemyType)
	:GameObject(texturesheet, _pos)
{
	SetReady(true);

	if (enemyType == 1)
		info.enemyType = info.follow;
	else if(enemyType == 2)
		info.enemyType = info.shooting;

	SetInfo();

	accleration.SetX(info.speed);
	accleration.SetY(info.speed);

	SDL_SetTextureColorMod(GetTexture(), 255, 255, 255);

	hitPoints = info.hitPoints;

	once = true;
	inScene = false;
}

void Enemy::Update()
{
	if (active)
	{
		SetPos(GetPos() + velocity);

		Uint8 r, g, b;
		SDL_GetTextureColorMod(GetTexture(), &r, &g, &b);

		SDL_SetTextureColorMod(GetTexture(), lerp(r, 255, 0.05), lerp(g, 58, 0.05), lerp(b, 58, 0.05));

		if (once)
		{
			SetPos(Vector(0, 0));
			once = false;
		}
		float scale = lerp(GetScale().GetX(), .2, 0.1);
		SetScale(Vector(scale, scale));

		Attack();

		ready = false;

	}
	else
	{
		ready = true;

		velocity.SetX(0);
		velocity.SetY(0);


		SetPos(Vector(-10, -10));

		SetScale(Vector(0, 0));
	}
}

void Enemy::Attack()
{
	if (info.enemyType == info.follow)
		Follow();
	
}

void Enemy::Follow()
{
	velocity.AddTo(accleration);

	accleration.SetAngle(atan2(300 - GetPos().GetY(), 400 - GetPos().GetX()));

	if (velocity.GetX() >= info.maxVelocity && velocity.GetY() >= info.maxVelocity)
	{
		velocity.SetX(info.maxVelocity);
		velocity.SetY(info.maxVelocity);
	}	
}

void Enemy::Damage()
{
	hitPoints--;
	if (hitPoints <= 0)
		Reset();
	Animate();
	SetColor();
}

void Enemy::SetInfo()
{
	switch (info.enemyType)
	{
	case 0:
		info.speed = 0.005;

		SetScale(Vector(.2, .2));

		info.maxVelocity = 1;
		info.hitPoints = 15;

		break;

	case 1:
		info.speed = 0.005;

		SetScale(Vector(.2, .2));

		info.maxVelocity = 1;
		info.hitPoints = 15;
		break;

	default:
		break;
	}
}

void Enemy::Animate()
{
	float scale = lerp(GetScale().GetX(), .35, 0.1);
	SetScale(Vector(scale, scale));
}

void Enemy::Reset()
{
	active = false;
	once = true;
	hitPoints = info.hitPoints;
}

bool Enemy::IsActive()
{
	return active;
}

void Enemy::SetActive(bool value)
{
	active = value;
}

bool Enemy::IsReady()
{
	return ready;
}

void Enemy::SetReady(bool value)
{
	ready = value;
}

void Enemy::SetColor()
{
	SDL_SetTextureColorMod(GetTexture(), 255, 255, 255);
}

bool Enemy::GetInScene()
{
	return inScene;
}

void Enemy::SetInScene(bool value)
{
	inScene = value;
}

void Enemy::Renderer()
{
	RenderEx(0);
}