#pragma once

#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

class Camera2D {
public:
    Camera2D(float width, float height)
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

    void UpdateCameraPosition(const glm::vec2& newPosition) {
        m_Position = newPosition;
        // Optionally add smoothing or other adjustments here
    }

private:
    glm::vec2 m_Position;
    float m_ZoomLevel;
    float m_Width, m_Height;
}; 
