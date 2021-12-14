#include "SimpleEnemy.h"

void SimpleEnemy::update(Vector3& targetPosition, float dt)
{
	Ogre::Vector3 moveDirection = (targetPosition - m_enemy_Node->getPosition());
	moveDirection.normalise();
	moveDirection.y = 0.0f;

	m_enemy_Node->translate(moveDirection * dt * m_movement_Speed);

	targetPosition.y = 0.0f;
	m_enemy_Node->lookAt(targetPosition, Ogre::Node::TransformSpace::TS_WORLD);
}
