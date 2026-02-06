#include "initManager.h"
#include "assetManager.h"
#include "shader.h"
#include "mesh.h"

#include <glad/glad.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <string>

int main(int argc, char* argv[]){
    const float vertices[] = {
        -0.5, -0.5,  0.0,  0.0, 0.0,
         0.5, -0.5,  0.0,  1.0, 0.0,
        -0.5,  0.5,  0.0,  0.0, 1.0,
         0.5,  0.5,  0.0,  1.0, 1.0
    };

    GLuint indices[] = {
        0, 1, 2,
        2, 3, 1
    };

    try {
        Init instanceMain("test", 3, 3, -1);

        Shader shader("shaders/temp.vert", "shaders/temp.frag");

        AssetManager asset;
        TextureData apple = asset.loadTexture("assets/apple.png");

        Mesh mesh1(vertices, sizeof(vertices), indices, sizeof(indices), 6);
        mesh1.addAttribute(0, 3, 5 * sizeof(float), (void*)0);
        mesh1.addAttribute(1, 2, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        mesh1.addTexture(apple, GL_REPEAT, GL_LINEAR);

        asset.freeTexture(apple);

        bool running = true;
        SDL_Event event;

        while(running){
            while(SDL_PollEvent(&event)){
                if(event.type == SDL_QUIT)
                    running = false;
            }

            glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            glUseProgram(shader.getShaders().shaderProgram);
            glBindVertexArray(mesh1.getGLObjects().VAO);
            glDrawElements(GL_TRIANGLES, mesh1.getIndexCount(), GL_UNSIGNED_INT, 0);

            SDL_GL_SwapWindow(instanceMain.getWindow());
        }
    }
    catch(const std::exception& e){
        std::cerr << e.what() << std::endl;

        return -1;
    }
}