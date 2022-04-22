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
	void Update(GameObject& playerInfo, GameObject& enemyInfo);
	void SetInfo();
	void SetColor();
	void Renderer();
	void Damage();
	void Animate();
	void Shoot(Projectile& projectile);

	bool IsActive();
	bool IsReady();

	void SetActive(bool value);
	void SetReady(bool value);

	bool GetInScene();
	void SetInScene(bool value);

	void CheckCollision(SDL_Rect A, SDL_Rect B,bool &isCollide);
	void PushBackward();

	void Reset();

private:
	struct Info info;

	Vector velocity;
	Vector accleration;
	
	GameObject playerInfo;
	GameObject enemyInfo;

	int hitPoints;

	bool active;
	bool ready;
	bool once;
	bool inScene;
	bool collidingWithPlayer;
	bool pushBack;
	bool collideWithEnemy;

	float maxTime, previousTime;



};
