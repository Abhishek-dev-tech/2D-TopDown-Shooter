#include "ObjectSpawner.h"

ObjectSpawner::ObjectSpawner()
{
	enemyMaxTime = 5;
	enemyPreviousTime = 0;
	once = true;

	noOfProjectiles = 20;
	noOfEnemies = 5;
}

void ObjectSpawner::Update()
{
	for (int i = 0; i < projectiles.size(); i++)
		projectiles[i].Update();

	for (int j = 0; j < enemies.size(); j++)
		enemies[j].Update();

	CheckCollision();

	if (SDL_GetTicks() * 0.001 - enemyPreviousTime >= enemyMaxTime)
	{
		enemyPreviousTime = SDL_GetTicks() * 0.001;

		GenerateEnemies();
	}

	CheckEnemiesInScene();
}

void ObjectSpawner::HandleEvents(SDL_Event event)
{
	
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

void ObjectSpawner::Renderer()
{
	for (int i = 0; i < enemies.size(); i++)
		enemies[i].Renderer();

	for (int i = 0; i < projectiles.size(); i++)
		projectiles[i].Renderer();
}