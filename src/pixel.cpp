#include "../include/pixel.hpp"
#include <SDL2/SDL.h>

Pixel::Pixel() = default;

Pixel::Pixel( int xPos, int yPos ): xPos(xPos), yPos(yPos)
{
  
}

void Pixel::render( int Red, int Green, int Blue, int Alpha )
{
  setPixelColor( Red, Green, Blue, Alpha );
  SDL_RenderDrawPoint( mRenderer->getRenderer(), xPos, yPos );
}

void Pixel::setPixelColor( int Red, int Green, int Blue, int Alpha )
{
  SDL_SetRenderDrawColor( mRenderer->getRenderer(), Red, Green, Blue, Alpha );
}
