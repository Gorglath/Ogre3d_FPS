#pragma once
#include <OgreApplicationContext.h>
class MouseMovementInput
{
public:
	virtual void setMouseMovementInput(const OgreBites::MouseMotionEvent& evt) {};
};