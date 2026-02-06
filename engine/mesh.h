#pragma once

#include <glad/glad.h>

struct GLObjects {
    GLuint VAO = 0;
    GLuint VBO = 0;
    GLuint EBO = 0;
};

struct TextureData; // makes the compiler stop whining, will change later

class Mesh {
    private:
        GLObjects gl;
        GLsizei indexCount = 0;
        GLuint texture = 0;

    public:
        Mesh(const void* vertexData, GLsizeiptr vertexSize, const GLuint* indices, GLsizeiptr indexSize, GLsizei indexCount);
        ~Mesh();

        void addAttribute(GLuint attribIndex, GLint attribSize, GLsizei stride, const void* offset) const;
        void addTexture(const TextureData& tex, GLint wrapParam, GLint filterParam);

        // getters
        const GLObjects& getGLObjects() const;
        GLuint getTexture() const;
        GLsizei getIndexCount() const;

        // disabled copying
        Mesh(const Mesh&) = delete;
        Mesh& operator = (const Mesh&) = delete;

        // moving allowed
        Mesh(Mesh&& other) noexcept;
        Mesh& operator=(Mesh&& other) noexcept;
};