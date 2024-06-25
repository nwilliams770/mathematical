#include "plane.hpp"

Plane::Plane(const Vec3& normal, float distance) :
  normal(normal), distance(distance) {}

void Plane::setFromPointNormal(const Vec3& point, const Vec3& newNormal)
{
  normal = newNormal.normalized();
  distance = normal.dot(point);
}

bool Plane::isPointOnPositiveSide(const Vec3& point)
{
  // Project onto the normal vector
  float dotProduct = normal.dot(point);

  // Geometrically, this means the point is further along the direction of the
  // normal vector than the plane itself.
  if (dotProduct > distance) { return true; }

  // point is on negative side or on the plane
  return false;
}