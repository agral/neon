/**
 * Name: Engine.hpp
 * Description: Provides an interface to a Neon rendering engine.
 * Created on: 26.07.2019
 * Last modified: 10.03.2020
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

  std::string pathAssets_;
  SDL_Window* window_;
  int windowWidth_;
  int windowHeight_;
  SDL_Renderer* renderer_;
  SDL_Surface* screenSurface_;
};

} // namespace neon
