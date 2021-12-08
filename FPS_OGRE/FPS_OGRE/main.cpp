
#include "Game.h"

int main(int argc, char* argv[])
{
	Game game;
	game.initApp();
	game.getRoot()->clearEventTimes();

	while (!game.getRoot()->endRenderingQueued())
	{
		if (!game.getRoot()->renderOneFrame()) {
			break;
		}
		game.update();
	}
	game.closeApp();
	return 0;
}