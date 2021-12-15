#include "Enemy.h"

void Enemy::init(int healthAmount, float movementSpeed)
{
	m_health = healthAmount;
	m_movement_Speed = movementSpeed;
}

void Enemy::clear(SceneManager* sceneManager)
{
	m_enemy_Node->detachAllObjects();
	sceneManager->destroyEntity(m_enemy_Mesh);
	sceneManager->destroySceneNode(m_enemy_Node);	
}
