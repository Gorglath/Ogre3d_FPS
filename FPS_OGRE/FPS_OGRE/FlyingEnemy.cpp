#include "FlyingEnemy.h"

void FlyingEnemy::update(Vector3& targetPosition, float dt)
{
	Ogre::Vector3 moveDirection = (targetPosition - m_enemy_Node->getPosition());
	moveDirection.normalise();

	m_enemy_Node->translate(moveDirection * dt * m_movement_Speed);

	m_enemy_Node->lookAt(targetPosition, Ogre::Node::TransformSpace::TS_WORLD);
}
