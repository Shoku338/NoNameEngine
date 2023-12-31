#pragma once

#include "GameObject.h"
#include <GL/glew.h>

class Player :public GameObject {
	float health;
	float shield;
	bool grounded = true;
public:
	float getHealth();
	float getShield();
	void setGround(bool state);
	bool getGrounded();
};

