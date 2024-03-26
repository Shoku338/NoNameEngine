
#include "Tile.h"
#include "SquareMeshVbo.h"
#include "GameEngine.h"

Tile::Tile(float size, int indexX, int indexY, unsigned int newTexture,int newTileType)
{
	tileSize = size;
	posIndexX = indexX;
	posIndexY = indexY;
	tileType = newTileType;

    // Assuming the origin (0,0) is at the bottom left and the aspect ratio is 16:9
    float bottomLeftX = 0.0f;
    float bottomLeftY = 0.0f;

    // Calculate the position in 3D space, adjusting for the bottom left corner
    float x = bottomLeftX + (indexX * size) + (0.5f * size);
    float y = bottomLeftY + (indexY * size) + (0.5f * size);
    float z = 0.0f;

    SetPosition(glm::vec3(x,y, z));
    SetSize(size, size);
    setTextureID(newTexture);
    
}

Tile::~Tile()
{
    // Add any cleanup logic here if needed
}

void Tile::setTextureID(unsigned int newTexture)
{
    texture = newTexture;
}

glm::vec3 Tile::getPosition()
{
    return pos;
}

void Tile::Render(glm::mat4 globalModelTransform)
{
	SquareMeshVbo* squareMesh = dynamic_cast<SquareMeshVbo*> (GameEngine::GetInstance()->GetRenderer()->GetMesh(to_string(tileType)));

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

void Tile::setSpawner(unsigned int enemyIndex)
{
	EnemyToSpawn = static_cast<EnemyList>(enemyIndex);
}

EnemyList Tile::getSpawner()
{
	return EnemyToSpawn;
}