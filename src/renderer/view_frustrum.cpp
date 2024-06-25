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
// Generate outward-pointing view frustrum planes
void ViewFrustrum::update(const Camera& camera)
{
  Vec3 cameraPosition = camera.getPosition();
  Vec3 cameraDirection = camera.getDirection().normalized();
  Vec3 cameraUp = camera.getUp().normalized();
  Vec3 cameraRight = cameraDirection.cross(cameraUp).normalized();

  Vec3 nearClipCenter = cameraPosition + cameraDirection * nearClip;
  Vec3 farClipCenter = cameraPosition + cameraDirection * farClip;

  LOG_ARGS("Camera Position: " ,cameraPosition.x ,", " ,cameraPosition.y ,", " ,cameraPosition.z);
  LOG_ARGS("Camera Direction: " ,cameraDirection.x ,", " ,cameraDirection.y ,", " ,cameraDirection.z);
  LOG_ARGS("Near Clip Center: " ,nearClipCenter.x ,", " ,nearClipCenter.y ,", " ,nearClipCenter.z);
  LOG_ARGS("Far Clip Center: " ,farClipCenter.x ,", " ,farClipCenter.y ,", " ,farClipCenter.z);

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

  LOG_ARGS("Near Clip Top Left: " ,nearClipTopLeft.x ,", " ,nearClipTopLeft.y ,", " ,nearClipTopLeft.z);
  LOG_ARGS("Near Clip Bottom Right: " ,nearClipBottomRight.x ,", " ,nearClipBottomRight.y ,", " ,nearClipBottomRight.z);

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


  // Generate vector pointing from nearClipTopLeft to nearClipBottomLeft (downward)
  // and cross by vector pointing from nearClipTopLeft to farClipTopLeft (forward from the POV of the camera)
  // Crossing them, using right-hand rule results in a vector normal of the left plane
  // pointing outwards of the view frustrum
  Vec3 leftPlaneNormal = (farClipTopLeft - nearClipTopLeft).cross(nearClipBottomLeft - nearClipTopLeft).normalized();
  updatePlane(Left, nearClipTopLeft, leftPlaneNormal);

  // Generate vector pointing from nearClipTopRight to nearClipBottomRight (downward)
  // and cross by vector pointing from farClipTopRight to nearClipTopRight (backward from the POV of the camera)
  // Crossing them, using right-hand rule results in a vector normal of the right plane
  // pointing outwards of the view frustrum
  Vec3 rightPlaneNormal = (nearClipBottomRight - nearClipTopRight).cross(farClipTopRight - nearClipTopRight).normalized();
  updatePlane(Right, nearClipTopRight, rightPlaneNormal);

  // Generate vector pointing from nearClipTopRight to nearClipTopLeft (leftward)
  // and cross by vector pointing from nearClipTopLeft to farClipTopLeft (forward from the POV of the camera)
  // Crossing them, using right-hand rule results in a vector normal of the top plane
  // pointing outwards of the view frustrum
  Vec3 topPlaneNormal = (nearClipTopRight - nearClipTopLeft).cross(farClipTopLeft - nearClipTopLeft).normalized();
  updatePlane(Top, nearClipTopLeft, topPlaneNormal);

  // Generate vector pointing from nearClipBottomLeft to nearClipBottomRight (rightward)
  // and cross by vector pointing from nearClipBottomLeft to farClipBottomLeft (forward from the POV of the camera)
  // Crossing them, using right-hand rule results in a vector normal of the bottom plane
  // pointing outwards of the view frustrum
  Vec3 bottomPlaneNormal = (nearClipBottomRight - nearClipBottomLeft).cross(farClipBottomLeft - nearClipBottomLeft).normalized();
  updatePlane(Bottom, nearClipBottomLeft, bottomPlaneNormal);

  LOG_ARGS("Left Plane Normal: ", leftPlaneNormal.x, ", ", leftPlaneNormal.y, ", ", leftPlaneNormal.z);
  LOG_ARGS("Right Plane Normal: ", rightPlaneNormal.x, ", ", rightPlaneNormal.y, ", ", rightPlaneNormal.z);
  LOG_ARGS("Top Plane Normal: ", topPlaneNormal.x, ", ", topPlaneNormal.y, ", ", topPlaneNormal.z);
  LOG_ARGS("Bottom Plane Normal: ", bottomPlaneNormal.x, ", ", bottomPlaneNormal.y, ", ", bottomPlaneNormal.z);
}

// Check if a point is inside the frustum
bool ViewFrustrum::isPointInside(const Vec3& point) const
{
  for (const auto& plane : planes)
  {
    if (!isPointInsidePlane(point, plane)) return false;
  }
  return true;
}

bool ViewFrustrum::isPointInsidePlane(const Vec3& point, const Plane& plane) const
{
  float distance = point.dot(plane.getNormal()) - plane.getDistance();
  // LOG_ARGS("Plane Normal (x, y, z): ", plane.getNormal().x, plane.getNormal().y, plane.getNormal().z);
  // LOG_ARGS("Plane Distance: ", plane.getDistance());
  // LOG_ARGS("Point (x, y, z): ", point.x, point.y, point.z);
  // LOG_ARGS("Distance from point to plane: ", distance);
  // > 0 - point is on the 'positive side' - in the direction of the normal
  // = 0 - point is on the plane
  // < 0 - point is on the 'negative side' - opposite direction of the normal
  return distance >= 0;
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
      if (isPointInsidePlane(vertex, plane))
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

void ViewFrustrum::updatePlane(int index, const Vec3& point, const Vec3& normal)
{
  planes[index].setFromPointNormal(point, normal);
}