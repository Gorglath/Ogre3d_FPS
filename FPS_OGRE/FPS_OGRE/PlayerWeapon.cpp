#include "PlayerWeapon.h"

void PlayerWeapon::init(Ogre::SceneManager* sceneManager,Ogre::SceneNode* weaponHolderNode)
{
	m_weapon_Offset = Ogre::Vector3(0.3f, -0.2f, -1.0f);
	m_weapon_Node = weaponHolderNode->createChildSceneNode();
	m_weapon_Node->setPosition(m_weapon_Offset);
	Ogre::Entity* weaponEnt = sceneManager->createEntity("Weapon", "Gun.mesh");
	weaponEnt->setMaterialName("Examples/Rockwall");
	m_weapon_Node->attachObject(weaponEnt);
	m_weapon_Node->scale(0.2f, 0.2f, 0.2f);
	m_weapon_Node->yaw(Ogre::Degree(5.0f));

}

