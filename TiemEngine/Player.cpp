#include "Player.h"

float Player::getHealth() {
	return health;
}
float Player::getShield() {
	return shield;
}
void Player::setGround(bool state) {
	grounded = state;
}
bool Player::getGrounded() {
	return grounded;
}

int Player::getJump() {
	return jumpCount;
}
void Player::setJump(int count) {
	jumpCount = count;
}