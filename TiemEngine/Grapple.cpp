#include "Grapple.h"
#include <iostream>


Grapple::Grapple(glm::vec3 startPosition, const string texture, float speed) : Bullet(startPosition, texture, speed)
{
    this->SetTexture(texture); // change to (name of bullet sprite)
    this->velocity.x = speed;
    
}

void Grapple::pull(Player& player,float dt,float speed) {
    
    // Apply the translation to the object
    if (abs(this->getPosition().x - player.getPosition().x) >= 10) {
        player.SmoothTranslate(this->getPosition(), dt, speed);
    }
}