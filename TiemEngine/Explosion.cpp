#include "Explosion.h"

Explosion::Explosion(const char* path, int MaxR, int MaxC, int newSpeed):AnimatedObject(path,MaxR,MaxC)
{
	speed = newSpeed;
}

void Explosion::Update()
{
	UpdateFrame();
}

void Explosion::UpdateFrame()
{
	frames++;

	if (frames > speed) {
		frames = 0;

		if (col >= MaxCol - 1) {
			col = 0;
			row++;

			if (row >= MaxRow - 1) {
				row = 0;
				expired = true;
			}
		}
		else {
			col++;
		}

		CalculateUV(row, col);
		//cout << "Row: " << row << ", Col: " << col << endl;
	}
}

bool Explosion::Expired()
{
	if (expired)
	{
		return true;
	}

	return false;
}