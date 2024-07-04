#ifndef VIEW_FRUSTRUM_H
#define VIEW_FRUSTRUM_H

#include <array>
#include "camera.hpp"

#include "vec3.hpp"
#include "matrix4.hpp"

class Renderer;
class RenderOptions;

class ViewFrustum
{
  public:
    ViewFrustum(float fieldOfViewYRadians, float aspectRatio, float nearClip, float farClip);

    void update(const Camera& camera);
    // Check if an axis-aligned bounding box is inside the frustum
    bool isAABBInside(const Vec3& min, const Vec3& max) const;

    Matrix4 getProjectionMatrix() const;
    void updateViewProjectionMatrix(const Camera& camera);
    Matrix4 getViewProjectionMatrix() const;

    void render(const Renderer& renderer, const RenderOptions& options) const;

  private:
    float fieldOfViewYRadians;
    float aspectRatio;
    float nearClip;
    float farClip;

    Matrix4 viewProjectionMatrix;
};

#endif