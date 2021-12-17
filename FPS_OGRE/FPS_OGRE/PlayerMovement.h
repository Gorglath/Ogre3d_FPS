#pragma once
#include <SDL.h>
#include <Ogre.h>
#include <OgreApplicationContext.h>
class PlayerMovement
{
public:
	PlayerMovement() = default;
	~PlayerMovement() = default;
	void init(Ogre::SceneManager * sceneManager);
	void update(float dt);
	void setKeyboardInput(const OgreBites::KeyboardEvent& evt);
	void setMouseMovementInput(const OgreBites::MouseMotionEvent& evt);
	void clear(Ogre::SceneManager* sceneManager);
	inline Ogre::Camera* getPlayerCamera() const { return m_player_Camera; }
	inline Ogre::SceneNode* getCameraNode() const { return m_camera_Pitch_Node; }
	inline Ogre::Vector3 getPlayerPosition() const { return m_camera_Node->getPosition(); }
private:
	void keyPressed(const OgreBites::KeyboardEvent& evt);
	void keyReleased(const OgreBites::KeyboardEvent& evt);
	void applyTranslation(float dt);
	void stopPlayer();
	void startLerping();
	void calculateDesiredDirection();
	void boundPlayerDirection(Ogre::Vector3& direction);
	Ogre::Vector3 Lerp(Ogre::Vector3 start, Ogre::Vector3 end, float percent);
	Ogre::Camera* m_player_Camera = nullptr;
	Ogre::SceneNode* m_camera_Node = nullptr;
	Ogre::SceneNode* m_camera_Yaw_Node = nullptr;
	Ogre::SceneNode* m_camera_Pitch_Node = nullptr;
	Ogre::SceneNode* m_camera_Roll_Node = nullptr;
	Ogre::Vector3 m_move_Direction = Ogre::Vector3::ZERO;
	Ogre::Vector3 m_desired_Direction = Ogre::Vector3::ZERO;;
	SDL_Keycode m_last_Key_Pressed = SDLK_0;
	float m_speed{ 10.0f };
	float m_camera_Pivot_Pitch{ 0 };
	float m_lerping_Percentage{ 0 };
	float m_lerping_Speed{ 4.0f };
	float m_player_Box_Bound_Value{ 90.0f };
	bool m_lerping{ false };
	bool m_running{ false };
	bool m_moving_Forward{ false };
	bool m_moving_Backward{ false };
	bool m_moving_Left{ false };
	bool m_moving_Right{ false };
	int m_number_Of_Keys_Pressed{ 0 };
};

