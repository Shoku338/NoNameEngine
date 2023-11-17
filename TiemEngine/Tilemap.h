#pragma once

#include <vector>
#include <GL/glew.h>
#include "GLRenderer.h" // Assuming you have a GLRenderer class

class Tilemap {
public:
    Tilemap(int width, int height, int tileSize);
    ~Tilemap();

    void SetTileset(GLRenderer* renderer, GLuint textureID, int tileWidth, int tileHeight);
    void LoadMapFromFile(const std::string& filePath); // New function for loading from a file
    void Render();
    int GetTileType(int x, int y);

private:
    int mapWidth;
    int mapHeight;
    int tileSize;

    GLuint tilesetTexture;
    std::vector<std::vector<int>> tileMap; // 2D vector representing the tile IDs
};
