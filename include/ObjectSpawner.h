#pragma once
#include "Enemy.h"
#include "GameObject.h"
#include <iostream>
#include <vector>
#include "Projectile.h"
#include "ShipParts.h"
#include "Vector.h"

class ObjectSpawner
{
public:

	ObjectSpawner();
	void SpawnEnemy(SDL_Renderer* renderer);
	void SpawnProjectile(SDL_Renderer* renderer);
	void Update();
	void HandleEvents(SDL_Event event);
	void Renderer();

	Enemy GetEnemies();
	std::vector<Enemy> GetAllSpawnedEnemies();

	Projectile& GetProjectiles();
	std::vector<Projectile> GetAllSpawnedProjectiles();

	void GenerateEnemies();
	void CheckCollision();
	void CheckEnemiesInScene();

	Enemy GetEnemiesInScene();

	void SpawnShipParts(int shipType, SDL_Renderer* renderer);
	std::vector<ShipParts> GetAllSpawnedShipParts();

	void DrawLine();

private:

	std::vector<Enemy> enemies;

	std::vector<Projectile> projectiles;

	std::vector<ShipParts> shipParts;

	SDL_Renderer* renderer;

	bool once;
	bool mouseButtonPressed;

	float enemyMaxTime, enemyPreviousTime;
	float shipProjectileMaxTime, shipProjectilePreviousTime;

	int noOfProjectiles;
	int noOfEnemies;

	Enemy m_tempEnemy;

};