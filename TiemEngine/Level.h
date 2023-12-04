#pragma once
#include "GameEngine.h"
#include "SquareMeshVbo.h"
#include "GameObject.h"
#include "ImageObject.h"
#include "Tile.h"
#include "Tilemap.h"
#include "Player.h"
#include "Bullet.h"
#include "Camera.h"


class Level
{
private:
	vector<DrawableObject*> objectsList;
	Player * player;
	float overlapX, overlapY;
	Tilemap * tilemap;
	Camera2D* camera;

public:
	virtual void LevelLoad();
	virtual void LevelInit();
	virtual void LevelUpdate(float dt);
	virtual void LevelDraw();
	virtual void LevelFree();
	virtual void LevelUnload();

	virtual void HandleKey(char key);
	virtual void HandleMouse(int type, int x, int y);
};
