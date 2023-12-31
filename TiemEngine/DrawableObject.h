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
	glm::vec3 rotation;

public:
	glm::mat4 getTransform();
	glm::vec3 velocity = glm::vec3(0, 0, 0);
	DrawableObject();
	~DrawableObject();
	virtual void Render(glm::mat4 globalModelTransform) = 0;
	void SetSize(float sizeX, float sizeY);
	void SetPosition(glm::vec3 newPosition);
	void Translate(glm::vec3 moveDistance);
	float getPosX();
	float getPosY();
	float getsizeX();
	float getsizeY();
	glm::mat4 rotateDegree(float degree);
	//Rotate, Scale ???
	//add rotate

};

