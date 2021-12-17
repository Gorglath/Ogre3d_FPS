#include "Player.h"
void Player::init(Ogre::SceneManager* sceneManager)
{
    m_player_Health = 3;
    m_is_Dead = false;
    m_player_Movement.init(sceneManager);
    m_player_Weapon.init(sceneManager,m_player_Movement.getCameraNode());
}

void Player::update(float dt)
{
    m_player_Movement.update(dt);
    m_player_Weapon.update(dt);
}

void Player::setKeyboardInput(const OgreBites::KeyboardEvent& evt)
{
    if (evt.keysym.sym == SDLK_ESCAPE)
    {
        m_quit = true;
    }
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

void Player::takeDamage(int amount)
{
    m_player_Health--;
    if (m_player_Health <= 0)
    {
        m_is_Dead = true;
    }
}
