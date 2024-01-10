#include "weapon.h"

Weapon::Weapon() {
	
}
void Weapon::update(glm::vec3 Playerpos) {
	this->pos = Playerpos;
}