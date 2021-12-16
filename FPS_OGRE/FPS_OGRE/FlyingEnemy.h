#pragma once
#include "Enemy.h"
#include "Ogre.h"

using namespace Ogre;
class FlyingEnemy :public Enemy
{
public:
	FlyingEnemy() = default;
	~FlyingEnemy() = default;
	void takeDamage(int amount) override;
	void update(Vector3 & targetPosition, float dt) override;
private:
	String m_default_Material_Name{ "FlyingDemon" };
	String m_hurt_Material_Name{ "FlyingDemon_Hurt" };
};

