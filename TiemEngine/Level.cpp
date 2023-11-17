#include "Level.h"
#define GRAVITY -15.0f
#define	COLLISION_LEFT				1<<0       //0001 = 1
#define	COLLISION_RIGHT				1<<1      // 0001 -> 0010 = 2
#define	COLLISION_TOP				1<<2       //0001 -> 0100 = 4
#define	COLLISION_BOTTOM			1<<3      // 0001 -> 1000 = 8

int Level::_detectCollisionAABB(float ax, float ay, float ah, float aw, float bx, float by, float bh, float bw) {
	int result = 0;

	float dx = ax - bx; // Calculate the distance between the centers of the two boxes along the x-axis
	float dy = ay - by; // Calculate the distance between the centers of the two boxes along the y-axis

	float combinedHalfWidths = abs(aw) / 2 + abs(bw) / 2; // Calculate the sum of the half-widths of the two boxes
	float combinedHalfHeights = abs(ah) / 2 + abs(bh) / 2; // Calculate the sum of the half-heights of the two boxes

	if (std::abs(dx) < combinedHalfWidths && std::abs(dy) < combinedHalfHeights) { // Check for collision
		overlapX = combinedHalfWidths - std::abs(dx); // Calculate the overlap along the x-axis
		overlapY = combinedHalfHeights - std::abs(dy); // Calculate the overlap along the y-axis

		// Determine the direction of the collision based on the overlap
		result |= dx > 0 ? 1 : 2;
		result |= dy > 0 ? 8 : 4;
	}

	return result;
}



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
	
	//player->Translate(player->velocity * dt);
	player->velocity.x *= (1.0f - 0.3f); //0.3 is friction for now
	//player->velocity.y += GRAVITY * dt; //Gravity
	for (int i = 0; i < objectsList.size(); i ++) {
		
		if (objectsList.at(i) != player) {
			int resultCol = _detectCollisionAABB(player->getPosX(), player->getPosY(), -player->getsizeY(), player->getsizeX(),
				objectsList.at(i)->getPosX(), objectsList.at(i)->getPosY(), -objectsList.at(i)->getsizeY(), objectsList.at(i)->getsizeX());
			if (resultCol== 0) {
				player->Translate(player->velocity * dt);

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
		case 'a': player->velocity.x = -50; break;//move velocity value
		case 'd': player->velocity.x = 50; break;//move velocity value
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