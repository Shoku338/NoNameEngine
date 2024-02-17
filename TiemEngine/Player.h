#pragma once
#include "AnimatedObject.h"
#include "weapon.h"
#include <GL/glew.h>
#include <iostream>

class Player :public AnimatedObject {
	float health = 10;
	float shield = 10;
	int jumpCount = 0;
	bool grounded = true;
	Weapon* currentWeapon;
	bool isFaceRight = true;
	bool hasFlippedRight = true;
	bool hasFlippedLeft = false;
	bool physic = true;
public:
	Player(const char* path, int MaxR, int MaxC);
	void update();
	void setPhysic(bool setPhysic);
	void setFaceRight(bool fliping);
	void checkFace();
	bool facingRight();
	float getHealth();
	float getShield();
	bool getPhysic();
	int getJump();
	Weapon * getWeapon();
	void setJump(int count);
	void setGround(bool state);
	bool getGrounded();
	void Render(glm::mat4 globalModelTransform);
	void setWeapon(Weapon* weapon);
};

