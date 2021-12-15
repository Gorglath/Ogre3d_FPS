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
private:
	void restart();
	void initializeGame();
	int m_playerHealth{ 3 };
	int m_currentLevel{ 1 };
	Ogre::SceneManager* m_scene_Manager{};
	Player m_player{};
	LevelManager m_levelManager{};
	InputManager m_input_Manager{};
};

