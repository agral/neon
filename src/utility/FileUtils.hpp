/**
 * Name: FileUtils.hpp
 * Description: Declares utility functions for filesystem-related tasks.
 * Created on: 09.03.2020
 * Last modified: 09.03.2020
 * Author: Adam Graliński (adam@gralin.ski)
 * License: MIT
 */

#pragma once

#include <string>

namespace neon::utility
{

extern bool directoryExists(const std::string& path);
extern bool getAssetsPath(std::string& output);

} // namespace neon::utility
