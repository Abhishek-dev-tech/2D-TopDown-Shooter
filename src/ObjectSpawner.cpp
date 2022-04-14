#include "ObjectSpawner.h"

ObjectSpawner::ObjectSpawner()
{
	enemyMaxTime = 5;
	enemyPreviousTime = 0;
	once = true;

	noOfProjectiles = 20;
	noOfEnemies = 5;

	m_tempEnemy.SetPos(Vector(400, 0));
	m_tempEnemy.SetScale(Vector(0, 0));
	m_tempEnemy.SetActive(false);

	shipProjectileMaxTime = .8;
	shipProjectilePreviousTime = 0;

}

void ObjectSpawner::Update()
{
	for (int i = 0; i < projectiles.size(); i++)
		projectiles[i].Update();

	for (int j = 0; j < enemies.size(); j++)
		enemies[j].Update();

	for (int k = 0; k < shipParts.size(); k++)
		shipParts[k].Update(GetEnemiesInScene());

	if (SDL_GetTicks() * 0.001 - shipProjectilePreviousTime >= shipProjectileMaxTime)
	{
		for (int p = 0; p < shipParts.size(); p++)
		{
			shipProjectilePreviousTime = SDL_GetTicks() * 0.001;
			if (!shipParts[p].GetOnAir() && shipParts[p].GetIsShoot())
				shipParts[p].Shoot(GetProjectiles());
		}
		
	}


	m_tempEnemy.SetPos(Vector(GetEnemiesInScene().GetPos().GetX(), GetEnemiesInScene().GetPos().GetY()));

	CheckCollision();

	if (SDL_GetTicks() * 0.001 - enemyPreviousTime >= enemyMaxTime)
	{
		enemyPreviousTime = SDL_GetTicks() * 0.001;

		GenerateEnemies();
	}

	CheckEnemiesInScene();
}

void ObjectSpawner::DrawLine()
{
	for (int i = 0; i < shipParts.size(); i++)
	{
		for (int j = 0; j < shipParts.size(); j++)
		{
			if (Vector::Distance(shipParts[i].GetPos(), shipParts[shipParts.size() - 1].GetPos()) < Vector::Distance(shipParts[j].GetPos(), shipParts[shipParts.size() - 1].GetPos()))
			{
				SDL_SetRenderDrawColor(shipParts[i].GetRenderer(), 255, 255, 255, SDL_ALPHA_OPAQUE);
				SDL_RenderDrawLine(shipParts[i].GetRenderer(), shipParts[i].GetPos().GetX() + shipParts[i].GetRect().w / 2,
					shipParts[i].GetPos().GetY() + shipParts[i].GetRect().h / 2,
					shipParts[shipParts.size() - 1].GetPos().GetX() + shipParts[shipParts.size() - 1].GetRect().w / 2,
					shipParts[shipParts.size() - 1].GetPos().GetY() + shipParts[shipParts.size() - 1].GetRect().h / 2);
				return;
			}	
		}
		
	}
	
}

void ObjectSpawner::HandleEvents(SDL_Event event)
{
	switch (event.type)
	{
	case SDL_MOUSEBUTTONDOWN:
		if (event.button.button == SDL_BUTTON_LEFT)
		{
			for (int i = 0; i < shipParts.size(); i++)
				shipParts[i].MouseButtonPressed();

			mouseButtonPressed = true;
		}
			
		break;

	default:
		break;
	}
}

void ObjectSpawner::CheckCollision()
{
	for (int i = 0; i < enemies.size(); i++)
	{
		for (int j = 0; j < projectiles.size(); j++)
		{
			if (Collision::IsCollide(enemies[i].GetRect(), projectiles[j].GetRect()))
			{
				projectiles[j].Reset();
				enemies[i].SetColor();
				enemies[i].Damage();
			}
		}
	}
}

void ObjectSpawner::CheckEnemiesInScene()
{
	for (int i = 0; i < enemies.size(); i++)
	{
		if (enemies[i].GetPos().GetX() < 800 && enemies[i].GetPos().GetX() > 0 && enemies[i].GetPos().GetY() < 600 && enemies[i].GetPos().GetY() > 0
			&& !enemies[i].GetInScene())
			enemies[i].SetInScene(true);
		else if(enemies[i].GetInScene() && !enemies[i].IsActive())
			enemies[i].SetInScene(false);
		
	}
}

void ObjectSpawner::SpawnEnemy(SDL_Renderer* renderer)
{
	for (int i = 0; i < noOfEnemies; i++)
	{
		Enemy tempEnemy("res/Enemy.png", Vector(-10, -10), 1);

		tempEnemy.SetRenderer(renderer);

		tempEnemy.SetScale(Vector(0, 0));

		enemies.push_back(tempEnemy);
	}	
}

void ObjectSpawner::SpawnProjectile(SDL_Renderer* renderer)
{
	for (int i = 0; i < noOfProjectiles; i++)
	{
		Projectile tempProjectile("res/Projectile.png", Vector(-10, -10));

		tempProjectile.SetRenderer(renderer);

		tempProjectile.SetScale(Vector(0, 0));

		projectiles.push_back(tempProjectile);
	}
}


Enemy ObjectSpawner::GetEnemies()
{
	for (int i = 0; i < enemies.size(); i++)
	{
		if (enemies[i].IsReady() && !enemies[i].IsActive())
		{
			return enemies[i];
		}
	}
}

Enemy ObjectSpawner::GetEnemiesInScene()
{
	for (int i = 0; i < enemies.size(); i++)
	{
		if (enemies[i].GetInScene() && enemies[i].IsActive())
		{
			return enemies[i];
		}
	}

	return m_tempEnemy;
}

std::vector<Enemy> ObjectSpawner::GetAllSpawnedEnemies()
{
	return enemies;
}

Projectile &ObjectSpawner::GetProjectiles()
{
	for (int i = 0; i < projectiles.size(); i++)
	{
		if (projectiles[i].IsReady() && !projectiles[i].IsActive())
		{
			return projectiles[i];
		}
	}
}

std::vector<Projectile> ObjectSpawner::GetAllSpawnedProjectiles()
{
	return projectiles;
}

void ObjectSpawner::GenerateEnemies()
{
	for (int i = 0; i < enemies.size(); i++)
	{
		if (enemies[i].IsReady() && !enemies[i].IsActive())
		{
			enemies[i].SetActive(true);
			return;
		}
	}
	
}

void ObjectSpawner::SpawnShipParts(int shipType, SDL_Renderer* renderer)
{
	ShipParts tempShipPart("res/Ship.png", Vector(-100, -100), shipType);

	tempShipPart.SetRenderer(renderer);

	tempShipPart.SetScale(Vector(.35, .35));
	tempShipPart.SetOnAir(true);

	shipParts.push_back(tempShipPart);
}

std::vector<ShipParts> ObjectSpawner::GetAllSpawnedShipParts()
{
	return shipParts;
}

void ObjectSpawner::Renderer()
{
	for (int i = 0; i < enemies.size(); i++)
		enemies[i].Renderer();

	for (int i = 0; i < projectiles.size(); i++)
		projectiles[i].Renderer();

	for (int k = 0; k < shipParts.size(); k++)
		shipParts[k].Renderer();

	DrawLine();
}