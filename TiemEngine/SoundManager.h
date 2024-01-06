#pragma once
#include "irrKlang.h"
#include <iostream>

using namespace std;

class SoundManager {
private:
    irrklang::ISoundEngine* soundEngine;

public:
    SoundManager();
    ~SoundManager();

    // Load a sound source from file with a given name
    irrklang::ISoundSource* loadSound(const char* name, const char* filePath);

    // Play a sound effect by name
    void playSound(const char* name, bool loop = false);

    // Stop all playing sounds
    void stopAllSounds();

    // Set the global volume (0.0 - 1.0)
    void setVolume(float volume);

    // Get the current global volume
    float getVolume() const;

    // Check if a sound is currently playing by name
    bool isSoundPlaying(const char* name) const;

    irrklang::ISoundEngine* engine();
};
