#include "../include/Renderer.h"

Renderer::Renderer(SDL_Window* window)
    : window(window), renderer(nullptr), texture(nullptr), width(0), height(0) {}

Renderer::~Renderer() 
{
    close();
}

bool Renderer::init() 
{
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) 
    {
        return false;
    }

    // Get window dimensions
    SDL_GetWindowSize(window, &width, &height);

    // Create texture for rendering
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
                                SDL_TEXTUREACCESS_STREAMING, width, height);
    if (!texture) 
    {
        return false;
    }

    return true;
}

void Renderer::close() 
{
    if (texture) 
    {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }

    if (renderer) 
    {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }
}

void Renderer::updatePixels(const std::vector<unsigned int>& pixels) 
{
    SDL_UpdateTexture(texture, nullptr, pixels.data(), width * sizeof(unsigned int));
}

void Renderer::render() 
{
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, nullptr, nullptr);
    SDL_RenderPresent(renderer);
}
