#pragma once

#include "GameObject.h"
#include <GL/glew.h>

class Player :public GameObject {
	float health;
	float shield;
	int jumpCount = 0;
	bool grounded = true;
public:
	float getHealth();
	float getShield();
	int getJump();
	void setJump(int count);
	void setGround(bool state);
	bool getGrounded();
};

