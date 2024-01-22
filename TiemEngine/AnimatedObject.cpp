
#include "AnimatedObject.h"
#include <iostream>
#include "AnimateMeshVbo.h"
#include "GameEngine.h"

AnimatedObject::AnimatedObject(const char* path, int MaxR, int MaxC) {
	this->row = row;
	this->col = col;
	MaxRow = MaxR;
	MaxCol = MaxC;
	texture = GameEngine::GetInstance()->GetRenderer()->LoadTexture(path);
	CalculateUV(0, 0);
}


float* AnimatedObject::CalculateUV(int r, int c) {

	float texData[8];
	float rows = r;
	float column = c;

	// HARD CODING FOR NOW
	// CALCULATING 4 COORDINATES
	// #1
	texData[0] = column / MaxCol, texData[1] = ((MaxRow - rows) + 1) / MaxRow;
	// #2
	texData[2] = (column + 1.0f) / MaxCol, texData[3] = ((MaxRow - rows) + 1) / MaxRow;
	// #3
	texData[4] = (column + 1.0f) / MaxCol, texData[5] = (MaxRow - rows) / MaxRow;
	// #4
	texData[6] = column / MaxCol, texData[7] = (MaxRow - rows) / MaxRow;


	/*for (int i = 0; i < 8; i++)
	{
		newUV[i] = texData[i];
	}*/

	return texData;
}

void AnimatedObject::UpdateFrame() {

	frames++;
	if (frames > speed) {
		frames = 0;

		col++;
		CalculateUV(row, col);
	}

}

void AnimatedObject::Render(glm::mat4 globalModelTransform)
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
		spriteMesh->Render();

	}
}
