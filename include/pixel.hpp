#pragma once

#include "renderer.hpp"
#include <iostream>

class Pixel
{
private:

  int xPos, yPos;
  Renderer* mRenderer = Renderer::getInstance();

public:

  Pixel();
  Pixel( int xPos, int yPos );

  void render( int Red, int Green, int Blue, int Alpha );

  void setPixelColor( int Red, int Green, int Blue, int Alpha );

  void printPixel()
  {
    std::cout << xPos << "\t" << yPos << "\n";
  }


};
