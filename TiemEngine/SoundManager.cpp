#include "SoundManager.h"

SoundManager::SoundManager() {
    soundEngine = irrklang::createIrrKlangDevice();
}

SoundManager::~SoundManager() {
    if (soundEngine) {
        soundEngine->drop();
        soundEngine = nullptr;
    }
}

bool SoundManager::loadSound(string name, const char* filePath) {
    if (soundSources.find(name) != soundSources.end())
    {
        return false;
    }
    else
    {
        irrklang::ISoundSource* soundSource = soundEngine->addSoundSourceFromFile(filePath);
        soundSources.insert({ name,soundSource });
        cout << "Loaded sound: " << name << " from file: " << filePath << endl;
        soundSource
        return true;
    }
    
    
}

irrklang::ISoundSource* SoundManager::getSound(string name) {
    if (soundSources.find(name) != soundSources.end())
    {
        return soundSources[name];
    }
    else
    {
        return nullptr;
    }
}

void SoundManager::playSound(string name, bool loop) {
    if (soundSources.find(name) != soundSources.end())
    {
        soundEngine->play2D(soundSources[name], loop);
        cout << "Playing sound: " << name << endl;
    }
    else
    {
        cout << "Error : Failed to load sound" << endl;
    }
    
    
}

void SoundManager::stopAllSounds() {
    soundEngine->stopAllSounds();
    cout << "Sound stop" << endl;
}

void SoundManager::setVolume(float volume) {
    soundEngine->setSoundVolume(volume);
}

float SoundManager::getVolume() const {
    return soundEngine->getSoundVolume();
}

bool SoundManager::isSoundPlaying(const char* name) const {
    if (name) {
        return soundEngine->isCurrentlyPlaying(name);
    }
    return false;
}

irrklang::ISoundEngine* SoundManager::returnEngine()
{
    return soundEngine;
}