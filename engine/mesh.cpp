#include "mesh.h"
#include "assetManager.h"

#include <glad/glad.h>

Mesh::Mesh(const void* vertexData, GLsizeiptr vertexSize, const GLuint* indices, GLsizeiptr indexSize, GLsizei indexCount){
    this->indexCount = indexCount;

    glGenVertexArrays(1, &gl.VAO);
    glBindVertexArray(gl.VAO);

    glGenBuffers(1, &gl.VBO);
    glBindBuffer(GL_ARRAY_BUFFER, gl.VBO);
    glBufferData(GL_ARRAY_BUFFER, vertexSize, vertexData, GL_STATIC_DRAW);

    glGenBuffers(1, &gl.EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gl.EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexSize, indices, GL_STATIC_DRAW);
}

void Mesh::addAttribute(GLuint attribIndex, GLint attribSize, GLsizei stride, const void* offset) const {
    glBindVertexArray(gl.VAO);
    glVertexAttribPointer(attribIndex, attribSize, GL_FLOAT, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(attribIndex);
}

void Mesh::addTexture(const TextureData& tex, GLint wrapParam, GLint filterParam){
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapParam);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapParam);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterParam);

    GLenum channels = (tex.nrChannels == 4)? GL_RGBA: GL_RGB; // channels check

    glTexImage2D(
        GL_TEXTURE_2D, 0, channels, 
        tex.width, tex.height, 0,
        channels, GL_UNSIGNED_BYTE,
        tex.texData
    );
    glGenerateMipmap(GL_TEXTURE_2D);
}

const GLObjects& Mesh::getGLObjects() const {
    return gl;
}
GLsizei Mesh::getIndexCount() const {
    return indexCount;
}
GLuint Mesh::getTexture() const {
    return texture;
}

Mesh::~Mesh(){
    glDeleteVertexArrays(1, &gl.VAO);
    glDeleteBuffers(1, &gl.VBO);
    glDeleteBuffers(1, &gl.EBO);
    glDeleteTextures(1, &texture);
}

// moving setup
Mesh::Mesh(Mesh&& other) noexcept {
    gl = other.gl;
    indexCount = other.indexCount;
    texture = other.texture;

    other.gl = {};
    other.indexCount = 0;
    other.texture = 0;
}

Mesh& Mesh::operator = (Mesh&& other) noexcept {
    if (this != &other){
        glDeleteVertexArrays(1, &gl.VAO);
        glDeleteBuffers(1, &gl.VBO);
        glDeleteBuffers(1, &gl.EBO);
        glDeleteTextures(1, &texture);

        gl = other.gl;
        indexCount = other.indexCount;
        texture = other.texture;

        other.gl = {};
        other.indexCount = 0;
        other.texture = 0;
    }
    return *this;
}