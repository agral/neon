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
