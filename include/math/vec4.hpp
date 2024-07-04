#ifndef VEC4_HPP
#define VEC4_HPP

#include "logging.hpp"
#include "vec3.hpp"

class Vec4
{
  public:
    float x, y, z, w;

    Vec4(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 1.0f)
      : x(x), y(y), z(z), w(w) {};
    Vec4(const Vec3& vec, float w) : x(vec.x), y(vec.y), z(vec.z), w(w) {}

    Vec4 operator+(const Vec4& other) const {
      return Vec4(x + other.x, y + other.y, z + other.z, w); // w remains unchanged
    }

    Vec4 operator-(const Vec4& other) const {
      return Vec4(x - other.x, y - other.y, z - other.z, w); // w remains unchanged
    }

    Vec4 operator*(float scalar) const {
      return Vec4(x * scalar, y * scalar, z * scalar, w); // w remains unchanged
    }

    Vec4& operator/=(float scalar) {
      x /= scalar;
      y /= scalar;
      z /= scalar;
      w /= scalar; // w should also be scaled for perspective divide
      return *this;
    }

    inline float magnitude() const {
      return std::sqrt(x * x + y * y + z * z + w * w);
    }

    Vec4& normalize()
    {
      float magnitude = this->magnitude();
      if (magnitude > 0)
      {
        x /= magnitude;
        y /= magnitude;
        z /= magnitude;
        w /= magnitude;
      } else {
        // LOG("Attempted to normalize a zero-length vector");
      }
      return *this;
    }

    Vec4 normalized() const
    {
      float magnitude = this->magnitude();
      if (magnitude > 0)
      {
        return Vec4(x / magnitude, y / magnitude, z / magnitude, w / magnitude);
      } else {
        // LOG("Attempted to normalize a zero-length vector");
        return Vec4();
      }
    }


};

#endif