#pragma once

#include "SquareMeshVbo.h"

class AnimateMeshVbo : public SquareMeshVbo {
protected:

public:
	static string const MESH_NAME;
	AnimateMeshVbo();
	void UpdateUV(float* newUV);
};