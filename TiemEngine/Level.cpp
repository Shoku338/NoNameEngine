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

	//Added by Kapom

	tilemap = new Tilemap(16, 9, 64 ,6,3, "../Resource/Texture/Map_with_grid.png", "../Resource/Texture/map.txt");
	tilemap->setTile(&objectsList);

	//cout << "Load Level" << endl;
}

void Level::LevelInit()
{
	camera = new Camera2D(GameEngine::GetInstance()->GetWindowWidth() , GameEngine::GetInstance()->GetWindowHeight());
	GameObject* other = new GameObject();
	other->SetTexture("../Resource/Texture/MOTIVATED.png");
	other->SetSize(128.0f, -128.0f);
	other->SetPosition(glm::vec3(200, 200, 0));
	objectsList.push_back(other);
	other->setCollision(true);
	//objectsList.at(0)->rotate(60);

	Bullet* bullet = new Bullet();
	bullet->SetTexture("../Resource/Texture/LaserB.png");
	bullet->SetSize(32.0f, -32.0f);
	bullet->SetPosition(glm::vec3(200, 200, 0));
	objectsList.push_back(bullet);
	//objectsList.at(0)->rotate(60);


	//Game object

	Player * ply = new Player();
	ply->SetTexture("../Resource/Texture/penguin.png");
	ply->SetSize(96.0f, -96.0f);
	objectsList.push_back(ply);
	ply->setCollision(true);
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

	// Update camera position based on player's new position
	if (camera) {
		camera->UpdateCameraPosition(glm::vec2(player->getPosX()- GameEngine::GetInstance()->GetGameWidth()/2, player->getPosY()- GameEngine::GetInstance()->GetGameHeight()/2));
		//printf("Window Width : %d, Window Height: %d\n", GameEngine::GetInstance()->GetWindowWidth(), GameEngine::GetInstance()->GetWindowHeight());
		//printf("PLayer position: %f, %f\n", player->getPosX(), player->getPosY());
	}


	


	for (int i = 0; i < tilemap->getTilemap().size(); i++)
	{
		GameObject* gameObject = dynamic_cast<GameObject*>(tilemap->getTilemap().at(i));
		if (gameObject) {
			if (gameObject->getCollision()) {
				int resultCol = player->detectCollisionAABB(gameObject->getPosX(), gameObject->getPosY(), abs(gameObject->getsizeY()), gameObject->getsizeX());
				if (resultCol == COLLISION_BOTTOM)
				{
					//game logic here
					player->setGround(true);
					player->velocity.y = 0;
				}
				if (resultCol == COLLISION_RIGHT)
				{
					//game logic here
					player->Translate(glm::vec3(-0.4, 0, 0));
				}
				//collision value
				//cout << player->getPosX() << ' ' << player->getPosY() << ' ' << objectsList.at(i)->getPosX() << ' ' << objectsList.at(i)->getPosY() << ' '<< resultCol << endl;
			}
		}
	}
	


	//objectsList.at(0)->velocity.x += 50.0; DON'T DO ANYTHING WITH THIS YET
	//objectsList.at(0)->Translate(objectsList.at(0)->velocity * dt);
	for (auto it = objectsList.begin(); it != objectsList.end();) {
		if (Bullet* bullet = dynamic_cast<Bullet*>(*it)) {
			bullet->update(dt);
			if (bullet->timesUp()) {
				it = objectsList.erase(it);
				continue;  // Skip the rest of the loop for this iteration
			}
		}
		
		if (GameObject* gameObject = dynamic_cast<GameObject*>(*it)) {
			//gameObject->Translate(gameObject->velocity);
			if (gameObject->getCollision()) {
				int resultCol = player->detectCollisionAABB(
					gameObject->getPosX(), gameObject->getPosY(),
					abs(gameObject->getsizeY()), gameObject->getsizeX());

				if (resultCol == COLLISION_BOTTOM) {
					// Game logic for collision at the bottom
					player->setGround(true);
					player->velocity.y = 0;
				}
				else if (resultCol == COLLISION_RIGHT) {
					// Game logic for collision on the right
					player->Translate(glm::vec3(-0.4, 0, 0));
				}

				// Additional collision handling logic can be added here
			}
		}

		++it;  // Increment the iterator for the next iteration
	}

}
	

void Level::LevelDraw()
{

	glm::mat4 viewMatrix = camera->GetViewMatrix();
	tilemap->Render(viewMatrix);
	//GameEngine::GetInstance()->Render(objectsList);

	if (camera) 
	{
		
		GameEngine::GetInstance()->Render(objectsList, viewMatrix);
		
		
	}
	else 
	{
		GameEngine::GetInstance()->Render(objectsList, glm::mat4(1.0));
	}
	
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
		case ' ':
		case 'w': 
			if (player->getGrounded()) {
			cout << "Rising hopper" << endl;
			player->velocity.y = 50.0f;
			
		}
			player->setGround(false);
			break; // jumping
		case 'a': player->velocity.x = -100.f; break;//move velocity value
		case 'd': player->velocity.x = 100.f; break;//move velocity value
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
    glm::vec2 playerPos = glm::vec2(player->getPosX(), player->getPosY());

	glm::vec3 bulletStartPosition = player->getPosition() + glm::vec3(10.0f, 0.0f, 0.0f); // Adjust the offset as needed

	// Create a new bullet and set its direction
	Bullet* newBullet = new Bullet(bulletStartPosition);
	newBullet->SetSize(20.f, 20.f);
	// Calculate direction from player position to mouse position
	glm::vec2 direction = glm::vec2(realX, realY) - glm::vec2(player->getPosX(), player->getPosY());
	// Shoot the bullet in the calculated direction
	newBullet->shootAt(direction, newBullet->getVelocity().x);
	objectsList.push_back(newBullet);
	//player->SetPosition(glm::vec3(realX, realY, 0));
}