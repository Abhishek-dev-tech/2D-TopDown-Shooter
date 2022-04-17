#include "ShipParts.h"

ShipParts::ShipParts(const char* texturesheet, Vector _pos, int shipType)
	:GameObject(texturesheet, _pos)
{
	if (shipType == 1)
		shipInfo.shipType = shipInfo.Shooting;
	else if (shipType == 2)
		shipInfo.shipType = shipInfo.Sword;

	angle = 0;

	smallestDistance = 99999;

	SetInfo();
}
 
void ShipParts::Update(Enemy enemy)
{
	if (!onAir)
	{
		angle = atan2(enemy.GetPos().GetY() - enemy.GetRect().w / 2 - GetPos().GetY(),
			enemy.GetPos().GetX() - enemy.GetRect().w / 2 - GetPos().GetX());

		SDL_SetTextureAlphaMod(GetTexture(), 255);

		if (enemy.IsActive())
			targetLocked = true;
		else
			targetLocked = false;

		Attack();
	}
	else
	{
		if(!stopShip)
			SetPos(Vector(GetMousePosX() - GetRect().w / 2, GetMousePosY() - GetRect().w / 2));

		SDL_SetTextureAlphaMod(GetTexture(), 180);
	}

	float scale = lerp(GetScale().GetX(), 0.35, 0.1);
	SetScale(Vector(scale, scale));
}

void ShipParts::Attack()
{
	if (shipInfo.shipType == shipInfo.Shooting)
		isShoot = true;
}

void ShipParts::Shoot(Projectile& projectile)
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

void ShipParts::AnimateShip()
{
	float scale = lerp(GetScale().GetX(), 0.475, 1);

	SetScale(Vector(scale, scale));
}

void ShipParts::Renderer(std::vector<ShipParts> shipParts)
{
	DrawLine(shipParts);
	RenderEx(angle);
}

void ShipParts::SetOnAir(bool value)
{
	onAir = value;
}

bool ShipParts::GetOnAir()
{
	return onAir;
}

void ShipParts::SetInfo()
{
	switch (shipInfo.shipType)
	{
	case 0:

		shipInfo.hitPoints = 50;
		shipInfo.AttackingSpeed = .5;

		break;

	case 1:

		shipInfo.hitPoints = 50;
		shipInfo.AttackingSpeed = 1;
		
		break;

	default:
		break;
	}
}

void ShipParts::MouseButtonPressed()
{
	onAir = false;
}

bool ShipParts::GetIsShoot()
{
	return isShoot;
}

void ShipParts::DrawLine(std::vector<ShipParts> shipParts)
{
	if (onAir)
	{
		int i = 0;
		for (i = 0; i < shipParts.size(); i++)
		{
			DistancesBetweenShipsParts.resize(shipParts.size());

			DistancesBetweenShipsParts[i] = Distance(Vector(GetPos().GetX() + GetRect().w / 2, GetPos().GetY() + GetRect().h / 2), 
				Vector(shipParts[i].GetPos().GetX() + shipParts[i].GetRect().w / 2, shipParts[i].GetPos().GetY() + shipParts[i].GetRect().h / 2));

			if (smallestDistance > DistancesBetweenShipsParts[i] && DistancesBetweenShipsParts[i] != 0)
			{
				smallestDistance = DistancesBetweenShipsParts[i];
				smallestDistanceIndex = i;
			}
			else if (smallestDistance < DistancesBetweenShipsParts[i])
			{
				smallestDistance = DistancesBetweenShipsParts[i];
			}
		}

		if (Distance(Vector(shipParts[smallestDistanceIndex].GetPos().GetX() + shipParts[smallestDistanceIndex].GetRect().w / 2, shipParts[smallestDistanceIndex].GetPos().GetY() + shipParts[smallestDistanceIndex].GetRect().h / 2),
			Vector(GetMousePosX(), GetMousePosY())) >= 90)
			stopShip = true;
		
		else
			stopShip = false;
	}

	SDL_SetRenderDrawColor(GetRenderer(), 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLine(GetRenderer(), GetPos().GetX() + GetRect().w / 2,
		GetPos().GetY() + GetRect().h / 2,
		shipParts[smallestDistanceIndex].GetPos().GetX() + shipParts[smallestDistanceIndex].GetRect().w / 2,
		shipParts[smallestDistanceIndex].GetPos().GetY() + shipParts[smallestDistanceIndex].GetRect().h / 2);
}