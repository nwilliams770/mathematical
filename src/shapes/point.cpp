#include "object.hpp"
#include "point.hpp"
#include "renderer.hpp"
#include "logging.hpp"

Point::Point(float x, float y, float z, const Color& color) : Object(color), position(x, y, z) {}

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

void Point::render(const Renderer& renderer) {
  renderer.setColor(color);
  renderer.renderPoint(position.x, position.y, position.z);
};