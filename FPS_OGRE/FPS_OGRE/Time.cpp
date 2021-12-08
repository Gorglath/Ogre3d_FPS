#include "Time.h"
#include <SDL.h>
#include <algorithm>

Time::Time() : frameStart(0), lastFrame(0), frameTime(0)
{
}

Time::~Time()
{
}

unsigned int Time::computeDeltaTime()
{
    frameStart = SDL_GetTicks();
    unsigned int dt = frameStart - lastFrame;
    dt = std::min(dt, MAX_DT);
    timeSinceStart += static_cast<float>(dt) / 1000.0f;
    lastFrame = frameStart;
    return dt;    // Clamp delta time
}

void Time::delayTime()
{
    frameTime = SDL_GetTicks() - frameStart;
    if (frameTime < frameDelay) {
        SDL_Delay(frameDelay - frameTime);
    }
}

double Time::timeSinceStart = 0.0f;
