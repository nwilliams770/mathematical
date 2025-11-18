#ifndef PLANE_HPP
#define PLANE_HPP

#include "vec3.hpp"

class Plane
{
  public:
    Plane(const Vec3& normal, float distance) : normal(normal), distance(distance) {}

    Vec3 getNormal() const { return normal; }
    float getDistance() const { return distance; }
    Vec3 getPointOnPlane() const
    {
      return normal * distance;
    }

    float distanceToPoint(const Vec3& point) const
    {
      return normal.dot(point) + distance;
    }

    void normalize()
    {
      float length = normal.magnitude();
      normal = normal / length;
      distance = distance / length;
    }

  private:
    Vec3 normal;
    float distance;
};

#endif