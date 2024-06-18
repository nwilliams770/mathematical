#include "plane.hpp"

Plane::Plane(const Vec3& normal, float distance) : normal(normal), distance(distance) {}

void Plane::setFromPointNormal(const Vec3& point, const Vec3& normal)
{

}

bool Plane::isPointOnPositiveSide(const Vec3& point)
{

}

Vec3 Plane::getNormal() const { return normal; }

float Plane::getDistance() const { return distance; }