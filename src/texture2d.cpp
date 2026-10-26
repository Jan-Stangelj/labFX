#include "texture2d.hpp"

#include "stb/stb_image.h"

#include <iostream>
#include <cmath>

texture2d::~texture2d() {
    if (m_id != 0) glDeleteTextures(1, &m_id);
}

texture2d::texture2d(texture2d&& other) noexcept {
    m_id = other.m_id;
    m_width = other.m_width;
    m_height = other.m_height;
    other.m_id = 0;
    other.m_width = 0;
    other.m_height = 0;
}

texture2d& texture2d::operator=(texture2d&& other) noexcept {
    if (this != &other) {
        if (m_id != 0) {
            std::cout << "WARNING: 2D texture already present on move destination. Overwriting.\n";
            glDeleteTextures(1, &m_id);
        }
        m_id = other.m_id;
        m_width = other.m_width;
        m_height = other.m_height;
        other.m_id = 0;
        other.m_width = 0;
        other.m_height = 0;
    }
    return *this;
}

bool texture2d::create(GLsizei width, GLsizei height, GLenum internalFormat, bool mipmapping) {
    if (width <= 0 || height <= 0) {
        std::cerr << "ERROR: Cannot create texture with dimensions, aborting: " << width << ' ' << height << '\n';
        return false;
    }
    
    m_width = width;
    m_height = height;

    if (m_id != 0) {
        std::cout << "WARNING: 2D texture already present. Deleting and re-allocating\n";
        glDeleteTextures(1, &m_id);
    }

    m_id = 0;
    glCreateTextures(GL_TEXTURE_2D, 1, &m_id);

    if (m_id == 0) {
        std::cout << "ERROR: Failed to create 2D texture. Aborting.\n";
        return false;
    }

    GLsizei levels = 1;

    if (mipmapping) levels = 1 + std::ceil(std::log2(std::max(width, height)));
    m_mips = levels;

    GLint magFilter = mipmapping ? GL_LINEAR_MIPMAP_LINEAR : GL_LINEAR;

    // TODO: Make these editable
    glTextureParameteri(m_id, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(m_id, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTextureParameteri(m_id, GL_TEXTURE_MIN_FILTER, magFilter);
    glTextureParameteri(m_id, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTextureStorage2D(m_id, levels, internalFormat, width, height);

    return true;
}

bool texture2d::create(const char* file, GLenum internalFormat, bool mipmapping) {
    int nrChannels;
    stbi_set_flip_vertically_on_load(true);

    void* data = nullptr;
    bool hdr = stbi_is_hdr(file);
    GLenum dataType = hdr ? GL_FLOAT : GL_UNSIGNED_BYTE;

    if (hdr) data = stbi_loadf(file, &m_width, &m_height, &nrChannels, 4);
    else data = stbi_load(file, &m_width, &m_height, &nrChannels, 4);

    if (data == nullptr) {
        std::cerr << "ERROR: Failed to load 2D texture " << file << '\n';
        return false;
    }

    if (create(m_width, m_height, internalFormat, mipmapping) == false) return false;

    if (loadData(GL_RGBA, dataType, data) == false) return false;

    stbi_image_free(data);
    return true;
}

bool texture2d::loadData(GLenum dataFormat, GLenum dataType, const void* data, GLint mip) const {
    if (m_id == 0) {
        std::cout << "NOTE: loadData called with no 2D texture present. Did nothing.\n";
        return false;
    }

    if (mip >= m_mips) {
        std::cout << "WARNING: Cannot write into non-existent 2D texture mips. Aborting.\n";
        return false;
    }

    glTextureSubImage2D(m_id, mip, 0, 0, m_width, m_height, dataFormat, dataType, data);
    return true;
}

bool texture2d::generateMipmaps() const {
    if (m_id == 0) {
        std::cout << "NOTE: generateMipmaps called with no 2D texture present. Did nothing.\n";
        return false;
    }

    if (m_mips == 1) {
        std::cout << "NOTE: generateMipmaps called with only 1 active 2D texture mip level. Did nothing.\n";
        return false;
    }

    glGenerateTextureMipmap(m_id);
    return true;
}

bool texture2d::bind(GLuint bindingPoint) const {
    if (m_id == 0) {
        std::cout << "NOTE: bind called with no 2D texture present. Did nothing.\n";
        return false;
    }

    glBindTextureUnit(bindingPoint, m_id);
    return true;
}