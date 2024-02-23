#include "Level.h"
#define GRAVITY -1200.0f
#define FRACTION .1f
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

	tilemap = new Tilemap(19, 9, 64, 4, 3, "../Resource/Texture/TileLevel1.png", "../Resource/Texture/map.txt");
	tilemap->setTile(&objectsList);

	Animate = new AnimateMeshVbo();
	Animate->LoadData();
	GameEngine::GetInstance()->AddMesh(AnimateMeshVbo::MESH_NAME, Animate);
	cout << AnimateMeshVbo::MESH_NAME << endl;

	ImageObject* BG = new ImageObject("../Resource/Texture/Desert.jpg");
	BG->SetSize(7520.0f, -1152.0f);
	BG->SetPosition(glm::vec3(3760.0f, 576.0f, 0));
	//BG->SetPosition(glm::vec3(BG->getPosX() / 2, (BG->getPosY() / 2) * -1, 0));
	backGroundObjects.push_back(BG);
		
	//cout << "Load Level" << endl;
}

void Level::LevelInit()
{
	//Tilemap and Enemies
	tilemap->setTile(&objectsList);

	//Camera
	camera = new Camera2D(GameEngine::GetInstance()->GetWindowWidth() , GameEngine::GetInstance()->GetWindowHeight());

	/*GameObject* other = new GameObject();
	other->SetTexture("../Resource/Texture/MOTIVATED.png");
	other->SetSize(128.0f, -128.0f);
	other->SetPosition(glm::vec3(500, 250, 0));
	objectsList.push_back(other);
	other->setCollision(true);*/

	
	//Game object

	Player* ply = new Player("../Resource/Texture/Main_Character_Run.png", 2, 9);

	ply->SetSize(178.0f, -140.0f);
	objectsList.push_back(ply);
	ply->setCollision(false);
	player = ply;
	player->SetPosition(glm::vec3(99.0f, 150.0f, 0.0f));
	player->setWeapon(new ProtoPlasma);


	// Initialize the sound manager and load/play music
	soundManager = new SoundManager();
	soundManager->loadSound("Zelda", "../Resource/Sound/TestZelda.mp3");
	soundManager->loadSound("Blaster", "../Resource/Sound/Blaster.mp3");
	soundManager->playSound("Zelda", true);
	soundManager->getSound("Zelda")->setDefaultVolume(0.3);

	//cout << "Init Level" << endl;
}



