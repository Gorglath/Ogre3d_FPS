#include "Player.h"

void Player::init(Ogre::SceneManager* sceneManager)
{
    //Create a new node to handle the camera.
    m_camera_Node = sceneManager->getRootSceneNode()->createChildSceneNode();
    m_camera_Node->setPosition(0, 5, 15);

    m_camera_Yaw_Node = m_camera_Node->createChildSceneNode();

    m_camera_Pitch_Node = m_camera_Yaw_Node->createChildSceneNode();

    // create the camera and attach it to the camera node.
    m_player_Camera = sceneManager->createCamera("myCam");
    m_player_Camera->setNearClipDistance(5); // specific to this sample
    m_player_Camera->setAutoAspectRatio(true);
    m_camera_Pitch_Node->attachObject(m_player_Camera);
}

void Player::setKeyboardInput(const OgreBites::KeyboardEvent& evt)
{
    if (evt.type == OgreBites::EventType::KEYDOWN) 
    {
        keyPressed(evt);
    }
    else if (evt.type == OgreBites::EventType::KEYUP)
    {
        keyReleased(evt);
    }
}

void Player::keyPressed(const OgreBites::KeyboardEvent& evt)
{
    if (evt.keysym.sym == OgreBites::SDLK_DOWN || m_moving_back)
    {
        m_moving_forward = false;
        m_moving_back = true;
        moveBackward();
    }
    if (evt.keysym.sym == OgreBites::SDLK_UP || m_moving_forward)
    {
        m_moving_back = false;
        m_moving_forward = true;
        moveForward();
    }

    if (evt.keysym.sym == OgreBites::SDLK_RIGHT || m_moving_right)
    {
        m_moving_left = false;
        m_moving_right = true;
        moveRight();
    }
    if (evt.keysym.sym == OgreBites::SDLK_LEFT || m_moving_left)
    {
        m_moving_right = false;
        m_moving_left = true;
        moveLeft();
    }
}

void Player::keyReleased(const OgreBites::KeyboardEvent& evt)
{
    if (evt.keysym.sym == OgreBites::SDLK_DOWN)
    {
        //Move the camera node by the new position.
        m_moving_back = false;
    }
    else if (evt.keysym.sym == OgreBites::SDLK_UP)
    {
        m_moving_forward = false;
    }

    if (evt.keysym.sym == OgreBites::SDLK_RIGHT)
    {
        m_moving_right = false;
    }
    else if (evt.keysym.sym == OgreBites::SDLK_LEFT)
    {
        m_moving_left = false;
    }
}
void Player::moveLeft()
{
    Ogre::Vector3 m_camera_Translation = Ogre::Vector3(-1.0f, 0.0f, 0.0f);
    applyTranslation(m_camera_Translation);
}
void Player::moveRight()
{
    Ogre::Vector3 m_camera_Translation = Ogre::Vector3(1.0f, 0.0f, 0.0f);
    applyTranslation(m_camera_Translation);
}
void Player::moveForward()
{
    Ogre::Vector3 m_camera_Translation = Ogre::Vector3(0.0f, 0.0f, -1.0f);
    applyTranslation(m_camera_Translation);
}
void Player::moveBackward()
{
    //Move the camera node by the new position.
    Ogre::Vector3 m_camera_Translation = Ogre::Vector3(0.0f, 0.0f, 1.0f);
    applyTranslation(m_camera_Translation);
}
void Player::applyTranslation(Ogre::Vector3& translation)
{
    m_camera_Node->translate(m_camera_Yaw_Node->getOrientation() * translation
        , Ogre::SceneNode::TS_LOCAL);
}
void Player::setMouseMovementInput(const OgreBites::MouseMotionEvent& evt)
{
    m_camera_Yaw_Node->yaw(Ogre::Degree(-0.5f * evt.xrel), Ogre::Node::TS_PARENT);
    float deltaPitch = -0.5f * evt.yrel;
    // bound the pitch
    if (!(m_camera_Pivot_Pitch + deltaPitch > 25 && deltaPitch > 0) &&
        !(m_camera_Pivot_Pitch + deltaPitch < -60 && deltaPitch < 0))
    {
        m_camera_Pitch_Node->pitch(Ogre::Degree(deltaPitch), Ogre::Node::TS_LOCAL);
        m_camera_Pivot_Pitch += deltaPitch;
    }
}
