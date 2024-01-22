
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
	this->SetSize(96.0f, -96.0f);

}


float* AnimatedObject::CalculateUV(int r, int c) {

	float rows = r;
	float column = c;

	
	newUV[0] = c / (MaxCol*1.0f);               // bottom left x
	newUV[1] = r / (MaxRow * 1.0f);  // bottom left y

	newUV[2] = (c + 1.0f) / (MaxCol * 1.0f);       // bottom right x
	newUV[3] = r / (MaxRow * 1.0f);  // bottom right y

	newUV[4] = (c + 1.0f) / (MaxCol * 1.0f);       // top right x
	newUV[5] = (1.0f + r) / (MaxRow * 1.0f);       // top right y

	newUV[6] = c / (MaxCol * 1.0f);               // top left x
	newUV[7] = (1.0f + r) / (MaxRow * 1.0f);


	return newUV;
}

void AnimatedObject::UpdateFrame() {

	frames++;
	if (frames > speed) {
		frames = 0;

		col++;
		//CalculateUV(row, col);
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

int AnimatedObject::getCol()
{
	return col;
}

int AnimatedObject::getRow()
{
	return row;
}

int AnimatedObject::getFrames()
{
	return frames;
}