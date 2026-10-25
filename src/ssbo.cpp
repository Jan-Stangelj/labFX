#include "ssbo.hpp"

#include <iostream>

ssbo::~ssbo() {
    if (m_id != 0) glDeleteBuffers(1, &m_id);
}

ssbo::ssbo(ssbo&& other) noexcept {
    m_id = other.m_id;
    other.m_id = 0;
}

ssbo& ssbo::operator=(ssbo&& other) noexcept {
    if (this != &other) {
        if (m_id != 0) {
            std::cout << "WARNING: SSBO already present on move destination. Overwriting.\n";
            glDeleteBuffers(1, &m_id);
        }
        m_id = other.m_id;
        other.m_id = 0;
    }
    return *this;
}

bool ssbo::create(GLsizeiptr size, const void* data) {
    if (size == 0) {
        std::cerr << "ERROR: Cannot create buffer with size of 0. Aborting\n";
        return false;
    }

    m_size = size;

    if (m_id != 0) {
        std::cout << "WARNING: SSBO already present. Deleting and re-allocating.\n";
        glDeleteBuffers(1, &m_id);
    }

    m_id = 0;
    glCreateBuffers(1, &m_id);

    if (m_id == 0) {
        std::cout << "ERROR: Failed to create SSBO. Aborting.\n";
        return false;
    }

    glNamedBufferStorage(m_id, size, data, 0); // need to add GL_DYNAMIC_STORAGE_BIT back if you want subsequent read/write on cpu

    return true;
}

bool ssbo::bind(GLuint bindingPoint) const {
    if (m_id == 0) {
        std::cout << "NOTE: bind called with no SSBO present. Did nothing.\n";
        return false;
    }

    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, bindingPoint, m_id);
    return true;
}