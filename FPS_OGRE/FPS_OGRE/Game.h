#pragma once

#include <Ogre.h>
#include <OgreApplicationContext.h>
#include "LevelManager.h"
#include "InputManager.h"
#include "Player.h"
#include "CollisionManager.h"
#include <vector>

using std::vector;
class Game : public OgreBites::ApplicationContext
{
public:
	Game();
	void setup();
	void update(float dt);
	bool keyPressed(const OgreBites::KeyboardEvent& evt);
private:
	Ogre::SceneManager* sceneManager{};
	Player m_player{};
	LevelManager m_levelManager{};
	InputManager m_input_Manager{};
};

