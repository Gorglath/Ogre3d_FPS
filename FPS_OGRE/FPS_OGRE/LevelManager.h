#pragma once
#include <Ogre.h>
#include "EnemiesManager.h"
class LevelManager
{
public:
	LevelManager() = default;
	~LevelManager() = default;
	void init(Ogre::SceneManager* sceneManager);
	void update(Ogre::SceneManager* sceneManager, float dt);
private:
	EnemiesManager m_enemies_Manager{};
};

