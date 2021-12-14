#pragma once
#include "Ogre.h"

using namespace Ogre;
class Enemy
{
public:
	Enemy() = default;
	~Enemy() = default;
	virtual void init(int healthAmount, float movementSpeed) { m_health = healthAmount; m_movement_Speed = movementSpeed; }
	virtual void update(Vector3 & targetPosition,float dt) {}
	virtual void takeDamage(int amount) { m_health -= amount; }
	void setEnemyNode(SceneNode* enemyNode) { m_enemy_Node = enemyNode; }
	void setEnemyMesh(Entity* enemyMesh) { m_enemy_Mesh = enemyMesh; }
	Vector3 getEnemyPosition() const { return m_enemy_Node->getPosition(); }
	Entity* getEnemyMesh() const { return m_enemy_Mesh; }
	int getHealth() const { return m_health; }
	void clear(SceneManager* sceneManager) 
	{
		m_enemy_Node->detachAllObjects(); 
		sceneManager->destroyEntity(m_enemy_Mesh); 
		sceneManager->destroySceneNode(m_enemy_Node);
	}
protected:
	int m_health{ 10 };
	float m_movement_Speed{ 5 };
	SceneNode* m_enemy_Node{};
	Entity* m_enemy_Mesh{};
};

