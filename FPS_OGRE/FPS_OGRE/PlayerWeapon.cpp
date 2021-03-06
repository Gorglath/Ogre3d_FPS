#include "PlayerWeapon.h"
void PlayerWeapon::init(SceneManager* sceneManager,SceneNode* weaponHolderNode)
{
	//Create a node to handle the weapon translation.
	m_weapon_Offset = Vector3(0.2f, -0.2f, -1.0f);
	m_weapon_Node = weaponHolderNode->createChildSceneNode();
	m_weapon_Node->setPosition(m_weapon_Offset);

	//Create the weapon entity.
	m_weapon_Mesh = sceneManager->createEntity("Weapon", "Gun.mesh");
	m_weapon_Mesh->setMaterialName("Gun");
	m_weapon_Node->attachObject(m_weapon_Mesh);
	m_weapon_Node->scale(0.1f, 0.1f, 0.1f);

	//Create a node to handle the weapon particle system.
	m_particle_Node = m_weapon_Node->createChildSceneNode();
	m_particle_Node_Offset = Vector3(1.7f,0,-0.2f);
	m_particle_Node->setPosition(m_particle_Node_Offset);
	m_particle_Node->roll(Degree(-90));

	// Create the weapon particle system.
	m_shooting_Particle_System = sceneManager->createParticleSystem("Fire", "Gun/Fire");
	m_shooting_Particle_System->setKeepParticlesInLocalSpace(false);
	m_particle_Node->attachObject(m_shooting_Particle_System);
	m_shooting_Particle_System->setEmitting(false);
	
	//Rotate the weapon to upright position.
	m_weapon_Node->yaw(Degree(85.0f));
	m_weapon_Node->pitch(Degree(90.0f));

	//Set rotation from shooting animation.
	m_initial_Rotation = m_weapon_Node->getOrientation();
	m_target_Rotation = Quaternion(Degree(45.0f),Vector3::UNIT_X) * m_initial_Rotation;
}

void PlayerWeapon::setMouseButtonInput(const OgreBites::MouseButtonEvent& evt)
{
	if (evt.button == OgreBites::BUTTON_LEFT)
	{
		if (evt.type == OgreBites::MOUSEBUTTONDOWN)
		{
			//Stop the particle system.
			m_shooting_Particle_System->setEmitting(true);
			m_weapon_Node->setOrientation(m_target_Rotation);

			m_timer_Animation = 0.0f;
			m_timer_Particles = 0.0f;

			m_is_Lerping = true;
			m_is_Shooting = true;
			m_is_Particle_Active = true;
		}
	}
}
void PlayerWeapon::clear(SceneManager* sceneManager)
{
	m_weapon_Node->detachAllObjects();

	sceneManager->destroySceneNode(m_weapon_Node);
	sceneManager->destroyEntity(m_weapon_Mesh);
}

void PlayerWeapon::update(float dt)
{
	if (m_is_Lerping)
	{
		m_timer_Animation += dt;
		//Lerp to the initial weapon rotation.
		Quaternion targetRotation = Quaternion::nlerp(m_timer_Animation/m_time_To_Return_To_Initial_Rotation, m_target_Rotation, m_initial_Rotation);
		m_weapon_Node->setOrientation(targetRotation);
		if (m_timer_Animation / m_time_To_Return_To_Initial_Rotation >= 1)
		{
			m_is_Lerping = false;
			m_timer_Animation = 0;
		}
	}

	if (m_is_Particle_Active)
	{
		m_timer_Particles += dt;
		if (m_timer_Particles >= m_time_To_Stop_Particles)
		{
			m_shooting_Particle_System->setEmitting(false);
			m_is_Particle_Active = false;
		}
	}
}


