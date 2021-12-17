#include "CollisionManager.h"
#include <utility>
#include <algorithm>

using std::swap;
using std::min;
using std::max;
/// <summary>
/// Check if the entities collide.
/// </summary>
/// <param name="lEntity"></param>
/// <param name="rEntity"></param>
/// <returns></returns>
bool CollisionManager::checkCollisionWithEntity(Ogre::Entity* lEntity, Ogre::Entity* rEntity)
{
	//Check if the entities are valid in the scene.
	if (lEntity->isAttached() && rEntity->isAttached())
	{
		return lEntity->getWorldBoundingBox().contains(rEntity->getBoundingBox());
	}
}
/// <summary>
/// Check if a certain point is colliding with enemy.
/// </summary>
/// <param name="entity"></param>
/// <param name="v"></param>
/// <returns></returns>
bool CollisionManager::checkCollisionWithPoint(Ogre::Entity* entity, Ogre::Vector3& v)
{
	//Check if the entity is valid in the scene.
	if (entity->isAttached()) 
	{
		Ogre::Vector3 minimum = entity->getWorldBoundingBox().getMinimum();
		Ogre::Vector3 maximum = entity->getWorldBoundingBox().getMaximum();
		return minimum.x <= v.x && v.x <= maximum.x &&
			minimum.y <= v.y && v.y <= maximum.y &&
			minimum.z <= v.z && v.z <= maximum.z;
	}
	else {
		return false;
	}
}
/// <summary>
/// Check if a line is intercecting with an entity.
/// </summary>
/// <param name="entity"></param>
/// <param name="L1"></param>
/// <param name="L2"></param>
/// <returns></returns>
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
/// <summary>
/// Check if the point is within the given box.
/// </summary>
/// <param name="Hit"></param>
/// <param name="B1"></param>
/// <param name="B2"></param>
/// <param name="Axis"></param>
/// <returns></returns>
int inline CollisionManager::InBox(Ogre::Vector3 Hit, Ogre::Vector3 B1, Ogre::Vector3 B2, const int Axis) {
	if (Axis == 1 && Hit.z > B1.z && Hit.z < B2.z && Hit.y > B1.y && Hit.y < B2.y) return 1;
	if (Axis == 2 && Hit.z > B1.z && Hit.z < B2.z && Hit.x > B1.x && Hit.x < B2.x) return 1;
	if (Axis == 3 && Hit.x > B1.x && Hit.x < B2.x && Hit.y > B1.y && Hit.y < B2.y) return 1;
	return 0;
}
/// <summary>
/// Get the intesection between to given points.
/// </summary>
/// <param name="fDst1"></param>
/// <param name="fDst2"></param>
/// <param name="P1"></param>
/// <param name="P2"></param>
/// <param name="hit"></param>
/// <returns></returns>
int inline CollisionManager::GetIntersection(float fDst1, float fDst2, Ogre::Vector3 P1, Ogre::Vector3 P2, Ogre::Vector3& hit) {
	if ((fDst1 * fDst2) >= 0.0f) return 0;
	if (fDst1 == fDst2) return 0;
	hit = P1 + (P2 - P1) * (-fDst1 / (fDst2 - fDst1));
	return 1;
}