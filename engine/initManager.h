#pragma once

#include <SDL2/SDL.h>

class Init {
    private:
        int sWidth = 1100; // temporary placeholder...
        int sHeight = 640; // ...values for testing

        SDL_Window* gWindow = nullptr;
        SDL_GLContext gContext = nullptr;

    public:
        // public getter function for the renderer to be able to safely access gWindow
        SDL_Window* getWindow() const;

        Init(const char* title, int majorVersion, int minorVersion, int vSync);
        ~Init();

        // disabled copying
        Init(const Init&) = delete;
        Init& operator = (const Init&) = delete;
};