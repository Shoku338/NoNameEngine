#pragma once

#include <vector>
#include <GL/glew.h>
#include "GLRenderer.h" // Assuming you have a GLRenderer class
#include "GameEngine.h"

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

private:
    int mapWidth;
    int mapHeight;
    int tileSize;

    vector<unsigned int> textures;
    std::vector<std::vector<int>> tileMap; // 2D vector representing the tile IDs
};
