#pragma once

#include "GameObject.h"

class AnimatedObject :public GameObject
{
protected:

	int frames = 0;
	int speed = 10;
	int row = 0;
	int col = 0;
	float newUV[8];
	float MaxRow = 0.0f;
	float MaxCol = 0.0f;

public:
	AnimatedObject(const char* path, int MaxR, int MaxC);
	~AnimatedObject();
	virtual void CalculateUV(int r, int c);
	void Render(glm::mat4 globalModelTransform);
	virtual void UpdateFrame();
	int getRow();
	int getCol();
	int getFrames();
	void Update();
	void setSpeed(int newSpeed);
	float* getNewUV();

};
