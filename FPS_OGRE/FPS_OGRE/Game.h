#pragma once

#include <Ogre.h>
#include <OgreApplicationContext.h>
#include "LevelManager.h"
#include "InputManager.h"
#include "Player.h"
#include "SoundManager.h"
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
	void setUpInputListeners();
	int m_current_Level{ 1 };
	Ogre::SceneManager* m_scene_Manager{};
	Player m_player{};
	LevelManager m_level_Manager{};
	InputManager m_input_Manager{};
	SoundManager m_sound_Manager{};
};

