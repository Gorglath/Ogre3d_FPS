#include "PlayerWeapon.h"
#include "OgreLog.h"
void PlayerWeapon::init(Ogre::SceneManager* sceneManager,Ogre::SceneNode* weaponHolderNode)
{
	m_weapon_Offset = Ogre::Vector3(0.2f, -0.2f, -1.0f);
	m_weapon_Node = weaponHolderNode->createChildSceneNode();
	m_weapon_Node->setPosition(m_weapon_Offset);
	Ogre::Entity* weaponEnt = sceneManager->createEntity("Weapon", "Gun.mesh");
	weaponEnt->setMaterialName("Examples/Rockwall");
	m_weapon_Node->attachObject(weaponEnt);
	m_weapon_Node->scale(0.1f, 0.1f, 0.1f);
	m_weapon_Node->yaw(Ogre::Degree(3.0f));
	m_weapon_Node->pitch(Ogre::Degree(5.0f));

}

void PlayerWeapon::setMouseButtonInput(const OgreBites::MouseButtonEvent& evt)
{
	Ogre::Log log("MouseButtonPress");
	if (evt.button == OgreBites::BUTTON_LEFT)
	{
		if (evt.type == OgreBites::MOUSEBUTTONDOWN)
		{
			log.logMessage("PressedLeftButton");
		}
		else if (evt.type == OgreBites::MOUSEBUTTONUP)
		{
			log.logMessage("ReleasedLeftButton");
		}
	}
}


