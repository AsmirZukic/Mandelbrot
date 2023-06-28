#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include <vector>

class Renderer {
public:
    Renderer(SDL_Window* window);
    ~Renderer();

    bool init();
    void close();

    void updatePixels(const std::vector<unsigned int>& pixels);
    void render();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    int width;
    int height;
};

#endif // RENDERER_H
