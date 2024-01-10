#pragma once
#include <GL/glew.h>
#include "GameObject.h"

class Weapon :public GameObject {
	
public:
	Weapon(const std::string& texturePath);
	void update(float dt);
};