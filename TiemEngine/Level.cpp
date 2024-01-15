#include "Level.h"
#define GRAVITY -100.0f
#define	COLLISION_LEFT				1
#define	COLLISION_RIGHT				2
#define	COLLISION_TOP				4
#define	COLLISION_BOTTOM			3
#define MAXX_JUMP 2


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
	other->SetPosition(glm::vec3(500, 250, 0));
	objectsList.push_back(other);
	other->setCollision(true);

	Bullet* bullet = new Bullet();
	bullet->SetTexture("../Resource/Texture/LaserB.png");
	bullet->SetSize(32.0f, -32.0f);
	bullet->SetPosition(glm::vec3(200, 200, 0));
	objectsList.push_back(bullet);
	//bullet->rotateDegree(60);


	//Game object

	Player* ply = new Player();
	ply->SetTexture("../Resource/Texture/Body.png");
	ply->SetSize(96.0f, -96.0f);
	objectsList.push_back(ply);
	ply->setCollision(false);
	player = ply;
	player->SetPosition(glm::vec3(100.0f, 150.0f, 0.0f));
	player->setWeapon("../Resource/Texture/Proto_plasma.png");
	//cout << "Init Level" << endl;



	// Initialize the sound manager and load/play music
	soundManager = new SoundManager();
	soundManager->loadSound("Zelda", "../Resource/Sound/TestZelda.mp3");
	soundManager->loadSound("Blaster", "../Resource/Sound/Blaster.mp3");
	soundManager->playSound("Zelda", true);
	soundManager->getSound("Zelda")->setDefaultVolume(0.4);
}


