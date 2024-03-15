#pragma once
#include "weapon.h"
#include "SoundManager.h"

class ProtoPlasma : public Weapon {
    bool canShoot = true;
    float cdTimer = 0.5f;
public:
    ProtoPlasma();
};