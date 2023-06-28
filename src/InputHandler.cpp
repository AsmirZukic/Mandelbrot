#include "../include/InputHandler.h"

InputHandler::InputHandler()
    : prevMouseX(0), prevMouseY(0), currMouseX(0), currMouseY(0) {}

InputHandler::~InputHandler() {}

void InputHandler::init() {
    prevMouseX = 0;
    prevMouseY = 0;
    currMouseX = 0;
    currMouseY = 0;
}

void InputHandler::handleEvent(const SDL_Event& event) {
    if (event.type == SDL_MOUSEMOTION) {
        int deltaX, deltaY;
        SDL_GetRelativeMouseState(&deltaX, &deltaY);
        
        currMouseX += deltaX;
        currMouseY += deltaY;
    }
}

void InputHandler::getMouseDelta(int& deltaX, int& deltaY) {
    deltaX = currMouseX - prevMouseX;
    deltaY = currMouseY - prevMouseY;

    prevMouseX = currMouseX;
    prevMouseY = currMouseY;
}
