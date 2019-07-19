/**
 * Name: Vec2D.cpp
 * Description: Implements a class representing a vector on a 2D plane.
 * Created on: 19.07.2019
 * Last modified: 19.07.2019
 * Author: Adam Graliński (adam@gralin.ski)
 * License: MIT
 */

#include "Vec2D.hpp"

#include <cmath>

namespace neon
{

Vec2D::Vec2D(double x, double y)
: m_x(x)
, m_y(y)
{
}

bool operator==(const Vec2D& lhs, const Vec2D& rhs)
{
  // TODO implement
  return false;
}

bool operator!=(const Vec2D& lhs, const Vec2D& rhs)
{
  // TODO implement
  return false;
}

} // namespace neon
