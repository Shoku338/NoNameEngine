#include "Tilemap.h"
#include "GLRenderer.h"
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>

Tilemap::Tilemap(int width, int height, int tileSize, int tileSetWidth, int tileSetHeight, string tileSet,string mapFile) : mapWidth(width), mapHeight(height), tileSize(tileSize) {
    // Initialize tileMap with default values or load it from a file
    texture = GameEngine::GetInstance()->GetRenderer()->LoadTexture(tileSet);
    for (int i = 0; i < tileSetHeight; i++)
    {   
        for (int j = 0; j < tileSetWidth; j++)
        {
            float newUv[8];
            calculateUV(tileSetWidth, tileSetHeight,j,i,newUv );
            if (i==0&&j==0)
            {
         
                for (int a = 0; a < 8; a++)
                {
                    cout << endl << newUv[a];
                }
            }
            
            SquareMeshVbo* square = new SquareMeshVbo();
            square->LoadDataTile(newUv);
            //cout << to_string((tileSetWidth * i) + j) << " ";
            GameEngine::GetInstance()->AddMesh(to_string((tileSetWidth*i)+j), square);
        }
        
    }


    // Load map data from TXT file
    LoadMapFromFile(mapFile);
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

void Tilemap::Render(const glm::mat4& viewMatrix)
{
    GameEngine::GetInstance()->RenderTile(TileList,viewMatrix);
}

int Tilemap::GetTileType(int x, int y)
{
    if (x >= 0 && x < mapWidth && y >= 0 && y < mapHeight) {
        return tileMap[y][x];
    }
    // Return a default value or handle out-of-bounds as needed
    return 0;
}

unsigned int Tilemap::getTexture()
{
    return texture;
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
            

            if (tileType == 20)
            {
                // Enemy Spawn Tile
                Tile* tile = new Tile(64.0f, x, y, texture, 11);
                Enemy* lootDrone = new Enemy("../Resource/Texture/enemy_lootdrone_idle_sprite.png", 1, 10);
                lootDrone->SetPosition(tile->getPosition());
                list->push_back(lootDrone);
                TileList.push_back(tile);
            }
            else
            {
                // Set the texture based on the tile type
                Tile* tile = new Tile(64.0f, x, y, texture, tileType);
                if (tileType != 11)
                {
                    tile->setCollision(true);
                }
                TileList.push_back(tile);
            }
            

            
          
        }
    }
}

void Tilemap::calculateUV(float MaxCol, float MaxRow, float CurrentCol, float CurrentRow, float* newUV)
{
    // Calculate UV coordinates starting from bottom-left in counter-clockwise order

    newUV[0] = CurrentCol / MaxCol;               // bottom left x
    newUV[1] = CurrentRow  / MaxRow;  // bottom left y

    newUV[2] = (CurrentCol + 1.0f) / MaxCol;       // bottom right x
    newUV[3] = CurrentRow / MaxRow;  // bottom right y

    newUV[4] = (CurrentCol + 1.0f) / MaxCol;       // top right x
    newUV[5] = (CurrentRow + 1) / MaxRow;       // top right y

    newUV[6] = CurrentCol / MaxCol;               // top left x
    newUV[7] = (CurrentRow + 1) / MaxRow;

    
}

vector<Tile*> Tilemap::getTilemap()
{
    return TileList;
}