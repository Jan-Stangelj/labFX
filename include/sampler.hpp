#pragma once

#include "glad/glad.h"

class sampler {
public:

    sampler();
    ~sampler();

    sampler(const sampler&) = delete;
    sampler& operator=(const sampler&) = delete;

    sampler(sampler&& other) noexcept;
    sampler& operator=(sampler&& other) noexcept;

    bool bind(GLuint bindingPoint) const;

private:

    GLuint m_id = 0;

};