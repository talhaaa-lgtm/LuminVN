#pragma once

#include <glad/glad.h>
#include <string>

struct ShaderComp {
    GLuint vertexShader = 0;
    GLuint fragmentShader = 0;
    GLuint shaderProgram = 0;
};

class Shader {
    private:
        ShaderComp shaders;

    public:
        const char* vertexShaderSource;
        const char* fragmentShaderSource;

        Shader(const char* vertexPath, const char* fragmentPath);
        ~Shader();

        std::string loadShaderSource(const char* path);

        // getter
        const ShaderComp& getShaders() const;

        // copying disabled
        Shader(const Shader&) = delete;
        Shader& operator = (const Shader&) = delete;

        // moving allowed
        Shader(Shader&& other) noexcept;
        Shader& operator=(Shader&& other) noexcept;
};