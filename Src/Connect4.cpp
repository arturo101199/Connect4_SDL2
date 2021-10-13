#include "Application.h"
#include "Game.h"

int main(int argc, char* args[])
{
	Application aplication;
	if (!Application::isWellInitialized) return -1;

	Game* game = new Game();
	if (!game->IsWellInitialized()) return -1;

	bool isApplicationEnded = false;
	bool isGameEnded = false;

	while(!isApplicationEnded)
	{
		game->Update();
		if (game->IsGameEnded()) isApplicationEnded = true;
		else if (game->IsGameRestarted())
		{
			game->~Game();
			game = new Game();
		}
	}

	delete game;

	return 0;
}