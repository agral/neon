#include <gtest/gtest.h>
#include <chrono>
#include <thread>

#include "../src/Timer.hpp"

using ::neon::Timer;

TEST(TimerTest, TimerStoppedAfterConstructed) {
  // Given a default-constructed Timer,
  Timer t{};

  // Then it's in a stopped state.
  EXPECT_FALSE(t.isStarted());
}

TEST(TimerTest, TimerCanBeStartedAndStopped) {
  // Given a Timer,
  Timer t{};

  // When it is manually started,
  t.start();

  // Then it is in a started state.
  EXPECT_TRUE(t.isStarted());

  // And when it is manually stopped,
  t.stop();

  // Then it is in a stopped state.
  EXPECT_FALSE(t.isStarted());
}

TEST(TimerTest, TimerAccuratelyReportsElapsedTime) {
  // Given a Timer,
  Timer t{};

  // when it is started and then, after some period of time, stopped,
  auto beforeStart = neon::Clock::now();
  t.start();
  auto afterStart = neon::Clock::now();

  std::this_thread::sleep_for(std::chrono::milliseconds(200));

  auto beforeMeasurement = neon::Clock::now();
  double durationMeasured = t.time();
  auto afterMeasurement = neon::Clock::now();

  // then:
  // - the time elapsed from just before turning on the Timer instance until just after taking the measurement
  //   should be greater than or equal to the duration measured by the Timer instance
  double duration1 = std::chrono::duration_cast<std::chrono::nanoseconds>(
      afterMeasurement - beforeStart).count() / 1'000'000'000.0;
  EXPECT_TRUE(duration1 >= durationMeasured);

  // - the time elapsed from just after turning on the Timer instance until just before taking the measurement
  //   should be smaller than or equal to the duration measured by the Timer instance
  double duration2 = std::chrono::duration_cast<std::chrono::nanoseconds>(
      beforeMeasurement - afterStart).count() / 1'000'000'000.0;
  EXPECT_TRUE(duration2 <= durationMeasured);
}
