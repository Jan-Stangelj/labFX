#include "camera.hpp"

#include "glm/ext.hpp"

debugCamera::debugCamera() {
    m_matrixBuffer.create(sizeof(glm::mat4) * 2);
}

void debugCamera::updateDirection(float x, float y) {
    x *= sensitivity;
    y *= sensitivity;

    m_yaw += x;
    m_pitch += y;

    if (m_pitch > 89.0f) m_pitch = 89.0f;
    if (m_pitch < -89.0f) m_pitch = -89.0f;
}

void debugCamera::updateOrigin(float deltaTime) {
    const bool* keys = SDL_GetKeyboardState(nullptr);

    float velocity = speed * deltaTime;

    if (keys[SDL_SCANCODE_W]) m_origin += m_front * velocity;
    if (keys[SDL_SCANCODE_S]) m_origin -= m_front * velocity;
    if (keys[SDL_SCANCODE_D]) m_origin += m_right * velocity;
    if (keys[SDL_SCANCODE_A]) m_origin -= m_right * velocity;
    if (keys[SDL_SCANCODE_E]) m_origin += m_up * velocity;
    if (keys[SDL_SCANCODE_Q]) m_origin -= m_up * velocity;
}

void debugCamera::apply(GLuint bindingPoint) {

    m_front.x = glm::cos(glm::radians(m_yaw)) * glm::cos(glm::radians(m_pitch));
    m_front.y = glm::sin(glm::radians(m_pitch));
    m_front.z = glm::sin(glm::radians(m_yaw)) * glm::cos(glm::radians(m_pitch));
    m_front = glm::normalize(m_front);

    m_right = glm::normalize(glm::cross(m_front, glm::vec3(0.0f, 1.0f, 0.0f)));
    m_up = glm::normalize(glm::cross(m_right, m_front));

    glm::vec3 lookAt = m_origin + m_front;

    glm::mat4 viewMatrix(1.0f);
    glm::mat4 projectionMatrix(1.0f);

    projectionMatrix = glm::perspective(glm::radians(fovY), aspectRatio, near, far);
    viewMatrix = glm::lookAt(m_origin, lookAt, glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 cameraMatrixData[] = { viewMatrix, projectionMatrix };

    m_matrixBuffer.write(0, sizeof(cameraMatrixData), cameraMatrixData);
    m_matrixBuffer.bind(bufferTarget::UNIFORM_BUFFER, bindingPoint);
}
