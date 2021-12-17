#pragma once
#include <Ogre.h>
#include "Enemy.h"
#include "SimpleEnemy.h"
#include "FlyingEnemy.h"
using namespace Ogre;
class EnemyFactories
{
public:
	/// <summary>
	/// Creates a base enemy entity.
	/// </summary>
	/// <param name="sceneManager"></param>
	/// <param name="position"></param>
	/// <param name="scale"></param>
	/// <param name="name"></param>
	/// <returns></returns>
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

	/// <summary>
	/// Create a simple enemy entity.
	/// </summary>
	/// <param name="sceneManager"></param>
	/// <param name="position"></param>
	/// <param name="scale"></param>
	/// <param name="name"></param>
	/// <returns></returns>
	static SimpleEnemy* CreateSimpleEnemy(SceneManager* sceneManager, Vector3& position, Vector3& scale, const char* name)
	{
		SimpleEnemy* enemy = new SimpleEnemy();
		enemy->setEnemyType(EnemyType::SIMPLE);

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
	/// <summary>
	/// Create a flying enemy entity.
	/// </summary>
	/// <param name="sceneManager"></param>
	/// <param name="position"></param>
	/// <param name="scale"></param>
	/// <param name="name"></param>
	/// <returns></returns>
	static FlyingEnemy* CreateFlyingEnemy(SceneManager* sceneManager, Vector3& position, Vector3& scale, const char* name)
	{
		FlyingEnemy* enemy = new FlyingEnemy();
		enemy->setEnemyType(EnemyType::FLYING);

		SceneNode* enemyNode = sceneManager->getRootSceneNode()->createChildSceneNode();
		enemyNode->setPosition(position);
		Entity* enemyMesh = sceneManager->createEntity(name, "FlyingDemon.mesh");
		enemyMesh->setMaterialName("FlyingDemon");
		enemyNode->attachObject(enemyMesh);
		enemyNode->setScale(scale);

		enemy->setEnemyNode(enemyNode);
		enemy->setEnemyMesh(enemyMesh);
		return enemy;
	}
};