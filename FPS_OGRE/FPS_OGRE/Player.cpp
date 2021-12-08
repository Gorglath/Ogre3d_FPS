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
        Ogre::Vector3 newTranslation(0.0f, 0.0f, 0.0f);
        if (evt.keysym.sym == OgreBites::SDLK_DOWN)
        {
            //Move the camera node by the new position.
            newTranslation = Ogre::Vector3(0.0f, 0.0f, 1.0f);
        }
        else if (evt.keysym.sym == OgreBites::SDLK_UP)
        {
            newTranslation = Ogre::Vector3(0.0f, 0.0f, -1.0f);
        }

        if (evt.keysym.sym == OgreBites::SDLK_RIGHT)
        {
            newTranslation = Ogre::Vector3(1.0f, 0.0f, 0.0f);
        }
        else if (evt.keysym.sym == OgreBites::SDLK_LEFT)
        {
            newTranslation = Ogre::Vector3(-1.0f, 0.0f, 0.0f);
        }
        m_camera_Node->translate(m_camera_Yaw_Node->getOrientation()* m_camera_Pitch_Node->getOrientation()* newTranslation
            , Ogre::SceneNode::TS_LOCAL);
    }
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
