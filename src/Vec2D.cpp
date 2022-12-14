#include "Vec2D.hpp"

#include <cmath>
#include <sstream>

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

//// Operators' implementation: ////
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

Vec2D& Vec2D::operator/=(double k)
{
  this->m_x /= k;
  this->m_y /= k;
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

Vec2D operator*(Vec2D v, double factor)
{
  v *= factor;
  return v;
}

Vec2D operator*(double factor, Vec2D v)
{
  return v * factor;
}

Vec2D operator/(Vec2D v, double k)
{
  v /= k;
  return v;
}
//// End of operators' implementation. ////

double Vec2D::magnitude() const
{
  return std::sqrt((m_x * m_x) + (m_y * m_y));
}

std::string Vec2D::toString() const
{
  std::stringstream ss;
  ss << "(" << m_x << ", " << m_y << ")";
  return ss.str();
}


} // namespace neon
