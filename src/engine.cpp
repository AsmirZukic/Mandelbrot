#include "../include/engine.h"
#include <iostream>
#include <stdexcept>

Engine::Engine()
{
  try
  {
    //If the window is equal to nullptr
    if( !( window->getWindow() ) )
    {
      throw "Could not create window";
    }
    else
    {
      //If the renderer is equal to nullptr
      if( !( renderer->getRenderer() ) )
        throw "Could not create Renderer";

      //Else the engine is running
      running = true;
    }
  } catch ( const char* msg )
  {
    std::cerr << msg << '\n';
    running = false;
  }
}

Engine::~Engine()
{
  running = false;

  window->close();
  renderer->close();
}

void Engine::handleInput()
{
  SDL_Event event;

  while( SDL_PollEvent( &event ) != 0 )
  {
    if( event.type == SDL_QUIT )
    {
      window->close();
    }
  }
}

void Engine::render()
{
  SDL_SetRenderDrawColor( renderer->getRenderer(), 0x00, 0x00, 0x00, 0xFF );

  SDL_RenderClear( renderer->getRenderer() );
}

const bool Engine::isRunning()
{
  return window->isOpen() && renderer->isCreated() && running;
}

void Engine::draw()
{
  SDL_RenderPresent( renderer->getRenderer() );
}
