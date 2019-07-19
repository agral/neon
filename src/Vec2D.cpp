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

Vec2D::Vec2D(const Vec2D& other)
: m_x(other.m_x)
, m_y(other.m_y)
{
}

Vec2D& Vec2D::operator=(const Vec2D& other)
{
  // TODO implement
  return *this;
}

bool operator==(const Vec2D& lhs, const Vec2D& rhs)
{
  return ((lhs.m_x == rhs.m_x) && (lhs.m_y == rhs.m_y));
}

bool operator!=(const Vec2D& lhs, const Vec2D& rhs)
{
  return !operator==(lhs, rhs);
}

} // namespace neon
