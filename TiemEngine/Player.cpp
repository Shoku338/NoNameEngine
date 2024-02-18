#include "Player.h"
#include "GameEngine.h"
#include "SquareMeshVbo.h"
#include "AnimateMeshVbo.h"

Player::Player(const char* path, int MaxR, int MaxC):AnimatedObject(path,MaxR,MaxC) {
	health = 10;
	shield = 10;
	jumpCount = 0;
	grounded = false;
}

void Player::setPhysic(bool setPhysic) {
	physic = setPhysic;
}
bool Player::getPhysic() {
	return physic;
}

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
void Player::update() {
	currentWeapon->update(this->getPosition()); 
	//cout << "Row: " << row << ", Col: " << col << endl;
}

void Player::Render(glm::mat4 globalModelTransform)
{
	AnimateMeshVbo* spriteMesh = dynamic_cast<AnimateMeshVbo*> (GameEngine::GetInstance()->GetRenderer()->GetMesh(AnimateMeshVbo::MESH_NAME));

	GLuint modelMatixId = GameEngine::GetInstance()->GetRenderer()->GetModelMatrixAttrId();
	GLuint colorId = GameEngine::GetInstance()->GetRenderer()->GetColorUniformId();
	GLuint renderModeId = GameEngine::GetInstance()->GetRenderer()->GetModeUniformId();

	if (modelMatixId == -1) {
		cout << "Error: Can't perform transformation " << endl;
		return;
	}
	if (colorId == -1) {
		cout << "Error: Can't set color " << endl;
		return;
	}
	if (renderModeId == -1) {
		cout << "Error: Can't set renderMode in ImageObject " << endl;
		return;
	}
	vector <glm::mat4> matrixStack;

	glm::mat4 currentMatrix = this->getTransform();

	if (spriteMesh != nullptr) {

		currentMatrix = globalModelTransform * currentMatrix;
		glUniformMatrix4fv(modelMatixId, 1, GL_FALSE, glm::value_ptr(currentMatrix));
		glUniform3f(colorId, color.x, color.y, color.z);
		glUniform1i(renderModeId, 1);
		glBindTexture(GL_TEXTURE_2D, texture);
		spriteMesh->UpdateUV(getNewUV());
		spriteMesh->Render();
		if (currentWeapon != nullptr) {
			currentWeapon->Render(globalModelTransform);
		}
	}
	
}

void Player::setFaceRight(bool fliping) {
	isFaceRight = fliping;
}

void Player::checkFace() {
	if (isFaceRight && !hasFlippedRight) {
		flip();
		currentWeapon->flip();
		hasFlippedRight = true;
		hasFlippedLeft = false;  // Reset the flag for the other direction
	}
	else if (!isFaceRight && !hasFlippedLeft) {
		flip();
		currentWeapon->flip();
		hasFlippedLeft = true;
		hasFlippedRight = false;  // Reset the flag for the other direction
	}
}

bool Player::facingRight()
{
	return isFaceRight;
	
}

Weapon * Player::getWeapon()
{
	return currentWeapon;
}
void Player::setWeapon(Weapon* weapon) {
	currentWeapon = weapon;
}