/**
 * Name: Timer.hpp
 * Description: Provides an interface to a class representing a timer/stopwatch.
 * Created on: 21.07.2019
 * Last modified: 21.07.2019
 * Author: Adam Graliński (adam@gralin.ski)
 * License: MIT
 */

#pragma once

#include <chrono>

namespace neon
{

typedef std::chrono::high_resolution_clock Clock;

class Timer
{
 public:
  Timer()
  : m_isStarted(false)
  {
  };

  void start();
  void stop();
  double time() const;
  bool isStarted() const { return m_isStarted; }

 private:
  std::chrono::time_point<Clock> m_startTimePoint;
  bool m_isStarted;
};

} // namespace neon
