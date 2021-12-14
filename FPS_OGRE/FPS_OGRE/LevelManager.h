#pragma once
#include <Ogre.h>
#include "EnemiesManager.h"
class LevelManager
{
public:
	LevelManager() = default;
	~LevelManager() = default;
	void init(Ogre::SceneManager* sceneManager);
	void update(Ogre::SceneManager* sceneManager, float dt,Ogre::Vector3& playerPos);
	void checkIfHitEnemy(Ogre::SceneManager* sceneManager, Ogre::Ray& shootingRay);
private:
	EnemiesManager m_enemies_Manager{};
};

