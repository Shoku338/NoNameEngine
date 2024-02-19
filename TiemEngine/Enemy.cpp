#include "Enemy.h"
#include "GameEngine.h"
#include "SquareMeshVbo.h"
#include "AnimateMeshVbo.h"
#include "Explosion.h"

Enemy::Enemy(const char* path, int MaxR, int MaxC) :AnimatedObject(path, MaxR, MaxC) {
	health = 10;
	grounded = true;
	setCollision(false);
	SetColor(1, 0, 0);
	
}

Enemy::Enemy(const char* path, int MaxR, int MaxC, int Health) :AnimatedObject(path, MaxR, MaxC) {
	health = Health;
	grounded = true;
	SetColor(2, 1, 1);
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
	//cout << "Row: " << row << ", Col: " << col << endl;
	if (currentFrame == 40)
	{
		renderMode = 1;
		currentFrame = 0;
	}
	currentFrame++;
}



void Enemy::Render(glm::mat4 globalModelTransform)
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
		glUniform1i(renderModeId, renderMode);
		glBindTexture(GL_TEXTURE_2D, texture);
		spriteMesh->UpdateUV(newUV);
		spriteMesh->Render();

	}

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

void Enemy::applyDamage(float damage)
{
	health -= damage;
	renderMode = 2;
	currentFrame = 0;
	//cout << "Hit RenderMode: " << renderMode << endl;
	
	
}

bool Enemy::handleDeath()
{
	if (health <= 0)
	{
		
		return true;
	}
	return false;
}
