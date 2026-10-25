#include "shader.hpp"

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

shader::~shader() {
    if (m_id) glDeleteProgram(m_id);
}

shader::shader(shader&& other) noexcept {
    m_id = other.m_id;
    other.m_id = 0;
}
shader& shader::operator=(shader&& other) noexcept {
    if (this != &other) {
        if (m_id)
            glDeleteProgram(m_id);
        m_id = other.m_id;
        other.m_id = 0;
    }
    return *this;
}

bool shader::loadFromFile(const char* vertexPath, const char* fragmentPath) {

    std::string vertexCode;
    std::string fragmentCode;

    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);

    try {

        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);

        std::stringstream vShaderStream, fShaderStream;

        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        vShaderFile.close();
        fShaderFile.close();

        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();

    } catch (std::ifstream::failure& e) {

        std::cout << "WARNING: Failed to read shader files, did nothing:\n- Vertex: " << vertexPath << "\n- Fragment: " << fragmentPath << '\n';
        return false;
    }

    return loadFromText(vertexCode.c_str(), fragmentCode.c_str());
}

bool shader::loadFromText(const char* vertexCode, const char* fragmentCode) {
    if (vertexCode == nullptr || fragmentCode == nullptr) {
        std::cout << "WARNING: No shader source code provided. Did nothing.\n";
        return false;
    }

    GLuint vertex = 0;
    GLuint fragment = 0;

    int success;
    char infoLog[512];

    // Vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertexCode, nullptr);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
        std::cerr << "ERROR: Vertex shader compilation failed, aborting: " << infoLog << "\n";
        glDeleteShader(vertex);
        return false;
    }

    // Fragment shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragmentCode, nullptr);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
        std::cerr << "ERROR: Fragment shader compilation failed, aborting: " << infoLog << "\n";
        glDeleteShader(vertex);
        glDeleteShader(fragment);
        return false;
    }

    GLuint program = glCreateProgram();
    glAttachShader(program, vertex);
    glAttachShader(program, fragment);

    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, nullptr, infoLog);
        std::cerr << "ERROR: Linking shader programs failed, aborting: " << infoLog << "\n";
        glDeleteShader(vertex);
        glDeleteShader(fragment);
        glDeleteProgram(program);
        return false;
    }

    if (m_id != 0) {
        std::cout << "WARNING: Shader already created, overwriting.\n";
        glDeleteProgram(m_id);
    }
    m_id = program;

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    return true;
}

bool shader::use() const {
    if (m_id == 0) {
        std::cout << "NOTE: Use called with no shader present. Did nothing.\n";
        return false;
    }
    
    glUseProgram(m_id);
    return true;
}