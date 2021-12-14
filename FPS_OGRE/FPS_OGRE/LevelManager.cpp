#include "LevelManager.h"

void LevelManager::init(Ogre::SceneManager* sceneManager)
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
	
	m_enemies_Manager.init(100, 5, 2);
}

void LevelManager::update(Ogre::SceneManager* sceneManager, float dt, Ogre::Vector3& playerPos)
{
	m_enemies_Manager.update(sceneManager, dt,playerPos);
}

void LevelManager::checkIfHitEnemy(Ogre::SceneManager* sceneManager, Ogre::Ray& shootingRay)
{
	m_enemies_Manager.damageEnemy(sceneManager, shootingRay);
}
