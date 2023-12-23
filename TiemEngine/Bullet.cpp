#include "Bullet.h"

Bullet::Bullet() {
    this->SetTexture("../Resource/Texture/LaserB.png"); // change to (name of bullet sprite)
    this->velocity.x = 100;
}
Bullet::Bullet(glm::vec3 startPosition) : startPosition(startPosition), timer(0.0f)
{
    this->SetTexture("../Resource/Texture/LaserB.png"); // change to (name of bullet sprite)
    this->velocity = glm::vec3(0.0f, 0.0f, 0.0f); // Initialize velocity to zero
    this->velocity.x = 100;
}
void Bullet::update(float dt) {
    timer += dt;
    this->Translate(this->velocity * (dt*2));
}
void Bullet::shootAt(glm::vec2 targetMousePos, float speed)
{
    // Calculate direction from start position to target mouse position
    glm::vec2 direction = glm::normalize(targetMousePos - glm::vec2(startPosition.x, startPosition.y));

    // Set velocity based on direction and speed
    this->velocity = glm::vec3(direction * speed, 0.0f);

    // Set the initial position of the bullet
    this->SetPosition(glm::vec3(startPosition.x, startPosition.y, startPosition.z));
}

bool Bullet::timesUp() {
    if (timer > TimeTD)
        return true;
    else
        return false;
}