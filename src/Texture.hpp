#pragma once

#include <SDL2/SDL.h>
#include <string>

namespace neon
{

class Texture
{
 public:
  Texture();
  ~Texture();
  bool loadFromFile(const std::string& path, SDL_Renderer* renderer);
  void render(
      int x,
      int y,
      SDL_Rect* clip = nullptr,
      double angle = 0.0,
      SDL_Point* center = nullptr,
      SDL_RendererFlip flip = SDL_FLIP_NONE
  ) const;
  int width() const;
  int height() const;

 private:
  SDL_Texture* texture_;
  SDL_Renderer* renderer_;
  int width_;
  int height_;
};

} // namespace neon
