
#include <iostream>
#include "Game.h"
#include "Time.h"

int main(int argc, char* argv[])
{
	Game game;
	Time time;
	//Initialize the application.
	game.initApp();
	game.getRoot()->clearEventTimes();	
	float dt;

	//Main game loop.
	while (!game.getRoot()->endRenderingQueued())
	{
        dt = static_cast<float>(time.computeDeltaTime()) / 1000.0f;

		if (!game.getRoot()->renderOneFrame()) {
			break;
		}

		game.update(dt);
		time.delayTime();
	}
	game.closeApp();
	return 0;
}