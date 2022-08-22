#pragma once

#include <map>
#include <string>
#include "Texture.hpp"

namespace neon
{

class TextureManager
{
 public:
  TextureManager(SDL_Renderer* renderer);
  ~TextureManager();

  bool loadMedia(const std::string& pathAssets, SDL_Renderer* renderer);
  bool loadFromFile(const std::string& key, const std::string& texturePath);
  Texture operator[](const std::string& key);
  const Texture& logo() { return logo_; }

 private:
  SDL_Renderer* renderer_;
  std::map<std::string, Texture> textures_;
  Texture logo_;
};

} // namespace neon
