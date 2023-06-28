#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <SDL2/SDL.h>

class InputHandler {
public:
    InputHandler();
    ~InputHandler();

    void init();
    void handleEvent(const SDL_Event& event);
    void getMouseDelta(int& deltaX, int& deltaY);

private:
    int prevMouseX;
    int prevMouseY;
    int currMouseX;
    int currMouseY;
};

#endif // INPUTHANDLER_H
