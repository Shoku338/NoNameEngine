#pragma once

#include<GL/glew.h>
#include "glm.hpp"
#include <vector>

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
	 void OnUpdate();
	 void Render();
	 void Emit(const ParticleProp& particleProps);

private:
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