#include <gtest/gtest.h>
#include <cmath>

#include "../src/Vec2D.hpp"

using ::neon::Vec2D;

namespace {
class Vec2DTest: public ::testing::Test {
protected:
  Vec2D m_vec;

  virtual void SetUp() override {
    m_vec = Vec2D{1.0, 2.0};
  }
};
} // end of anonymous namespace

TEST_F(Vec2DTest, ConstructorAssignsMemberFields) {
  // Given a Vec2D instance, when constructed using explicit values in SetUp method,
  // Then the instance's fields match the arguments provided to a constructor.
  ASSERT_EQ(m_vec.x(), 1.0);
  ASSERT_EQ(m_vec.y(), 2.0);
}

TEST_F(Vec2DTest, CopyConstructorAssignsMemberFields) {
  // Given an existing Vec2D instance,
  // When a new Vec2D is instantiated from that existing instance,
  Vec2D copy{m_vec};

  // Then that new instance's fields match the fields of the original instance.
  ASSERT_EQ(m_vec.x(), copy.x());
  ASSERT_EQ(m_vec.y(), copy.y());
}

TEST_F(Vec2DTest, AssignmentOperatorAssignsMemberFields) {
  // Given two existing Vec2D instances
  Vec2D other{};

  // When one of these instances is assigned to from the other,
  other = m_vec;

  // Then that instance's member fields match the fields of the source instance.
  ASSERT_EQ(m_vec.x(), other.x());
  ASSERT_EQ(m_vec.y(), other.y());
}

TEST_F(Vec2DTest, SettersUpdateTheValueOfMemberFields) {
  m_vec.setX(3.0);
  EXPECT_EQ(m_vec.x(), 3.0);

  m_vec.setY(4.0);
  EXPECT_EQ(m_vec.y(), 4.0);

  m_vec.setXY(5.0, 6.0);
  EXPECT_EQ(m_vec.x(), 5.0);
  EXPECT_EQ(m_vec.y(), 6.0);
}


// Tests of Vec2D's comparison operators:
TEST_F(Vec2DTest, OperatorEquals) {
  // Given two extra Vec2D instances, one of which has the same field values as the default one;
  Vec2D v1{m_vec.x(), m_vec.y()};
  // and the second one has different values as the default,
  Vec2D v2{m_vec.x() + 1.0, m_vec.y() + 1.0};

  // When comparing these instances,
  // Then the first should be deemed equal to the original one, and the second one not equal.
  EXPECT_TRUE(m_vec == v1);
  EXPECT_FALSE(m_vec == v2);
}


/*
TEST_CASE("Vec2D class correctly implements its features")
{
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

  SECTION("operator*(double) works correctly")
  {
    double a = 12, b = 34, k = 5;
    ::neon::Vec2D v(a, b);
    ::neon::Vec2D w = v * k;
    CHECK(w.x() == a * k);
    CHECK(w.y() == b * k);
  }

  SECTION("operator*=(double) works correctly")
  {
    double a = 12, b = 34, k = 7;
    ::neon::Vec2D v(a, b);
    v *= k;
    CHECK(v.x() == a * k);
    CHECK(v.y() == b * k);
  }

  SECTION("operator/(double) works correctly")
  {
    double a = 12, b = 36, k = 4;
    ::neon::Vec2D v(a, b);
    ::neon::Vec2D w = v / k;
    CHECK(w.x() == a / k);
    CHECK(w.y() == b / k);
  }

  SECTION("operator/=(double) works correctly")
  {
    double a = 12, b = 36, k = 3;
    ::neon::Vec2D v(a, b);
    v /= k;
    CHECK(v.x() == a / k);
    CHECK(v.y() == b / k);
  }

  //// End of arithmetic operators' tests. ////

  SECTION("Vec2D's magnitude is correctly calculated")
  {
    double a = -3, b = -4;
    ::neon::Vec2D v1(a, b);
    CHECK(v1.magnitude() == std::sqrt((a * a) + (b * b)));
  }

  SECTION("Vec2D's toString() method correctly serializes the instances")
  {
    ::neon::Vec2D v(12, 34);
    CHECK(v.toString() == "(12, 34)");

    // Ensures that floating point values get serialized correctly as well:
    ::neon::Vec2D w(54.321, -9.876);
    CHECK(w.toString() == "(54.321, -9.876)");
  }
}
*/
