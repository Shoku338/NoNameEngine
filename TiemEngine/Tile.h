#pragma once

#include "GameObject.h"

enum EnemyList
{
    None = 0,
    LootDrone,
    Scout
};

class Tile :public GameObject
{
	float tileSize;
    int posIndexX, posIndexY;
    vector<vector<int>> tileMap;
    string tileName;
    int tileType = 0;
    EnemyList EnemyToSpawn;

public:
	
    Tile(float size,int indexX,int indexY,unsigned int texture, int newTileType);
    ~Tile();
    void setTextureID(unsigned int newTexture);
    void Render(glm::mat4 globalModelTransform);
    glm::vec3 getPosition();
    void setSpawner(unsigned int EnemyIndex);
    EnemyList getSpawner();


};