#include "camera.hpp"
#include "view_frustum.hpp"
#include "renderer_constants.hpp"
#include "render_options.hpp"
#include "matrix4.hpp"


#include <cmath>


ViewFrustum::ViewFrustum(float fieldOfViewYRadians, float aspectRatio, float nearClip, float farClip)
  : fieldOfViewYRadians(fieldOfViewYRadians), aspectRatio(aspectRatio), nearClip(nearClip), farClip(farClip)
{}

void ViewFrustum::update(const Camera& camera) {
  updateViewProjectionMatrix(camera);
}

void ViewFrustum::updateViewProjectionMatrix(const Camera& camera) {
  LOG("Updating view project matrix");
  Matrix4 viewMatrix = camera.getViewMatrix();
  LOG_ARGS("viewMatrix Row 0:", viewMatrix(0, 0), viewMatrix(0, 1), viewMatrix(0, 2), viewMatrix(0, 3));

  Matrix4 projectionMatrix = getProjectionMatrix();
  LOG_ARGS("projectionMatrix Row 0:", projectionMatrix(0, 0), projectionMatrix(0, 1), projectionMatrix(0, 2), projectionMatrix(0, 3));

  viewProjectionMatrix = projectionMatrix * viewMatrix;
  LOG_ARGS("viewProjectionMatrix Row 0:", viewProjectionMatrix(0, 0), viewProjectionMatrix(0, 1), viewProjectionMatrix(0, 2), viewProjectionMatrix(0, 3));
  LOG("Updated view project matrix");

}

Matrix4 ViewFrustum::getViewProjectionMatrix() const {
  return viewProjectionMatrix;
}

Matrix4 ViewFrustum::getProjectionMatrix() const {
  LOG_ARGS("Datums for perspective matrix:", "fieldOfViewYRadians", fieldOfViewYRadians,"aspectRatio", aspectRatio, "nearClip", nearClip, "farClip", farClip);

  Matrix4 perspectiveMatrix = Matrix4::perspective(fieldOfViewYRadians, aspectRatio, nearClip, farClip);

  LOG_ARGS("perspectiveMatrix Row 0:", perspectiveMatrix(0, 0), perspectiveMatrix(0, 1), perspectiveMatrix(0, 2), perspectiveMatrix(0, 3));
  LOG_ARGS("perspectiveMatrix Row 1:", perspectiveMatrix(1, 0), perspectiveMatrix(1, 1), perspectiveMatrix(1, 2), perspectiveMatrix(1, 3));
  LOG_ARGS("perspectiveMatrix Row 2:", perspectiveMatrix(2, 0), perspectiveMatrix(2, 1), perspectiveMatrix(2, 2), perspectiveMatrix(2, 3));
  LOG_ARGS("perspectiveMatrix Row 3:", perspectiveMatrix(3, 0), perspectiveMatrix(3, 1), perspectiveMatrix(3, 2), perspectiveMatrix(3, 3));
  return perspectiveMatrix;
}

// Check if an axis-aligned bounding box is inside the frustum
bool ViewFrustum::isAABBInside(const Vec3& min, const Vec3& max) const
{
  std::array<Vec3, 8> worldSpaceVertices = {
    min,
    Vec3(min.x, min.y, max.z),
    Vec3(min.x, max.y, min.z),
    Vec3(min.x, max.y, max.z),
    Vec3(max.x, min.y, min.z),
    Vec3(max.x, min.y, max.z),
    Vec3(max.x, max.y, min.z),
    max
  };

      // Log the view-projection matrix row by row
    LOG_ARGS("ViewProjectionMatrix Row 0:", viewProjectionMatrix(0, 0), viewProjectionMatrix(0, 1), viewProjectionMatrix(0, 2), viewProjectionMatrix(0, 3));
    LOG_ARGS("ViewProjectionMatrix Row 1:", viewProjectionMatrix(1, 0), viewProjectionMatrix(1, 1), viewProjectionMatrix(1, 2), viewProjectionMatrix(1, 3));
    LOG_ARGS("ViewProjectionMatrix Row 2:", viewProjectionMatrix(2, 0), viewProjectionMatrix(2, 1), viewProjectionMatrix(2, 2), viewProjectionMatrix(2, 3));
    LOG_ARGS("ViewProjectionMatrix Row 3:", viewProjectionMatrix(3, 0), viewProjectionMatrix(3, 1), viewProjectionMatrix(3, 2), viewProjectionMatrix(3, 3));

    for (const auto& worldSpaceVertex : worldSpaceVertices) {
      LOG_ARGS("World space vertex:", worldSpaceVertex.x, worldSpaceVertex.y, worldSpaceVertex.z);

      Vec4 clipSpaceVertex = viewProjectionMatrix * Vec4(worldSpaceVertex, 1.0f);

      LOG_ARGS("Clip space vertex:", clipSpaceVertex.x, clipSpaceVertex.y, clipSpaceVertex.z);

      if (clipSpaceVertex.x < -clipSpaceVertex.w || clipSpaceVertex.x > clipSpaceVertex.w ||
          clipSpaceVertex.y < -clipSpaceVertex.w || clipSpaceVertex.y > clipSpaceVertex.w ||
          clipSpaceVertex.z < -clipSpaceVertex.w || clipSpaceVertex.z > clipSpaceVertex.w)
      {
        LOG_ARGS("Vertex outside frustum:", clipSpaceVertex.x, clipSpaceVertex.y, clipSpaceVertex.z, clipSpaceVertex.w);

        return false;
      }
    }
  return true;
}

// void ViewFrustum::render(const Renderer& renderer, const RenderOptions& options) const {
//     if (!options.renderFrustrum) return;

//     // Set color for frustum rendering
//     renderer.setColor(RendererConstants::FRUSTRUM_COLOR);

//     std::vector<Vec3> corners;
//     getCorners(corners);

//     // Draw frustum edges
//     renderer.renderFrustum(corners);

//     // Set color for normals rendering
//     renderer.setColor(RendererConstants::DEBUG_COLOR);

//     std::vector<std::pair<Vec3, Vec3>> normals;
//     getNormals(normals);
//     for (const auto& normal : normals) {
//         renderer.renderNormal(normal.first, normal.second);
//     }
// }