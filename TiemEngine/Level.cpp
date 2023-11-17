#include "Level.h"
#define GRAVITY -15.0f
#define	COLLISION_LEFT				1
#define	COLLISION_RIGHT				2
#define	COLLISION_TOP				4
#define	COLLISION_BOTTOM			3





void Level::LevelLoad()
{
	SquareMeshVbo * square = new SquareMeshVbo();
	square->LoadData();
	GameEngine::GetInstance()->AddMesh(SquareMeshVbo::MESH_NAME, square);

	//cout << "Load Level" << endl;
}

void Level::LevelInit()
{
	

	ImageObject* other = new ImageObject();
	other->SetTexture("../Resource/Texture/MOTIVATED.png");
	other->SetSize(128.0f, -128.0f);
	other->SetPosition(glm::vec3(200, 200, 0));
	objectsList.push_back(other);


	//Added by Kapom

	Tilemap tilemap(1024, 576, 1);
	tilemap.LoadMapFromFile("../Resource/Texture/map.txt");

	// Loop through the tile map and create tiles based on the map data
	for (int y = 0; y < 9; ++y) {
		for (int x = 0; x < 16; ++x) {
			int tileType = tilemap.GetTileType(x, y);

			Tile* tile = new Tile(64.0f, x, y, tileType);

			// Set the texture based on the tile type
			if (tileType == 1) {
				tile->SetTexture("../Resource/Texture/grass.png");
			}
			else {
				tile->SetTexture("../Resource/Texture/water.jpg"); 
			}

			TileList.push_back(tile);
		}
	}

	//Game object

	GameObject * obj = new GameObject();
	obj->SetTexture("../Resource/Texture/Player.png");
	obj->SetSize(96.0f, -96.0f);
	objectsList.push_back(obj);

	player = obj;
	player->SetPosition(glm::vec3(100.0f, 100.0f, 0.0f));


	

	//cout << "Init Level" << endl;
}

void Level::LevelUpdate(float dt)
{
	
	//cout << "Update Level" << endl;
	
	player->Translate(player->velocity * dt);
	player->velocity.x *= (1.0f - 0.1f); //0.3 is friction for now
	player->velocity.y += GRAVITY * dt; //Gravity
	for (int i = 0; i < objectsList.size(); i ++) {
		
		if (objectsList.at(i) != player) {
			int resultCol = player->detectCollisionAABB(objectsList.at(i)->getPosX(), objectsList.at(i)->getPosY(), abs(objectsList.at(i)->getsizeY()), objectsList.at(i)->getsizeX());
			if (resultCol == COLLISION_BOTTOM)
			{
				player->Translate(glm::vec3(0, 10, 0));
			}
			
			//collision value
			//cout << player->getPosX() << ' ' << player->getPosY() << ' ' << objectsList.at(i)->getPosX() << ' ' << objectsList.at(i)->getPosY() << ' '<< resultCol << endl;
		}
	}
	

}

void Level::LevelDraw()
{
	GameEngine::GetInstance()->RenderTile(TileList);
	GameEngine::GetInstance()->Render(objectsList);
	
	//cout << "Draw Level" << endl;
}

void Level::LevelFree()
{
	cout << "Free Level" << endl;
	for (DrawableObject* obj : objectsList) {
		delete obj;
	}
	objectsList.clear();

	for (Tile* tile : TileList) {
		delete tile;
	}
	TileList.clear();
	
}

void Level::LevelUnload()
{
	GameEngine::GetInstance()->ClearMesh();
	//cout << "Unload Level" << endl;
}

void Level::HandleKey(char key)
{
	 
	switch (key)
	{
		case 'w': player->velocity.y = 128.0f; 
			player->setGround(false);	break; // jumping
		case 'a': player->velocity.x = -50.f; break;//move velocity value
		case 'd': player->velocity.x = 50.f; break;//move velocity value
			//need spacebar
		case ' ': player->velocity.y = 5.0f;
			player->setGround(false);	break; 
		
		case 'q': GameEngine::GetInstance()->GetStateController()->gameStateNext = GameState::GS_QUIT; ; break;
		case 'r': GameEngine::GetInstance()->GetStateController()->gameStateNext = GameState::GS_RESTART; ; break;
		case 'e': GameEngine::GetInstance()->GetStateController()->gameStateNext = GameState::GS_LEVEL2; ; break;
		
	}
	
	
}

void Level::HandleMouse(int type, int x, int y)
{
	float realX, realY;

	// Calculate Real X Y 
	float h = GameEngine::GetInstance()->GetWindowHeight();
	float w = GameEngine::GetInstance()->GetWindowWidth();
	float hg = GameEngine::GetInstance()->GetGameHeight();
	float wg = GameEngine::GetInstance()->GetGameWidth();
	
	//cout << h << ',' << w << endl;
	cout << "mouse x,y " << x << ',' << y << endl;
	realX = (x) / (w /wg);
	realY = hg - (y / (h / hg));
	cout << realX << ',' << realY << endl;
	

	player->SetPosition(glm::vec3(realX, realY, 0));
}