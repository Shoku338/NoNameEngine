    #pragma once

    #include "gtc/matrix_transform.hpp"
    #include "gtc/type_ptr.hpp"
    #include "Player.h"
    #include"Tilemap.h"
    #include <algorithm>
    #include<iostream>

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

        void UpdateCameraPosition(const glm::vec2& playerPosition, bool faceRight, float dt, float levelMinX, float levelMaxX, float levelMinY, float levelMaxY) {
            float leftOffset = 200.0f; // Adjust for player and screen offset when facing right
            float rightOffset = 850.0f; // Adjust for player and screen offset when facing left
            float screenHeight = GameEngine::GetInstance()->GetWindowHeight();
            float screenMidPointY = screenHeight / 2.0f;

            // Determine the target position based on the player's facing direction
            float targetPositionX = faceRight ? playerPosition.x - leftOffset : playerPosition.x - rightOffset;

            // Determine the target position for vertical movement
            float targetPositionY = playerPosition.y - screenMidPointY;

            float smoothingSpeed = 2.50f; // The higher the value, the faster the camera moves to the target position

            // Calculate the difference between the current position and the target position
            float positionDifferenceX = targetPositionX - m_Position.x;
            float positionDifferenceY = targetPositionY - m_Position.y;

            // Move the camera to the target position smoothly
            m_Position.x += positionDifferenceX * smoothingSpeed * dt;
            m_Position.y += positionDifferenceY * smoothingSpeed * dt;

            // Ensure the camera does not move out of map boundaries
            m_Position.x = std::max(m_Position.x, levelMinX);
            m_Position.x = std::min(m_Position.x, levelMaxX);
            m_Position.y = std::max(m_Position.y, levelMinY);
            m_Position.y = std::min(m_Position.y, levelMaxY);
        }


    

        glm::vec2 getPosition(){
            return m_Position;
        }
    private:
        glm::vec2 m_Position;
        float m_ZoomLevel;
        int m_Width, m_Height;
    }; 
