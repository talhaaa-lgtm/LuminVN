#include "shader.h"

#include <fstream>
#include <sstream>
#include <iostream>

std::string Shader::loadShaderSource(const char* path) {
    std::ifstream file(path);

    if (!file.is_open()) {
        std::cerr << "Failed to open shader file: " << path << "\n";
        return "";
    }
    std::stringstream buffer;
    buffer << file.rdbuf();

    return buffer.str();
}

Shader::Shader(const char* vertexPath, const char* fragmentPath) {
    std::string vertexCode = loadShaderSource(vertexPath);
    std::string fragmentCode = loadShaderSource(fragmentPath);

    if (vertexCode.empty() || fragmentCode.empty()) {
        std::cerr << "Shader source empty!\n";

        return;
    }

    const char* vertexSource = vertexCode.c_str();
    const char* fragmentSource = fragmentCode.c_str();

    shaders.vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(shaders.vertexShader, 1, &vertexSource, nullptr);
    glCompileShader(shaders.vertexShader);

    shaders.fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(shaders.fragmentShader, 1, &fragmentSource, nullptr);
    glCompileShader(shaders.fragmentShader);

    shaders.shaderProgram = glCreateProgram();
    glAttachShader(shaders.shaderProgram, shaders.vertexShader);
    glAttachShader(shaders.shaderProgram, shaders.fragmentShader);
    glLinkProgram(shaders.shaderProgram);
}

const ShaderComp& Shader::getShaders() const{
    return shaders;
}

Shader::~Shader(){
    glDeleteShader(shaders.vertexShader);
    glDeleteShader(shaders.fragmentShader);
    glDeleteProgram(shaders.shaderProgram);
}

// moving setup
Shader& Shader::operator = (Shader&& other) noexcept {
    if (this != &other) {
        glDeleteShader(shaders.vertexShader);
        glDeleteShader(shaders.fragmentShader);
        glDeleteProgram(shaders.shaderProgram);

        shaders = other.shaders;
        other.shaders = {};
    }
    return *this;
}