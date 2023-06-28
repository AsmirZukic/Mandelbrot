#include "../include/Window.h"

Window::Window(const std::string& title, int width, int height)
    : title(title), width(width), height(height), window(nullptr) {}

Window::~Window() {
    close();
}

bool Window::init() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        return false;
    }

    // Create a window
    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              width, height, SDL_WINDOW_SHOWN);
    if (!window) {
        SDL_Quit();
        return false;
    }

    return true;
}

void Window::close() {
    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }

    SDL_Quit();
}

SDL_Window* Window::getSDLWindow() const {
    return window;
}
