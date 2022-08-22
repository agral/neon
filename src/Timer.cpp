#include "Timer.hpp"

namespace neon
{

void Timer::start()
{
  m_startTimePoint = Clock::now();
  m_isStarted = true;
}

void Timer::stop()
{
  m_isStarted = false;
}

double Timer::time() const
{
  double result = -1.0;
  if (m_isStarted)
  {
    Clock::time_point t = Clock::now();
    result = std::chrono::duration_cast<std::chrono::nanoseconds>(t - m_startTimePoint).count() / 1000000000.0;
  }
  return result;
}

} // namespace neon
