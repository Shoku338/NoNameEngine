#pragma once

#include <vector>
#include <GL/glew.h>
#include "GLRenderer.h" // Assuming you have a GLRenderer class
#include "GameEngine.h"
#include "GameObject.h"
#include "Enemy.h"


class Tilemap {
public:
    Tilemap(int width, int height, int tileSize, int tileSetWidth,int tileSetHeight, string tileSet, string mapFile);
    ~Tilemap();
    void LoadMapFromFile(const std::string& filePath); // New function for loading from a file
    void Render(const glm::mat4& viewMatrix);
    int GetTileType(int x, int y);
    unsigned int getTexture();
    int getWidth();
    int getHeight();
    vector<Tile*> getTilemap();
    void setTile(vector<DrawableObject*> * list);
    void calculateUV(float MaxCol, float MaxRow, float CurrentCol, float CurrentRow, float* newUV);

private:
    int mapWidth;
    int mapHeight;
    int tileSize;
    vector<Tile*> TileList;
    unsigned int texture;
    std::vector<std::vector<int>> tileMap; // 2D vector representing the tile IDs

};
