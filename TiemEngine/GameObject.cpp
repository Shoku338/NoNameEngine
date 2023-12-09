
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

int GameObject::detectCollisionAABB(float bx, float by, float bh, float bw) {
	float aHalfWidth = abs(size.x / 2.0f);
	float aHalfHeight = abs(size.y / 2.0f);
	float aQuatWidth = abs(size.x / 4.0f);
	float aQuatHeight = abs(size.y / 4.0f);

	float bTop = abs(by + (bh / 2));
	float bBot = abs(by - (bh / 2));
	float bRig = abs(bx + (bw / 2));
	float bLef = abs(bx - (bw / 2));

	// Calculate the eight points for each object
	float aPoints[8][2] = {
		{pos.x - aQuatWidth, pos.y + aHalfHeight},   // half top left
		{pos.x + aQuatWidth, pos.y + aHalfHeight},    // half top right
		{pos.x + aHalfWidth, pos.y + aQuatHeight},   // upper mid right
		{pos.x + aHalfWidth, pos.y - aQuatHeight},    // lower mid right
		{pos.x - aQuatWidth, pos.y - aHalfHeight},     // half bottom left
		{pos.x + aQuatWidth, pos.y - aHalfHeight},   // half bottom right
		{pos.x - aHalfWidth, pos.y + aQuatHeight},   // upper mid left
		{pos.x - aHalfWidth, pos.y - aQuatHeight}    // lower mid left
	};

	//collision logic
	int collisionResult = 0;
	if (aPoints[0][1] >= bBot && aPoints[0][1] < by) {
		cout << "TOP" << endl;
		return 4;
	}
	else if (aPoints[4][1] <= bTop && aPoints[4][1] >= by) {
		cout << "BOTTOM" << endl;
		return 3;
	}
	else if (aPoints[2][0] >= bLef && (aPoints[2][1] < bTop && aPoints[3][1] > bBot) && aPoints[2][0] <= bx) {
		cout << "RIGHT" << endl;
		return 2;
	}	
	else if (aPoints[6][0] <= bRig && (aPoints[6][1] < bTop && aPoints[6][1] > bBot) && aPoints[6][0] > bx) {
		cout << "LEFT" << endl;
		return 1;
	}

	return collisionResult;
}

bool  GameObject::getCollision() {
	return haveCollision;
}
void  GameObject::setCollision(bool have) {
	haveCollision = have;
}