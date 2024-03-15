#include "ProtoPlasma.h"

ProtoPlasma::ProtoPlasma() {
    this->SetTexture("../Resource/Texture/Proto_plasma.png");
    this->SetSize(135.0f, -135.0f);
    canShoot = true;
    cdTimer = 0.5f;
}
