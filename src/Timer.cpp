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
  m_isStarted = true;
}

void Timer::stop()
{
  m_isStarted = false;
}

} // namespace neon
