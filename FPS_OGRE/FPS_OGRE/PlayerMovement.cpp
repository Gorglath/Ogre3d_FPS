#include "PlayerMovement.h"
#include "Player.h"
void PlayerMovement::init(Ogre::SceneManager* sceneManager)
{
    //Create a new node to handle the camera.
    m_camera_Node = sceneManager->getRootSceneNode()->createChildSceneNode();

    m_camera_Node->setPosition(0, 5, 0);
    m_camera_Yaw_Node = m_camera_Node->createChildSceneNode();

    m_camera_Pitch_Node = m_camera_Yaw_Node->createChildSceneNode();


    SceneNode* cursorNode = m_camera_Pitch_Node->createChildSceneNode();
    cursorNode->yaw(Degree(180));
    cursorNode->setPosition(Vector3(0.0f, 0.0f, -0.3f));
    cursorNode->scale(0.003f, 0.003f, 0.003f);

    Entity* cursor = sceneManager->createEntity("Cursor", "Cursor.mesh");
    cursor->setMaterialName("Cursor");
    cursorNode->attachObject(cursor);

    // create the camera and attach it to the camera node.
    m_player_Camera = sceneManager->createCamera("myCam");
    m_player_Camera->setNearClipDistance(0.1f); 
    m_player_Camera->setAutoAspectRatio(true);
    m_camera_Pitch_Node->attachObject(m_player_Camera);
    SDL_SetRelativeMouseMode(SDL_TRUE);
}

void PlayerMovement::update(float dt)
{
    calculateDesiredDirection();

    if (m_lerping)
    {
        m_lerping_Percentage += m_lerping_Speed;
        if ((m_lerping_Percentage * dt) > 1.0f)
        {
            m_lerping_Percentage = 1.0f;
            m_lerping = false;
            m_move_Direction = m_desired_Direction;
        }
    }

    applyTranslation(dt);
}

void PlayerMovement::setKeyboardInput(const OgreBites::KeyboardEvent& evt)
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

void PlayerMovement::keyPressed(const OgreBites::KeyboardEvent& evt)
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

void PlayerMovement::keyReleased(const OgreBites::KeyboardEvent& evt)
{
    if (evt.keysym.sym == SDLK_s)
    {
        m_number_Of_Keys_Pressed--;
        m_moving_Backward = false;
        if (m_number_Of_Keys_Pressed > 0)
        {
            startLerping();
        }
    }
    if (evt.keysym.sym == SDLK_w)
    {
        m_number_Of_Keys_Pressed--;
        m_moving_Forward = false;
        if (m_number_Of_Keys_Pressed > 0)
        {
            startLerping();
        }
    }

    if (evt.keysym.sym == SDLK_d)
    {
        m_number_Of_Keys_Pressed--;
        m_moving_Right = false;
        if (m_number_Of_Keys_Pressed > 0)
        {
            startLerping();
        }
    }
    if (evt.keysym.sym == SDLK_a)
    {
        m_number_Of_Keys_Pressed--;
        m_moving_Left = false;
        if (m_number_Of_Keys_Pressed > 0)
        {
            startLerping();
        }
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
void PlayerMovement::applyTranslation(float dt)
{
    Ogre::Vector3 newTranslation;
    if (m_move_Direction != Ogre::Vector3::ZERO)
    {
        newTranslation = Lerp(m_move_Direction, m_desired_Direction, m_lerping_Percentage * dt);
    }
    else
    {
        newTranslation = m_desired_Direction;
    }

    if (m_running)
    {
        newTranslation *= 1.7f;
    }
    m_camera_Node->translate(m_camera_Yaw_Node->getOrientation() * newTranslation * dt
        , Ogre::SceneNode::TS_LOCAL);
}
void PlayerMovement::stopPlayer()
{
    m_last_Key_Pressed = SDLK_0;
    m_move_Direction = Ogre::Vector3::ZERO;
    m_desired_Direction = Ogre::Vector3::ZERO;
    m_lerping_Percentage = 0.0f;
    m_lerping = true;
    m_moving_Backward = false;
    m_moving_Forward = false;
    m_moving_Right = false;
    m_moving_Left = false;
}
void PlayerMovement::startLerping()
{
    m_lerping = true;
    m_lerping_Percentage = 0.0f;
    m_move_Direction = m_desired_Direction;
}
void PlayerMovement::calculateDesiredDirection()
{
    m_desired_Direction = Ogre::Vector3::ZERO;
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
}
Ogre::Vector3 PlayerMovement::Lerp(Ogre::Vector3 start, Ogre::Vector3 end, float percent)
{
    Ogre::Vector3 returnVector = (start + percent * (end - start));
    return returnVector;
}
void PlayerMovement::setMouseMovementInput(const OgreBites::MouseMotionEvent& evt)
{
    m_camera_Yaw_Node->yaw(Ogre::Degree(-0.5f * evt.xrel), Ogre::Node::TS_PARENT);
    float deltaPitch = -0.5f * evt.yrel;
    // bound the pitch
    if (!(m_camera_Pivot_Pitch + deltaPitch > 65 && deltaPitch > 0) &&
        !(m_camera_Pivot_Pitch + deltaPitch < -60 && deltaPitch < 0))
    {
        m_camera_Pitch_Node->pitch(Ogre::Degree(deltaPitch), Ogre::Node::TS_LOCAL);
        m_camera_Pivot_Pitch += deltaPitch;
    }

}

void PlayerMovement::clear(Ogre::SceneManager* sceneManager)
{
    m_camera_Pitch_Node->detachAllObjects();
    m_camera_Yaw_Node->detachAllObjects();
    m_camera_Node->detachAllObjects();

    sceneManager->destroyCamera(m_player_Camera);
    sceneManager->destroySceneNode(m_camera_Node);
    sceneManager->destroySceneNode(m_camera_Yaw_Node);
    sceneManager->destroySceneNode(m_camera_Pitch_Node);
}
