#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

class Collision
{
public:
	static bool IsCollide(const SDL_Rect& recA, const SDL_Rect& recB);
};
