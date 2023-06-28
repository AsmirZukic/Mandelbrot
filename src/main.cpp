#include <iostream>
#include <vector>
#include <SDL2/SDL.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const double ZOOM_FACTOR = 1.1;

class MandelbrotRenderer
{
public:
    MandelbrotRenderer() : window(nullptr), renderer(nullptr), texture(nullptr), isRunning(false), zoomLevel(1.0), offsetX(0.0), offsetY(0.0)
    {
        if (SDL_Init(SDL_INIT_VIDEO) < 0)
        {
            std::cout << "SDL initialization failed. SDL Error: " << SDL_GetError() << std::endl;
            return;
        }

        window = SDL_CreateWindow("Mandelbrot Set", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (!window)
        {
            std::cout << "Window creation failed. SDL Error: " << SDL_GetError() << std::endl;
            return;
        }

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (!renderer)
        {
            std::cout << "Renderer creation failed. SDL Error: " << SDL_GetError() << std::endl;
            return;
        }

        texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_HEIGHT);
        if (!texture)
        {
            std::cout << "Texture creation failed. SDL Error: " << SDL_GetError() << std::endl;
            return;
        }

        isRunning = true;
    }

    ~MandelbrotRenderer()
    {
        SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    void render()
    {
        std::vector<Uint32> pixels(SCREEN_WIDTH * SCREEN_HEIGHT, 0);

        for (int i = 0; i < SCREEN_WIDTH; ++i)
        {
            for (int j = 0; j < SCREEN_HEIGHT; ++j)
            {
                double x0 = (i - SCREEN_WIDTH / 2.0 + offsetX) * zoomLevel / SCREEN_WIDTH;
                double y0 = (j - SCREEN_HEIGHT / 2.0 + offsetY) * zoomLevel / SCREEN_HEIGHT;

                double x = 0.0;
                double y = 0.0;

                int iterations = 0;
                const int maxIterations = 200;

                while (x * x + y * y <= 4 && iterations < maxIterations)
                {
                    double xTemp = x * x - y * y + x0;
                    y = 2 * x * y + y0;
                    x = xTemp;
                    ++iterations;
                }

                Uint8 r = static_cast<Uint8>(iterations % 256);
                Uint8 g = static_cast<Uint8>(iterations % 128);
                Uint8 b = static_cast<Uint8>(iterations % 64);

                pixels[j * SCREEN_WIDTH + i] = SDL_MapRGB(SDL_AllocFormat(SDL_PIXELFORMAT_ARGB8888), r, g, b);
            }
        }

        SDL_UpdateTexture(texture, nullptr, pixels.data(), SCREEN_WIDTH * sizeof(Uint32));
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, nullptr, nullptr);
        SDL_RenderPresent(renderer);
    }

    void handleInput()
    {
        SDL_Event event;
        while (SDL_PollEvent(&event) != 0)
        {
            if (event.type == SDL_QUIT)
            {
                isRunning = false;
            }
            else if (event.type == SDL_MOUSEWHEEL)
            {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);

                if (event.wheel.y > 0)
                {
                    zoomIn(mouseX, mouseY);
                }
                else if (event.wheel.y < 0)
                {
                    zoomOut(mouseX, mouseY);
                }
            }
            else if (event.type == SDL_MOUSEMOTION && event.motion.state & SDL_BUTTON(SDL_BUTTON_LEFT))
            {
                dragImage(event.motion.xrel, event.motion.yrel);
            }
        }
    }

    bool isRunning;

private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;

    double zoomLevel;
    double offsetX;
    double offsetY;

    void zoomIn(int mouseX, int mouseY)
    {
        double prevZoomLevel = zoomLevel;

        double offsetX = (mouseX - SCREEN_WIDTH / 2.0) * zoomLevel / (SCREEN_WIDTH / 2.0);
        double offsetY = (mouseY - SCREEN_HEIGHT / 2.0) * zoomLevel / (SCREEN_HEIGHT / 2.0);

        this->offsetX -= offsetX;
        this->offsetY -= offsetY;

        zoomLevel *= ZOOM_FACTOR;

        double newOffsetX = (mouseX - SCREEN_WIDTH / 2.0) * zoomLevel / (SCREEN_WIDTH / 2.0);
        double newOffsetY = (mouseY - SCREEN_HEIGHT / 2.0) * zoomLevel / (SCREEN_HEIGHT / 2.0);

        this->offsetX += offsetX - newOffsetX;
        this->offsetY += offsetY - newOffsetY;
    }

    void zoomOut(int mouseX, int mouseY)
    {
        double prevZoomLevel = zoomLevel;

        double offsetX = (mouseX - SCREEN_WIDTH / 2.0) * zoomLevel / (SCREEN_WIDTH / 2.0);
        double offsetY = (mouseY - SCREEN_HEIGHT / 2.0) * zoomLevel / (SCREEN_HEIGHT / 2.0);

        this->offsetX += offsetX;
        this->offsetY += offsetY;

        zoomLevel /= ZOOM_FACTOR;

        double newOffsetX = (mouseX - SCREEN_WIDTH / 2.0) * zoomLevel / (SCREEN_WIDTH / 2.0);
        double newOffsetY = (mouseY - SCREEN_HEIGHT / 2.0) * zoomLevel / (SCREEN_HEIGHT / 2.0);

        this->offsetX -= offsetX - newOffsetX;
        this->offsetY -= offsetY - newOffsetY;
    }

    void dragImage(int deltaX, int deltaY)
    {
        offsetX -= deltaX * zoomLevel / SCREEN_WIDTH;
        offsetY -= deltaY * zoomLevel / SCREEN_HEIGHT;
    }
};

int main(int argc, char *argv[])
{
    MandelbrotRenderer renderer;

    while (renderer.isRunning)
    {
        renderer.handleInput();
        renderer.render();
    }

    return 0;
}
