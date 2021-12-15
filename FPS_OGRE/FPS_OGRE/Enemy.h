#pragma once
#include "Ogre.h"

using namespace Ogre;

enum class EnemyType 
{
	NONE,
	SIMPLE,
	FLYING
};
class Enemy
{
public:
	Enemy() = default;
	~Enemy() = default;
	virtual void init(int healthAmount, float movementSpeed);
	virtual void update(Vector3 & targetPosition,float dt) {}
	virtual void takeDamage(int amount) { m_health -= amount; }
	void setEnemyNode(SceneNode* enemyNode) { m_enemy_Node = enemyNode; }
	void setEnemyMesh(Entity* enemyMesh) { m_enemy_Mesh = enemyMesh; }
	void setEnemyType(EnemyType enemyType) { m_enemy_Type = enemyType; }
	inline Vector3 getEnemyPosition() const { return m_enemy_Node->getPosition(); }
	inline Entity* getEnemyMesh() const { return m_enemy_Mesh; }
	inline EnemyType getEnemyType() const { return m_enemy_Type; }
	inline int getHealth() const { return m_health; }
	void clear(SceneManager* sceneManager);
protected:
	int m_health{ 10 };
	float m_movement_Speed{ 5 };
	SceneNode* m_enemy_Node{};
	Entity* m_enemy_Mesh{};
	EnemyType m_enemy_Type{};
};

