#include "buffer.hpp"

#include <iostream>

buffer::~buffer() {
    if (m_id != 0) glDeleteBuffers(1, &m_id);
}

buffer::buffer(buffer&& other) noexcept {
    m_id = other.m_id;
    other.m_id = 0;
}

buffer& buffer::operator=(buffer&& other) noexcept {
    if (this != &other) {
        if (m_id != 0) {
            std::cout << "WARNING: Buffer already present on move destination. Overwriting.\n";
            glDeleteBuffers(1, &m_id);
        }
        m_id = other.m_id;
        other.m_id = 0;
    }
    return *this;
}

bool buffer::create(GLsizeiptr size, const void* data) {
    if (size == 0) {
        std::cerr << "ERROR: Cannot create buffer with size of 0. Aborting\n";
        return false;
    }

    m_size = size;

    if (m_id != 0) {
        std::cout << "WARNING: Buffer already present. Deleting and re-allocating.\n";
        glDeleteBuffers(1, &m_id);
    }

    m_id = 0;
    glCreateBuffers(1, &m_id);

    if (m_id == 0) {
        std::cout << "ERROR: Failed to create buffer. Aborting.\n";
        return false;
    }

    glNamedBufferStorage(m_id, size, data, 0); // need to add GL_DYNAMIC_STORAGE_BIT back if you want subsequent read/write on cpu

    return true;
}

bool buffer::bind(bufferTarget type, GLuint bindingPoint) const {
    if (m_id == 0) {
        std::cout << "NOTE: bind called with no buffer present. Did nothing.\n";
        return false;
    }

    glBindBufferBase(static_cast<GLenum>(type), bindingPoint, m_id);
    return true;
}