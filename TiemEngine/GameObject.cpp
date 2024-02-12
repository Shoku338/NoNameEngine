
#include "GameObject.h"
#include "GameEngine.h"
#include "SquareMeshVbo.h"



GameObject::GameObject()
{
	color = glm::vec3(0.0, 0.0, 0.0);
}


GameObject::~GameObject()
{

}
void GameObject::flip() 
{
	glm::vec3 flipSize = glm::vec3(-this->getsizeX(), this->getsizeY(), 1);
	this->SetSize(flipSize.x, flipSize.y);
}

void GameObject::SetColor(float r, float g, float b)
{
	color = glm::vec3(r, g, b);
}

void GameObject::SetTexture(string path)
{
	texture = GameEngine::GetInstance()->GetRenderer()->LoadTexture(path);
}

void GameObject::Render(glm::mat4 globalModelTransform)
{
	SquareMeshVbo *squareMesh = dynamic_cast<SquareMeshVbo *> (GameEngine::GetInstance()->GetRenderer()->GetMesh(SquareMeshVbo::MESH_NAME));

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

	}
}

int GameObject::detectCollisionAABB(float bx, float by, float bh, float bw, float dt) {
	
	float aHalfWidth = abs(size.x / 2.0f);
	float aHalfHeight = abs(size.y / 2.0f);
	float aQuatWidth = abs(size.x / 4.0f);
	float aQuatHeight = abs(size.y / 4.0f);

	float bTop = abs(by + (bh / 2));
	float bBot = abs(by - (bh / 2));
	float bRig = abs(bx + (bw / 2));
	float bLef = abs(bx - (bw / 2));

	float posX = this->getPosX() + (this->getVelocity().x * dt);
	float posY = this->getPosY() + (this->getVelocity().y * dt);
	// Calculate the eight points for each object
	float aPoints[8][2] = {
		{posX - aQuatWidth, posY + aHalfHeight},   // half top left
		{posX + aQuatWidth, posY + aHalfHeight},    // half top right
		{posX + aHalfWidth, posY + aQuatHeight},   // upper right
		{posX + aHalfWidth, posY - aQuatHeight},    // lower right
		{posX - aQuatWidth, posY - aHalfHeight},     // half bottom left
		{posX + aQuatWidth, posY - aHalfHeight},   // half bottom right
		{posX - aHalfWidth, posY + aQuatHeight},   // upper left
		{posX - aHalfWidth, posY - aQuatHeight}    // lower left
	};

	//collision logic

	if (aPoints[0][1] >= bBot && (aPoints[0][0] <= bRig && aPoints[1][0] >= bLef) && aPoints[0][1] < by) {
		//cout << "TOP" << endl;
		return 4;
	}
	else if (aPoints[4][1] <= bTop && (aPoints[4][0] <= bRig && aPoints[5][0] >= bLef) && aPoints[4][1] >= by) {
		//cout << "BOTTOM" << endl;
		return 3;
	}
	else if (aPoints[2][0] >= bLef && (aPoints[2][1] >= bBot && aPoints[3][1] < bTop) && aPoints[2][0] <= bx) {
		//cout << "RIGHT" << endl;
		return 2;
	}
	else if (aPoints[6][0] <= bRig && (aPoints[6][1] < bTop && aPoints[6][1] > bBot) && aPoints[6][0] > bx) {
		//cout << "LEFT" << endl;
		return 1;
	}
	return 0;
}

bool  GameObject::getCollision() {
	return haveCollision;
}
void  GameObject::setCollision(bool have) {
	haveCollision = have;
}

void GameObject::SmoothTranslate(const glm::vec3& targetPosition, float deltaTime, float speed) {
	glm::vec3 position = this->getPosition();
	glm::vec3 translationVector = targetPosition - position;
	glm::vec3 normalVelVec = glm::normalize(translationVector);
	float interpolationFactor = speed * deltaTime;
	this->Translate(normalVelVec * interpolationFactor);
}

void GameObject::Update()
{

}