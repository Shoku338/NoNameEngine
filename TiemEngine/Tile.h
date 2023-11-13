#pragma once

#include "GameObject.h"

class Tile :public GameObject
{
	float tileSize;
    int posIndexX, posIndexY;

public:
	
    Tile(float size,int indexX,int indexY,unsigned int texture);
    ~Tile();
    void setTextureID(unsigned int newTexture);


};