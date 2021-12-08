#include "InputManager.h"
#include <OgreLog.h>
#include <algorithm>
using std::find;

void InputManager::addKeyboardInputListener(KeyboardInput* listener)
{
    //Check if the object already listening for input.
    if (find(m_keyboard_Input_Objects.begin(), m_keyboard_Input_Objects.end(), listener) == m_keyboard_Input_Objects.end())
    {
        m_keyboard_Input_Objects.push_back(listener);
    }
    else
    {
        //Element already listening.
    }
}

void InputManager::addMouseMovementListener(MouseMovementInput* listener)
{
    if (find(m_mouse_Movement_Input_Objects.begin(), m_mouse_Movement_Input_Objects.end(), listener) == m_mouse_Movement_Input_Objects.end())
    {
        m_mouse_Movement_Input_Objects.push_back(listener);
    }
    else
    {
        //Element already listening.
    }
}

void InputManager::addMouseButtonListener(MouseButtonInput* listener)
{
    if (find(m_mouse_Button_Input_Objects.begin(), m_mouse_Button_Input_Objects.end(), listener) == m_mouse_Button_Input_Objects.end())
    {
        m_mouse_Button_Input_Objects.push_back(listener);
    }
    else
    {
        //Element already listening.
    }
}

void InputManager::addMouseWheelListener(MouseWheelInput* listener)
{
    if (find(m_mouse_Wheel_Input_Objects.begin(), m_mouse_Wheel_Input_Objects.end(), listener) == m_mouse_Wheel_Input_Objects.end())
    {
        m_mouse_Wheel_Input_Objects.push_back(listener);
    }
    else
    {
        //Element already listening.
    }
}

void InputManager::removeKeyboardInputListener(KeyboardInput* listener)
{
    auto it = find(m_keyboard_Input_Objects.begin(), m_keyboard_Input_Objects.end(), listener);

    if (it != m_keyboard_Input_Objects.end())
    {
        m_keyboard_Input_Objects.erase(it);
    }
    else
    {
        //Element not found.
    }
}

void InputManager::removeMouseMovementListener(MouseMovementInput* listener)
{
    auto it = find(m_mouse_Movement_Input_Objects.begin(), m_mouse_Movement_Input_Objects.end(), listener);
    
    if (it != m_mouse_Movement_Input_Objects.end())
    {
        m_mouse_Movement_Input_Objects.erase(it);
    }
    else
    {
        //Element not found.
    }
}

void InputManager::removeMouseButtonListener(MouseButtonInput* listener)
{
    auto it = find(m_mouse_Button_Input_Objects.begin(), m_mouse_Button_Input_Objects.end(), listener);

    if (it != m_mouse_Button_Input_Objects.end())
    {
        m_mouse_Button_Input_Objects.erase(it);
    }
    else
    {
        //Element not found.
    }
}

void InputManager::removeMouseWheelListener(MouseWheelInput* listener)
{
    auto it = find(m_mouse_Wheel_Input_Objects.begin(), m_mouse_Wheel_Input_Objects.end(), listener);

    if (it != m_mouse_Wheel_Input_Objects.end())
    {
        m_mouse_Wheel_Input_Objects.erase(it);
    }
    else
    {
        //Element not found.
    }
}

bool InputManager::keyPressed(const OgreBites::KeyboardEvent& evt)
{
    Ogre::Log log("KeyboardEvent");
    log.logMessage("PressedKeyboard");
    for (auto& object : m_keyboard_Input_Objects)
    {
        object->setKeyboardInput(evt);
    }
    return true;
}

bool InputManager::keyReleased(const OgreBites::KeyboardEvent& evt)
{
    Ogre::Log log("KeyboardEvent");
    log.logMessage("ReleasedKeyboard");
    for (auto& object : m_keyboard_Input_Objects)
    {
        object->setKeyboardInput(evt);
    }
    return false;
}

bool InputManager::mouseMoved(const OgreBites::MouseMotionEvent& evt)
{
    Ogre::Log log("MouseMoveEvent");
    log.logMessage("MovedMouse");
    for (auto& object : m_mouse_Movement_Input_Objects)
    {
        object->setMouseMovementInput(evt);
    }
    return false;
}

bool InputManager::mousePressed(const OgreBites::MouseButtonEvent& evt)
{
    Ogre::Log log("MouseButtonEvent");
    log.logMessage("MousePressed");
    for (auto& object : m_mouse_Button_Input_Objects)
    {
        object->setMouseButtonInput(evt);
    }
    return false;
}

bool InputManager::mouseReleased(const OgreBites::MouseButtonEvent& evt)
{
    Ogre::Log log("MouseButtonEvent");
    log.logMessage("MouseReleased");
    for (auto& object : m_mouse_Button_Input_Objects)
    {
        object->setMouseButtonInput(evt);
    }
    return false;
}

bool InputManager::mouseWheelRolled(const OgreBites::MouseWheelEvent& evt)
{
    Ogre::Log log("MouseWheelEvent");
    log.logMessage("MouseWheelRolled");
    for (auto& object : m_mouse_Wheel_Input_Objects)
    {
        object->setMouseWheelInput(evt);
    }
    return false;
}
