#include "weapon.h"

void Weapon::update(glm::vec3 Playerpos) {
    this->pos = Playerpos;
}
void Weapon::Fire(glm::vec2 targetPosition, vector<DrawableObject*>& objectsList, SoundManager* soundManager) {
    glm::vec3 bulletStartPosition = this->getPosition() + glm::vec3(10.0f, 20.0f, 0.0f); // Adjust the offset as needed
    Bullet* newBullet = new Bullet(bulletStartPosition, "../Resource/Texture/bullet3.png", 150.f);
    newBullet->SetSize(20.f, 20.f); 
    newBullet->shootAt(targetPosition, newBullet->getVelocity().x);
    objectsList.push_back(newBullet);

    // SoundEffect
    soundManager->playSound("Blaster", false);
}