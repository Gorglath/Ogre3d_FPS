#include "Player.h"
void Player::init(Ogre::SceneManager* sceneManager)
{
    m_player_Movement.init(sceneManager);
    m_player_Weapon.init(sceneManager,m_player_Movement.getCameraNode());
}

void Player::update(float dt)
{
    m_player_Movement.update(dt);
}

void Player::setKeyboardInput(const OgreBites::KeyboardEvent& evt)
{
    m_player_Movement.setKeyboardInput(evt);
}

void Player::setMouseMovementInput(const OgreBites::MouseMotionEvent& evt)
{
    m_player_Movement.setMouseMovementInput(evt);
}

void Player::setMouseButtonInput(const OgreBites::MouseButtonEvent& evt)
{
    m_player_Weapon.setMouseButtonInput(evt);
}

void Player::clear(Ogre::SceneManager* sceneManager)
{
    m_player_Movement.clear(sceneManager);
    m_player_Weapon.clear(sceneManager);
}
