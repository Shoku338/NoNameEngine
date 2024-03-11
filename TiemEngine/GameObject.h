#pragma once

#include "DrawableObject.h"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

class GameObject :public DrawableObject
{
protected:
	glm::vec3 color;
	unsigned int texture = -1;
	bool haveCollision = false;
	float collisionModifierX = 1.0f;
	float collisionModifierY = 1.0f;

public:
	GameObject();
	GameObject(string Path);
	~GameObject();
	void flip();
	void SetColor(float r, float g, float b);
	void SetTexture(string path);
	bool getCollision();
	void setCollision(bool have);
	void Update();
	virtual void Render(glm::mat4 globalModelTransform);
	virtual int detectCollisionAABB(float bx, float by, float bh, float bw,float dt);
	void SmoothTranslate(const glm::vec3& targetPosition, float deltaTime, float speed);
	virtual float getCollisionX();
	virtual float getCollisionY();
	
	
};


