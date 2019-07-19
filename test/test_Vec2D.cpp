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

  SECTION("Vec2D's copy constructor correctly assigns the member fields")
  {
    ::neon::Vec2D original(12, 34);
    ::neon::Vec2D another(original);
    CHECK(another.x() == original.x());
    CHECK(another.y() == original.y());
  }

  SECTION("Vec2D's assignment operator correctly assigns values from other instance")
  {
    ::neon::Vec2D v1(12, 34);
    ::neon::Vec2D v2(56, 78);
    v1 = v2;
    CHECK(v1.x() == v2.x());
    CHECK(v1.y() == v2.y());

    // Also assures that the original vector has not been modified:
    CHECK(v2.x() == 56);
    CHECK(v2.y() == 78);
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

  //// Arithmetic operators' tests: ////
  SECTION("operator+ works correctly")
  {
    double a = 12, b = 34, c = 56, d = 78;
    ::neon::Vec2D v(a, b), w(c, d);

    ::neon::Vec2D s = v + w;

    CHECK(s.x() == a + c);
    CHECK(s.y() == b + d);
  }

  SECTION("operator+= works correctly")
  {
    double a = 21, b = 43, c = 65, d = 87;
    ::neon::Vec2D v(a, b), w(c, d);
    v += w;

    CHECK(v.x() == a + c);
    CHECK(v.y() == b + d);
  }

  SECTION("unary minus operator works correctly")
  {
    double a = 12, b = 34;
    ::neon::Vec2D v(a, b);
    ::neon::Vec2D w = -v;
    CHECK(w.x() == -a);
    CHECK(w.y() == -b);
  }

  SECTION("operator- works correctly")
  {
    double a = 12, b = 34, c = 56, d = 78;
    ::neon::Vec2D v(a, b), w(c, d);
    ::neon::Vec2D s = v - w;
    CHECK(s.x() == a - c);
    CHECK(s.y() == b - d);
  }

  SECTION("operator-= works correctly")
  {
    double a = 12, b = 34, c = 56, d = 78;
    ::neon::Vec2D v(a, b), w(c, d);
    v -= w;
    CHECK(v.x() == a - c);
    CHECK(v.y() == b - d);
  }
}
