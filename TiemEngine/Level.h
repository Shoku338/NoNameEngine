#pragma once
#include "GameEngine.h"
#include "SquareMeshVbo.h"
#include "GameObject.h"
#include "ImageObject.h"
#include "Tile.h"
#include "Tilemap.h"

class Level
{
private:
	vector<DrawableObject*> objectsList;
	vector<Tile*> TileList;
	GameObject * player;
	float overlapX, overlapY;

public:
	int _detectCollisionAABB(float ax, float ay, float ah, float aw, float bx, float by, float bh, float bw);
	virtual void LevelLoad();
	virtual void LevelInit();
	virtual void LevelUpdate(float dt);
	virtual void LevelDraw();
	virtual void LevelFree();
	virtual void LevelUnload();

	virtual void HandleKey(char key);
	virtual void HandleMouse(int type, int x, int y);
};
