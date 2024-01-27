#pragma once
#include "GameObject.h"
#include "weapon.h"
#include <GL/glew.h>
#include <iostream>

class Player :public GameObject {
	float health = 10;
	float shield = 10;
	int jumpCount = 0;
	bool grounded = true;
	Weapon currentWeapon;
	bool isFaceRight = true;
	bool hasFlippedRight = true;
	bool hasFlippedLeft = false;
public:
	Player();
	void update();
	void setFaceRight(bool fliping);
	void checkFace();
	float getHealth();
	float getShield();
	int getJump();
	Weapon * getWeapon();
	void setJump(int count);
	void setGround(bool state);
	bool getGrounded();
	void Render(glm::mat4 globalModelTransform);
	void setWeapon(string weaponTexture);
};

