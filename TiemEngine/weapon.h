#pragma once
#include <GL/glew.h>
#include "GameObject.h"
#include "SoundManager.h"
#include "Bullet.h"
#include "ParticleData.h"
#include "ParticleSystem.h"

class Weapon :public GameObject {
public:
	enum shootingType {
		normal = 0,
		burst = 1,
		charge = 2,
	};
	Weapon();
	Weapon(int type);
	virtual void update(glm::vec3 Playerpos);
	virtual void Fire(glm::vec2 targetPosition, vector<DrawableObject*>& objectsList, SoundManager* soundManager,ParticleSystem* ps);
private:
	glm::vec3 barrelPos;
	bool isBurstFiring = false;
	int burstBulletCount = 0;
	float burstCooldownTimer = 0.5f;
	int fireType = 0;
	bool canShoot = true;
	float cdTimer = 0.5f;
};
