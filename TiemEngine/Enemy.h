#pragma once
#include "AnimatedObject.h"
#include "weapon.h"
#include <GL/glew.h>
#include <iostream>

class Enemy :public AnimatedObject {
	enum States {
		patrol = 0,
		Detect = 1,
		Attack = 2,
	};
	float walkSpeed = 30.0f;
	States currentState;
	float health = 10;
	bool grounded = true;
	Weapon currentWeapon;
	bool isFaceRight = true;
	bool hasFlippedRight = true;
	bool hasFlippedLeft = false;
	int renderMode = 1;
	int currentFrame = 0;
	glm::vec3 startingPosition;
	float attackRange = 64;
	
public:
	Enemy(const char* path, int MaxR, int MaxC);
	Enemy(const char* path, int MaxR, int MaxC,int Health);
	void Update(float dt);
	void Render(glm::mat4 globalModelTransform);
	void setFaceRight(bool fliping);
	void checkFace();
	float getHealth();
	void setGround(bool state);
	bool getGrounded();
	void applyDamage(float damage);
	bool handleDeath();
	

};