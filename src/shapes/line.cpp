#include "line.hpp"
#include "renderer.hpp"
#include "vec3.hpp"

Line::Line(Vec3 start, Vec3 end, const Color& color, float strokeWeight)
  : Object(color), start(start), end(end), strokeWeight(strokeWeight) {}

float Line::calculateDistance(const Camera& camera) const
{
  float distanceStart = (start - camera.getPosition()).magnitude();
  float distanceEnd = (end - camera.getPosition()).magnitude();

  return (distanceStart + distanceEnd) / 2.0f;
}


json Line::toJSON() const
{
  return json{
    {JsonKeys::VERTICES,
      {{JsonKeys::X, start.x}, {JsonKeys::Y, start.y}, {JsonKeys::Z, start.z},},
      {{JsonKeys::X, end.x}, {JsonKeys::Y, end.y}, {JsonKeys::Z, end.z},},
    },
    {JsonKeys::COLOR, color.toJSON()},
  };
}

void Line::fromJSON(const json& j)
{
  start = Vec3(
    j[JsonKeys::VERTICES][0][JsonKeys::X], j[JsonKeys::VERTICES][0][JsonKeys::Y], j[JsonKeys::VERTICES][0][JsonKeys::Z]
  );
  end = Vec3(
    j[JsonKeys::VERTICES][1][JsonKeys::X], j[JsonKeys::VERTICES][1][JsonKeys::Y], j[JsonKeys::VERTICES][1][JsonKeys::Z]
  );
  setColor(Color::fromJSON(j[JsonKeys::COLOR]));
}


void Line::render(const Renderer& renderer, const Camera& camera, const RenderOptions& options) {
  float distance = calculateDistance(camera);
  int distanceOpacity = Renderer::calculateOpacity(distance, camera.getFrustum());
  int renderOpacity = (color.getOpacity() * distanceOpacity) / 255; // TODO const

  Color renderColor = color;
  renderColor.setOpacity(renderOpacity);

  renderer.setColor(renderColor);
  renderer.renderLine(start, end, strokeWeight);

  renderBoundingBox(renderer, options);
};