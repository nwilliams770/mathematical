#include "camera.hpp"
#include "view_frustum.hpp"
#include "renderer_constants.hpp"
#include "render_options.hpp"
#include "matrix4.hpp"
#include "plane.hpp"
#include "renderer.hpp"
#include "render_options.hpp"

#include <cmath>


ViewFrustum::ViewFrustum(float fieldOfViewYRadians, float aspectRatio, float nearClip, float farClip)
  : fieldOfViewYRadians(fieldOfViewYRadians), aspectRatio(aspectRatio), nearClip(nearClip), farClip(farClip)
{}

void ViewFrustum::update(const Camera& camera)
{
  updateViewProjectionMatrix(camera);
}

void ViewFrustum::updateViewProjectionMatrix(const Camera& camera)
{
  LOG("Updating view project matrix");
  Matrix4 viewMatrix = camera.getViewMatrix();
  LOG_ARGS("View Matrix Row 0:", viewMatrix(0, 0), viewMatrix(0, 1), viewMatrix(0, 2), viewMatrix(0, 3));
  LOG_ARGS("View Matrix Row 1:", viewMatrix(1, 0), viewMatrix(1, 1), viewMatrix(1, 2), viewMatrix(1, 3));
  LOG_ARGS("View Matrix Row 2:", viewMatrix(2, 0), viewMatrix(2, 1), viewMatrix(2, 2), viewMatrix(2, 3));
  LOG_ARGS("View Matrix Row 3:", viewMatrix(3, 0), viewMatrix(3, 1), viewMatrix(3, 2), viewMatrix(3, 3));



  Matrix4 perspectiveMatrix = getPerspectiveMatrix();
  LOG_ARGS("Perspective Matrix Row 0:", perspectiveMatrix(0, 0), perspectiveMatrix(0, 1), perspectiveMatrix(0, 2), perspectiveMatrix(0, 3));
  LOG_ARGS("Perspective Matrix Row 1:", perspectiveMatrix(1, 0), perspectiveMatrix(1, 1), perspectiveMatrix(1, 2), perspectiveMatrix(1, 3));
  LOG_ARGS("Perspective Matrix Row 2:", perspectiveMatrix(2, 0), perspectiveMatrix(2, 1), perspectiveMatrix(2, 2), perspectiveMatrix(2, 3));
  LOG_ARGS("Perspective Matrix Row 3:", perspectiveMatrix(3, 0), perspectiveMatrix(3, 1), perspectiveMatrix(3, 2), perspectiveMatrix(3, 3));

  viewProjectionMatrix = perspectiveMatrix * viewMatrix;

  LOG_ARGS("ViewProjection Matrix Row 0:", viewProjectionMatrix(0, 0), viewProjectionMatrix(0, 1), viewProjectionMatrix(0, 2), viewProjectionMatrix(0, 3));
  LOG_ARGS("ViewProjection Matrix Row 1:", viewProjectionMatrix(1, 0), viewProjectionMatrix(1, 1), viewProjectionMatrix(1, 2), viewProjectionMatrix(1, 3));
  LOG_ARGS("ViewProjection Matrix Row 2:", viewProjectionMatrix(2, 0), viewProjectionMatrix(2, 1), viewProjectionMatrix(2, 2), viewProjectionMatrix(2, 3));
  LOG_ARGS("ViewProjection Matrix Row 3:", viewProjectionMatrix(3, 0), viewProjectionMatrix(3, 1), viewProjectionMatrix(3, 2), viewProjectionMatrix(3, 3));
}

Matrix4 ViewFrustum::getPerspectiveMatrix() const {
  LOG_ARGS("Datums for perspective matrix:", "fieldOfViewYRadians", fieldOfViewYRadians,"aspectRatio", aspectRatio, "nearClip", nearClip, "farClip", farClip);

  Matrix4 perspectiveMatrix = Matrix4::perspective(fieldOfViewYRadians, aspectRatio, nearClip, farClip);

  return perspectiveMatrix;
}

std::array<Plane, 6> ViewFrustum::getFrustumPlanes() const
{
  const Matrix4& vp = viewProjectionMatrix;
  std::array<Plane, 6> planes = {
    Plane(Vec3(vp(0, 3) + vp(0, 0), vp(1, 3) + vp(1, 0), vp(2, 3) + vp(2, 0)), vp(3, 3) + vp(3, 0)),  // Left
    Plane(Vec3(vp(0, 3) - vp(0, 0), vp(1, 3) - vp(1, 0), vp(2, 3) - vp(2, 0)), vp(3, 3) - vp(3, 0)),  // Right
    Plane(Vec3(vp(0, 3) + vp(0, 1), vp(1, 3) + vp(1, 1), vp(2, 3) + vp(2, 1)), vp(3, 3) + vp(3, 1)),  // Bottom
    Plane(Vec3(vp(0, 3) - vp(0, 1), vp(1, 3) - vp(1, 1), vp(2, 3) - vp(2, 1)), vp(3, 3) - vp(3, 1)),  // Top
    Plane(Vec3(vp(0, 2), vp(1, 2), vp(2, 2)), vp(3, 2)),                                             // Near
    Plane(Vec3(vp(0, 3) - vp(0, 2), vp(1, 3) - vp(1, 2), vp(2, 3) - vp(2, 2)), vp(3, 3) - vp(3, 2))   // Far
  };

  for (auto& plane : planes) {
    plane.normalize();
  }

  return planes;
}

void ViewFrustum::render(const Renderer& renderer, const RenderOptions& options) const {
  if (!options.renderFrustum) return;

  // // Set color for frustum rendering
  // renderer.setColor(RendererConstants::FRUSTRUM_COLOR);

  // std::vector<Vec3> corners;
  // getCorners(corners);

  // // Draw frustum edges
  // renderer.renderPolygon(corners);
}