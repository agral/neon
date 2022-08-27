#include <gtest/gtest.h>
#include <cmath>

#include "../src/Vec2D.hpp"

using ::neon::Vec2D;

namespace {
class Vec2DTest: public ::testing::Test {
public:
  static constexpr double m_x{1.0};
  static constexpr double m_y{2.0};

protected:
  Vec2D m_vec;

  virtual void SetUp() override {
    m_vec = Vec2D{m_x, m_y};
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

// --- Tests of Vec2D's comparison operators:
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

TEST_F(Vec2DTest, OperatorNotEquals) {
  // Given two extra Vec2D instances, one of which has the same field values as the default one;
  Vec2D v1{m_vec.x(), m_vec.y()};
  // and the second one has different values as the default,
  Vec2D v2{m_vec.x() + 1.0, m_vec.y() + 1.0};

  // When comparing these instances,
  // Then the first should not be deemed not equal to the original one, and the second one should be deemed not equal.
  EXPECT_FALSE(m_vec != v1);
  EXPECT_TRUE(m_vec != v2);
}
// --- End of tests of Vec2D1s comparison operators.

// --- Tests of Vec2D's arithmetic operators:
TEST_F(Vec2DTest, OperatorBinaryPlus) {
  // Given an extra Vec2D instance,
  Vec2D another{3.0, 5.0};

  // When the sum of both vectors is computed using an overloaded operator+,
  Vec2D sum{m_vec + another};

  // Then the individual fields of the created instance are a sum of the components' relevant fields.
  EXPECT_EQ(sum.x(), m_vec.x() + another.x());
  EXPECT_EQ(sum.y(), m_vec.y() + another.y());
}

TEST_F(Vec2DTest, OperatorPlusEquals) {
  // Given an extra Vec2D instance and remembering its original dimensions,
  double x{3.0}, y{5.0};
  Vec2D another{x, y};

  // When the default instance is added to this instance using an overloaded operator+=,
  another += m_vec;

  // Then the individual fields of the modified instance are each increased accordingly.
  EXPECT_EQ(another.x(), x + m_vec.x());
  EXPECT_EQ(another.y(), y + m_vec.y());
}

TEST_F(Vec2DTest, OperatorUnaryMinus) {
  // Given a Vec2D instance constructed in a SetUp method,
  // When another instance is created using a copy constructor with that instance negated,
  Vec2D another{-m_vec};

  // Then each of the dimensions of the new Vec2D is equal to the negation of the corresponding dimension
  // of the original Vec2D instance.
  EXPECT_EQ(another.x(), -m_vec.x());
  EXPECT_EQ(another.y(), -m_vec.y());
}

TEST_F(Vec2DTest, OperatorBinaryMinus) {
  // Given an extra Vec2D instance,
  Vec2D another{3.0, 5.0};

  // When the difference of both vectors is computed using an overloaded operator-,
  Vec2D diff{m_vec - another};

  // Then the individual fields of the created instance are each a difference of the relevant fields
  // of these two instances.
  EXPECT_EQ(diff.x(), m_vec.x() - another.x());
  EXPECT_EQ(diff.y(), m_vec.y() - another.y());
}

TEST_F(Vec2DTest, OperatorMinusEquals) {
  // Given an extra Vec2D instance and remembering its original dimensions,
  double x{3.0}, y{5.0};
  Vec2D another{x, y};

  // When the default instance is subtracted from this instance using an overloaded operator-=,
  another -= m_vec;

  // Then the individual fields of the modified instance are each decreased accordingly.
  EXPECT_EQ(another.x(), x - m_vec.x());
  EXPECT_EQ(another.y(), y - m_vec.y());
}

TEST_F(Vec2DTest, OperatorMulDouble) {
  // Given an instance of a Vec2D created in a SetUp method and a scale factor,
  double factor{3.0};

  // When a new instance is created with the original value multiplied by this factor
  // using an overloaded operator*,
  Vec2D another{m_vec * factor};

  // Then the individual fields of the created instance are each a product
  // of the relevant fields of the original instance and the factor.
  EXPECT_EQ(another.x(), m_vec.x() * factor);
  EXPECT_EQ(another.y(), m_vec.y() * factor);
}

TEST_F(Vec2DTest, OperatorMulEqualsDouble) {
  // Given an instance of a Vec2D created in a SetUp method and a scale factor
  double factor{3.0};

  // When it is multiplied by that factor using an overloaded operator*=,
  m_vec *= factor;

  // Then the individual fields are each a product
  // of their original values and the factor.
  EXPECT_EQ(m_vec.x(), Vec2DTest::m_x * factor);
  EXPECT_EQ(m_vec.y(), Vec2DTest::m_y * factor);
}

TEST_F(Vec2DTest, OperatorDivDouble) {
  // Given an instance of a Vec2D created in a SetUp method and a value to divide it by,
  double divisor{3.0};

  // When a new instance is created with the original value divided by this divisor
  // using an overloaded operator/,
  Vec2D another{m_vec / divisor};

  // Then the individual fields of the created instance are each a quotient
  // of the relevant fields of the original instance and the divisor.
  EXPECT_EQ(another.x(), m_vec.x() / divisor);
  EXPECT_EQ(another.y(), m_vec.y() / divisor);
}

TEST_F(Vec2DTest, OperatorDivEqualsDouble) {
  // Given an instance of a Vec2D created in a SetUp method and a value to divide it by,
  double divisor{3.0};

  // When it is divided by that divisor using an overloaded operator/=,
  m_vec /= divisor;

  // Then the individual fields are each a quotient
  // of their original values divided by the divisor.
  EXPECT_EQ(m_vec.x(), Vec2DTest::m_x / divisor);
  EXPECT_EQ(m_vec.y(), Vec2DTest::m_y / divisor);
}
// --- End of tests of Vec2D's arithmetic operators.

TEST_F(Vec2DTest, MagnitudeIsCorrectlyCalculated) {
  // Given an instance of a Vec2D created in a SetUp method,
  // When its magnitude is calculated,
  // Then the returned value matches the formula for the hypotenuse of a right triangle.
  EXPECT_EQ(m_vec.magnitude(), std::sqrt((m_vec.x() * m_vec.x()) + (m_vec.y() * m_vec.y())));
}
