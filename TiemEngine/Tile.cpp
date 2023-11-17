
#include "Tile.h"

Tile::Tile(float size, int indexX, int indexY, unsigned int newTexture)
{
	tileSize = size;
	posIndexX = indexX;
	posIndexY = indexY;

    // Assuming the origin (0,0) is at the bottom left and the aspect ratio is 16:9
    float bottomLeftX = 0.0f;
    float bottomLeftY = 0.0f;

    // Calculate the position in 3D space, adjusting for the bottom left corner
    float x = bottomLeftX + (indexX * size) + (0.5f * size);
    float y = bottomLeftY + (indexY * size) + (0.5f * size);
    float z = 0.0f;

    SetPosition(glm::vec3(x,y, z));
    SetSize(size, -size);
	texture = newTexture;
    
}

Tile::~Tile()
{
    // Add any cleanup logic here if needed
}

void Tile::setTextureID(unsigned int newTexture)
{

}
