#include "GameObject.h"
#include "Player.h"

#include <iostream>

Player::Player(const char* texturesheet, Vector _pos)
	:GameObject(texturesheet, _pos)
{
	accleration.SetLength(0.025);

	velocity.SetAngle(0);

	previousTime = 0;
	maxTime = 0.2;

	maxVelocity = 2.25;

	SetScale(Vector(.7, .7));
}

void Player::Update(ObjectSpawner& objectSpawner)
{
	SetPos(GetPos() + velocity);

	if (velocity.GetLength() >= maxVelocity)
		velocity.SetLength(maxVelocity);

	float dy, dx;
	dx = GetPos().GetX() + GetRect().w / 2 - GetMousePosX();
	dy = GetPos().GetY() + GetRect().h / 2 - GetMousePosY();

	angle = atan2(dy, dx);

	accleration.SetAngle(angle);	

	if (SDL_GetTicks() * 0.001 - previousTime >= maxTime && mouseButtonPressed)
	{
		previousTime = SDL_GetTicks() * 0.001;
		ShootProjectiles(objectSpawner.GetProjectiles());
	}
}

void Player::ShootProjectiles(Projectile &projectile)
{
	projectile.SetPos(Vector(GetPos().GetX() + GetRect().w / 2 - cos(angle) * GetRect().h / 2
		, GetPos().GetY() + GetRect().h / 2 - sin(angle) * GetRect().h / 2));

	projectile.SetActive(true);
	projectile.SetReady(false);

	projectile.SetProjectileAngle(angle);

	projectile.SetScale(Vector(.5, .5));	
}

void Player::HandleEvents(SDL_Event event)
{
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

	if (currentKeyStates[SDL_SCANCODE_W])
		velocity.SubTo(accleration);

	else if (currentKeyStates[SDL_SCANCODE_S])
		velocity.AddTo(accleration);

	if (event.type == SDL_MOUSEBUTTONDOWN)
		mouseButtonPressed = true;
	else if (event.type == SDL_MOUSEBUTTONUP)
		mouseButtonPressed = false;
}

void Player::TakeDamage()
{

}

void Player::Renderer()
{
	RenderEx(accleration.GetAngle() - (90 * 3.14 / 180));
}

