#pragma once
#include <GL/glew.h>
#include "GameObject.h"

class Weapon :public GameObject {
public:
	Weapon();
	void update(glm::vec3 Playerpos);
};