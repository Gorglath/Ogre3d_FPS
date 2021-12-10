#pragma once
#include <Ogre.h>
#include <OgreApplicationContext.h>
class PlayerWeapon
{
public:
	void init(Ogre::SceneManager* sceneManager,Ogre::SceneNode* weaponHolderNode);
	void setMouseButtonInput(const OgreBites::MouseButtonEvent& evt);
	void setIsShooting(bool state) { m_is_Shooting = false; }
	inline bool getShooting() const { return m_is_Shooting; }

private:
	Ogre::Vector3 m_weapon_Offset = Ogre::Vector3(0.0f,0.0f,-1.0f);
	Ogre::SceneNode* m_weapon_Node = nullptr;
	bool m_is_Shooting{ false };


};

