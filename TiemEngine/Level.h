#pragma once
#include "GameEngine.h"
#include "SquareMeshVbo.h"
#include "GameObject.h"
#include "ImageObject.h"

class Level
{
private:
	vector<DrawableObject*> objectsList;
	ImageObject * player;
	float realLeftWall = ((-GameEngine::GetInstance()->GetWindowWidth() / 2) / 100.0f);

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
