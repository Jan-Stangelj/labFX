#pragma once

#include "glad/glad.h"

enum bufferTarget : GLenum {
    SHADER_STORAGE_BUFFER = GL_SHADER_STORAGE_BUFFER,
    UNIFORM_BUFFER = GL_UNIFORM_BUFFER
};

class buffer {
public:

    buffer() = default;
    ~buffer();

    buffer(const buffer&) = delete;
    buffer& operator=(const buffer&) = delete;

    buffer(buffer&& other) noexcept;
    buffer& operator=(buffer&& other) noexcept;

    bool create(GLsizeiptr size, const void* data = nullptr);
    bool bind(bufferTarget type, GLuint bindingPoint) const;

private:

    GLuint m_id = 0;
    GLsizei m_size = 0;

};