void Level::LevelUpdate(float dt)
{
	
	//cout << "Update Level" << endl;
	
	player->Translate(player->velocity * dt);
	player->velocity.x *= (1.0f - 0.1f); //0.3 is friction for now
	player->update();
	if (player->velocity.y >= -100.0f) {
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
					player->setJump(0);
					player->velocity.y = 0;
				}
				else if (resultCol == COLLISION_RIGHT)
				{
					//game logic here
					player->Translate(glm::vec3(-0.7, 0, 0));
					player->velocity.x = 0;
				}
				else if (resultCol == COLLISION_LEFT) {
					// Game logic for collision on the left of player
					player->Translate(glm::vec3(0.5, 0, 0));
					player->velocity.x = 0;
				}
				else if (resultCol == COLLISION_TOP) {
					// Game logic for collision at the Top of player
					player->Translate(glm::vec3(0, -0.5, 0));
					player->velocity.y = 0;
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
			if (Grapple* grapple = dynamic_cast<Grapple*>(*it)) {
				// Check for collision with other GameObjects
				for (auto otherIt = objectsList.begin(); otherIt != objectsList.end(); )
				{
					if (GameObject* gameObject2 = dynamic_cast<GameObject*>(*otherIt)) {
						if(gameObject2->getCollision()){
							int colG = grapple->detectCollisionAABB(
								gameObject2->getPosX(), gameObject2->getPosY(),
								abs(gameObject2->getsizeY()), gameObject2->getsizeX());
							//cout << "colresult:" << colG << endl;
							if (colG != 0) {
								// Collision detected, execute pull function
								//cout << "boop" << endl;
								grapple->velocity = glm::vec3(0, 0, 0);
								grapple->pull(*player, dt*2, 150);
								// Handle other logic if needed
							}
						}
					}
					++otherIt;
				}
			}
		}
		
		 if (GameObject* gameObject = dynamic_cast<GameObject*>(*it)) {
			//gameObject->Translate(gameObject->velocity);
			 if(gameObject->getCollision()){
				 int resultCol = player->detectCollisionAABB(
					 gameObject->getPosX(), gameObject->getPosY(),
					 abs(gameObject->getsizeY()), gameObject->getsizeX());
				 if (resultCol == COLLISION_BOTTOM) {
					 // Game logic for collision at the bottom of player
					 player->setGround(true);
					 player->setJump(0);
					 player->velocity.y = 0;
				 }
				 else if (resultCol == COLLISION_RIGHT) {
					 // Game logic for collision on the right of player
					 player->Translate(glm::vec3(-0.5, 0, 0));
					 player->velocity.x = 0;
				 }
				 else if (resultCol == COLLISION_LEFT) {
					 // Game logic for collision on the left of player
					 player->Translate(glm::vec3(0.5, 0, 0));
					 player->velocity.x = 0;
				 }
				 else if (resultCol == COLLISION_TOP) {
					 // Game logic for collision at the Top of player
					 player->Translate(glm::vec3(0, -0.5, 0));
					 player->velocity.y = 0;
				 }
			 }

				// Additional collision handling logic can be added here
			
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

	if (soundManager) {
		soundManager->stopAllSounds();
		delete soundManager;
		soundManager = nullptr; // Ensure the pointer is set to nullptr after deletion
	}

}

void Level::LevelUnload()
{
	GameEngine::GetInstance()->ClearMesh();
	cout << "Unload Level" << endl;

	
}

void Level::HandleKey(char key)
{
	 
	switch (key)
	{
		case ' ':
		case 'w': 
			if (player->getJump() < MAXX_JUMP) {
			cout << "Rising hopper" << endl;
			player->velocity.y = 100.0f;
			player->setJump(player->getJump() + 1);
		}
			player->setGround(false);
			break; // jumping
		case 'a': 
			if(player->getVelocity().x <= 70)
			{
				player->velocity.x += -10.f; 
			}
			break;//move velocity value
		case 'd':
			if (player->getVelocity().x >= -70)
			{
				player->velocity.x += 10.f;
			}
			break;//move velocity value
		case 'C'://dashing
			if (player->velocity.x < 0)
				player->velocity.x -= 500.f; 
			else if(player->velocity.x >= 0)
				player->velocity.x += 500.f;
			break;
			//need spacebar		
		case 'q': GameEngine::GetInstance()->GetStateController()->gameStateNext = GameState::GS_QUIT; ; break;
		case 'r': GameEngine::GetInstance()->GetStateController()->gameStateNext = GameState::GS_RESTART; ; break;
		case 'e': GameEngine::GetInstance()->GetStateController()->gameStateNext = GameState::GS_LEVEL2; ;
			break;
		case '1': player->setWeapon("../Resource/Texture/Proto_plasma.png"); break;
		case '2': player->setWeapon("../Resource/Texture/Tier2_rapid machinegun.png"); break;
		
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
	glm::vec2 offset = camera->getPosition();
	realX = realX + offset.x;
	realY = realY + offset.y;
	cout << realX << ',' << realY << endl;
    glm::vec2 playerPos = glm::vec2(player->getPosX(), player->getPosY());
	cout << "player pos :" << playerPos.x << ',' << playerPos.y << endl;
	glm::vec3 bulletStartPosition = player->getPosition() + glm::vec3(10.0f, 20.0f, 0.0f); // Adjust the offset as needed
	if (type == 0) {
		// Create a new bullet and set its direction
		Bullet* newBullet = new Bullet(bulletStartPosition, "../Resource/Texture/bullet3.png",150.f);
		newBullet->SetSize(20.f, 20.f);
		//newBullet->setCollision(false);
		// Shoot the bullet in the calculated direction
		newBullet->shootAt(glm::vec2(realX, realY), newBullet->getVelocity().x);
		objectsList.push_back(newBullet);
		
		//SoundEffect
		soundManager->playSound("Blaster", false);
	}
	else if (type == 1) {
		Grapple* grapple = new Grapple(bulletStartPosition, "../Resource/Texture/temp-grapple.png",75.f);
		grapple->SetSize(20.f, 20.f);
		//grapple->setCollision(false);
		// Shoot the bullet in the calculated direction
		grapple->shootAt(glm::vec2(realX, realY), grapple->getVelocity().x);
		objectsList.push_back(grapple);
		cout << "SUCC" << endl;
	}
	
}