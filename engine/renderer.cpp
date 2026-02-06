#include "renderer.h"
#include "mesh.h"
#include "shader.h"

#include <glad/glad.h>

void Renderer::draw(const Mesh& meshName, const Shader& shader, GLsizei indexCount, const void* indexOffset){
    glUseProgram(shader.getShaders().shaderProgram);
    glBindVertexArray(meshName.getGLObjects().VAO);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, meshName.getTexture());

    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, indexOffset);
}