#include "CollisionManager.h"
#include <utility>
#include <algorithm>

using std::swap;
using std::min;
using std::max;
bool CollisionManager::checkCollisionWithEntity(Ogre::Entity* lEntity, Ogre::Entity* rEntity)
{
    return lEntity->getWorldBoundingBox().contains(rEntity->getBoundingBox());
}

bool CollisionManager::checkCollisionWithPoint(Ogre::Entity* entity, Ogre::Vector3& position)
{
	return entity->getWorldBoundingBox().contains(position);
}

bool CollisionManager::checkLineBox(Ogre::Entity* entity, Ogre::Vector3 L1, Ogre::Vector3 L2)
{
	Ogre::Vector3 Hit = Ogre::Vector3::ZERO;
	Ogre::Vector3 B1 = entity->getWorldBoundingBox().getMinimum();
	Ogre::Vector3 B2 = entity->getWorldBoundingBox().getMaximum();

	if (L2.x < B1.x && L1.x < B1.x) return false;
	if (L2.x > B2.x && L1.x > B2.x) return false;
	if (L2.y < B1.y && L1.y < B1.y) return false;
	if (L2.y > B2.y && L1.y > B2.y) return false;
	if (L2.z < B1.z && L1.z < B1.z) return false;
	if (L2.z > B2.z && L1.z > B2.z) return false;
	if (L1.x > B1.x && L1.x < B2.x &&
		L1.y > B1.y && L1.y < B2.y &&
		L1.z > B1.z && L1.z < B2.z)
	{
		return true;
	}
	if ((GetIntersection(L1.x - B1.x, L2.x - B1.x, L1, L2, Hit) && InBox(Hit, B1, B2, 1))
		|| (GetIntersection(L1.y - B1.y, L2.y - B1.y, L1, L2, Hit) && InBox(Hit, B1, B2, 2))
		|| (GetIntersection(L1.z - B1.z, L2.z - B1.z, L1, L2, Hit) && InBox(Hit, B1, B2, 3))
		|| (GetIntersection(L1.x - B2.x, L2.x - B2.x, L1, L2, Hit) && InBox(Hit, B1, B2, 1))
		|| (GetIntersection(L1.y - B2.y, L2.y - B2.y, L1, L2, Hit) && InBox(Hit, B1, B2, 2))
		|| (GetIntersection(L1.z - B2.z, L2.z - B2.z, L1, L2, Hit) && InBox(Hit, B1, B2, 3)))
	{
		return true;
	}

	return false;
}
int inline CollisionManager::InBox(Ogre::Vector3 Hit, Ogre::Vector3 B1, Ogre::Vector3 B2, const int Axis) {
	if (Axis == 1 && Hit.z > B1.z && Hit.z < B2.z && Hit.y > B1.y && Hit.y < B2.y) return 1;
	if (Axis == 2 && Hit.z > B1.z && Hit.z < B2.z && Hit.x > B1.x && Hit.x < B2.x) return 1;
	if (Axis == 3 && Hit.x > B1.x && Hit.x < B2.x && Hit.y > B1.y && Hit.y < B2.y) return 1;
	return 0;
}
int inline CollisionManager::GetIntersection(float fDst1, float fDst2, Ogre::Vector3 P1, Ogre::Vector3 P2, Ogre::Vector3& hit) {
	if ((fDst1 * fDst2) >= 0.0f) return 0;
	if (fDst1 == fDst2) return 0;
	hit = P1 + (P2 - P1) * (-fDst1 / (fDst2 - fDst1));
	return 1;
}