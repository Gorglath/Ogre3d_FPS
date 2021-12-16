#include "SoundManager.h"

#include <fstream>
#include <filesystem>
void SoundManager::loadSounds()
{
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
    std::filesystem::path basePath = std::filesystem::current_path();
    basePath += m_sounds_Folder_path;
    for(auto& [key,val]:m_gameSounds)
    {
        std::string path = basePath.string();
        path.append(key);
        path.append(".wav");
        const char* c = path.c_str();
        val.loadSound(c);
    }
}

void SoundManager::loopSound(const char* name, int channel, bool override = false)
{
    m_gameSounds.at(name).loopSound(channel, override);
}
void SoundManager::playSound(const char* name, int channel,bool override = false)
{
    m_gameSounds.at(name).playSound(channel,override);
}
void SoundManager::stopSound(int channel)
{
    Mix_HaltChannel(channel);
}