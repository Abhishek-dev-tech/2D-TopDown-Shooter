#pragma once
#include "GameObject.h"
#include "Collision.h"
#include "Projectile.h"


struct Info
{
public:
	enum type
	{
		follow,
		shooting
	};

	float speed;
	float maxVelocity;
	type enemyType;
	int hitPoints;
};

class Enemy : public GameObject
{
public:
	Enemy(const char* texturesheet, Vector _pos, int enemyType);

	Enemy() = default;

	void Attack();
	void Follow();
	void Update(GameObject& playerInfo);
	void SetInfo();
	void SetColor();
	void Renderer();
	void Damage();
	void Animate();

	bool IsActive();
	bool IsReady();

	void SetActive(bool value);
	void SetReady(bool value);

	bool GetInScene();
	void SetInScene(bool value);

	void CheckCollision(SDL_Rect A, SDL_Rect B);

	void ShootLaser();

	void Reset();

private:
	struct Info info;

	Vector velocity;
	Vector accleration;
	
	GameObject playerInfo;

	int hitPoints;

	bool active;
	bool ready;
	bool once;
	bool inScene;
	bool shootingEnemyStop;

	float maxTime, previousTime;

};
