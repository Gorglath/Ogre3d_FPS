#pragma once
#include <Ogre.h>
#include <OgreApplicationContext.h>
#include "KeyboardInput.hpp"
#include "MouseMovementInput.hpp"

class Player : public KeyboardInput, public MouseMovementInput
{
public:
	Player() = default;
	~Player() = default;
	void init(Ogre::SceneManager* sceneManager);
	void setKeyboardInput(const OgreBites::KeyboardEvent& evt) override;
	void setMouseMovementInput(const OgreBites::MouseMotionEvent& evt) override;
	inline Ogre::Camera* getPlayerCamera() const { return m_player_Camera; }
private:
	void keyPressed(const OgreBites::KeyboardEvent& evt);
	void keyReleased(const OgreBites::KeyboardEvent& evt);
	void moveLeft();
	void moveRight();
	void moveForward();
	void moveBackward();
	void applyTranslation(Ogre::Vector3& translation);
	Ogre::Camera* m_player_Camera;
	Ogre::SceneNode* m_camera_Node;
	Ogre::SceneNode* m_camera_Yaw_Node;
	Ogre::SceneNode* m_camera_Pitch_Node;
	Ogre::SceneNode* m_camera_Roll_Node;
	float m_camera_Pivot_Pitch{ 0 };
	bool m_moving_left{ false };
	bool m_moving_forward{ false };
	bool m_moving_right{ false };
	bool m_moving_back{ false };
};

