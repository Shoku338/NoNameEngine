#pragma once

#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "Player.h"

class Camera2D {
public:
    Camera2D(int width, int height)
        : m_Position(0.0f, 0.0f), m_ZoomLevel(1.0f), m_Width(width), m_Height(height) {}

    void MoveLeft(float delta) { m_Position.x -= delta; }
    void MoveRight(float delta) { m_Position.x += delta; }
    void MoveUp(float delta) { m_Position.y += delta; }
    void MoveDown(float delta) { m_Position.y -= delta; }

    void ZoomIn(float factor) { m_ZoomLevel *= factor; }
    void ZoomOut(float factor) { m_ZoomLevel /= factor; }

    glm::mat4 GetViewMatrix() const {
        glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(m_ZoomLevel, m_ZoomLevel, 1.0f));
        glm::mat4 translateMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-m_Position.x, -m_Position.y, 0.0f));
        return translateMatrix * scaleMatrix; // Note the order of multiplication
    }

    void UpdateCameraPosition(const glm::vec2& playerPosition, bool faceRight) {
        float screenMidPoint = m_Position.x + (m_Width / 2.0f);
        float forwardThreshold = faceRight ? screenMidPoint + (m_Width / 4.0f) : screenMidPoint - (m_Width / 4.0f);
        float backwardThreshold = faceRight ? screenMidPoint - (m_Width / 4.0f) : screenMidPoint + (m_Width / 4.0f);

        // Check if the player has moved past the midpoint of the screen to the right
        if (playerPosition.x > forwardThreshold) {
            // Move the camera right
            float moveAmount = playerPosition.x - forwardThreshold;
            m_Position.x += moveAmount;
        }
        // Check if the player moves back past the backwardThreshold
        else if (playerPosition.x < backwardThreshold) {
            // Move the camera left
            float moveAmount = playerPosition.x - backwardThreshold;
            m_Position.x += moveAmount; // This will be a negative value, moving the camera to the left
        }

        // Ensure the camera does not move left past the game's starting point (e.g., 0 or another minimum x value)
        m_Position.x = std::max(m_Position.x, 0.0f);

        // Adjust camera position when the player is facing left
        if (!faceRight) {
            m_Position.x += m_Width;  // Move the camera to the right side of the player
        }
    }

    

    glm::vec2 getPosition(){
        return m_Position;
    }
private:
    glm::vec2 m_Position;
    float m_ZoomLevel;
    int m_Width, m_Height;
}; 
