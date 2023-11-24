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
	glm::vec3 velocity;
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
	void rotate(int degree);
	//Rotate, Scale ???
	//add rotate

};

