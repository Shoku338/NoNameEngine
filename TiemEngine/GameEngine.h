#pragma once

#include <vector>
#include "DrawableObject.h"
#include "GLRenderer.h"
#include "GameStateController.h"
#include "Bullet.h"
#include "Tile.h"
#include "glm.hpp"
#include "irrKlang.h"

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
	void Render(vector<DrawableObject*> renderObjects, const glm::mat4& viewMatrix);
	void RenderTile(vector<Tile*> renderTile,const glm::mat4& viewMatrix);
	int GetWindowWidth();
	int GetWindowHeight();
	int GetGameWidth();
	int GetGameHeight();
	Bullet* instantiateObject(float width, float height, glm::vec3 velocity, glm::vec3 position);

};