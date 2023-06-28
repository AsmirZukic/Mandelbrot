#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <iostream>
#include <SDL2/SDL.h>

class Window {
public:
    Window(const std::string& title, int width, int height);
    ~Window();

    bool init();
    void close();

    SDL_Window* getSDLWindow() const;

private:
    std::string title;
    int width;
    int height;
    SDL_Window* window;
};

#endif // WINDOW_H
