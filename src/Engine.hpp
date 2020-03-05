/**
 * Name: Engine.hpp
 * Description: Provides an interface to a Neon rendering engine.
 * Created on: 26.07.2019
 * Last modified: 25.10.2019
 * Author: Adam Graliński (adam@gralin.ski)
 * License: MIT
 */

#pragma once

#include <SDL2/SDL.h>

namespace neon
{

class Engine
{
 public:
  Engine();
  ~Engine();
  Engine(const Engine& other) = delete;
  Engine& operator=(const Engine& other) = delete;

  bool init();
  void startMainLoop();

 private:
  void close();
  SDL_Window* m_window;
  SDL_Renderer* m_renderer;
  SDL_Surface* m_screenSurface;
};

} // namespace neon
