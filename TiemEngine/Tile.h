#pragma once

#include "GameObject.h"


class Tile :public GameObject
{
	float tileSize;
    int posIndexX, posIndexY;
    vector<vector<int>> tileMap;

public:
	
    Tile(float size,int indexX,int indexY,unsigned int texture);
    ~Tile();
    void setTextureID(unsigned int newTexture);
    glm::vec3 getPosition();


};