#pragma once
#include <Ogre.h>d
class LevelManager
{
public:
	LevelManager() = default;
	~LevelManager() = default;
	void init(Ogre::SceneManager* sceneManager);
};

