#include <Game.h>

Game game;
int main(int args, char* argc[])
{
	const int fps = 120;
	const int frameDelay = 1000 / fps;

	Uint32 frameStart;
	int frameTime;


	game.Init("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 900, false, false);

	while (game.Running())
	{
		frameStart = SDL_GetTicks();

		game.HandleEvents();
		game.Update();
		game.Renderer();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
			SDL_Delay(frameDelay - frameTime);
	}

	game.Clean();

	return 0;
}