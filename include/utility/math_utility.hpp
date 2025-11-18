#ifndef MATH_UTILITY_HPP
#define MATH_UTILITY_HPP

#include <vector>
#include "vec3.hpp"
#include "plane.hpp"

namespace MathUtility
{
  float inline lerp(float start, float end, float interpolationFactor)
  {
    return start + (end - start) * interpolationFactor;
  }
  std::vector<Vec3> sutherlandHodgmanClip(const std::vector<Vec3>& vertices, const Plane& plane);
}

std::vector<Vec3> MathUtility::sutherlandHodgmanClip(const std::vector<Vec3>& vertices, const Plane& plane) {
  std::vector<Vec3> clippedVertices;
  size_t numVertices = vertices.size();

  // Iterate over each edge of the polygon
  for (size_t i = 0; i < numVertices; ++i) {
    const Vec3& currentVertex = vertices[i];
    const Vec3& prevVertex = vertices[(i + numVertices - 1) % numVertices];

    // Calculate distances of vertices from the plane
    float currentDistance = plane.distanceToPoint(currentVertex);
    float prevDistance = plane.distanceToPoint(prevVertex);

    // Check if the vertices are inside the plane
    bool currentInside = currentDistance >= 0.0f;
    bool prevInside = prevDistance >= 0.0f;

    LOG_ARGS("Current Vertex:", currentVertex.x, currentVertex.y, currentVertex.z, "Distance:", currentDistance);
    LOG_ARGS("Previous Vertex:", prevVertex.x, prevVertex.y, prevVertex.z, "Distance:", prevDistance);
    LOG_ARGS("Current Inside:", currentInside, "Previous Inside:", prevInside);

    // Case 1: One vertex is inside, the other is outside
    if (currentInside != prevInside) {
      // Compute how far along the edge the intersection lies
      float interpolationFactor = prevDistance / (prevDistance - currentDistance);
      // Compute intersection point using the existing lerp function
      Vec3 intersection = Vec3(
          MathUtility::lerp(prevVertex.x, currentVertex.x, interpolationFactor),
          MathUtility::lerp(prevVertex.y, currentVertex.y, interpolationFactor),
          MathUtility::lerp(prevVertex.z, currentVertex.z, interpolationFactor)
      );
      LOG_ARGS("Intersection:", intersection.x, intersection.y, intersection.z);

      clippedVertices.push_back(intersection);
    }

    // Case 2: Current vertex is inside (it will be added to the list)
    if (currentInside) {
      clippedVertices.push_back(currentVertex);
    }
  }
  LOG("Clipped Vertices:");
  for (const auto& vertex : clippedVertices) {
      LOG_ARGS(vertex.x, vertex.y, vertex.z);
  }
  // Case 3: Both vertices are outside the frustum (handled implicitly as nothing is added to the list)
  return clippedVertices;
}

#endif