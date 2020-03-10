/**
 * Name: Engine.hpp
 * Description: Provides an interface to a Neon rendering engine.
 * Created on: 26.07.2019
 * Last modified: 09.03.2020
 * Author: Adam Graliński (adam@gralin.ski)
 * License: MIT
 */

#pragma once

#include <SDL2/SDL.h>
#include <string>

namespace neon
{

class Engine
{
 public:
  static const int DEFAULT_WINDOW_WIDTH;
  static const int DEFAULT_WINDOW_HEIGHT;
  static const Uint32 DEFAULT_WINDOW_FLAGS;

 public:
  Engine();
  ~Engine();
  Engine(const Engine& other) = delete;
  Engine& operator=(const Engine& other) = delete;

  bool init(
      const std::string& title = "Neon",
      int posX = SDL_WINDOWPOS_UNDEFINED,
      int posY = SDL_WINDOWPOS_UNDEFINED,
      int width = DEFAULT_WINDOW_WIDTH,
      int height = DEFAULT_WINDOW_HEIGHT,
      Uint32 flags = DEFAULT_WINDOW_FLAGS
  );
  void startMainLoop();

 private:
  void close();

  std::string m_pathAssets;
  SDL_Window* m_window;
  int m_windowWidth;
  int m_windowHeight;
  SDL_Renderer* m_renderer;
  SDL_Surface* m_screenSurface;
};

} // namespace neon
