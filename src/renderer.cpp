#include "../include/renderer.hpp"
#include <iostream>
#include <stdexcept>

Renderer* Renderer::iRenderer = nullptr;

Renderer::Renderer()=default;

Renderer::Renderer( Window* window )
{
  try
  {
    mRenderer = SDL_CreateRenderer( window->getWindow() , -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );

    if( !mRenderer )
    {
      throw SDL_GetError();
    }
    else
    {
      SDL_SetRenderDrawColor( mRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
    }
  }catch( const char* msg)
  {
    std::cerr << msg << '\n';
  }
}

Renderer::~Renderer()
{
  std::cout << "Renderer destructor called. \n";

  close();
}

void Renderer::close()
{
  SDL_DestroyRenderer( mRenderer );
  mRenderer = nullptr;

}

//Singleton getter method
Renderer* Renderer::getInstance()
{
  //If the instance is equal to nullptr
  if( !iRenderer )
    //Create a new instance of the renderer
    iRenderer = new Renderer( Window::getInstance() );

  //Else return the renderer instance
  return iRenderer;
}
