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
  double x() const { return m_x; }
  double y() const { return m_y; }
  void setX(double newX) { m_x = -1; } // TODO implement
  void setY(double newY) { m_y = -1; } // TODO implement
  void setXY(double newX, double newY) { m_x = -1; m_y = -1; } // TODO implement

 private:
  double m_x;
  double m_y;
};

} // namespace neon
