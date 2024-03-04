#pragma once
#include "glm.hpp"
#include <vector>
#include <string>

using namespace std;

class DrawableObject
{
protected:
	
	glm::vec3 pos;
	glm::vec3 size;
	float degree;
public:
	virtual glm::mat4 getTransform();
	glm::vec3 velocity = glm::vec3(0, 0, 0);
	DrawableObject();
	~DrawableObject();
	virtual void Render(glm::mat4 globalModelTransform) = 0;
	void SetSize(float sizeX, float sizeY);
	void SetPosition(glm::vec3 newPosition);
	void Translate(glm::vec3 moveDistance);
	float getPosX();
	glm::vec3 getPosition();
	glm::vec3 getVelocity();
	float getPosY();
	float getsizeX();
	float getsizeY();
	void rotateDegree(float degree);
	virtual void Update();
	//Rotate, Scale ???
	//add rotate

};

