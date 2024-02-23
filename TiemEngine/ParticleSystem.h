#pragma once

#include<GL/glew.h>
#include "glm.hpp"
#include <vector>
#include <cstdlib>
#include <ctime>

struct ParticleProp
{
	glm::vec2 Position;
	glm::vec2 Velocity, VelocityVariation;
	glm::vec4 ColorBegin, ColorEnd;
	float SizeBegin, SizeEnd, SizeVariation;
	float LifeTime = 1.0f;
	
};

class ParticleSystem
{
public:
	 ParticleSystem();
	 void Update();
	 void Render();
	 void Emit(const ParticleProp& particleProps,int index);

private:
	float dt = 0.01f;
	struct Particle
	{
		glm::vec2 Position;
		glm::vec2 Velocity;
		glm::vec4 ColorBegin, ColorEnd;
		float SizeBegin, SizeEnd;
		float Rotation = 0.0f;

		float LifeTime = 1.0f;
		float LifeRemaining = 0.0f;

		bool Active = false;
	};
	std::vector<Particle> ParticlePool;
};