#pragma once
#include "Enemy.h"
#include "GameObject.h"
#include <iostream>
#include <vector>
#include "Projectile.h"
#include "DestroyedParts.h"

class ObjectSpawner
{
public:

	ObjectSpawner();
	void SpawnEnemy(SDL_Renderer* renderer);
	void SpawnProjectile(SDL_Renderer* renderer);
	void SpawnDestroyedParts(SDL_Renderer* renderer);
	void Update(GameObject& gameObject);
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

private:

	std::vector<Enemy> enemies;

	std::vector<Projectile> projectiles;

	std::vector<DestroyedParts> enemyDestroyedParts;

	SDL_Renderer* renderer;

	bool once;
	bool mouseButtonPressed;

	float enemyMaxTime, enemyPreviousTime;

	int noOfProjectiles;
	int noOfEnemies;
};