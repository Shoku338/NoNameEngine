#pragma once
#include <GL/glew.h>
#include "GameObject.h"

class GrapleLine :public GameObject {
	
public:
	void Render(glm::mat4 globalModelTransform);
};