/**
 * Name: test_Timer.cpp
 * Description: Contains the unit tests for neon::Timer class implementation.
 * Created on: 21.07.2019
 * Last modified: 21.07.2019
 * Author: Adam Graliński (adam@gralin.ski)
 * License: MIT
 */

#include <catch2/catch.hpp>
#include "../src/Timer.hpp"

TEST_CASE("Timer class correctly implements its features")
{
  SECTION("Timer can be started and stopped")
  {
    ::neon::Timer t;
    t.start();
    CHECK(t.isStarted() == true);
    t.stop();
    CHECK(t.isStarted() == false);
  }
}
