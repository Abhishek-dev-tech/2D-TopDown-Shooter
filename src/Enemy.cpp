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

	accleration.SetLength(info.speed);

	SDL_SetTextureColorMod(GetTexture(), 255, 255, 255);

	hitPoints = info.hitPoints;

	once = true;
	inScene = false;
	pushBack = false;
	collidingWithPlayer = false;
}

void Enemy::Update(GameObject& gameObject)
{
	if (active)
	{
		if(!pushBack)
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

		playerInfo = gameObject;

		Attack();
		CheckCollision();
		PushBackward();

		ready = false;

	}
	else
	{
		ready = true;

		velocity.SetLength(0);


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
	velocity.SetAngle(atan2(playerInfo.GetPos().GetY() - GetPos().GetY(), playerInfo.GetPos().GetX() - GetPos().GetX()));

	if (velocity.GetLength() <= info.maxVelocity && !pushBack)
	{
		velocity.AddTo(accleration);
	}	


}

void Enemy::CheckCollision()
{
	if (Collision::IsCollide(GetRect(), playerInfo.GetRect()))
	{
		collidingWithPlayer = true;
		pushBack = true;
	}	
	else
		collidingWithPlayer = false;
}

void Enemy::PushBackward()
{
	if (collidingWithPlayer || pushBack)
	{
		SetPos(GetPos() - velocity);

		if (Distance(playerInfo.GetPos(), GetPos()) > 100)
		{
			velocity.SetLength(GetLength() * 0.1);
			pushBack = false;
		}		
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

		info.maxVelocity = 1.5;
		info.hitPoints = 15;

		break;

	case 1:
		info.speed = 0.005;

		SetScale(Vector(.2, .2));

		info.maxVelocity = 2;
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