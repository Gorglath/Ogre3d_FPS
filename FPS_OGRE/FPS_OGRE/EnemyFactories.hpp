#pragma once
#include <Ogre.h>

using namespace Ogre;
class EnemyFactories
{
public:
	static SceneNode* CreateBaseEnemy(SceneManager* sceneManager, Vector3& position, Vector3& scale, const char* name)
	{
		SceneNode* enemyNode = sceneManager->getRootSceneNode()->createChildSceneNode();
		enemyNode->setPosition(position);

		Entity* enemy = sceneManager->createEntity(name, "Demon.mesh");
		enemy->setMaterialName("Demon");
		enemyNode->attachObject(enemy);
		enemyNode->setScale(scale);

		return enemyNode;
	}
};