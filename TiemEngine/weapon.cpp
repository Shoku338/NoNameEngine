#include "weapon.h"

Weapon::Weapon()
{
    canShoot = true;
    cdTimer = 0.5f;
    fireType = 0;
}

Weapon::Weapon(int type)
{
    canShoot = true;
    cdTimer = 0.5f;
    fireType = type;
}

void Weapon::update(glm::vec3 Playerpos) {
    this->pos = Playerpos;
    //cout << "cooldown " << cdTimer << ", shoot" << canShoot << ", type " << fireType << endl;
    if (cdTimer > 0 && !canShoot) {
        cdTimer -= 0.01;
    }
    else
    {
        canShoot = true;
        cdTimer = 0.5f; // Reset cdTimer to its initial value
    }
}

void Weapon::Fire(glm::vec2 targetPosition, vector<DrawableObject*>& objectsList, SoundManager* soundManager,ParticleSystem* ps) {
    if (canShoot) {
        glm::vec3 weaponPos = getPosition();
        glm::vec3 barrelOffset = { 45.0f, 25.0f, 0.0f };
        float rotationRadians = glm::radians(this->getDegree());
        float cosTheta = cos(rotationRadians);
        float sinTheta = sin(rotationRadians);
        glm::vec3 rotatedOffset = {
            barrelOffset.x * cosTheta - barrelOffset.y * sinTheta,
            barrelOffset.x * sinTheta + barrelOffset.y * cosTheta,
            0.0f
        };
        barrelPos = weaponPos + rotatedOffset;
        glm::vec3 bulletStartPosition = barrelPos; // Adjust the offset as needed
        if (fireType == normal) {
            Bullet* newBullet = new Bullet(bulletStartPosition, "../Resource/Texture/bullet3.png", 150.f);
            newBullet->SetSize(20.f, 20.f);
            newBullet->shootAt(targetPosition, newBullet->getVelocity().x);
            objectsList.push_back(newBullet);
        }
        else if (fireType == burst) {
            if (!isBurstFiring && burstBulletCount == 0) {
                isBurstFiring = true;
                // Reset the burst firing cooldown timer
                burstCooldownTimer = 0.1f;
            }
            if (isBurstFiring) {
                if (burstBulletCount < 3 && burstCooldownTimer <= 0) {
                    Bullet* newBullet = new Bullet(bulletStartPosition, "../Resource/Texture/bullet3.png", 150.f);
                    newBullet->SetSize(20.f, 20.f);
                    newBullet->shootAt(targetPosition, newBullet->getVelocity().x);
                    objectsList.push_back(newBullet);
                    burstBulletCount++;
                    // Reset the cooldown timer for the next bullet
                    burstCooldownTimer = 0.1f;
                }
                // Update the cooldown timer
                burstCooldownTimer -= 0.1;
                if (burstBulletCount >= 3) {
                    // Reset burst firing state after firing three bullets
                    isBurstFiring = false;
                    burstBulletCount = 0;
                }
            }
        }
        
        // SoundEffect
        soundManager->playSound("Blaster", false);

        //Particle Effects
        ParticleProp m_Particle = ParticleData::PlasmaGun;
        m_Particle.Position = barrelPos;
        for (size_t i = 0; i < 20 ; i++)
        {
            ps->Emit(m_Particle, Boom);
        }
        canShoot = false;
    }
}

