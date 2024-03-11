#pragma once
#include "AnimatedObject.h"
#include "weapon.h"
#include <GL/glew.h>
#include <iostream>
#include "glm.hpp"

class Player :public AnimatedObject {
	enum States {
		IDLE = 0,
		RUNNINGFORWARD = 1,
		RUNNINGBACKWARD = 2,
		JUMPING = 3
	};
	

	float health = 10;
	float shield = 10;
	int jumpCount = 0;
	bool grounded = true;
	Weapon* currentWeapon;
	bool isFaceRight = true;
	bool hasFlippedRight = true;
	bool hasFlippedLeft = false;
	States currentState;
	States prevState;
	bool physic = true;
	bool JumpStart = false;
	unsigned int textureCape = -1;
	

	
public:
	
	Player(const char* pathCharacter, const char* pathCape, int MaxR, int MaxC);
	void Update();
	void UpdateFrame();
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
	int  detectCollisionAABB(float bx, float by, float bh, float bw, float dt);
	bool isMoving = false;
};

