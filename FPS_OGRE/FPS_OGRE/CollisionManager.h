#pragma once
#include <Ogre.h>
class CollisionManager
{
public:
	static bool checkCollision(Ogre::Entity* lEntity, Ogre::Entity* rEntity);
	static bool checkLineBox(Ogre::Entity* entity, Ogre::Vector3 lineStart, Ogre::Vector3 lineDirection);
private:
	CollisionManager();
	static int inline GetIntersection(float fDst1, float fDst2, Ogre::Vector3 P1, Ogre::Vector3 P2, Ogre::Vector3& hit);
	static int inline InBox(Ogre::Vector3 Hit, Ogre::Vector3 B1, Ogre::Vector3 B2, const int Axis);
};

