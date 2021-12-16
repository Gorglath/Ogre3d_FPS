#pragma once
#include <Ogre.h>
#include "EnemiesManager.h"
#include "LevelParser.hpp"
class LevelManager
{
public:
	LevelManager() = default;
	~LevelManager() = default;
	void init(Ogre::SceneManager* sceneManager, int levelNumber);
	void update(Ogre::SceneManager* sceneManager, float dt,Ogre::Vector3 playerPos, SoundManager& soundManager);
	void checkIfHitEnemy(Ogre::SceneManager* sceneManager, Ogre::Ray& shootingRay, SoundManager& soundManager);
	bool checkIfPlayerGotHit(Ogre::SceneManager* sceneManager, Ogre::Vector3 playerPos);
	void clear(Ogre::SceneManager* sceneManager);
	inline bool getHasEnemyLeftToSpawn() const { return m_enemies_Manager.hasEnemyLeft(); }
private:
	EnemiesManager m_enemies_Manager{};
};

