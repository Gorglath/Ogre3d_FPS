#pragma once

#include <Ogre.h>
#include <OgreApplicationContext.h>
#include "LevelManager.h"
#include "Player.h"
class Game : public OgreBites::ApplicationContext, public OgreBites::InputListener
{
public:
	Game();
	void setup();
	bool keyPressed(const OgreBites::KeyboardEvent& evt);
private:
	Player m_player;
};

