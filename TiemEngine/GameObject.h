#pragma once

#include "DrawableObject.h"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
class GameObject :public DrawableObject
{
protected:
	glm::vec3 color;
	unsigned int texture = -1;
	bool haveCollision = true;

public:
	GameObject();
	~GameObject();
	void SetColor(float r, float g, float b);
	void SetTexture(string path);
	bool getCollision();
	void setCollision(bool have);
	virtual void Render(glm::mat4 globalModelTransform);
	int detectCollisionAABB(float bx, float by, float bh, float bw);
	
};

