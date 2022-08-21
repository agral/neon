/**
 * Name: test_Timer.cpp
 * Description: Contains the unit tests for neon::Timer class implementation.
 * Created on: 21.07.2019
 * Last modified: 21.07.2019
 * Author: Adam Graliński (adam@gralin.ski)
 * License: MIT
 */

#include <catch2/catch.hpp>
#include <chrono>
#include <thread>
#include "../src/Timer.hpp"

TEST_CASE("Timer class correctly implements its features")
{
  SECTION("Timer is in stopped state after being initialized")
  {
    ::neon::Timer t;
    CHECK(t.isStarted() == false);
  }

  SECTION("Timer can be started and stopped")
  {
    ::neon::Timer t;
    t.start();
    CHECK(t.isStarted() == true);
    t.stop();
    CHECK(t.isStarted() == false);
  }

  SECTION("Timer accurately reports the elapsed time")
  {
    ::neon::Timer t;
    std::chrono::time_point<neon::Clock> beforeStart = neon::Clock::now();
    t.start();
    std::chrono::time_point<neon::Clock> afterStart = neon::Clock::now();

    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    std::chrono::time_point<neon::Clock> beforeMeas = neon::Clock::now();
    double durT = t.time();
    std::chrono::time_point<neon::Clock> afterMeas = neon::Clock::now();
    t.stop();

    double dur1 = std::chrono::duration_cast<std::chrono::nanoseconds>(afterMeas - beforeStart).count() / 1000000000.0;
    double dur2 = std::chrono::duration_cast<std::chrono::nanoseconds>(beforeMeas - afterStart).count() / 1000000000.0;

    // dur1 is the time elapsed from before turning on the Timer until just after taking the measurement.
    // This implies that dur1 should be greater than or equal to durT measured by the Timer.
    CHECK(dur1 >= durT);

    // dur2 is the time elapsed from after turning on the Timer until just before taking the measurement.
    // This implies that dur2 should be equal to or less than durT measured by the Timer.
    CHECK(dur2 <= durT);
  }
}
