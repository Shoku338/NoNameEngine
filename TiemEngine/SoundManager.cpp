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

irrklang::ISoundSource* SoundManager::loadSound(const char* name, const char* filePath) {
    irrklang::ISoundSource* soundSource = soundEngine->addSoundSourceFromFile(filePath);
    //soundSource->setName(name);
    cout << "Loaded sound: " << name << " from file: " << filePath << endl;
    return soundSource;
}

void SoundManager::playSound(const char* name, bool loop) {
    soundEngine->play2D(name, loop);
    cout << "Playing sound: " << name << endl;
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

irrklang::ISoundEngine* SoundManager::engine()
{
    return soundEngine;
}