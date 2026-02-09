#pragma once

#include <glad/glad.h>

class Mesh;
class Shader;

class Renderer {
    public:
        Renderer() = default;

        void draw(const Mesh& meshName, const Shader& shader, GLsizei indexCount, const void* indexOffset = nullptr);

        // disabled copying
        Renderer(const Renderer&) = delete;
        Renderer& operator = (const Renderer&) = delete;

        // moving allowed
        Renderer(Renderer&& other) noexcept;
        Renderer& operator=(Renderer&& other) noexcept;
};