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
	void update(float dt);
	inline bool getShooting() const { return m_is_Shooting; }

private:
	Vector3 m_weapon_Offset = Vector3(0.0f,0.0f,-1.0f);
	SceneNode* m_weapon_Node = nullptr;
	Entity* m_weapon_Mesh = nullptr;
	Quaternion m_initial_Rotation{};
	Quaternion m_target_Rotation{};
	ParticleSystem* m_shooting_Particle_System{};
	float m_timer_Animation{ 0 };
	float m_time_To_Return_To_Initial_Rotation{ 0.3f };
	float m_timer_Particles{ 0 };
	float m_time_To_Stop_Particles{ 0.1f };
	bool m_is_Shooting{ false };
	bool m_is_Lerping{ false };
	bool m_is_Particle_Active{ false };


};

