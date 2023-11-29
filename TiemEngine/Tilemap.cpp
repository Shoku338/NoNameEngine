#include "Tilemap.h"
#include "GLRenderer.h"
#include <fstream>
#include <sstream>

Tilemap::Tilemap(int width, int height, int tileSize) : mapWidth(width), mapHeight(height), tileSize(tileSize) {
    // Initialize tileMap with default values or load it from a file
    textures.push_back(GameEngine::GetInstance()->GetRenderer()->LoadTexture("../Resource/Texture/water.jpg"));
    textures.push_back(GameEngine::GetInstance()->GetRenderer()->LoadTexture("../Resource/Texture/grass.png"));
}


Tilemap::~Tilemap() {
    // Clean up any resources if needed
    for (Tile* tile : TileList) {
        delete tile;
    }
    TileList.clear();
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
    GameEngine::GetInstance()->RenderTile(TileList);
}

int Tilemap::GetTileType(int x, int y)
{
    if (x >= 0 && x < mapWidth && y >= 0 && y < mapHeight) {
        return tileMap[y][x];
    }
    // Return a default value or handle out-of-bounds as needed
    return 0;
}

unsigned int Tilemap::getTexture(int index)
{
    return textures[index];
}

int Tilemap::getWidth()
{
    return mapWidth;
}

int Tilemap::getHeight()
{
    return mapHeight;
}

void Tilemap::setTile(vector<DrawableObject*> * list)
{
    for (int y = 0; y < mapHeight; ++y) {
        for (int x = 0; x < mapWidth; ++x) {
            int tileType = tileMap[y][x];

            Tile* tile = new Tile(64.0f, x, y, tileType);

            // Set the texture based on the tile type
            if (tileType == 1) {
                tile->setTextureID(textures[1]);
            }
            else if (tileType == 2)
            {
                //tile->setTextureID(textures[1]);
             

                GameObject* zelda = new GameObject();
                zelda->SetTexture("../Resource/Texture/Zelda.png");
                zelda->SetSize(128.0f, -96.0f);
                zelda->SetPosition(tile->getPosition());
                list->push_back(zelda);

            }
            else if (tileType == 0)
            {
                tile->setTextureID(textures[0]);
            }

            TileList.push_back(tile);
            //cout << "push back tile " << endl;
        }
    }
}

//float* Tilemap::calculateUV(float MaxRow, float MaxCol, float CurrentRow, float CurrentCol)
//{
//    
//}