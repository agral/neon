#include "Logger.hpp"

namespace neon::log
{

LogLevel Logger::s_cutoutLevel = VERBOSE;

std::string levelToString(LogLevel level)
{
  if (level == VERBOSE)
  {
    return "V";
  }
  else if (level == DEBUG)
  {
    return "D";
  }
  else if (level == INFO)
  {
    return "I";
  }
  else if (level == WARNING)
  {
    return "W";
  }
  else if (level == ERROR)
  {
    return "E";
  }

  return "C";
}

Logger::~Logger()
{
  m_os << std::endl;
  fprintf(stdout, "%s", m_os.str().c_str());
  fflush(stdout);
}

std::ostringstream& Logger::get(LogLevel level)
{
  m_os << "[" << levelToString(level) << "] ";
  return m_os;
}

} // namespace neon::log
