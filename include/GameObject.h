#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Vector.h"

class GameObject : protected Vector
{
public:
	GameObject(const char* texturesheet, Vector _pos);

	GameObject() = default;

	void RenderEx(float angle);
	Vector GetPos();
	void SetPos(Vector value);

	Vector GetScale();
	void SetScale(Vector value);

	SDL_Rect GetRect();

	void SetRenderer(SDL_Renderer* renderer);
	SDL_Renderer* GetRenderer();

	SDL_Texture* GetTexture();

	int GetMousePosX();
	int GetMousePosY();



private:

	Vector position;
	Vector scale;

	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect;
	SDL_Renderer* renderer;

	const char* texturesheet;

	int mouseX, mouseY;
};
