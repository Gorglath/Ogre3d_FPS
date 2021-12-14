#pragma once
#include "Enemy.h"
#include "Ogre.h"

using namespace Ogre;
class FlyingEnemy :public Enemy
{
public:
	FlyingEnemy() = default;
	~FlyingEnemy() = default;
	void update(Vector3 & targetPosition, float dt) override;
};

