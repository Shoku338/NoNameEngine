#include "Level.h"
#define GRAVITY -15.0f

int _detectCollisionAABB(float ax, float ay, float ah, float aw, float bx, float by, float bh, float bw) {
	int result = 0;

	float dx = ax - bx; // Calculate the distance between the centers of the two boxes along the x-axis
	float dy = ay - by; // Calculate the distance between the centers of the two boxes along the y-axis

	float combinedHalfWidths = aw / 2 + bw / 2; // Calculate the sum of the half-widths of the two boxes
	float combinedHalfHeights = ah / 2 + bh / 2; // Calculate the sum of the half-heights of the two boxes

	if (std::abs(dx) < combinedHalfWidths && std::abs(dy) < combinedHalfHeights) { // Check for collision
		float overlapX = combinedHalfWidths - std::abs(dx); // Calculate the overlap along the x-axis
		float overlapY = combinedHalfHeights - std::abs(dy); // Calculate the overlap along the y-axis

		// Determine the direction of the collision based on the overlap
		result |= dx > 0 ? 1 : 2;
		result |= dy > 0 ? 8 : 4;
	}
	//cout << result << endl;
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
	//Added by Kapom
	ImageObject* other = new ImageObject();
	other->SetTexture("../Resource/Texture/MOTIVATED.png");
	other->SetSize(2.0f, -2.0f);
	other->SetPosition(glm::vec3(2, 2, 0));
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
	//test collision at wall
	/*if (player->getPosX() < -3) {
		player->Translate(glm::vec3 (-3, player->getPosY(), 0.0f));
	}*/
	//cout << player->getPosX() << endl;
	player->velocity.x *= (1.0f - 0.7f); //0.7 is friction for now
	//player->velocity.y += GRAVITY * dt;
	for (int i = 0; i < objectsList.size(); i ++) {
		if (objectsList.at(i) != player) {
			int _result = _detectCollisionAABB(player->getPosX(), player->getPosY(), 1.f, 1.f, objectsList.at(i)->getPosX(), objectsList.at(i)->getPosY(), 2.f, 2.f);
			//cout << player->getPosX() << ' ' << player->getPosY() << ' ' << objectsList.at(0)->getPosX() << ' ' << objectsList.at(0)->getPosY() << endl;
			//cout << _result << endl;
		}
	}
	

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
			player->setGround(false);	break; // jumping
		case 'a': player->velocity.x = -5; break;//move velocity value
		case 'd': player->velocity.x = 5; break;//move velocity value
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
	
	cout << h << ',' << w << endl;

	realX = (x - (w / 2)) / (w / 6.0f);
	realY = -(y - (h / 2)) / (h / 6.0f);
	cout << realX << ',' << realY << endl;
	

	player->SetPosition(glm::vec3(realX, realY, 0));
}