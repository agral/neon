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
  void setBackgroundFillColor(SDL_Color clBackgroundFill);

 private:
  void close();

  std::string pathAssets_;
  SDL_Window* window_;
  int windowWidth_;
  int windowHeight_;
  SDL_Renderer* renderer_;
  SDL_Surface* screenSurface_;
  SDL_Color clBackgroundFill_;
};

} // namespace neon
