#include "Enemy.h"
#include "GameEngine.h"
#include "SquareMeshVbo.h"
#include "AnimateMeshVbo.h"

Enemy::Enemy(const char* path, int MaxR, int MaxC) :AnimatedObject(path, MaxR, MaxC) {
	health = 10;
	grounded = true;
}

Enemy::Enemy(const char* path, int MaxR, int MaxC, int Health) :AnimatedObject(path, MaxR, MaxC) {
	health = Health;
	grounded = true;
}

float Enemy::getHealth() {
	return health;
}

void Enemy::setGround(bool state) {
	grounded = state;
}
bool Enemy::getGrounded() {
	return grounded;
}

void Enemy::Update() {
	UpdateFrame();
}



void Enemy::setFaceRight(bool fliping) {
	isFaceRight = fliping;
}

void Enemy::checkFace() {
	if (isFaceRight && !hasFlippedRight) {
		flip();
		currentWeapon.flip();
		hasFlippedRight = true;
		hasFlippedLeft = false;  // Reset the flag for the other direction
	}
	else if (!isFaceRight && !hasFlippedLeft) {
		flip();
		currentWeapon.flip();
		hasFlippedLeft = true;
		hasFlippedRight = false;  // Reset the flag for the other direction
	}
}

