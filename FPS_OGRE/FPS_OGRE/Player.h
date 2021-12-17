#pragma once
#include <Ogre.h>
#include <OgreApplicationContext.h>
#include "KeyboardInput.hpp"
#include "MouseMovementInput.hpp"
#include "MouseButtonInput.hpp"
#include "PlayerMovement.h"
#include "PlayerWeapon.h"

class Player : public KeyboardInput, public MouseMovementInput, public MouseButtonInput
{
public:
	Player() = default;
	~Player() = default;
	void init(Ogre::SceneManager* sceneManager);
	void update(float dt);
	void setKeyboardInput(const OgreBites::KeyboardEvent& evt) override;
	void setMouseMovementInput(const OgreBites::MouseMotionEvent& evt) override;
	void setMouseButtonInput(const OgreBites::MouseButtonEvent& evt) override;
	void setIsShooting(bool state) { m_player_Weapon.setIsShooting(state); }
	void clear(Ogre::SceneManager* sceneManager);
	void takeDamage(int amount);
	inline Ogre::Camera* getPlayerCamera() const { return m_player_Movement.getPlayerCamera(); }
	inline Ogre::Vector3 getPlayerPosition() const { return m_player_Movement.getPlayerPosition(); }
	inline bool getIsShooting() const { return m_player_Weapon.getShooting(); }
	inline bool getIsQuiting() const { return m_quit; }
	inline bool getIsDead() const { return m_is_Dead; }
private:
	int m_player_Health{ 3 };
	bool m_is_Dead{ false };
	bool m_quit{ false };
	PlayerMovement m_player_Movement;
	PlayerWeapon m_player_Weapon;
};

