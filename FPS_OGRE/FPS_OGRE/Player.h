#pragma once
#include <SDL.h>
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
	void update(float dt);
	void setKeyboardInput(const OgreBites::KeyboardEvent& evt) override;
	void setMouseMovementInput(const OgreBites::MouseMotionEvent& evt) override;
	inline Ogre::Camera* getPlayerCamera() const { return m_player_Camera; }
private:
	void keyPressed(const OgreBites::KeyboardEvent& evt);
	void keyReleased(const OgreBites::KeyboardEvent& evt);
	void applyTranslation(float dt);
	void stopPlayer();
	void startLerping();
	void calculateDesiredDirection();
	Ogre::Vector3 Lerp(Ogre::Vector3 start, Ogre::Vector3 end, float percent);
	Ogre::Camera* m_player_Camera;
	Ogre::SceneNode* m_camera_Node;
	Ogre::SceneNode* m_camera_Yaw_Node;
	Ogre::SceneNode* m_camera_Pitch_Node;
	Ogre::SceneNode* m_camera_Roll_Node;
	Ogre::Vector3 m_move_Direction;
	Ogre::Vector3 m_desired_Direction;
	SDL_Keycode m_last_Key_Pressed;
	float m_speed{10.0f };
	float m_camera_Pivot_Pitch{ 0 };
	float m_lerping_Percentage{ 0 };
	float m_lerping_Speed{ 2.0f };
	bool m_lerping{ false };
	bool m_running{ false };
	bool m_moving_Forward{ false };
	bool m_moving_Backward{ false };
	bool m_moving_Left{ false };
	bool m_moving_Right{ false };
	int m_number_Of_Keys_Pressed{ 0 };
};