void Level::LevelUpdate(float dt)
{
	//cout << "Update Level" << endl;
	
	if (player->getPhysic()) {
		player->Translate(player->velocity * dt);
	}
	
	if (player->velocity.x < 1&& player->velocity.x > -1)
	{
		player->velocity.x = 0;
	}
	else 
	{
		player->velocity.x *= (1.0f - FRACTION); //friction
	}

	//player->Update();
	if (!player->getGrounded()) {
		//cout << "add grav" << endl;
		if(player->velocity.y >= -1000)
			player->velocity.y += GRAVITY * dt; //Gravity
	}

	// Update camera position with an offset
	float halfScreenWidth = GameEngine::GetInstance()->GetWindowWidth() / 2.0f;
	float levelMinX = 0.0f; // Assuming the level starts at X=0
	float levelMaxX = tilemap->getWidth() * tilemap->getTileSize();

	if (camera && player) {

		glm::vec2 playerPosition(player->getPosX(), player->getPosY());

		//std::cout<<"Player Position: (" << playerPosition.x << ", " << playerPosition.y << ")" << std::endl;

		// Example: Set an offset to move the player to the left and lower the camera
		//
		glm::vec2 offset(-50.0f, -100.0f); // Adjust the x and y coordinates as needed
		camera->UpdateCameraPosition(playerPosition, player->facingRight(),dt, levelMinX, levelMaxX);


		// Print camera position (optional for debugging)
		glm::vec2 cameraPosition = camera->getPosition();
		//camera->MoveRight(100.0f);
		//std::cout << "Camera Position: (" << cameraPosition.x << ", " << cameraPosition.y << ")" << std::endl;
	}


	for (int i = 0; i < tilemap->getTilemap().size(); i++)
	{
		GameObject* gameObject = dynamic_cast<GameObject*>(tilemap->getTilemap().at(i));
		if (gameObject) {
			if (gameObject->getCollision()) {
				int resultCol = player->detectCollisionAABB(gameObject->getPosX(), gameObject->getPosY(), abs(gameObject->getsizeY()), gameObject->getsizeX(), dt);
				if (resultCol == COLLISION_BOTTOM)
				{
					//game logic here
					player->setJump(0);
					player->velocity.y = 0;
					player->setGround(true);
					float offsetY = (gameObject->getPosition().y + abs(gameObject->getsizeY() / 2)) - (player->getPosition().y - abs(player->getsizeY() / 2));
					player->Translate(glm::vec3(0.0f, offsetY, 0.0f));
				}
				else if (resultCol == COLLISION_RIGHT) {
					// Game logic for collision on the right of player
					float offsetX = (gameObject->getPosition().x - abs(gameObject->getsizeX() / 2)) - (player->getPosition().x + abs(player->getsizeX() / 2));
					player->Translate(glm::vec3(offsetX, 0, 0));
					player->velocity.x = 0;
				}
				else if (resultCol == COLLISION_LEFT) {
					// Game logic for collision on the left of player
					float offsetX = (gameObject->getPosition().x + abs(gameObject->getsizeX() / 2)) - (player->getPosition().x - abs(player->getsizeX() / 2));
					player->Translate(glm::vec3(offsetX, 0, 0));
					player->velocity.x = 0;
				}
				else if (resultCol == COLLISION_TOP) {
					// Game logic for collision at the Top of player
					float offsetY = (gameObject->getPosition().y - abs(gameObject->getsizeY() / 2)) - (player->getPosition().y + abs(player->getsizeY() / 2));
					player->Translate(glm::vec3(0.0f, offsetY, 0.0f));
					player->velocity.y -= 100;
				}
				else
				{
					player->setGround(false);
				}
			}
		}
	}
	for (auto it = objectsList.begin(); it != objectsList.end();) {
		if (Bullet* bullet = dynamic_cast<Bullet*>(*it)) {
			bullet->update(dt);
			bool removeBullet = false;
			if (Grapple* grapple = dynamic_cast<Grapple*>(bullet)) {
				// Check for collision with other GameObjects
				for (auto otherIt = objectsList.begin(); otherIt != objectsList.end();)
				{
					if (GameObject* gameObject2 = dynamic_cast<GameObject*>(*otherIt)) {
						if (gameObject2->getCollision()) {
							int colG = grapple->detectCollisionAABB(
								gameObject2->getPosX(), gameObject2->getPosY(),
								abs(gameObject2->getsizeY()), gameObject2->getsizeX(), dt);
							//cout << "colresult:" << colG << endl;
							if (colG) {
								// Collision detected, execute pull function
								//cout << "boop" << endl;
								grapple->velocity = glm::vec3(0, 0, 0);
								grapple->pull(*player, dt * 2, 150);
								// Handle other logic if needed
							}
						}
					}
					++otherIt;
				}
				for (int i = 0; i < tilemap->getTilemap().size(); i++)
				{
					GameObject* otherIt = dynamic_cast<GameObject*>(tilemap->getTilemap().at(i));
					if (GameObject* gameObject2 = dynamic_cast<GameObject*>(otherIt)) {
						if (gameObject2->getCollision()) {
							int colG = grapple->detectCollisionAABB(
								gameObject2->getPosX(), gameObject2->getPosY(),
								abs(gameObject2->getsizeY()), gameObject2->getsizeX(), dt);

							if (colG) {

								// Collision detected, execute pull function

								grapple->velocity = glm::vec3(0, 0, 0);
								grapple->pull(*player, dt * 2, 150);
								// Handle other logic if needed
							}
						}
					}
					++otherIt;
				}
				
			}
			else {
				for (auto otherIt = objectsList.begin(); otherIt != objectsList.end();) {
					if (Enemy* collidingObject = dynamic_cast<Enemy*>(*otherIt)) {
						int colB = bullet->detectCollisionAABB(
							collidingObject->getPosX(), collidingObject->getPosY(),
							abs(collidingObject->getsizeY()), collidingObject->getsizeX(), dt);
						if (colB) {
							//check if the bulet is a grapple
							collidingObject->applyDamage(1);
							cout << "SUPER AMAZING EXPLOSION IS HAPPENING RN" << endl;
							removeBullet = true;//mark to be destroy
						}
					}
					++otherIt;
				}
			}
			
			if (bullet->timesUp() || removeBullet) {
				it = objectsList.erase(it);
				continue;  // Skip the rest of the loop for this iteration
			}
			
		}
		if (Grapple* grapple = dynamic_cast<Grapple*>(*it)) {
			
		}
		else {
			player->setPhysic(true);
		}
		 if (GameObject* gameObject = dynamic_cast<GameObject*>(*it)) {
			//gameObject->Translate(gameObject->velocity);
			 if(gameObject->getCollision()){
				 int resultCol = player->detectCollisionAABB(
					 gameObject->getPosX(), gameObject->getPosY(),
					 abs(gameObject->getsizeY()), gameObject->getsizeX(), dt);
				 if (resultCol == COLLISION_BOTTOM) {
					 //game logic here
					 player->setJump(0);
					 player->velocity.y = 0;
					 player->setGround(true);
					 float offsetY = (gameObject->getPosition().y + abs(gameObject->getsizeY() / 2)) - (player->getPosition().y - abs(player->getsizeY() / 2));
					 //cout << offsetY << endl;
					 player->Translate(glm::vec3(0.0f, offsetY, 0.0f));

				 }
				 else if (resultCol == COLLISION_RIGHT) {
					 // Game logic for collision on the right of player
					 float offsetX = (gameObject->getPosition().x - abs(gameObject->getsizeX() / 2)) - (player->getPosition().x + abs(player->getsizeX() / 2));
					 player->Translate(glm::vec3(offsetX, 0, 0));
					 player->velocity.x = 0;
				 }
				 else if (resultCol == COLLISION_LEFT) {
					 // Game logic for collision on the left of player
					 float offsetX = (gameObject->getPosition().x + abs(gameObject->getsizeX() / 2)) - (player->getPosition().x - abs(player->getsizeX() / 2));
					 player->Translate(glm::vec3(offsetX, 0, 0));
					 player->velocity.x = 0;
				 }
				 else if (resultCol == COLLISION_TOP) {
					 // Game logic for collision at the Top of player
					 player->Translate(glm::vec3(0, -0.5, 0));
					 player->velocity.y = 0;
				 }
				 else
				 {
					 player->setGround(false);
				 }
			 }

				// Additional collision handling logic can be added here
			
		 }
		++it;  // Increment the iterator for the next iteration
	}



	// Update Animation and Death
	for (DrawableObject* object : objectsList)
	{
		if (Enemy* enemy = dynamic_cast<Enemy*>(object)) {
			if (enemy->handleDeath()) {
				
				Explosion* deathExplosion = new Explosion("../Resource/Texture/explosion.png",5,5,1);
				deathExplosion->SetPosition(object->getPosition());
				objectsList.push_back(deathExplosion);
				objectsList.erase(std::remove(objectsList.begin(), objectsList.end(), object), objectsList.end());
				delete object; // Assuming you need to delete the object from memory
				

			}
			else
			{
				object->Update();
			}
		}
		else if(Explosion* explosion = dynamic_cast<Explosion*>(object))
		{
			if (explosion->Expired()) {

				objectsList.erase(std::remove(objectsList.begin(), objectsList.end(), object), objectsList.end());
				delete object; // Assuming you need to delete the object from memory


			}
			else
			{
				object->Update();
			}
		}
		else 
		{
			object->Update();
		}
		
	}
}

