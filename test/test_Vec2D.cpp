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

  SECTION("Vec2D's constructor correctly assigns the member fields")
  {
    ::neon::Vec2D v(12, 34);
    CHECK(v.x() == 12);
    CHECK(v.y() == 34);
  }

  SECTION("operator== correctly tests Vec2D instances for equivalence")
  {
    ::neon::Vec2D v1a(12, 34);
    ::neon::Vec2D v2(56, 78);
    ::neon::Vec2D v1b(12, 34);

    CHECK(v1a == v1b);
    CHECK_FALSE(v1a == v2);
  }

  SECTION("operator!= correctly tests Vec2D instances for nonequivalence")
  {
    ::neon::Vec2D v1a(12, 34);
    ::neon::Vec2D v2(56, 78);
    ::neon::Vec2D v1b(12, 34);

    CHECK(v1a != v2);
    CHECK_FALSE(v1a != v1b);
  }
}
