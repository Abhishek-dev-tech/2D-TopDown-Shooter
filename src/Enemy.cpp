#include "Enemy.h"
#include "iostream"

Enemy::Enemy(const char* texturesheet, Vector _pos, int enemyType)
	:GameObject(texturesheet, _pos)
{
	SetReady(true);

	if (enemyType == 1)
	{
		info.enemyType = info.follow;
	}
	else if (enemyType == 2)
	{
		info.enemyType = info.shooting;
		previousTime = 0;
		maxTime = 0.3f;
	}

	SetInfo();

	accleration.SetLength(info.speed);

	hitPoints = info.hitPoints;

	once = true;
	inScene = false;
	active = false;

}

void Enemy::Update(GameObject& playerInfo, GameObject& enemyInfo, Projectile &projectile)
{
	if (active)
	{
		if (Distance(playerInfo.GetPos(), GetPos()) >= 125 && info.enemyType == info.shooting)
		{
			SetPos(GetPos() + velocity);

		}
		else if(info.enemyType == info.follow)
		{
			SetPos(GetPos() + velocity);
		}

		if (SDL_GetTicks() * 0.001 - previousTime >= maxTime && info.enemyType == info.shooting)
		{
			previousTime = SDL_GetTicks() * 0.001;
			//Shoot(projectile);

		}

		Uint8 r, g, b;
		SDL_GetTextureColorMod(GetTexture(), &r, &g, &b);

		if(info.enemyType == info.follow)
			SDL_SetTextureColorMod(GetTexture(), lerp(r, 255, 0.05), lerp(g, 58, 0.05), lerp(b, 58, 0.05));
		else
			SDL_SetTextureColorMod(GetTexture(), lerp(r, 255, 0.05), lerp(g, 188, 0.05), lerp(b, 42, 0.05));

		if (once)
		{
			int randX = rand() % 1100;
			int randY = rand() % 850;

			SetPos(Vector(randX, randY));
			once = false;
		}

		float scale;

		if(info.enemyType == info.follow)
			scale = lerp(GetScale().GetX(), .2, 0.1);
		else
			scale = lerp(GetScale().GetX(), 1, 0.1);

		SetScale(Vector(scale, scale));

		this->playerInfo = playerInfo;
		this->enemyInfo = enemyInfo;

		Attack();
		CheckCollision(GetRect(), playerInfo.GetRect());
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
	Follow();	
}

void Enemy::Follow()
{
	if (velocity.GetLength() <= info.maxVelocity)
	{
		velocity.AddTo(accleration);
		std::cout << accleration.GetLength() << "\n";

	}

	velocity.SetAngle(atan2(playerInfo.GetPos().GetY() - GetPos().GetY(), playerInfo.GetPos().GetX() - GetPos().GetX()));	
}

void Enemy::CheckCollision(SDL_Rect A, SDL_Rect B)
{
	if (info.enemyType == info.follow && Collision::IsCollide(A, B))
	{
		Reset();
	}
}

void Enemy::Shoot(Projectile& projectile)
{
	projectile.SetPos(Vector(GetPos().GetX() + GetRect().w / 2 - cos(velocity.GetAngle()) * GetRect().h / 2
		, GetPos().GetY() + GetRect().h / 2 - sin(velocity.GetAngle()) * GetRect().h / 2 ));

	projectile.SetActive(true);
	projectile.SetReady(false);
	
	projectile.SetProjectileAngle(atan2(playerInfo.GetPos().GetY() + playerInfo.GetRect().h / 2 - GetPos().GetY() + GetRect().h / 2, playerInfo.GetPos().GetX() + playerInfo.GetRect().w / 2 - GetPos().GetX() + GetRect().w / 2));

	projectile.SetScale(Vector(.5, .5));
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
		info.speed = 0.1;

		SetScale(Vector(.2, .2));

		info.maxVelocity = 1.5;
		info.hitPoints = 15;

		break;

	case 1:
		info.speed = 0.005;

		SetScale(Vector(.2, .2));

		info.maxVelocity = 1.2;
		info.hitPoints = 15;
		break;

	default:
		break;
	}
}

void Enemy::Animate()
{
	float scale;
	if (info.enemyType == info.follow)
		scale = lerp(GetScale().GetX(), .35, 0.1);
	else
		scale = lerp(GetScale().GetX(), 1.4, 0.1);

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
	RenderEx(atan2(playerInfo.GetPos().GetY() + playerInfo.GetRect().h / 2 - GetPos().GetY() + GetRect().h / 2, playerInfo.GetPos().GetX() + playerInfo.GetRect().w / 2 - GetPos().GetX() + GetRect().w / 2) + 90 * 3.14 / 180);
}