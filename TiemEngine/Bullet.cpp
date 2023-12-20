#include "Bullet.h"

Bullet::Bullet() {
    this->SetTexture("../Resource/Texture/LaserB.png"); // change to (name of bullet sprite)
    this->velocity.x = 100;
}
void Bullet::update(float dt) {
    timer += dt;
    this->Translate(this->velocity * (dt*2));
}
bool Bullet::timesUp() {
    if (timer > TimeTD)
        return true;
    else
        return false;
}