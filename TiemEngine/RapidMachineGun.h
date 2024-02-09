#pragma once
#include "weapon.h"
#include "SoundManager.h"

class RapidMachineGun : public Weapon {
public:
    RapidMachineGun();
    void update(glm::vec3 Playerpos);
    void Fire(glm::vec2 targetPosition, vector<DrawableObject*>& objectsList, SoundManager* soundManager);
};