#pragma once
#include "KeyboardInput.hpp"
#include "MouseMovementInput.hpp"
#include "MouseButtonInput.hpp"
#include "MouseWheelInput.hpp"
#include <OgreApplicationContext.h>
#include <vector>

using std::vector;
class InputManager : public OgreBites::InputListener
{
public:
	InputManager() = default;
	~InputManager() = default;

	void addKeyboardInputListener(KeyboardInput* listener);
	void addMouseMovementListener(MouseMovementInput* listener);
	void addMouseButtonListener(MouseButtonInput* listener);
	void addMouseWheelListener(MouseWheelInput* listener);

	void removeKeyboardInputListener(KeyboardInput* listener);
	void removeMouseMovementListener(MouseMovementInput* listener);
	void removeMouseButtonListener(MouseButtonInput* listener);
	void removeMouseWheelListener(MouseWheelInput* listener);

	bool keyPressed(const OgreBites::KeyboardEvent& evt);
	bool keyReleased(const OgreBites::KeyboardEvent& evt);
	bool mouseMoved(const OgreBites::MouseMotionEvent& evt);
	bool mousePressed(const OgreBites::MouseButtonEvent& evt);
	bool mouseReleased(const OgreBites::MouseButtonEvent& evt);
	bool mouseWheelRolled(const OgreBites::MouseWheelEvent& evt);

private:
	vector<KeyboardInput*> m_keyboard_Input_Objects{};
	vector<MouseWheelInput*> m_mouse_Wheel_Input_Objects{};
	vector<MouseButtonInput*> m_mouse_Button_Input_Objects{};
	vector<MouseMovementInput*> m_mouse_Movement_Input_Objects{};
};

