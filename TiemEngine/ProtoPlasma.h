#pragma once
#include "weapon.h"
#include "SoundManager.h"

class ProtoPlasma : public Weapon {
    bool canShoot = true;
    float cdTimer = 0.5f;
public:
    ProtoPlasma();
    void update(glm::vec3 Playerpos);
    void Fire(glm::vec2 targetPosition, vector<DrawableObject*>& objectsList,SoundManager* soundManager);
};