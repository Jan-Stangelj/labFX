#pragma once

#include "glad/glad.h"

class texture2 {
public:

    texture2() = default;
    ~texture2();

    texture2(const texture2&) = delete;
    texture2& operator=(const texture2&) = delete;

    texture2(texture2&& other) noexcept;
    texture2& operator=(texture2&& other) noexcept;

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