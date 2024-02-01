#pragma once
#include "AnimatedObject.h"
#include "weapon.h"
#include <GL/glew.h>
#include <iostream>

class Enemy :public AnimatedObject {
	float health = 10;
	bool grounded = true;
	Weapon currentWeapon;
	bool isFaceRight = true;
	bool hasFlippedRight = true;
	bool hasFlippedLeft = false;
public:
	Enemy(const char* path, int MaxR, int MaxC);
	Enemy(const char* path, int MaxR, int MaxC,int Health);
	void Update();
	void setFaceRight(bool fliping);
	void checkFace();
	float getHealth();
	float getShield();
	void setGround(bool state);
	bool getGrounded();
	

};