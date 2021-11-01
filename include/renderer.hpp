#pragma once

#include "window.hpp"

class Renderer
{
private:
  SDL_Renderer* mRenderer = nullptr;

  static Renderer* iRenderer;

  Renderer();
  Renderer( Window* window );
  Renderer( const Renderer& );
  
public:

  ~Renderer();

  void close();

  const bool isCreated() { return mRenderer; }

  SDL_Renderer* getRenderer() { return mRenderer; }

  static Renderer* getInstance();

};
