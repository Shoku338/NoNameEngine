#include "ParticleSystem.h"
#include "GameEngine.h"
#include "AnimateMeshVbo.h"
#include "gtx/compatibility.hpp"


ParticleSystem::ParticleSystem():AnimatedObject()
{
	ParticlePool.resize(1000);
	//CurrentShape = Basic;
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

void ParticleSystem::Emit(const ParticleProp& particleProps,ParticleShape shape)
{
	Particle& particle = ParticlePool[m_PoolIndex];
	particle.Active = true;
	particle.Position = particleProps.Position;
	particle.Rotation = static_cast<float>(std::rand()) / RAND_MAX * 2.0f * 3.14f;

	//Velocity
	
	switch (shape) {
	case ParticleShape::Basic:
		particle.Velocity = particleProps.Velocity;
		particle.Velocity.x += particleProps.VelocityVariation.x * (static_cast<float>(std::rand()) / RAND_MAX - 0.5f);
		particle.Velocity.y += particleProps.VelocityVariation.y * (static_cast<float>(std::rand()) / RAND_MAX - 0.5f);
		
	case ParticleShape::Circle:
	{
		// Generate random angle for velocity direction
		float angle = static_cast<float>(std::rand()) / RAND_MAX * 2.0f * glm::pi<float>();
		particle.Velocity = glm::vec2(std::cos(angle), std::sin(angle)) * glm::length(particleProps.Velocity);
	
	}
	break;
	case ParticleShape::Boom:
	{

		// Generate random angle for velocity direction
		float angle = static_cast<float>(std::rand()) / RAND_MAX * 2.0f * glm::pi<float>();

		// Apply velocity variation
		float speed = glm::length(particleProps.Velocity);
		float minAdjustedSpeed = speed - particleProps.VelocityVariation.x; // Minimum adjusted speed
		float maxAdjustedSpeed = speed + particleProps.VelocityVariation.x; // Maximum adjusted speed
		float adjustedSpeed = minAdjustedSpeed + (maxAdjustedSpeed - minAdjustedSpeed) * (static_cast<float>(std::rand()) / RAND_MAX);
		adjustedSpeed = std::max(0.0f, adjustedSpeed); // Ensure adjusted speed is not negative

		// Calculate velocity with adjusted speed
		particle.Velocity = glm::vec2(std::cos(angle), std::sin(angle)) * adjustedSpeed;
		break;
	}
	break;
	case ParticleShape::Cone:
	{
		// Generate random angle within cone angle
		float coneAngle = glm::radians(30.0f); // Example cone angle (30 degrees)
		float angle = static_cast<float>(std::rand()) / RAND_MAX * coneAngle - coneAngle / 2.0f;
		glm::vec2 direction = glm::normalize(particleProps.Velocity);
		// Rotate direction vector by random angle
		glm::vec2 rotatedDirection = glm::vec2(std::cos(angle) * direction.x - std::sin(angle) * direction.y,
			std::sin(angle) * direction.x + std::cos(angle) * direction.y);

		// Introduce velocity variation
		glm::vec2 velocityVariation = particleProps.VelocityVariation;
		glm::vec2 randomVariation = glm::vec2((static_cast<float>(std::rand()) / RAND_MAX - 0.5f),
			(static_cast<float>(std::rand()) / RAND_MAX - 0.5f));
		glm::vec2 finalVelocity = rotatedDirection * glm::length(particleProps.Velocity);

		// Adjust random variation to stay within cone boundaries and maintain direction
		float coneBoundaryFactor = glm::dot(finalVelocity, particleProps.Velocity) / (glm::length(finalVelocity) * glm::length(particleProps.Velocity));
		randomVariation *= coneBoundaryFactor;
		if (glm::dot(finalVelocity, particleProps.Velocity) < 0)
			randomVariation = -randomVariation;

		// Apply velocity variation
		finalVelocity += velocityVariation * randomVariation;

		particle.Velocity = finalVelocity;
	}
	break;
	}


	//Color
	particle.ColorBegin = particleProps.ColorBegin;
	particle.ColorEnd = particleProps.ColorEnd;

	particle.LifeTime = particleProps.LifeTime;
	particle.LifeRemaining = particleProps.LifeTime;
	particle.SizeBegin = particleProps.SizeBegin + particleProps.SizeVariation * (static_cast<float>(std::rand()) / RAND_MAX - 0.5f);
	particle.SizeEnd = particleProps.SizeEnd;

	m_PoolIndex = --m_PoolIndex % ParticlePool.size();

}

void ParticleSystem::Render(glm::mat4 globalModelTransform)
{
	AnimateMeshVbo* spriteMesh = dynamic_cast<AnimateMeshVbo*> (GameEngine::GetInstance()->GetRenderer()->GetMesh(AnimateMeshVbo::MESH_NAME));

	GLuint modelMatixId = GameEngine::GetInstance()->GetRenderer()->GetModelMatrixAttrId();
	GLuint colorId = GameEngine::GetInstance()->GetRenderer()->GetColorUniformId();
	GLuint renderModeId = GameEngine::GetInstance()->GetRenderer()->GetModeUniformId();

	if (modelMatixId == -1) {
		cout << "Error: Can't perform transformation " << endl;
		return;
	}
	if (colorId == -1) {
		cout << "Error: Can't set color " << endl;
		return;
	}
	if (renderModeId == -1) {
		cout << "Error: Can't set renderMode in ImageObject " << endl;
		return;
	}
	vector <glm::mat4> matrixStack;
	if (spriteMesh != nullptr) {

		for (auto& particle : ParticlePool)
		{
			if (!particle.Active)
				continue;

			// Fade away particles
			float life = particle.LifeRemaining / particle.LifeTime;
			glm::vec4 color = glm::lerp(particle.ColorEnd, particle.ColorBegin, life);
			//color.a = color.a * life;

			float size = glm::lerp(particle.SizeEnd, particle.SizeBegin, life);

			// Render
			glm::mat4 currentMatrix = glm::translate(glm::mat4(1.0f), { particle.Position.x, particle.Position.y, 0.0f })
				* glm::rotate(glm::mat4(1.0f), particle.Rotation, { 0.0f, 0.0f, 1.0f })
				* glm::scale(glm::mat4(1.0f), { size, size, 1.0f });
			currentMatrix = globalModelTransform * currentMatrix;
			glUniformMatrix4fv(modelMatixId, 1, GL_FALSE, glm::value_ptr(currentMatrix));
			glUniform3f(colorId, color.x, color.y, color.z);
			glUniform1i(renderModeId, 0);
			glBindTexture(GL_TEXTURE_2D, texture);
			spriteMesh->UpdateUV(newUV);
			spriteMesh->Render();
		}

	}

	
}