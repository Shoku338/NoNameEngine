#include "ProtoPlasma.h"

ProtoPlasma::ProtoPlasma():Weapon(0) {
    this->SetTexture("../Resource/Texture/Proto_plasma.png");
    this->SetSize(135.0f, -135.0f);
    canShoot = true;
    cdTimer = 0.5f;
    
}
