#pragma once
#include <OgreApplicationContext.h>

class MouseWheelInput
{
public:
	virtual void setMouseWheelInput(const OgreBites::MouseWheelEvent& evt) {};
};