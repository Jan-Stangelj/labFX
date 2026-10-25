#pragma once

#include "glad/glad.h"

class texture2d {
public:

    texture2d() = default;
    ~texture2d();

    texture2d(const texture2d&) = delete;
    texture2d& operator=(const texture2d&) = delete;

    texture2d(texture2d&& other) noexcept;
    texture2d& operator=(texture2d&& other) noexcept;

    bool create(GLsizei width, GLsizei height, GLenum internalFormat, bool mipmapping);
    bool create(const char* file, GLenum internalFormat, bool mipmapping);

    bool loadData(GLenum dataFormat, GLenum dataType, const void* data, GLint mip = 0) const;

    bool generateMipmaps() const;

    bool bind(GLuint bindingPoint) const;

private:

    GLuint m_id = 0;

    GLsizei m_width = 0;
    GLsizei m_height = 0;
    GLsizei m_mips = 0;

};