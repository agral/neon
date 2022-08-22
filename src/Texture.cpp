#include "Texture.hpp"
#include <SDL2/SDL_image.h>
#include "log/Logger.hpp"

namespace neon
{

Texture::Texture()
: texture_(nullptr)
, renderer_(nullptr)
, width_(0)
, height_(0)
{
}

Texture::~Texture()
{
  // texture_ is an owning pointer, but it might not have been allocated. Frees the texture if allocated.
  if (texture_ != nullptr)
  {
    SDL_DestroyTexture(texture_);
    texture_ = nullptr;
  }

  // renderer_ is a non-owning pointer to the window renderer.
  renderer_ = nullptr;
}

bool Texture::loadFromFile(const std::string& path, SDL_Renderer* renderer)
{
  if (renderer == nullptr) {
    LOG(log::ERROR) << "Can not create a texture without a dedicated renderer.";
    return false;
  }

  const char* cpath = path.c_str();
  SDL_Surface* surface = IMG_Load(cpath);
  if (surface == nullptr) {
    LOG(log::ERROR) << "Image from file [" << path << "] could not be loaded.";
    LOG(log::ERROR) << "SDL error: " << SDL_GetError();
    return false;
  }

  texture_ = SDL_CreateTextureFromSurface(renderer, surface);
  if (texture_ == nullptr) {
    LOG(log::ERROR) << "Unable to create texture from surface [" << path << "].";
    LOG(log::ERROR) << "SDL error: " << SDL_GetError();
    return false;
  }
  SDL_SetTextureBlendMode(texture_, SDL_BLENDMODE_BLEND);
  width_ = surface->w;
  height_ = surface->h;
  renderer_ = renderer;
  SDL_FreeSurface(surface);

  LOG(log::VERBOSE) << "Created a texture from file [" << path << "], renderer = " << renderer_;

  return true;
}

void Texture::render(
    int x,
    int y,
    SDL_Rect* clip,
    double angle,
    SDL_Point* center,
    SDL_RendererFlip flip
) const
{
  LOG(log::VERBOSE) << "[Texture] Render(), renderer = " << renderer_
      << ",\nTexture = " << texture_
      << ",\nX: " << x << ", Y: " << y
      << "\n, width = " << width_ << ", height = " << height_;
  SDL_Rect targetBox = {x, y, width_, height_};

  if (clip != nullptr) {
    targetBox.w = clip->w;
    targetBox.h = clip->h;
  }

  SDL_RenderCopyEx(renderer_, texture_, clip, &targetBox, angle, center, flip);
}

int Texture::width() const
{
  return width_;
}

int Texture::height() const
{
  return height_;
}

} // namespace neon
