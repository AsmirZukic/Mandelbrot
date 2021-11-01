#pragma once
#include "window.hpp"
#include "renderer.hpp"

class Engine
{
private:
  bool running = false;

public:
  Window* window = Window::getInstance();
  Renderer* renderer = Renderer::getInstance();

  Engine();

  ~Engine();

  void handleInput();

  virtual void render();

  const bool isRunning();

  void draw();

};
