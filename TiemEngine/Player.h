#pragma once

#include "GameObject.h"

class Player :public GameObject {
	float health;
	float shield;
public:
	float getHealth();
	float getShield();
};

