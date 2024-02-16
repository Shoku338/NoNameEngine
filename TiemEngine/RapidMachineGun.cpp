#include "RapidMachineGun.h"

RapidMachineGun::RapidMachineGun() {
    this->SetTexture("../Resource/Texture/Tier2_rapid machinegun.png");
    this->SetSize(135.0f, -135.0f);
}
void RapidMachineGun::update(glm::vec3 Playerpos) {
    this->pos = Playerpos + glm::vec3(10.0f, 0.0f, 0.0f);
}
void RapidMachineGun::Fire(glm::vec2 targetPosition, vector<DrawableObject*>& objectsList, SoundManager* soundManager) {
    glm::vec3 bulletStartPosition = this->getPosition() + glm::vec3(10.0f, 20.0f, 0.0f); // Adjust the offset as needed
    Bullet* newBullet = new Bullet(bulletStartPosition, "../Resource/Texture/LaserB.png", 150.f);//[Editable] last number are the speed
    newBullet->SetSize(20.f, 20.f);
    newBullet->shootAt(targetPosition, newBullet->getVelocity().x);
    objectsList.push_back(newBullet);

    // SoundEffect
    soundManager->playSound("Blaster", false);
}