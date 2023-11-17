#include "Tilemap.h"
#include "GLRenderer.h"
#include <fstream>
#include <sstream>

Tilemap::Tilemap(int width, int height, int tileSize) : mapWidth(width), mapHeight(height), tileSize(tileSize) {
    // Initialize tileMap with default values or load it from a file
}

Tilemap::~Tilemap() {
    // Clean up any resources if needed
}

void Tilemap::SetTileset(GLRenderer* renderer, GLuint textureID, int tileWidth, int tileHeight) {
    /*tilesetTexture = textureID;
    tilesetWidth = tileWidth;
    tilesetHeight = tileHeight;
    renderer->SetTileset(this, textureID, tileWidth, tileHeight);*/
}

void Tilemap::LoadMapFromFile(const std::string& filePath) {
    std::ifstream file(filePath);

    if (!file.is_open()) {
        // Failed to open file
        return;
    }

    std::vector<std::vector<int>> tempMap;  // Temporary vector to store rows in reverse order

    std::string line;
    while (std::getline(file, line)) {
        std::vector<int> row;
        std::istringstream ss(line);
        int tileID;
        while (ss >> tileID) {
            row.push_back(tileID);
        }
        tempMap.push_back(row);
    }

    file.close();

    // Reverse the order of rows
    std::reverse(tempMap.begin(), tempMap.end());

    // Copy the reversed map to tileMap
    tileMap = tempMap;

}

void Tilemap::Render() 
{
   
}

int Tilemap::GetTileType(int x, int y)
{
    if (x >= 0 && x < mapWidth && y >= 0 && y < mapHeight) {
        return tileMap[y][x];
    }
    // Return a default value or handle out-of-bounds as needed
    return 0;
}