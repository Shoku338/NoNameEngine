#pragma once

#include "AnimatedObject.h"
#include "weapon.h"
#include <GL/glew.h>
#include <iostream>

class Explosion :public AnimatedObject {
	bool expired = false;
public:
	Explosion(const char* path, int MaxR, int MaxC, int newSpeed);
	void Update();
	void UpdateFrame();
	bool Expired();

	
};