#pragma once
#include <OgreApplicationContext.h>

class MouseButtonInput
{
public:
	virtual void setMouseButtonInput(const OgreBites::MouseButtonEvent& evt) {};
};