#include "initManager.h"

#include <glad/glad.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

Init::Init(const char* title, int majorVersion, int minorVersion, int vSync){
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
        throw std::runtime_error(std::string("SDL_Init Failed: ") + SDL_GetError());
    else {
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, majorVersion);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, minorVersion);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

        gWindow = SDL_CreateWindow(
                    title,
                    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                    sWidth, sHeight,
                    SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL
        );

        if(gWindow == nullptr)
            throw std::runtime_error(std::string("Window init fail: ") + SDL_GetError());
        else {
            if((gContext = SDL_GL_CreateContext(gWindow)) == nullptr)
                throw std::runtime_error(std::string("Context creation fail: ") + SDL_GetError());
            else {
                switch(vSync){
                    case -1:
                        SDL_GL_SetSwapInterval(-1); // ADAPTIVE VSYNC
                        break;
                    case 0:
                        SDL_GL_SetSwapInterval(0); // immediate updates (extremely GPU intensive)
                        break;
                    default:
                        SDL_GL_SetSwapInterval(1); // VSYNC (default)
                        break;
                }

                if(!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
                    throw std::runtime_error(std::string("GLAD init fail: ") + SDL_GetError());
                else {
                    glViewport(0, 0, sWidth, sHeight);

                    glEnable(GL_BLEND);
                    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

                    std::cout << "INIT SUCCESS" << std::endl;
                }
            }
        }
    }
}

SDL_Window* Init::getWindow() const {
    return gWindow;
}

Init::~Init(){
    SDL_GL_DeleteContext(gContext);
    gContext = nullptr;

    SDL_DestroyWindow(gWindow);
    gWindow = nullptr;

    SDL_Quit();
}