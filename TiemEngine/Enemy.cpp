#include "Enemy.h"
#include "GameEngine.h"
#include "SquareMeshVbo.h"
#include "AnimateMeshVbo.h"
#include "Explosion.h"

Enemy::Enemy(const char* path, int MaxR, int MaxC) :AnimatedObject(path, MaxR, MaxC) {
	health = 4;
	grounded = true;
	setCollision(false);
	SetColor(1, 0, 0);
	startingPosition = this->getPosition();
	currentState = patrol;
}

Enemy::Enemy(const char* path, int MaxR, int MaxC, int Health) :AnimatedObject(path, MaxR, MaxC) {
	health = Health;
	grounded = true;
	SetColor(2, 1, 1);
	startingPosition = this->getPosition();
	currentState = patrol;
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

void Enemy::Update(vector<Tile*> map,float dt) {
	UpdateFrame();
	switch (currentState) {
	case patrol:
		static bool moveRight = true;
		static float patrolDistance = 3 * 64; // 3 blocks * 64 pixels per block
		for (int i = 0; i < map.size(); i++) {
			// Check if the current tile contains an enemy
			GameObject* tile = dynamic_cast<GameObject*>(map.at(i));
			
			// If it's not an enemy, proceed with collision detection and movement
			if (tile && tile->getCollision()) {
				if (Enemy* enemy = dynamic_cast<Enemy*>(tile)) {
					continue; // Skip collision detection and movement if it's an enemy
				}

				// Perform collision detection
				int nmeCol = this->detectCollisionAABB(tile->getPosX(), tile->getPosY(), abs(tile->getsizeY()), tile->getsizeX(), dt);
				// Handle collision results
				if (nmeCol == 1 || nmeCol == 2) {
					moveRight = !moveRight;
				}
				// Move according to the patrol direction
				if (moveRight) {
					// Move right
					SetPosition(getPosition() + (glm::vec3(walkSpeed, 0, 0) * dt));
				}
				else {
					// Move left
					SetPosition(getPosition() - (glm::vec3(walkSpeed, 0, 0) * dt));
				}
				// Check if reached the end of patrol distance
				if (abs(getPosition().x - startingPosition.x) >= patrolDistance) {
					moveRight = !moveRight; // Change direction
				}
			}
		}

		break;
	/*case Detect:
		glm::vec2 playerPosition = GameEngine::GetInstance()->GetPlayerPosition();
		glm::vec2 enemyPosition = glm::vec2(getPosition().x, getPosition().y);

		// Calculate direction vector towards the player
		glm::vec2 direction = glm::normalize(playerPosition - enemyPosition);

		// Move the enemy towards the player
		SetPosition(getPosition() + glm::vec3(direction.x * speed, direction.y * speed, 0));
		break;
	case Attack:
		glm::vec2 playerPosition = GameEngine::GetInstance()->GetPlayerPosition();
		glm::vec2 enemyPosition = glm::vec2(getPosition().x, getPosition().y);

		float distanceToPlayer = glm::length(playerPosition - enemyPosition);
		if (distanceToPlayer < attackRange) {
			// Start shooting bullets at the player
			//FireBullet(playerPosition); // Implement this function to shoot bullets
		}
		break;*/
	}
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
