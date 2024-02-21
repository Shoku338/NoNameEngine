#include "ProtoPlasma.h"

ProtoPlasma::ProtoPlasma() {
    this->SetTexture("../Resource/Texture/Proto_plasma.png");
    this->SetSize(135.0f, -135.0f);
    canShoot = true;
    cdTimer = 0.5f;
}
void ProtoPlasma::update(glm::vec3 Playerpos) {
    this->pos = Playerpos + glm::vec3(10.0f,0.0f,0.0f);
    if (cdTimer > 0) {
        cdTimer -= 0.01;
    }
    else
    {
        canShoot = true;
        cdTimer = 0.5f;
    }

}
void ProtoPlasma::Fire(glm::vec2 targetPosition, vector<DrawableObject*>& objectsList, SoundManager* soundManager) {
    if (canShoot) {
        glm::vec3 bulletStartPosition = this->getPosition() + glm::vec3(10.0f, 20.0f, 0.0f); // Adjust the offset as needed
        Bullet* newBullet = new Bullet(bulletStartPosition, "../Resource/Texture/bullet3.png", 1700.f);//[Editable]last number is SPEEEDDDDD
        newBullet->SetSize(60.f, 20.f);
        newBullet->shootAt(targetPosition, newBullet->getVelocity().x);
        objectsList.push_back(newBullet);

        // SoundEffect
        soundManager->playSound("Blaster", false);
        canShoot = false;
        cdTimer -= 0.01;
    }
    
}