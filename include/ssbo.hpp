#pragma once

#include "glad/glad.h"

class ssbo {
public:

    ssbo() = default;
    ~ssbo();

    ssbo(const ssbo&) = delete;
    ssbo& operator=(const ssbo&) = delete;

    ssbo(ssbo&& other) noexcept;
    ssbo& operator=(ssbo&& other) noexcept;

    bool create(GLsizeiptr size, const void* data = nullptr);
    bool bind(GLuint bindingPoint) const;

private:

    GLuint m_id = 0;
    GLsizei m_size = 0;

};