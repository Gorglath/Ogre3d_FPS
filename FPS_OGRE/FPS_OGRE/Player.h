#pragma once
#include <Ogre.h>
#include <OgreApplicationContext.h>
class Player
{
public:
	Player() = default;
	~Player() = default;
	void init(Ogre::SceneManager* sceneManager);
	bool keyPressed(const OgreBites::KeyboardEvent& evt);
	inline Ogre::Camera* getPlayerCamera() const { return m_player_Camera; }
private:
	Ogre::Camera* m_player_Camera;
	Ogre::SceneNode* m_camera_Node;
};

