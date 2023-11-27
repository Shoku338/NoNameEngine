#include "Level.h"
#define GRAVITY -40.0f
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
	ImageObject* bullet = new ImageObject();
	bullet->SetTexture("../Resource/Texture/LaserB.png");
	bullet->SetSize(32.0f, -32.0f);
	bullet->SetPosition(glm::vec3(200, 200, 0));
	objectsList.push_back(bullet);
	//objectsList.at(0)->rotate(60);

	ImageObject* other = new ImageObject();
	other->SetTexture("../Resource/Texture/MOTIVATED.png");
	other->SetSize(128.0f, -128.0f);
	other->SetPosition(glm::vec3(200, 200, 0));
	objectsList.push_back(other);
	//objectsList.at(0)->rotate(60);

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
				tile->setTextureID(tilemap.getTexture(1));
				TileList.push_back(tile);
			}
			else if(tileType == 2)
			{
				tile->setTextureID(tilemap.getTexture(0));
				TileList.push_back(tile);

				ImageObject* zelda = new ImageObject();
				zelda ->SetTexture("../Resource/Texture/Zelda.png");
				zelda ->SetSize(128.0f, -128.0f);
				zelda->SetPosition(tile->getPosition());
				objectsList.push_back(zelda);

			}
			else if(tileType == 0)
			{
				tile->setTextureID(tilemap.getTexture(0));
				TileList.push_back(tile);
			}

			//TileList.push_back(tile);
		}
	}

	//Game object

	Player * ply = new Player();
	ply->SetTexture("../Resource/Texture/Main_Character.png");
	ply->SetSize(96.0f, -96.0f);
	objectsList.push_back(ply);

	player = ply;
	player->SetPosition(glm::vec3(100.0f, 100.0f, 0.0f));
	//cout << "Init Level" << endl;
}


void Level::LevelUpdate(float dt)
{
	
	//cout << "Update Level" << endl;
	
	player->Translate(player->velocity * dt);
	player->velocity.x *= (1.0f - 0.1f); //0.3 is friction for now
	if (player->velocity.y >= -50.0f) {
		//cout << "add grav" << endl;
		player->velocity.y += GRAVITY * dt; //Gravity
	}
	//objectsList.at(0)->velocity.x += 50.0; DON'T DO ANYTHING WITH THIS YET
	//objectsList.at(0)->Translate(objectsList.at(0)->velocity * dt);
	for (int i = 0; i < objectsList.size(); i ++) {
		
		if (objectsList.at(i) != player) {
			int resultCol = player->detectCollisionAABB(objectsList.at(i)->getPosX(), objectsList.at(i)->getPosY(), abs(objectsList.at(i)->getsizeY()), objectsList.at(i)->getsizeX());
			if (resultCol == COLLISION_BOTTOM)
			{
				//game logic here
				player->setGround(true);
				player->velocity.y = 0;
				player->Translate(glm::vec3(0, 0.5, 0));
			}
			if (resultCol == COLLISION_RIGHT)
			{
				//game logic here
				player->Translate(glm::vec3(-0.4, 0, 0));
			}
			
			//collision value
			//cout << player->getPosX() << ' ' << player->getPosY() << ' ' << objectsList.at(i)->getPosX() << ' ' << objectsList.at(i)->getPosY() << ' '<< resultCol << endl;
		}
		if (objectsList.at(i)->getPosX() >= GameEngine::GetInstance()->GetGameWidth()) {
			objectsList.erase(objectsList.begin() + i);
			
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
		case ' ':
		case 'w': if (player->getGrounded()) {
			cout << "Rising hopper" << endl;
			player->velocity.y = 50.0f;
		}
			player->setGround(false);
			break; // jumping
		case 'a': player->velocity.x = -50.f; break;//move velocity value
		case 'd': player->velocity.x = 50.f; break;//move velocity value
			//need spacebar
		
		
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