#include "init.hpp"

#include "SDL3/SDL.h"

#include <iostream>

bool init(bool debug) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "Failed to init SDL3, aborting: " << SDL_GetError() << '\n';
        return false;
    }
    if (!SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4)) {
        std::cerr << "Failed to set OpenGL attribute, aborting: " << SDL_GetError() << '\n';
        return false;
    }
    if (!SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6)) {
        std::cerr << "Failed to set OpenGL attribute, aborting: " << SDL_GetError() << '\n';
        return false;
    }
    if (!SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE)) {
        std::cerr << "Failed to set OpenGL attribute, aborting: " << SDL_GetError() << '\n';
        return false;
    }
    if (debug) {
        if (!SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG)) {
            std::cerr << "Failed to set OpenGL attribute, aborting: " << SDL_GetError() << '\n';
            return false;
        }
    }
    return true;
}

bool quit() {
    SDL_Quit();
    return true;
}