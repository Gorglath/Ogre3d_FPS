#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include "Sound.h"
#include <map>
#include <string>
class SoundManager
{
    public:
    SoundManager() = default;
    ~SoundManager() = default;

    void loadSounds();
    void playSound(const char* name, int channel,bool override);
    void loopSound(const char* name, int channel, bool override);
    void stopSound(int channel);

    inline bool getIsPlaying(int channel) const {return Mix_Playing(channel);} 
    private:
    std::string m_sounds_Folder_path = "\\Assets\\sounds\\";
    std::map<std::string,Sound> m_gameSounds = 
    {
        {"Enemy_Death",Sound()},
        {"Enemy_Hit",Sound()},
        {"Gun_Shot",Sound()},
        {"Enemy_Spawn",Sound()},
        {"Round_1",Sound()},
        {"Round_2",Sound()},
        {"Round_3",Sound()},
        {"Music",Sound()},
        {"Player_Hit",Sound()}
    };
};

#endif