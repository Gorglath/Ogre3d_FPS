#include "LevelManager.h"

void LevelManager::init(Ogre::SceneManager* sceneManager, int levelNumber)
{
	//Create the room.
	Ogre::SceneNode* roomNode = sceneManager->getRootSceneNode()->createChildSceneNode();
	roomNode->scale(10, 10, 10);
	roomNode->setPosition(0.0f, 100.0f, 0.0f);
	Ogre::Entity* floor = sceneManager->createEntity("Room.mesh");

	//Set the entity parameters and materials.
	floor->setMaterialName("Room");
	floor->setCastShadows(false);

	//Add the entity to the scene.
	roomNode->attachObject(floor);
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

void LevelManager::update(Ogre::SceneManager* sceneManager, float dt, Ogre::Vector3 playerPos)
{
	m_enemies_Manager.update(sceneManager, dt,playerPos);
}

void LevelManager::checkIfHitEnemy(Ogre::SceneManager* sceneManager, Ogre::Ray& shootingRay)
{
	m_enemies_Manager.damageEnemy(sceneManager, shootingRay);
}

bool LevelManager::checkIfPlayerGotHit(Ogre::SceneManager* sceneManager, Ogre::Vector3 playerPos)
{
	return m_enemies_Manager.checkIfCollidingWithPosition(sceneManager,playerPos);
}

void LevelManager::clear(Ogre::SceneManager* sceneManager)
{
	m_enemies_Manager.clear(sceneManager);
}
