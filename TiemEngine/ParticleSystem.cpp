#include "ParticleSystem.h"

ParticleSystem::ParticleSystem()
{
	ParticlePool.resize(1000);
}

void ParticleSystem::Update()
{
	for (auto& particle : ParticlePool )
	{
		if (!particle.Active) 
		{
			continue;
		}

		if (particle.LifeRemaining <= 0.0f)
		{
			particle.Active = false;
			continue;
		}
		
		particle.LifeRemaining -= dt;
		particle.Position += particle.Velocity * dt;
		particle.Rotation += 0.01f * dt;
	}
}

void ParticleSystem::Emit(const ParticleProp& particleProps,int index)
{
	Particle& particle = ParticlePool[index];
	particle.Active = true;
	particle.Position = particleProps.Position;
	//particle.Rotation =
	
	//Velocity

	//Color
	particle.ColorBegin = particleProps.ColorBegin;
	particle.ColorEnd = particleProps.ColorEnd;

	particle.LifeTime = particleProps.LifeTime;
	particle.LifeRemaining = particleProps.LifeTime;
	particle.SizeBegin = particleProps.SizeBegin + particleProps.SizeVariation;
	particle.SizeEnd = particleProps.SizeEnd;
}

void ParticleSystem::Render()
{
	
}