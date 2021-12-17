#include "Enemy.h"

void Enemy::init(int healthAmount, float movementSpeed)
{
	m_health = healthAmount;
	m_movement_Speed = movementSpeed;
}

void Enemy::clear(SceneManager* sceneManager)
{
	//Detach all the nodes attached to the enemy.
	m_enemy_Node->detachAllObjects();
	//Destroy all enemy related objects.
	sceneManager->destroyEntity(m_enemy_Mesh);
	sceneManager->destroySceneNode(m_enemy_Node);	
}
