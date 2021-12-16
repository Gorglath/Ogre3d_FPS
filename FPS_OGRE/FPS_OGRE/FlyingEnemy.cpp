#include "FlyingEnemy.h"

void FlyingEnemy::takeDamage(int amount)
{
	m_enemy_Mesh->setMaterialName(m_hurt_Material_Name);
	m_is_Took_Damage = true;
	m_health--;
	m_timer = 0;
}

void FlyingEnemy::update(Vector3& targetPosition, float dt)
{
	Ogre::Vector3 moveDirection = (targetPosition - m_enemy_Node->getPosition());
	moveDirection.normalise();

	m_enemy_Node->translate(moveDirection * dt * m_movement_Speed);

	m_enemy_Node->lookAt(targetPosition, Ogre::Node::TransformSpace::TS_WORLD);

	if (m_is_Took_Damage)
	{
		m_timer += dt;
		if (m_timer >= m_hurt_Material_Duration)
		{
			m_enemy_Mesh->setMaterialName(m_default_Material_Name);
			m_is_Took_Damage = false;
		}
	}
}
