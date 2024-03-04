
#include "GameEngine.h"
#include "Camera.h"

GameEngine* GameEngine::instance = nullptr;

GameEngine::GameEngine()
{
	renderer = nullptr;
}

GameEngine * GameEngine::GetInstance()
{
	if (instance == nullptr) {
		instance = new GameEngine();
	}
	return instance;
}

GLRenderer * GameEngine::GetRenderer()
{
	return this->renderer;
}

GameStateController* GameEngine::GetStateController()
{
	return this->stateController;
}

void GameEngine::Init(int width, int height)
{
	winWidth = width;
	winHeight = height;
	renderer = new GLRenderer(width, height);
	renderer->InitGL("../Resource/Shader/vertext.shd", "../Resource/Shader/fragment.shd");
	SetDrawArea(0, 1024, 0, 576);
	SetBackgroundColor(1.0f, 1.0f, 200.0f / 255);

	stateController = new GameStateController();
	stateController->Init(GameState::GS_LEVEL1);
	srand(time(nullptr));
}

void GameEngine::Render(vector<DrawableObject*> renderObjects, const glm::mat4& viewMatrix)
{
	this->GetRenderer()->Render(renderObjects, viewMatrix);
}

void GameEngine::RenderTile(vector<Tile*> renderTile, const glm::mat4& viewMatrix)
{
	this->GetRenderer()->RenderTile(renderTile,viewMatrix);
}

void GameEngine::SetDrawArea(float left, float right, float bottom, float top)
{
	widthGame = right;
	heightGame = top;
	renderer->SetOrthoProjection(left, right, bottom, top);
}

void GameEngine::SetBackgroundColor(float r, float g, float b)
{
	renderer->SetClearColor(1.0f, 1.0f, 200.0f / 255);
}

void GameEngine::AddMesh(string name, MeshVbo* mesh)
{
	renderer->AddMesh(name, mesh);
}

void GameEngine::ClearMesh()
{
	renderer->ClearMesh();
}

int GameEngine::GetWindowWidth()
{
	return winWidth;
}

int GameEngine::GetWindowHeight()
{
	return winHeight;
}
int GameEngine::GetGameWidth()
{
	return widthGame;
}

int GameEngine::GetGameHeight()
{
	return heightGame;
}

Bullet* GameEngine::instantiateObject(float width, float height, glm::vec3 velocity, glm::vec3 position) {
	Bullet* bulet = new Bullet;
	bulet->SetPosition(position);
	bulet->SetSize(width, height);
	return bulet;
}