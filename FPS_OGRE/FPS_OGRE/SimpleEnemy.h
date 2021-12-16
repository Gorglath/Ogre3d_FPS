#pragma once
#include "Enemy.h"
#include "Ogre.h"

using namespace Ogre;
class SimpleEnemy :public Enemy
{
public:
	SimpleEnemy() = default;
	~SimpleEnemy() = default;
	void takeDamage(int amount) override;
	void update(Vector3& targetPosition,float dt) override;
private:
	String m_default_Material_Name{ "Demon" };
	String m_hurt_Material_Name{ "Demon_Hurt" };
};

