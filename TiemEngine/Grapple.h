#pragma once
#include <GL/glew.h>
#include "Bullet.h"
#include "Player.h"
#include "GameObject.h"

class Grapple :public Bullet {
	
public:
	Grapple(glm::vec3 startPosition, const string texture, float speed);
	void pull(Player& player, float dt, float speed);
}; 
