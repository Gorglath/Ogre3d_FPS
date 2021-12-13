#include "LevelManager.h"

void LevelManager::init(Ogre::SceneManager* sceneManager)
{
	Ogre::SceneNode* roomNode = sceneManager->getRootSceneNode()->createChildSceneNode();
	roomNode->scale(10, 10, 10);
	roomNode->setPosition(0.0f, 100.0f, 0.0f);
	//Create a new entity which will be populated by the basic plane mesh (names must match).
	Ogre::Entity* floor = sceneManager->createEntity("Room.mesh");

	//Set the entity parameters and materials.
	floor->setMaterialName("Room");
	floor->setCastShadows(false);

	//Add the entity to the root scene.
	roomNode->attachObject(floor);
}