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

std::vector<Vec3> Point::toPolygon() const
{
  LOG_ARGS("Point position", position.x, position.y, position.z, "Size:", size);

  // Position for drawing represents center of the point
  float halfSize = size / 2.0f;
  LOG_ARGS("Polygon position 1", position.x - halfSize, position.y - halfSize, position.z);
  LOG_ARGS("Polygon position 2", position.x + halfSize, position.y - halfSize, position.z);
  LOG_ARGS("Polygon position 3", position.x + halfSize, position.y + halfSize, position.z);
  LOG_ARGS("Polygon position 4", position.x - halfSize, position.y + halfSize, position.z);
  return {
      Vec3(position.x - halfSize, position.y - halfSize, position.z),
      Vec3(position.x + halfSize, position.y - halfSize, position.z),
      Vec3(position.x + halfSize, position.y + halfSize, position.z),
      Vec3(position.x - halfSize, position.y + halfSize, position.z)
  };
}

json Point::toJSON() const
{
  return json{
    {JsonKeys::VERTICES, {{JsonKeys::X, position.x}, {JsonKeys::Y, position.y}, {JsonKeys::Z, position.z} }},
    {JsonKeys::SIZE, size},
    {JsonKeys::COLOR, color.toJSON()},
  };
}

void Point::fromJSON(const json& j)
{
  position.x = j[JsonKeys::VERTICES][0][JsonKeys::X];
  position.y = j[JsonKeys::VERTICES][0][JsonKeys::Y];
  position.z = j[JsonKeys::VERTICES][0][JsonKeys::Z];
  size = j[JsonKeys::SIZE];
  setColor(Color::fromJSON(j[JsonKeys::COLOR]));
}