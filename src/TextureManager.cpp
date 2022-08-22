#include "TextureManager.hpp"
#include "log/Logger.hpp"

namespace neon
{

TextureManager::TextureManager(SDL_Renderer* renderer)
: renderer_(renderer)
, textures_{}
{
  if (renderer_ == nullptr) {
    LOG(log::CRITICAL) << "nullptr passed as renderer in TextureManager's constructor. Throwing.";
    throw -1;
  }
}

TextureManager::~TextureManager()
{
  // No need to deallocate memory manually as it is already cleaned up by Texture's destructors.
}

bool TextureManager::loadMedia(const std::string& pathAssets, SDL_Renderer* renderer)
{
  if (!logo_.loadFromFile(pathAssets + "neon_logo.png", renderer)) {
    LOG(log::ERROR) << "Failed to load the neon logo file";
    return false;
  }
  return true;
}

bool TextureManager::loadFromFile(const std::string& key, const std::string& path)
{
  auto it = textures_.find(key);
  if (it != textures_.end())
  {
    LOG(log::WARNING) << "[TextureManager] Reusing key \"" << key << "\" - old contents will be dropped.";
  }

  Texture t;
  auto isSuccessful = t.loadFromFile(path, renderer_);
  if (isSuccessful)
  {
    textures_[key] = t;
  }

  return isSuccessful;
}

Texture TextureManager::operator[](const std::string& key)
{
  auto it = textures_.find(key);

  // In case of nonexistent key, logs and returns a default value (Neon project logo).
  if (it == textures_.end()) {
    LOG(log::WARNING) << "[TextureManager] Reading from unset key \"" << key << "\".";
    return logo_;
  }

  return textures_.at(key);
}

} // namespace neon
