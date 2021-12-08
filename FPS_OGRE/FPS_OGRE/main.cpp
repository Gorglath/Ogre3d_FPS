
#include "Game.h"

int main(int argc, char* argv[])
{
	Game game;
	game.initApp();
	game.getRoot()->startRendering();
	game.closeApp();
	return 0;
}