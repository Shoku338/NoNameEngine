#pragma once
#include <GL/glew.h>
#include "GameObject.h"

class Bullet:public GameObject {
	float timer = 0.f;
	float TimeTD = 2.f;
public:	
	//Bullet(float width,float height,glm::vec3 velocity,glm::vec3 position);
	Bullet();
	void update(float dt);
	bool timesUp();
};