#include <catch2/catch.hpp>
#include "../src/Vec2D.hpp"

TEST_CASE("Vec2D class correctly implements its features")
{
  SECTION("Vec2D's setX, setY and setXY methods correctly set the member fields")
  {
    ::neon::Vec2D v;
    v.setX(12);
    REQUIRE(v.x() == 12);
    v.setY(34);
    REQUIRE(v.y() == 34);
    v.setXY(56, 78);
    REQUIRE(v.x() == 56);
    REQUIRE(v.y() == 78);
  }
}
