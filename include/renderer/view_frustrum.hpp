#ifndef VIEW_FRUSTRUM_H
#define VIEW_FRUSTRUM_H

#include <array>
#include "camera.hpp"
#include "plane.hpp"
#include "vec3.hpp"

class ViewFrustrum
{
  public:
    ViewFrustrum(float fieldOfViewYRadians, float aspectRatio, float nearClip, float farClip);

    // Update the frustum based on the camera's position and orientation
    // Generate inward-pointing view frustrum planes
    void update(const Camera& camera);

    // Check if a point is inside the frustum
    bool isPointInside(const Vec3& point) const;
    bool isPointInsidePlane(const Vec3& point, const Plane& plane) const;

    // Check if an axis-aligned bounding box is inside the frustum
    bool isAABBInside(const Vec3& min, const Vec3& max) const;

  private:
    float fieldOfViewYRadians;
    float aspectRatio;
    float nearClip;
    float farClip;

    std::array<Plane, 6> planes;
    enum { Near = 0, Far, Left, Right, Top, Bottom };

    void updatePlane(int index, const Vec3& point, const Vec3& normal);
};

#endif