#include "Player.h"
#include "GameEngine.h"
#include "SquareMeshVbo.h"

Player::Player() {
	health = 10;
	shield = 10;
	jumpCount = 0;
	grounded = true;
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
	currentWeapon.update(this->pos); 
}

void Player::Render(glm::mat4 globalModelTransform)
{
	SquareMeshVbo* squareMesh = dynamic_cast<SquareMeshVbo*> (GameEngine::GetInstance()->GetRenderer()->GetMesh(SquareMeshVbo::MESH_NAME));

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

	if (squareMesh != nullptr) {

		currentMatrix = globalModelTransform * currentMatrix;
		glUniformMatrix4fv(modelMatixId, 1, GL_FALSE, glm::value_ptr(currentMatrix));
		glUniform3f(colorId, color.x, color.y, color.z);
		glUniform1i(renderModeId, 1);
		glBindTexture(GL_TEXTURE_2D, texture);
		squareMesh->Render();
		currentWeapon.Render(globalModelTransform);
	}
	
}

void Player::setWeapon(string weaponTexture) {
	currentWeapon.SetTexture(weaponTexture);
	currentWeapon.SetSize(this->getsizeX(),this->getsizeY());
	currentWeapon.SetPosition(this->pos);
}