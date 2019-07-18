/**
 * Name: Logger.hpp
 * Description: Provides an interface of a simple logging utility.
 * Created on: 16.07.2019
 * Last modified: 18.07.2019
 * Author: Adam Graliński (adam@gralin.ski)
 * License: MIT
 */

#pragma once

#include <sstream>

#define LOG(level) if (level <= ::neon::log::Logger::s_cutoutLevel) ::neon::log::Logger().get(level)

namespace neon::log
{

enum LogLevel {
  CRITICAL,
  ERROR,
  WARNING,
  INFO,
  DEBUG,
  VERBOSE
};

class Logger
{
 public:
  static LogLevel s_cutoutLevel;

  Logger(const Logger&) = delete;
  Logger& operator=(const Logger&) = delete;
  Logger() {};

  virtual ~Logger();
  std::ostringstream& get(LogLevel level = INFO);

 private:
  std::ostringstream m_os;
};

} // namespace neon::log
