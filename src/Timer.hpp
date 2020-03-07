/**
 * Name: Timer.hpp
 * Description: Provides an interface to a class representing a timer/stopwatch.
 * Created on: 21.07.2019
 * Last modified: 06.03.2020
 * Author: Adam Graliński (adam@gralin.ski)
 * License: MIT
 */

#pragma once

#include <chrono>

namespace neon
{

using Clock = std::chrono::high_resolution_clock;

class Timer
{
 public:
  void start();
  void stop();
  double time() const;
  bool isStarted() const { return m_isStarted; }

 private:
  std::chrono::time_point<Clock> m_startTimePoint;
  bool m_isStarted = false;
};

} // namespace neon
