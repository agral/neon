/**
 * Name: Timer.cpp
 * Description: Implements a class representing a timer/stopwatch.
 * Created on: 21.07.2019
 * Last modified: 21.07.2019
 * Author: Adam Graliński (adam@gralin.ski)
 * License: MIT
 */

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
