#pragma once

#include "SDL3/SDL.h"

class window {
public:

    window() = default;
    ~window();

    bool create(unsigned int width, unsigned int height, const char* title);

    bool swapBuffers();

    bool select() const;

private:

    SDL_Window* m_window = nullptr;
    SDL_GLContext m_context = 0;

};