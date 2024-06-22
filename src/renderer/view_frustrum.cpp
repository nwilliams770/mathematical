#include "camera.hpp"
#include "view_frustrum.hpp"

#include <cmath>

// In a right-handed coordinate system, the right-hand rule states that if you
// point the index finger of your right hand in the direction of the first
// vector (a) and your middle finger in the direction of the second vector (b),
// your thumb points in the direction of the cross product (a×b).


ViewFrustrum::ViewFrustrum(float fieldOfViewYRadians, float aspectRatio, float nearClip, float farClip)
  : fieldOfViewYRadians(fieldOfViewYRadians), aspectRatio(aspectRatio), nearClip(nearClip), farClip(farClip)
{}

// Update the frustum based on the camera's position and orientation
// Generate inward-pointing view frustrum planes
void ViewFrustrum::update(const Camera& camera)
{
  Vec3 cameraPosition = camera.getPosition();
  Vec3 cameraDirection = camera.getDirection();
  Vec3 cameraUp = camera.getUp();
  Vec3 cameraRight = cameraDirection.cross(cameraUp);

  Vec3 nearClipCenter = cameraPosition + cameraDirection * nearClip;
  Vec3 farClipCenter = cameraPosition + cameraDirection * farClip;

  // tan(fov / 2) = (nearHeight / 2) / nearClip - solve for nearHeight
  float nearClipHeight = 2 * nearClip * std::tan(fieldOfViewYRadians / 2.0f);
  float nearClipWidth = nearClipHeight * aspectRatio;
  float farClipHeight = 2 * farClip * std::tan(fieldOfViewYRadians / 2.0f);
  float farClipWidth = farClipHeight * aspectRatio;

  Vec3 nearClipTopLeft = nearClipCenter +
    (cameraUp * (nearClipHeight / 2)) -
    (cameraRight * (nearClipWidth / 2));
  Vec3 nearClipTopRight = nearClipCenter +
    (cameraUp * (nearClipHeight / 2)) +
    (cameraRight * (nearClipWidth / 2));
  Vec3 nearClipBottomLeft = nearClipCenter -
    (cameraUp * (nearClipHeight / 2)) -
    (cameraRight * (nearClipWidth / 2));
  Vec3 nearClipBottomRight = nearClipCenter -
    (cameraUp * (nearClipHeight / 2)) +
    (cameraRight * (nearClipWidth / 2));

  Vec3 farClipTopLeft = farClipCenter +
    (cameraUp * (farClipHeight / 2)) -
    (cameraRight * (farClipWidth / 2));
  Vec3 farClipTopRight = farClipCenter +
    (cameraUp * (farClipHeight / 2)) +
    (cameraRight * (farClipWidth / 2));
  Vec3 farClipBottomLeft = farClipCenter -
    (cameraUp * (farClipHeight / 2)) -
    (cameraRight * (farClipWidth / 2));
  Vec3 farClipBottomRight = farClipCenter -
    (cameraUp * (farClipHeight / 2)) +
    (cameraRight * (farClipWidth / 2));

  // TODO: Maybe update to this https://gamedev.stackexchange.com/a/156758 More efficient and used in professional engines
  updatePlane(Near, nearClipCenter, cameraDirection);
  updatePlane(Far, farClipCenter, -cameraDirection);

  // Generate vector pointing from nearClipBottomLeft to nearClipTopLeft (upward)
  // and cross by vector pointing from nearClipTopLeft to farClipTopLeft (forward from the POV of the camera)
  // Crossing them, using right-hand rule results in a vector normal of the left plane
  // pointing inwards of the view frustrum
  Vec3 leftPlaneNormal = (nearClipTopLeft - nearClipBottomLeft).cross(farClipTopLeft - nearClipTopLeft).normalized();
  updatePlane(Left, nearClipTopLeft, leftPlaneNormal);

  // Generate vector pointing from nearClipTopRight to farClipTopRight (forward from the POV of the camera)
  // and cross by vector pointing from nearClipTopRight to nearClipBottomRight (downward)
  // Crossing them, using right-hand rule results in a vector normal of the right plane
  // pointing inwards of the view frustrum
  Vec3 rightPlaneNormal = (farClipTopRight - nearClipTopRight).cross(nearClipBottomRight - nearClipTopRight).normalized();
  updatePlane(Right, nearClipTopRight, rightPlaneNormal);

  // Generate vector pointing from nearClipTopLeft to nearClipTopRight (rightward)
  // and cross by vector pointing from nearClipTopLeft to farClipTopLeft (forward from the POV of the camera)
  // Crossing them, using right-hand rule results in a vector normal of the top plane
  // pointing inwards of the view frustrum
  Vec3 topPlaneNormal = (nearClipTopRight - nearClipTopLeft).cross(farClipTopLeft - nearClipTopLeft).normalized();
  updatePlane(Top, nearClipTopRight, topPlaneNormal);

  // Generate vector pointing from nearClipBottomLeft to farClipBottomLeft (forward from the POV of the camera)
  // and cross by vector pointing from nearClipBottomRight to nearClipBottomLeft (leftward)
  // Crossing them, using right-hand rule results in a vector normal of the bottom plane
  // pointing inwards of the view frustrum
  Vec3 bottomPlaneNormal = (farClipBottomLeft - nearClipBottomLeft).cross(nearClipBottomRight - nearClipBottomLeft).normalized();
  updatePlane(Bottom, farClipBottomRight, bottomPlaneNormal);
}

// Check if a point is inside the frustum
bool ViewFrustrum::isPointInside(const Vec3& point) const
{
  for (const auto& plane : planes)
  {
    // > 0 - point is on the 'positive side' - in the direction of the normal
    // = 0 - point is on the plane
    // < 0 - point is on the 'negative side' - opposite direction of the normal
    if (point.dot(plane.getNormal()) - plane.getDistance() < 0) return false;
  }
  return true;
}

// Check if an axis-aligned bounding box is inside the frustum
bool ViewFrustrum::isAABBInside(const Vec3& min, const Vec3& max) const
{
  std::array<Vec3, 8> vertices = {
    min,
    Vec3(min.x, min.y, max.z),
    Vec3(min.x, max.y, min.z),
    Vec3(min.x, max.y, max.z),
    Vec3(max.x, min.y, min.z),
    Vec3(max.x, min.y, max.z),
    Vec3(max.x, max.y, min.z),
    max
  };

  for (const auto& plane : planes)
  {
    bool allOutside = true;
    for (const auto& vertex : vertices)
    {
      if (vertex.dot(plane.getNormal()) - plane.getDistance() >= 0)
      {
        allOutside = false; // At least one vertex is inside or on the plane
        break;
      }
    }
    if (allOutside)
    {
      return false; // If all vertices are outside one plane, AABB is outside the frustum
    }
  }
  return true; // If all planes have at least one vertex inside or on the plane, the AABB is inside the frustum
}