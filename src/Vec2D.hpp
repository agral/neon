/**
 * Name: Vec2D.hpp
 * Description: Provides an interface to a class representing a vector on a 2D plane.
 * Created on: 18.07.2019
 * Last modified: 19.07.2019
 * Author: Adam Graliński (adam@gralin.ski)
 * License: MIT
 */

#pragma once

namespace neon
{

class Vec2D
{
 public:
  Vec2D(double x = 0.0, double y = 0.0);
  Vec2D(const Vec2D& other);
  Vec2D& operator=(const Vec2D& other);
  Vec2D& operator+=(const Vec2D& other);
  Vec2D& operator-=(const Vec2D& other);
  Vec2D& operator*=(double k);

  double x() const { return m_x; }
  double y() const { return m_y; }
  void setX(double newX) { m_x = newX; }
  void setY(double newY) { m_y = newY; }
  void setXY(double newX, double newY) { m_x = newX; m_y = newY; }

  friend bool operator==(const Vec2D& lhs, const Vec2D& rhs);
  friend bool operator!=(const Vec2D& lhs, const Vec2D& rhs);
  friend Vec2D operator-(const Vec2D& v);

 private:
  double m_x;
  double m_y;
};

bool operator==(const Vec2D& lhs, const Vec2D& rhs);
bool operator!=(const Vec2D& lhs, const Vec2D& rhs);
Vec2D operator+(Vec2D lhs, const Vec2D& rhs);
Vec2D operator-(const Vec2D& v);
Vec2D operator-(Vec2D lhs, const Vec2D& rhs);
Vec2D operator*(const Vec2D& lhs, double k);

} // namespace neon
