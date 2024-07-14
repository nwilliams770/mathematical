#include "object.hpp"
#include "point.hpp"
#include "renderer.hpp"
#include "logging.hpp"
#include "vec3.hpp"

Point::Point(float x, float y, float z, const Color& color, float size)
  : Object(color), position(x, y, z), size(size) {}

float Point::calculateDistance(const Camera& camera) const
{
  return (position - camera.getPosition()).magnitude();
}

json Point::toJSON() const
{
  return json{
    {JsonKeys::VERTICES, {{JsonKeys::X, position.x}, {JsonKeys::Y, position.y}, {JsonKeys::Z, position.z} }},
    {JsonKeys::COLOR, color.toJSON()},
  };
}

void Point::fromJSON(const json& j)
{
  position.x = j[JsonKeys::VERTICES][0][JsonKeys::X];
  position.y = j[JsonKeys::VERTICES][0][JsonKeys::Y];
  position.z = j[JsonKeys::VERTICES][0][JsonKeys::Z];
  setColor(Color::fromJSON(j[JsonKeys::COLOR]));
}

void Point::render(const Renderer& renderer, const Camera& camera,const RenderOptions& options) {
  float distance = calculateDistance(camera);
  int distanceOpacity = Renderer::calculateOpacity(distance, camera.getFrustum());
  int renderOpacity = (color.getOpacity() * distanceOpacity) / 255; // TODO const

  Color renderColor = color;
  renderColor.setOpacity(renderOpacity);

  renderer.setColor(renderColor);
  renderer.renderPoint(position, size);

  renderBoundingBox(renderer, options);
}