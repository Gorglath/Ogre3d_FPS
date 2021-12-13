#include "PlayerWeapon.h"
void PlayerWeapon::init(Ogre::SceneManager* sceneManager,Ogre::SceneNode* weaponHolderNode)
{
	m_weapon_Offset = Ogre::Vector3(0.2f, -0.2f, -1.0f);
	m_weapon_Node = weaponHolderNode->createChildSceneNode();
	m_weapon_Node->setPosition(m_weapon_Offset);

	Ogre::Entity* weaponEnt = sceneManager->createEntity("Weapon", "Gun.mesh");
	weaponEnt->setMaterialName("Gun");
	m_weapon_Node->attachObject(weaponEnt);
	
	m_weapon_Node->scale(0.1f, 0.1f, 0.1f);

	m_weapon_Node->yaw(Ogre::Degree(90.0f));
	m_weapon_Node->pitch(Ogre::Degree(90.0f));

}

void PlayerWeapon::setMouseButtonInput(const OgreBites::MouseButtonEvent& evt)
{
	if (evt.button == OgreBites::BUTTON_LEFT)
	{
		if (evt.type == OgreBites::MOUSEBUTTONDOWN)
		{
			m_is_Shooting = true;
		}
		else if (evt.type == OgreBites::MOUSEBUTTONUP)
		{
			m_is_Shooting = false;
		}
	}
}


