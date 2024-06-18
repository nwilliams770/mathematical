#ifndef PLANE_HPP
#define PLANE_HPP

#include "vec3.hpp"

class Plane
{
  public:
    Plane(const Vec3& normal = Vec3(), float distance = 0.0f);

    void setFromPointNormal(const Vec3& point, const Vec3& normal);

    bool isPointOnPositiveSide(const Vec3& point);

    Vec3 getNormal() const;
    float getDistance() const;

  private:
    Vec3 normal;
    float distance;
};

#endif