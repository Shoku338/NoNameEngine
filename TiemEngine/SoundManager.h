#pragma once
#include "irrKlang.h"
#include <iostream>
#include <map>

using namespace std;

class SoundManager {
private:
    irrklang::ISoundEngine* soundEngine;
    map<string,irrklang::ISoundSource*> soundSources;

public:
    SoundManager();
    ~SoundManager();

    // Load a sound source from file with a given name
    bool loadSound(string name, const char* filePath);

    // Get sound source from the map
    irrklang::ISoundSource* getSound(string name);

    // Play a sound effect by name
    void playSound(string name, bool loop = false);

    // Stop all playing sounds
    void stopAllSounds();

    // Set the global volume (0.0 - 1.0)
    void setVolume(float volume);

    // Get the current global volume
    float getVolume() const;

    // Check if a sound is currently playing by name
    bool isSoundPlaying(const char* name) const;

    irrklang::ISoundEngine* returnEngine();
};
