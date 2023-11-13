
#include "Tile.h"

Tile::Tile(float size, int indexX, int indexY, unsigned int newTexture)
{
	tileSize = size;
	posIndexX = indexX;
	posIndexY = indexY;

	texture = newTexture;
}