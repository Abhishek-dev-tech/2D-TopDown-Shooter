#include "Game.h"
#include "TextureManager.h"


Game::Game()
	:player("res/Player.png", Vector(400, 300))
{}

Game::~Game()
{}

void Game::Init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen, bool Windowed)
{
	int flag = 0;	

	if (fullscreen)
		flag = SDL_WINDOW_FULLSCREEN;
	else if(Windowed)
		flag = SDL_WINDOW_MAXIMIZED;

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

	objectSpawner.SpawnProjectile(renderer);
	objectSpawner.SpawnEnemy(renderer);
	
}

void Game::HandleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}

	objectSpawner.HandleEvents(event);
	player.HandleEvents(event);
}

void Game::Update()
{
	player.Update(objectSpawner);
	objectSpawner.Update();
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