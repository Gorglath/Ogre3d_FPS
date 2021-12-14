#pragma once
#include "Enemy.h"
#include "Ogre.h"

using namespace Ogre;
class SimpleEnemy :public Enemy
{
public:
	SimpleEnemy() = default;
	~SimpleEnemy() = default;
	void update(Vector3& targetPosition,float dt) override;
};

