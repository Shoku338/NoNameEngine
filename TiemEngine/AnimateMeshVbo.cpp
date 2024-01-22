
#include "AnimateMeshVbo.h"
#include <iostream>

string const AnimateMeshVbo::MESH_NAME = "AnimateSquare";

AnimateMeshVbo::AnimateMeshVbo()
{
	cout << endl << "new Animated Mesh" << endl;
}

void AnimateMeshVbo::UpdateUV(float* newUV)
{


	GLfloat texData[] =
	{
		newUV[2],newUV[3],
	   newUV[0],newUV[1],
		newUV[6],newUV[7],
	  newUV[4],newUV[5]

	  

	};


	//UpdateVbo

	glGenBuffers(1, &(this->texVboId));
	glBindBuffer(GL_ARRAY_BUFFER, this->texVboId);
	glBufferData(GL_ARRAY_BUFFER, 2 * 4 * sizeof(GLfloat), texData, GL_STATIC_DRAW);


}