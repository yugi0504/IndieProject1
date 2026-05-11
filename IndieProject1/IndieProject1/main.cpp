#include "GameManager.hpp"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	GameManager game;

	if (!game.Initialize())
	{
		return -1;
	}

	game.Run();

	game.Finalize();

	return 0;
}