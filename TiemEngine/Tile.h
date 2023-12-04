#pragma once

#include "GameObject.h"


class Tile :public GameObject
{
	float tileSize;
    int posIndexX, posIndexY;
    vector<vector<int>> tileMap;
    string tileName;
    int tileType = 0;

public:
	
    Tile(float size,int indexX,int indexY,unsigned int texture, int newTileType);
    ~Tile();
    void setTextureID(unsigned int newTexture);
    void Render(glm::mat4 globalModelTransform);
    glm::vec3 getPosition();


};