#pragma once

#include<GL/glew.h>
#include "glm.hpp"
#include <vector>
#include <cstdlib>
#include <ctime>
#include <random>
#include "AnimatedObject.h"

struct ParticleProp
{
	glm::vec2 Position;
	glm::vec2 Velocity, VelocityVariation;
	glm::vec4 ColorBegin, ColorEnd;
	float SizeBegin, SizeEnd, SizeVariation;
	float LifeTime = 1.0f;
	
};

class ParticleSystem: public AnimatedObject
{
public:
	 ParticleSystem();
	 void Update();
	 void Render(glm::mat4 globalModelTransform);
	 void Emit(const ParticleProp& particleProps);
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
	uint32_t m_PoolIndex = 999;
};