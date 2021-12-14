#pragma once
#include <Ogre.h>
#include "Enemy.h"
using namespace Ogre;
class EnemyFactories
{
public:
	static Enemy* CreateBaseEnemy(SceneManager* sceneManager, Vector3& position, Vector3& scale, const char* name)
	{
		Enemy* enemy = new Enemy();
		SceneNode* enemyNode = sceneManager->getRootSceneNode()->createChildSceneNode();
		enemyNode->setPosition(position);
		Entity* enemyMesh = sceneManager->createEntity(name, "Demon.mesh");
		enemyMesh->setMaterialName("Demon");
		enemyNode->attachObject(enemyMesh);
		enemyNode->setScale(scale);

		enemy->setEnemyNode(enemyNode);
		enemy->setEnemyMesh(enemyMesh);
		return enemy;
	}
};