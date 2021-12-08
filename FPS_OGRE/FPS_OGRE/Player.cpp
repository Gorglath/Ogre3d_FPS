#include "Player.h"

void Player::init(Ogre::SceneManager* sceneManager)
{
    //Create a new node to handle the camera.
    m_camera_Node = sceneManager->getRootSceneNode()->createChildSceneNode();
    m_camera_Node->setPosition(0, 5, 15);
    m_camera_Node->lookAt(Ogre::Vector3(0, 4, 10), Ogre::Node::TS_PARENT);

    // create the camera and attach it to the camera node.
    m_player_Camera = sceneManager->createCamera("myCam");
    m_player_Camera->setNearClipDistance(5); // specific to this sample
    m_player_Camera->setAutoAspectRatio(true);
    m_camera_Node->attachObject(m_player_Camera);
}

bool Player::keyPressed(const OgreBites::KeyboardEvent& evt)
{
    if (evt.keysym.sym == OgreBites::SDLK_DOWN)
    {
        //Move the camera node by the new position.
        Ogre::Vector3 pos = m_camera_Node->getPosition();
        Ogre::Vector3 newPos(0.0f, 0.0f, 1.0f);
        m_camera_Node->translate(newPos);
    }
    else if (evt.keysym.sym == OgreBites::SDLK_UP)
    {
        Ogre::Vector3 pos = m_camera_Node->getPosition();
        Ogre::Vector3 newPos(0.0f, 0.0f, -1.0f);
        m_camera_Node->translate(newPos);
    }

    if (evt.keysym.sym == OgreBites::SDLK_RIGHT)
    {
        Ogre::Vector3 pos = m_camera_Node->getPosition();
        Ogre::Vector3 newPos(1.0f, 0.0f, 0.0f);
        m_camera_Node->translate(newPos);
    }
    else if (evt.keysym.sym == OgreBites::SDLK_LEFT)
    {
        Ogre::Vector3 pos = m_camera_Node->getPosition();
        Ogre::Vector3 newPos(-1.0f, 0.0f, 0.0f);
        m_camera_Node->translate(newPos);
    }
    return true;
}