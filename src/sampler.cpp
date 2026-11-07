#include "sampler.hpp"

#include <iostream>

sampler::sampler() {
    glCreateSamplers(1, &m_id);

glSamplerParameteri(m_id, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glSamplerParameteri(m_id, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glSamplerParameteri(m_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glSamplerParameteri(m_id, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}
sampler::~sampler() {
    glDeleteSamplers(1, &m_id);
}

sampler::sampler(sampler&& other) noexcept {
    m_id = other.m_id;
    other.m_id = 0;
}
sampler& sampler::operator=(sampler&& other) noexcept {
    if (this != &other) {
        if (m_id != 0) {
            std::cout << "WARNING: sampler already present on move destination. Overwriting.\n";
            glDeleteSamplers(1, &m_id);
        }
        m_id = other.m_id;
        other.m_id = 0;
    }
    return *this;
}

bool sampler::bind(GLuint bindingPoint) const {
    if (m_id == 0) {
        std::cout << "NOTE: bind called with no sampler present. Did nothing.\n";
        return false;
    }
    glBindSampler(bindingPoint, m_id);
    return true;
}