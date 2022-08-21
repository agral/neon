#include "FileUtils.hpp"

#include <filesystem>

#include "log/Logger.hpp"

namespace neon::utility {

const std::string ASSETS_DIRECTORY_NAME {"assets"};

std::optional<std::string> getAssetsPath()
{
  // TODO: add Windows support. This works only on Linux.
  try {
    auto executable_file {std::filesystem::canonical("/proc/self/exe")};
    auto executable_path {executable_file.parent_path()};
    LOG(log::VERBOSE) << "Exe path: " << executable_path;
    auto root_path {executable_path.parent_path()};
    LOG(log::VERBOSE) << "Root path: " << root_path;

    auto maybe_assets_path = root_path;
    maybe_assets_path += "/" + ASSETS_DIRECTORY_NAME + "/";
    LOG(log::VERBOSE) << "Trying assets path: " << maybe_assets_path;

    if (std::filesystem::is_directory(maybe_assets_path)) {
      LOG(log::DEBUG) << "Successfully found assets path: " << maybe_assets_path;
      return {maybe_assets_path.string()};
    }
  }
  catch (...) {
    // in case of any errors, just return an empty optional (below).
  }
  return {};
}

} // namespace neon::utility
