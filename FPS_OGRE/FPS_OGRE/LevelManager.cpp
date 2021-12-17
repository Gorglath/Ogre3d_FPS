#include "LevelManager.h"

void LevelManager::init(Ogre::SceneManager* sceneManager, int levelNumber)
{
	//Create the room.
	Ogre::SceneNode* roomNode = sceneManager->getRootSceneNode()->createChildSceneNode();
	roomNode->scale(10, 10, 10);
	roomNode->setPosition(0.0f, 100.0f, 0.0f);
	Ogre::Entity* room = sceneManager->createEntity("Room.mesh");

	//Set the room parameters and materials.
	room->setMaterialName("Room");
	room->setCastShadows(false);

	//Add the room to the scene.
	roomNode->attachObject(room);

	//Load the current level from a file.
	LevelParser parser;
	if (parser.tryParseLevel(levelNumber))
	{
		int numberOfSimpleEnemies = parser.getNumberOfSimpleEnemies();
		int numberOfFlyingEnemies = parser.getNumberOfFlyingEnemies();
		int maxSpawnTime = parser.getMaxSpawnTime();
		int minSpawnTime = parser.getMinSpawnTime();
		int difficulty = parser.getDifficulty();

		m_enemies_Manager.init(numberOfSimpleEnemies, numberOfFlyingEnemies, maxSpawnTime, minSpawnTime,difficulty);
	}
}

void LevelManager::update(Ogre::SceneManager* sceneManager, float dt, Ogre::Vector3 playerPos,SoundManager& soundManager)
{
	m_enemies_Manager.update(sceneManager, dt,playerPos,soundManager);
}

void LevelManager::checkIfHitEnemy(Ogre::SceneManager* sceneManager, Ogre::Ray& shootingRay, SoundManager& soundManager)
{
	m_enemies_Manager.damageEnemy(sceneManager, shootingRay, soundManager);
}

bool LevelManager::checkIfPlayerGotHit(Ogre::SceneManager* sceneManager, Ogre::Vector3 playerPos)
{
	return m_enemies_Manager.checkIfCollidingWithPosition(sceneManager,playerPos);
}

void LevelManager::clear(Ogre::SceneManager* sceneManager)
{
	m_enemies_Manager.clear(sceneManager);
}
