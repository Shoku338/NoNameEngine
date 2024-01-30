#pragma once
#include <GL/glew.h>
#include "GameObject.h"

class GrapleLine :public GameObject {
	
public:
	GrapleLine(glm::vec3 startPos);
	void Render(glm::mat4 globalModelTransform);
	void updateCurrent(glm::vec3 playerPos, glm::vec3 headPos);
};