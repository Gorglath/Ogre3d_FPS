#include "PlayerWeapon.h"
void PlayerWeapon::init(SceneManager* sceneManager,SceneNode* weaponHolderNode)
{
	m_weapon_Offset = Vector3(0.2f, -0.2f, -1.0f);
	m_weapon_Node = weaponHolderNode->createChildSceneNode();
	m_weapon_Node->setPosition(m_weapon_Offset);

	m_weapon_Mesh = sceneManager->createEntity("Weapon", "Gun.mesh");
	m_weapon_Mesh->setMaterialName("Gun");
	m_weapon_Node->attachObject(m_weapon_Mesh);
	
	m_weapon_Node->scale(0.1f, 0.1f, 0.1f);

	m_weapon_Node->yaw(Degree(90.0f));
	m_weapon_Node->pitch(Degree(90.0f));

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

void PlayerWeapon::clear(SceneManager* sceneManager)
{
	m_weapon_Node->detachAllObjects();

	sceneManager->destroySceneNode(m_weapon_Node);
	sceneManager->destroyEntity(m_weapon_Mesh);
}


