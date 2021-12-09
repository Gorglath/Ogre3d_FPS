#pragma once

#include <Ogre.h>
#include <OgreApplicationContext.h>
#include "LevelManager.h"
#include "InputManager.h"
#include "Player.h"
#include "CollisionManager.h"
class Game : public OgreBites::ApplicationContext
{
public:
	Game();
	void setup();
	void update(float dt);
	bool keyPressed(const OgreBites::KeyboardEvent& evt);
private:
	Player m_player{};
	InputManager m_input_Manager{};
	Ogre::Entity* barrel = nullptr;
};

