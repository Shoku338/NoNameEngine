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

    std::string line;
    while (std::getline(file, line)) {
        std::vector<int> row;
        std::istringstream ss(line);
        int tileID;
        while (ss >> tileID) {
            row.push_back(tileID);
        }
        tileMap.push_back(row);
    }

    file.close();

    // Print the loaded map to the console
    for (const auto& row : tileMap) {
        for (int tileID : row) {
            std::cout << tileID << " ";
        }
        std::cout << std::endl;
    }
}

void Tilemap::Render() {
    //for (int y = 0; y < mapHeight; ++y) {
    //    for (int x = 0; x < mapWidth; ++x) {
    //        int tileID = tileMap[y][x];
    //        if (tileID != -1) { // Assuming -1 represents an empty tile
    //            int srcX = (tileID % (tilesetWidth / tileSize)) * tileSize;
    //            int srcY = (tileID / (tilesetWidth / tileSize)) * tileSize;
    //            int destX = x * tileSize;
    //            int destY = y * tileSize;

    //            // Assuming you have a method in GLRenderer to render a tile using OpenGL
    //            RenderTile(tilesetTexture, srcX, srcY, destX, destY, tileSize, tileSize);
    //        }
    //    }
    //}
}