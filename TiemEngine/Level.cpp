#include "Level.h"
#define GRAVITY -15.0f


void Level::LevelLoad()
{
	SquareMeshVbo * square = new SquareMeshVbo();
	square->LoadData();
	GameEngine::GetInstance()->AddMesh(SquareMeshVbo::MESH_NAME, square);

	//cout << "Load Level" << endl;
}

void Level::LevelInit()
{
	//Added by Kapom
	ImageObject* other = new ImageObject();
	other->SetTexture("../Resource/Texture/MOTIVATED.png");
	other->SetSize(2.0f, -2.0f);
	other->SetPosition(glm::vec3(2, 2, 1));
	objectsList.push_back(other);

	ImageObject * obj = new ImageObject();
	obj->SetTexture("../Resource/Texture/Player.png");
	obj->SetSize(1.0f, -1.0f);
	objectsList.push_back(obj);

	player = obj;
	player->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));

	

	//cout << "Init Level" << endl;
}

void Level::LevelUpdate(float dt)
{
	
	//cout << "Update Level" << endl;
	//gonna make pos public need it too much
	player->Translate(player->velocity * dt);
	//collide left
	if (player->getPosX() <= realLeftWall) {
		player->SetPosition(glm::vec3 (realLeftWall + 0.5, player->getPosY(), 0));
		cout << "wall" << endl;
	}
	player->velocity.x *= (1.0f - 0.7f);//0.7 is friction for now
	//player->velocity.y += GRAVITY * dt;

	
}

void Level::LevelDraw()
{
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
		case 'w': player->velocity.y = 5.0f; 
			player->setGround(false);	break;
		case 'a': player->velocity.x = -5; break;//(move velocity value
		case 'd': player->velocity.x = 5; break;//(move velocity value
			//need spacebar
		case ' ': player->velocity.y = 5.0f;
			player->setGround(false);	break; break;
		
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
	
	cout << h << ',' << w << endl;

	realX = (x - (w / 2)) / 100.0f;
	realY = -(y - (h / 2)) / 100.0f;
	cout << realX << ',' << realY << endl;
	

	player->SetPosition(glm::vec3(realX, realY, 0));
}