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
