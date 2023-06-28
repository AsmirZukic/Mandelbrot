#include "../include/Window.h"
#include "../include/Renderer.h"
#include "../include/InputHandler.h"
#include "../include/Fractal.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char* argv[])
{
    // Create a window
    Window window("Mandelbrot Set", SCREEN_WIDTH, SCREEN_HEIGHT);
    if (!window.init())
    {
        std::cerr << "Window creation failed." << std::endl;
        return 1;
    }

    // Create a renderer
    Renderer renderer(window.getSDLWindow());
    if (!renderer.init())
    {
        std::cerr << "Renderer creation failed." << std::endl;
        return 1;
    }

    // Create an input handler
    InputHandler inputHandler;
    inputHandler.init();

    // Create the fractal generator
    Fractal fractal(SCREEN_WIDTH, SCREEN_HEIGHT);

    // Main loop
    bool isRunning = true;
    while (isRunning)
    {
        // Handle events
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            inputHandler.handleEvent(event);

            if (event.type == SDL_QUIT)
            {
                isRunning = false;
            }
        }

        // Handle input
        int deltaX, deltaY;
        inputHandler.getMouseDelta(deltaX, deltaY);
        fractal.updateOffset(deltaX, deltaY);

        // Generate fractal pixels
        std::vector<unsigned int> pixels = fractal.generate();

        // Update renderer with new pixels
        renderer.updatePixels(pixels);

        // Render the scene
        renderer.render();
    }

    return 0;
}
