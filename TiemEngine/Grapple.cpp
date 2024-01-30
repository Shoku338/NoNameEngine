#include "Grapple.h"
#include "GameEngine.h"
#include "SquareMeshVbo.h"
#include <iostream>


Grapple::Grapple(glm::vec3 startPosition, const string texture, float speed) : Bullet(startPosition, texture, speed), Granline(startPosition)
{
    this->SetTexture(texture); // change to (name of bullet sprite)
    this->velocity.x = speed;
	
}



void Grapple::pull(Player& player,float dt,float speed) {
    //set position and strech grapple line
	
	Granline.updateCurrent(player.getPosition() + glm::vec3(10.0f, 20.0f, 0.0f),this->getPosition());
    // Apply the translation to the object
    if (abs(this->getPosition().x - player.getPosition().x) >= 10) {
        player.SmoothTranslate(this->getPosition(), dt, speed);
    }
    else {
        this->setTimer(0);
    }
}

void Grapple::Render(glm::mat4 globalModelTransform)
{
	Granline.Render(globalModelTransform);
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
	}

}