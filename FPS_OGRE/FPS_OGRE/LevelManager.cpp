#include "LevelManager.h"

void LevelManager::init(Ogre::SceneManager* sceneManager)
{
	//Generate a basic plane mesh to serve as a ground.
	Ogre::MeshManager::getSingleton().createPlane("floor", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		Ogre::Plane(Ogre::Vector3::UNIT_Y, 0), 100, 100, 10, 10, true, 1, 10, 10, Ogre::Vector3::UNIT_Z);
	
	//Create a new entity which will be populated by the basic plane mesh (names must match).
	Ogre::Entity* floor = sceneManager->createEntity("Floor", "floor");

	//Set the entity parameters and materials.
	floor->setMaterialName("Examples/Rockwall");
	floor->setCastShadows(false);

	//Add the entity to the root scene.
	sceneManager->getRootSceneNode()->attachObject(floor);
}