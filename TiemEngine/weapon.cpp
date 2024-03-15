#include "weapon.h"


Weapon::Weapon()
{
    canShoot = true;
    cdTimer = 0.5f;
}

void Weapon::update(glm::vec3 Playerpos) {
    this->pos = Playerpos;
    cout << "cooldown" << cdTimer << ", shoot" << canShoot << endl;
    if (cdTimer > 0) {
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
        Bullet* newBullet = new Bullet(bulletStartPosition, "../Resource/Texture/bullet3.png", 150.f);
        newBullet->SetSize(20.f, 20.f);
        newBullet->shootAt(targetPosition, newBullet->getVelocity().x);
        objectsList.push_back(newBullet);
        
        // SoundEffect
        soundManager->playSound("Blaster", false);

        //Particle Effects
        ParticleProp m_Particle = ParticleData::Gun;
        m_Particle.Position = barrelPos;
        for (size_t i = 0; i < 2; i++)
        {
            ps->Emit(m_Particle, Circle);
        }
        canShoot = false;
    }
}

