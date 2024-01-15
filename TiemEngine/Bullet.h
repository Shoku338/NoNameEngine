#pragma once
#include <GL/glew.h>
#include "GameObject.h"

class Bullet:public GameObject {
	float timer = 0.f;
	float TimeTD = 2.f;
	glm::vec3 startPosition;
public:	
	//Bullet(float width,float height,glm::vec3 velocity,glm::vec3 position);
	Bullet();
	Bullet(glm::vec3 startPosition,const string texture, float speed);
	void update(float dt);
	void shootAt(glm::vec2 targetMousePos, float speed);
	bool timesUp();
	void setTimer(float time);
};