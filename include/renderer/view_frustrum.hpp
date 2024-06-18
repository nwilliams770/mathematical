#ifndef VIEW_FRUSTRUM_H
#define VIEW_FRUSTRUM_H

#include "camera.hpp"
#include "vec3.hpp"
#include <array>

class ViewFrustrum
{
  public:
    ViewFrustrum(float fieldOfViewY, float aspectRatio, float nearClip, float farClip);

    // Update the frustum based on the camera's position and orientation
    void update(const Camera& camera);

    // Check if a point is inside the frustum
    bool isPointInside(const Vec3& point) const;

    // Check if an axis-aligned bounding box is inside the frustum
    bool isAABBInside(const Vec3& min, const Vec3& max) const;

  private:
    float fieldOfViewY;
    float aspectRatio;
    float nearClip;
    float farClip;

    std::array<Plane, 6> planes;

    enum Pla
};

#endif