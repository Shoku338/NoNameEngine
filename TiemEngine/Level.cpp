#include "Level.h"
#define GRAVITY -5.0f

void Level::LevelLoad()
{
	SquareMeshVbo * square = new SquareMeshVbo();
	square->LoadData();
	GameEngine::GetInstance()->AddMesh(SquareMeshVbo::MESH_NAME, square);

	//cout << "Load Level" << endl;
}

void Level::LevelInit()
{
	ImageObject * obj = new ImageObject();
	obj->SetTexture("../Resource/Texture/Player.png");
	obj->SetSize(0.5f, -0.5f);
	objectsList.push_back(obj);

	player = obj;
	player->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));

	//Added by Kapom
	ImageObject* other = new ImageObject();
	other->SetTexture("../Resource/Texture/MOTIVATED.png");
	other->SetSize(2.0f, -2.0f);
	other->SetPosition(glm::vec3(2, 2, 1));
	objectsList.push_back(other);

	//cout << "Init Level" << endl;
}

void Level::LevelUpdate(float dt)
{
	
	//cout << "Update Level" << endl;
	//gonna make pos public need it too much
	player->velocity.x *= (1.0f - 0.7f);
	if (!player->getGrounded()) {
		player->velocity.y = GRAVITY *dt;
		
	}
	if (player->getPosX() <= -GameEngine::GetInstance()->GetWindowHeight() + 0.2) {
		player->SetPosition(glm::vec3(player->getPosX(), -GameEngine::GetInstance()->GetWindowHeight() +0.2, 0.0f));
	}
	
	player->Translate(player->velocity * dt);
	
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
		case 'w': player->velocity.y = 15.0f; 
			player->setGround(false);	break;
		
			//need spacebar
		case ' ': player->velocity.y = 1; break;
		//case 'w': player->Translate(glm::vec3(0, 0.1, 0)); break;
		//case 's': player->Translate(glm::vec3(0, -0.1, 0)); break;
		//case 'a': player->Translate(glm::vec3(-0.1, 0, 0)); break;
		//case 'd': player->Translate(glm::vec3(0.1, 0, 0)); break;
		case 'q': GameEngine::GetInstance()->GetStateController()->gameStateNext = GameState::GS_QUIT; ; break;
		case 'r': GameEngine::GetInstance()->GetStateController()->gameStateNext = GameState::GS_RESTART; ; break;
		case 'e': GameEngine::GetInstance()->GetStateController()->gameStateNext = GameState::GS_LEVEL2; ; break;
		
	}
	switch (key) {
	case 'a': player->velocity.x = -5; break;//(move velocity value
	case 'd': player->velocity.x = 5; break;//(move velocity value
	}
	
}

void Level::HandleMouse(int type, int x, int y)
{
	float realX, realY;

	// Calculate Real X Y 
	float h = GameEngine::GetInstance()->GetWindowHeight();
	float w = GameEngine::GetInstance()->GetWindowWidth();
	
	//cout << x << ',' << y << endl;

	realX = (x - (w / 2)) / 100.0f;
	realY = (-(y - (h / 2))) / 100.0f;
	//cout << realX << ',' << realY << endl;
	

	player->SetPosition(glm::vec3(realX, realY, 0));
}