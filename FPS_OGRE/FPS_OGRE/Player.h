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
	inline bool getIsShooting() const { return m_player_Weapon.getShooting(); }
	inline Ogre::Camera* getPlayerCamera() const { return m_player_Movement.getPlayerCamera(); }
private:
	PlayerMovement m_player_Movement;
	PlayerWeapon m_player_Weapon;
};

