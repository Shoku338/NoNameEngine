#pragma once
#include "GameEngine.h"
#include "SquareMeshVbo.h"
#include "GameObject.h"
#include "ImageObject.h"
#include "Player.h"
#include "Bullet.h"
#include "Camera.h"
#include "Grapple.h"
#include "GrappleLine.h"

//Added by Kapom
#include "Tile.h"
#include "Tilemap.h"
#include "SoundManager.h"
#include "AnimatedObject.h"
#include "AnimateMeshVbo.h"

class Level
{
private:
	vector<DrawableObject*> objectsList;
	Player * player;
	float overlapX, overlapY;
	Tilemap * tilemap;
	Camera2D* camera;
	SoundManager* soundManager;

	AnimatedObject* TestA;
	AnimatedObject* TestB;
	AnimateMeshVbo* Animate;
	vector<DrawableObject*> backGroundObjects;

public:
	virtual void LevelLoad();
	virtual void LevelInit();
	virtual void LevelUpdate(float dt);
	virtual void LevelDraw();
	virtual void LevelFree();
	virtual void LevelUnload();

	virtual void HandleKey(char key);
	virtual void HandleMouse(int type, int x, int y);
	virtual void ArmToMouse(int x, int y);
	void ClearBuffer();
};
