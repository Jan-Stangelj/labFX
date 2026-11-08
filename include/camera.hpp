#pragma once

#include "buffer.hpp"

#include "SDL3/SDL.h"

#include "glm/glm.hpp"

class debugCamera {
public:

    debugCamera();
    ~debugCamera() = default;

    debugCamera(const debugCamera& other);
    debugCamera& operator=(const debugCamera& other);

    void updateDirection(float x, float y);
    void updateOrigin(float deltaTime);
    void apply(GLuint bindingPoint = 0);

    float fovY = 60.0f;
    float aspectRatio = 16.0f/9.0f;

    float near = 0.1f;
    float far = 100.0f;

    float speed = 1.0f;
    float sensitivity = 1.0f;

private:

    buffer m_matrixBuffer;

    glm::vec3 m_origin = glm::vec3(0.0f, 0.0f, 1.0f);

    glm::vec3 m_front = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 m_up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 m_right = glm::vec3(1.0f, 0.0f, 0.0f);

    float m_yaw = -90.0f;
    float m_pitch = 0.0f;

};