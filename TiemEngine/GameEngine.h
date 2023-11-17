#pragma once

#include <vector>
#include "DrawableObject.h"
#include "GLRenderer.h"
#include "GameStateController.h"
#include "Tile.h"

using namespace std;
class GameEngine
{
	static GameEngine* instance;
	int winWidth, winHeight;
	int widthGame, heightGame;
	
	GLRenderer *renderer;
	GameStateController* stateController;
	GameEngine();
public:
	static GameEngine* GetInstance();
	GLRenderer * GetRenderer();
	GameStateController* GetStateController();
	void Init(int width, int height);
	void SetDrawArea(float left, float right, float bottom, float top);
	void SetBackgroundColor(float r, float g, float b);
	void AddMesh(string name, MeshVbo* mesh);
	void ClearMesh();
	void Render(vector<DrawableObject*> renderObjects);
	void RenderTile(vector<Tile*> renderTile);
	int GetWindowWidth();
	int GetWindowHeight();
	int GetGameWidth();
	int GetGameHeight();
};