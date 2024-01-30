#include "GrappleLine.h"
#include "GameEngine.h"
#include "SquareMeshVbo.h"

GrapleLine::GrapleLine(glm::vec3 startPos) {
	this->SetPosition(startPos);
	this->SetSize(1.0f, 1.0f);
}

void GrapleLine::Render(glm::mat4 globalModelTransform) {
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

	glm::mat4 currentMatrix =  glm::translate(glm::mat4(1.0f), glm::vec3(0.5f, .0f, .0f));

	currentMatrix = this->getTransform() * currentMatrix;

	if (squareMesh != nullptr) {

		currentMatrix = globalModelTransform * currentMatrix;
		glUniformMatrix4fv(modelMatixId, 1, GL_FALSE, glm::value_ptr(currentMatrix));
		glUniform3f(colorId, color.x, color.y, color.z);
		glUniform1i(renderModeId, 1);
		glBindTexture(GL_TEXTURE_2D, texture);
		squareMesh->Render();

	}
}

void GrapleLine::updateCurrent(glm::vec3 playerPos,glm::vec3 headPos) {
	
	glm::vec3 currVec = headPos - playerPos;
	glm::vec2 direction = glm::normalize(glm::vec2(currVec.x, currVec.y));
	float magnitude = glm::length(glm::vec2(currVec.x, currVec.y));

	SetSize(magnitude, 1.0f);
	SetPosition(playerPos);

	// Rotate to the direction
	float degree = glm::degrees(atan2(direction.y, direction.x));
	this->rotateDegree(degree);
}
