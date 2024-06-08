#ifndef VEC3_HPP
#define VEC3_HPP

#include <cmath>
#include <stdexcept>
#include "logging.hpp"

class Vec3
{
  public:
    float x, y, z;

    Vec3(float x = 0.0f, float y = 0.0f, float z = 0.0f ) : x(x), y(y), z(z) {};

    Vec3 operator+(const Vec3& other) const
    {
      return Vec3(x + other.x, y + other.y, z + other.z);
    }

    Vec3 operator-(const Vec3& other) const
    {
      return Vec3(x - other.x, y - other.y, z - other.z);
    }

    Vec3 operator*(float scalar) const
    {
      return Vec3(x * scalar, y * scalar, z * scalar);
    }

    Vec3 operator/(float scalar) const
    {
      if (scalar == 0) {
        throw std::runtime_error("Division by zero");
      }
      return Vec3(x / scalar, y / scalar, z / scalar);
    }

    Vec3& normalize()
    {
      float magnitude = std::sqrt(x * x + y * y + z * z);
      if (magnitude > 0)
      {
        x /= magnitude;
        y /= magnitude;
        z /= magnitude;
      } else {
        LOG("Attempted to normalize a zero-length vector");
      }
      return *this;
    }
};

#endif