#pragma once
#include <GL/glew.h>
#include "GameObject.h"
#include "SoundManager.h"
#include "Bullet.h"

class Weapon :public GameObject {
public:
	virtual void update(glm::vec3 Playerpos);
	virtual void Fire(glm::vec2 targetPosition, vector<DrawableObject*>& objectsList, SoundManager* soundManager);
};
