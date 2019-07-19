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
  if (this != &other)
  {
    m_x = other.m_x;
    m_y = other.m_y;
  }
  return *this;
}

Vec2D& Vec2D::operator+=(const Vec2D& other)
{
  this->m_x += other.m_x;
  this->m_y += other.m_y;
  return *this;
}

Vec2D& Vec2D::operator-=(const Vec2D& other)
{
  this->m_x -= other.m_x;
  this->m_y -= other.m_y;
  return *this;
}

Vec2D& Vec2D::operator*=(double k)
{
  this->m_x *= k;
  this->m_y *= k;
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

Vec2D operator+(Vec2D lhs, const Vec2D& rhs)
{
  lhs += rhs;
  return lhs;
}

Vec2D operator-(const Vec2D& v)
{
  return Vec2D(-v.m_x, -v.m_y);
}

Vec2D operator-(Vec2D lhs, const Vec2D& rhs)
{
  lhs -= rhs;
  return lhs;
}

Vec2D operator*(const Vec2D& v, double k)
{
  return Vec2D(v.x() * k, v.y() * k);
}

} // namespace neon
