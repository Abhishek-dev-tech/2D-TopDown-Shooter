#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include "ObjectSpawner.h"


class Game
{
public:
	Game();
	~Game();

	void Init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	void HandleEvents();
	void Update();
	void Renderer();
	void Clean();

	bool Running() { return isRunning; }

private:
	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;

	Player player;
	ObjectSpawner objectSpawner;

	float maxTime, previousTime;
};
