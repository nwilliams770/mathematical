#include "object.hpp"
#include "vec3.hpp"
#include "renderer.hpp"
#include "renderer_constants.hpp"

void Object::renderBoundingBox(const Renderer& renderer, const RenderOptions& options) const
{
  if (!options.renderBoundingBoxes) return;

    Vec3 min = getMin();
    Vec3 max = getMax();
    std::array<Vec3, 8> corners = {
      Vec3(min.x, min.y, min.z),
      Vec3(max.x, min.y, min.z),
      Vec3(max.x, max.y, min.z),
      Vec3(min.x, max.y, min.z),
      Vec3(min.x, min.y, max.z),
      Vec3(max.x, min.y, max.z),
      Vec3(max.x, max.y, max.z),
      Vec3(min.x, max.y, max.z),
    };

    renderer.setColor(RendererConstants::BOUNDING_BOX_COLOR);
    // Bottom face
    renderer.renderLine(corners[0], corners[1]);
    renderer.renderLine(corners[1], corners[2]);
    renderer.renderLine(corners[2], corners[3]);
    renderer.renderLine(corners[3], corners[0]);

    // Top face
    renderer.renderLine(corners[4], corners[5]);
    renderer.renderLine(corners[5], corners[6]);
    renderer.renderLine(corners[6], corners[7]);
    renderer.renderLine(corners[7], corners[4]);

    // Vertical edges
    renderer.renderLine(corners[0], corners[4]);
    renderer.renderLine(corners[1], corners[5]);
    renderer.renderLine(corners[2], corners[6]);
    renderer.renderLine(corners[3], corners[7]);
}