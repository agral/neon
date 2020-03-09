/**
 * Name: FileUtils.cpp
 * Description: Implements utility functions for filesystem-related tasks.
 * Created on: 09.03.2020
 * Last modified: 09.03.2020
 * Author: Adam Graliński (adam@gralin.ski)
 * License: MIT
 */

#include "FileUtils.hpp"

#include <limits.h>
#include <sys/stat.h>
#include <unistd.h>

namespace neon::utility
{

const char PATH_SEPARATOR = '/';
const std::string BIN_DIRECTORY_NAME = "bin";
const std::string ASSETS_DIRECTORY_NAME = "assets";

bool directoryExists(const std::string& path)
{
  struct stat info;
  return ((stat(path.c_str(), &info) == 0) && (info.st_mode & S_IFDIR));
}

bool getAssetsPath(std::string& output)
{
  char buffer[PATH_MAX];
  ssize_t count = ::readlink("/proc/self/exe", buffer, PATH_MAX);
  if (count > 0) {
    auto tmp = std::string(buffer, count);
    auto pos = tmp.rfind(PATH_SEPARATOR + BIN_DIRECTORY_NAME + PATH_SEPARATOR);
    if (pos != std::string::npos)
    {
      output = std::string(buffer, pos) + PATH_SEPARATOR + ASSETS_DIRECTORY_NAME + PATH_SEPARATOR;
      return directoryExists(output);
    }
  }
  return false;
}

} // namespace neon::utility
