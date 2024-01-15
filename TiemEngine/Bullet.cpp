#include "Bullet.h"
#include <iostream>

Bullet::Bullet() {
    this->SetTexture("../Resource/Texture/LaserB.png"); // change to (name of bullet sprite)
    //this->velocity.x = 100;
}
Bullet::Bullet(glm::vec3 startPosition,const string texture,float speed) : startPosition(startPosition), timer(0.0f)
{
    this->SetTexture(texture); // change to (name of bullet sprite)
    this->velocity.x = speed;
}
void Bullet::update(float dt) {
    timer += dt;
    this->Translate(this->velocity * (dt*2));
}
void Bullet::shootAt(glm::vec2 targetMousePos, float speed)
{
    // Calculate direction from start position to target mouse position
    glm::vec2 direction = glm::normalize(targetMousePos - glm::vec2(startPosition.x, startPosition.y));
    //rotate to the direction
    float degree = glm::degrees(atan2(direction.y, direction.x));
    cout << "degree to rotate : " << degree << endl;
    this->rotateDegree(degree);
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

void Bullet::setTimer(float time) {
    TimeTD = time;
}