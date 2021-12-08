#pragma once
#include <OgreApplicationContext.h>

class KeyboardInput
{
public:
	virtual void setKeyboardInput(const OgreBites::KeyboardEvent& evt) {};
};