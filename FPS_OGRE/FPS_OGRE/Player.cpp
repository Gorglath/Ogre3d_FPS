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
    SDL_SetRelativeMouseMode(SDL_TRUE);
}

void Player::update(float dt)
{
    if (m_moving_Backward)
    {
        m_desired_Direction += Ogre::Vector3(0.0f, 0.0f, 1.0f);
    }
    if (m_moving_Forward)
    {
        m_desired_Direction += Ogre::Vector3(0.0f, 0.0f, -1.0f);
    }
    if (m_moving_Left)
    {
        m_desired_Direction += Ogre::Vector3(-1.0f, 0.0f, 0.0f);
    }
    if (m_moving_Right)
    {
        m_desired_Direction += Ogre::Vector3(1.0f, 0.0f, 0.0f);
    }
    m_desired_Direction.normalise();
    m_desired_Direction *= m_speed;
    if (m_lerping)
    {
        m_lerping_Percentage += dt * m_lerping_Speed;
        if (m_lerping_Percentage > 1.0f)
        {
            m_lerping_Percentage = 1.0f;
            m_lerping = false;
            m_move_Direction = m_desired_Direction;
        }
    }

    applyTranslation(dt);
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
    if (evt.keysym.sym == SDLK_s)
    {
        m_moving_Backward = true;
        if (m_last_Key_Pressed != SDLK_s)
        {
            m_number_Of_Keys_Pressed++;
            m_last_Key_Pressed = SDLK_s;
            startLerping();
        }
    }
    if (evt.keysym.sym == SDLK_w)
    {
        m_moving_Forward = true;
        if (m_last_Key_Pressed != SDLK_w)
        {
            m_number_Of_Keys_Pressed++;
            m_last_Key_Pressed = SDLK_w;
            startLerping();
        }
    }

    if (evt.keysym.sym == SDLK_d)
    {
        m_moving_Right = true;
        if (m_last_Key_Pressed != SDLK_d)
        {
            m_number_Of_Keys_Pressed++;
            m_last_Key_Pressed = SDLK_d;
            startLerping();
        }
    }
    if (evt.keysym.sym == SDLK_a)
    {
        m_moving_Left = true;
        if (m_last_Key_Pressed != SDLK_a)
        {
            m_number_Of_Keys_Pressed++;
            m_last_Key_Pressed = SDLK_a;
            startLerping();
        }
    }
    if (evt.keysym.sym == SDLK_LSHIFT)
    {
        m_running = true;
    }
}

void Player::keyReleased(const OgreBites::KeyboardEvent& evt)
{
    if (evt.keysym.sym == SDLK_s)
    {
        m_number_Of_Keys_Pressed--;
        m_moving_Backward = false;
    }
    if (evt.keysym.sym == SDLK_w)
    {
        m_number_Of_Keys_Pressed--;
        m_moving_Forward = false;
    }

    if (evt.keysym.sym == SDLK_d)
    {
        m_number_Of_Keys_Pressed--;
        m_moving_Right = false;
    }
    if (evt.keysym.sym == SDLK_a)
    {
        m_number_Of_Keys_Pressed--;
        m_moving_Left = false;
    }
    if (m_number_Of_Keys_Pressed <= 0)
    {
        stopPlayer();
    }
    if (evt.keysym.sym == SDLK_LSHIFT)
    {
        m_running = false;
    }
}
void Player::applyTranslation(float dt)
{
    Ogre::Vector3 newTranslation;
    if (m_move_Direction != Ogre::Vector3::ZERO)
    {
        newTranslation = Lerp(m_move_Direction, m_desired_Direction, m_lerping_Percentage);
    }
    else
    {
        newTranslation = m_desired_Direction;
        m_move_Direction = m_desired_Direction;
    }

    if (m_running)
    {
        newTranslation *= 1.7f;
    }
    m_camera_Node->translate(m_camera_Yaw_Node->getOrientation() * newTranslation * dt
        , Ogre::SceneNode::TS_LOCAL);
}
void Player::stopPlayer()
{
    m_last_Key_Pressed = SDLK_0;
    m_desired_Direction = Ogre::Vector3::ZERO;
    m_lerping_Percentage = 0.0f;
    m_lerping = true;
    m_moving_Backward = false;
    m_moving_Forward = false;
    m_moving_Right = false;
    m_moving_Left = false;
}
void Player::startLerping()
{
    m_lerping = true;
    m_lerping_Percentage = 0.0f;
    m_move_Direction = m_desired_Direction;
}
Ogre::Vector3 Player::Lerp(Ogre::Vector3 start, Ogre::Vector3 end, float percent)
{
    Ogre::Vector3 returnVector = (start + percent * (end - start));
    return returnVector;
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
