#pragma once

#include "glad/glad.h"

enum samplerWrap : GLenum {
    REPEAT = GL_REPEAT,
    CLAMP_TO_EDGE = GL_CLAMP_TO_EDGE,
    MIRRORED_REPEAT = GL_MIRRORED_REPEAT
};

enum samplerFilter {
    BILINEAR,
    TRILINEAR,
    ANISOTROPIC
};

class sampler {
public:

    sampler();
    ~sampler();

    sampler(const sampler&) = delete;
    sampler& operator=(const sampler&) = delete;

    sampler(sampler&& other) noexcept;
    sampler& operator=(sampler&& other) noexcept;

    bool bind(GLuint bindingPoint) const;

    void setWrap(samplerWrap wrap);
    void setFilter(samplerFilter filter);
    void setAnisotropy(GLfloat level);

private:

    GLuint m_id = 0;

};
