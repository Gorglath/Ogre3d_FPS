#pragma once
#include <Ogre.h>
#include <OgreApplicationContext.h>
using namespace Ogre;
class PlayerWeapon
{
public:
	void init(SceneManager* sceneManager,SceneNode* weaponHolderNode);
	void setMouseButtonInput(const OgreBites::MouseButtonEvent& evt);
	void setIsShooting(bool state) { m_is_Shooting = false; }
	void clear(SceneManager* sceneManager);
	inline bool getShooting() const { return m_is_Shooting; }

private:
	Vector3 m_weapon_Offset = Vector3(0.0f,0.0f,-1.0f);
	SceneNode* m_weapon_Node = nullptr;
	Entity* m_weapon_Mesh = nullptr;
	bool m_is_Shooting{ false };


};

