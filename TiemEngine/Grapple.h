#pragma once
#include <GL/glew.h>
#include "Bullet.h"
#include "Player.h"
#include "GameObject.h"
#include "GrappleLine.h"

class Grapple :public Bullet {
	GrapleLine Granline;
public:
	Grapple(glm::vec3 startPosition, const string texture, float speed);
	//virtual void update(Player& player,float dt);
	void pull(Player& player, float dt, float speed);
	void Render(glm::mat4 globalModelTransform);
}; 
