#include "Sound.h"

void Sound::loadSound(const char* name)
{
    m_sound = Mix_LoadWAV(name);
}
void Sound::loopSound(int channel, bool override)
{
    playSound(channel, override, -1);
}

void Sound::playSound(int channel, bool override)
{
    playSound(channel, override, 0);
}
void Sound::playSound(int channel, bool override, int loops)
{
    if (!Mix_Playing(channel) && !override)
    {
        Mix_PlayChannel(channel, m_sound, loops);
    }
    else if (override)
    {
        Mix_HaltChannel(channel);
        Mix_PlayChannel(channel, m_sound, loops);
    }
}