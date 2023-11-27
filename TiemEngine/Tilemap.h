#pragma once

#include <vector>
#include <GL/glew.h>
#include "GLRenderer.h" // Assuming you have a GLRenderer class
#include "GameEngine.h"
#include "GameObject.h"


class Tilemap {
public:
    Tilemap(int width, int height, int tileSize);
    ~Tilemap();
    void LoadMapFromFile(const std::string& filePath); // New function for loading from a file
    void Render();
    int GetTileType(int x, int y);
    unsigned int getTexture(int index);
    int getWidth();
    int getHeight();
    void setTile(vector<DrawableObject*> * list);
    float* calculateUV(float MaxRow, float MaxCol, float CurrentRow, float CurrentCol);

private:
    int mapWidth;
    int mapHeight;
    int tileSize;
    vector<Tile*> TileList;
    vector<unsigned int> textures;
    std::vector<std::vector<int>> tileMap; // 2D vector representing the tile IDs
};