void Level::LevelDraw()
{

	//SetViewMatrix
	glm::mat4 viewMatrix = camera->GetViewMatrix();

	//Clear Buffer
	ClearBuffer();

	//Background
	GameEngine::GetInstance()->Render(backGroundObjects, viewMatrix);

	//Tilemap
	GameEngine::GetInstance()->RenderTile(tilemap->getTilemap(), viewMatrix);
	
	
	//Object and Camera
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

	/*for (Tile* tiles : tilemap->getTilemap()) {
		delete tiles;
	}
	tilemap->getTilemap().clear();*/

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
			player->setGround(false);
			if (player->getJump() < MAXX_JUMP) {
			//cout << "Rising hopper" << endl;
				player->velocity.y = 500.0f; //[Editable] Jump velo
				player->setJump(player->getJump() + 1);
			}
			for (auto it = objectsList.begin(); it != objectsList.end(); ++it) {
				if (Grapple* grapple = dynamic_cast<Grapple*>(*it)) {
					// Remove the grapple from the objects list
					delete grapple; // Delete the grapple object
					objectsList.erase(it);
					break; // Exit the loop after removing the grapple
				}
			}
			player->setPhysic(true);
			break; // jumping
		case 'a': //move right
			if(player->getVelocity().x <= 120)
			{
				player->velocity.x += -25.f; //[Editable] walk speed left
			}
			break;//move velocity value
		case 'd': // move left
			if (player->getVelocity().x >= -120)
			{
				player->velocity.x += 25.f; //[Editable] walk speed right
			}
			break;//move velocity value
		case 'C'://dashing

			if (player->velocity.x < 0)
				player->velocity.x -= 5500.f; //[Editable] Dash left
			else if(player->velocity.x >= 0)
				player->velocity.x += 5500.f; //[Editable] Dash right
			break;
			//need spacebar		
		case 'q': GameEngine::GetInstance()->GetStateController()->gameStateNext = GameState::GS_QUIT; ; break;
		case 'r': GameEngine::GetInstance()->GetStateController()->gameStateNext = GameState::GS_RESTART; ; break;
		//case 'e': GameEngine::GetInstance()->GetStateController()->gameStateNext = GameState::GS_LEVEL2; ;
			break;
		case '1': player->setWeapon(new ProtoPlasma); break;
		case '2': player->setWeapon(new RapidMachineGun); break;
		
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
	realX = (x) / (w / wg);
	realY = hg - (y / (h / hg));
	glm::vec2 offset = camera->getPosition();
	realX = realX + offset.x;
	realY = realY + offset.y;	
	cout << realX << ',' << realY << endl;
	glm::vec2 playerPos = glm::vec2(player->getPosition().x, player->getPosition().y);
	glm::vec3 bulletStartPosition = player->getPosition() + glm::vec3(10.0f, 20.0f, 0.0f); // Adjust the offset as needed
	if (type == 0) {
		player->getWeapon()->Fire(glm::vec2(realX, realY), objectsList, soundManager);
	}
	else if (type == 1) {
		bool grappleExists = false;

		// Check if any Grapple objects exist in objectsList
		for (auto it = objectsList.begin(); it != objectsList.end(); ++it) {
			if (dynamic_cast<Grapple*>(*it) != nullptr) {
				// A Grapple object already exists
				grappleExists = true;
				break;
			}
		}

		// If no Grapple object exists, add a new one
		if (!grappleExists) {
			Grapple* grapple = new Grapple(bulletStartPosition, "../Resource/Texture/Hook.png", 700.f);
			grapple->SetSize(20.f, 20.f);
			grapple->shootAt(glm::vec2(realX, realY), grapple->getVelocity().x);
			objectsList.push_back(grapple);
		}

	}
}
void Level::ArmToMouse(int x, int y) {
	float realX, realY;

	// Calculate Real X Y 
	float h = GameEngine::GetInstance()->GetWindowHeight();
	float w = GameEngine::GetInstance()->GetWindowWidth();
	float hg = GameEngine::GetInstance()->GetGameHeight();
	float wg = GameEngine::GetInstance()->GetGameWidth();

	realX = (x) / (w / wg);
	realY = hg - (y / (h / hg));
	glm::vec2 offset = camera->getPosition();
	realX = realX + offset.x;
	realY = realY + offset.y;
	//cout << "mouse x,y " << realX << ',' << realY << endl;
	glm::vec2 direction = glm::normalize(glm::vec2(realX, realY) - glm::vec2(player->getPosX(), player->getPosY()));
	float degree = glm::degrees(atan2(direction.y, direction.x));
	//cout << "rotate by " << degree << endl;
	if (degree < 90 && degree >= -90) {
		player->setFaceRight(true);
		player->checkFace();
		player->getWeapon()->rotateDegree(degree);
		//cout << "degree:" << degree << endl;
	}
	else {
		player->setFaceRight(false);
		player->checkFace();
		player->getWeapon()->rotateDegree(degree - 180);
		//cout << "degree:" << degree << endl;
	}
}

void Level::ClearBuffer()
{
	// Clear color buffer and depth buffer once per frame
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}