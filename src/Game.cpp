#include "Game.h"
#include "TextureManager.h"


Game::Game()
	:player("res/Ship.png", Vector(400, 300))
{}

Game::~Game()
{}

void Game::Init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flag = 0;	

	if (fullscreen)
		flag = SDL_WINDOW_FULLSCREEN;

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)	{

		std::cout << "Everything is fine..." << std::endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flag);

		renderer = SDL_CreateRenderer(window, -1, 0);

		player.SetRenderer(renderer);

		isRunning = true;
	}
	else {
		isRunning = false;
	}

	previousTime = 0;
	maxTime = 0.75;

	objectSpawner.SpawnProjectile(renderer);
	objectSpawner.SpawnEnemy(renderer);
	
}

void Game::HandleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

	switch (event.type)
	{
	case SDL_KEYDOWN:
		if (event.key.keysym.sym == SDLK_1)
			objectSpawner.SpawnShipParts(1, renderer);
		else if (event.key.keysym.sym == SDLK_2)
			objectSpawner.SpawnShipParts(2, renderer);
		break;

	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}

	objectSpawner.HandleEvents(event);
}

void Game::Update()
{
	player.Update(objectSpawner.GetEnemiesInScene());


	objectSpawner.Update();

	if (SDL_GetTicks() * 0.001 - previousTime >= maxTime)
	{
		previousTime = SDL_GetTicks() * 0.001;
		player.ShootProjectiles(objectSpawner.GetProjectiles());
	}
}

void Game::Renderer()
{

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
	player.Renderer();
	objectSpawner.Renderer();

	SDL_RenderPresent(renderer);
}

void Game::Clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}