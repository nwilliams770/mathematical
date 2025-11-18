#include <cmath>
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

std::vector<Vec3> Line::toPolygon() const
{
  float halfStrokeWeight = strokeWeight / 2.0f;
  Vec3 direction = (end - start).normalize();

  Vec3 arbitraryVector;
  if (fabs(direction.x) < 0.1f && fabs(direction.y) < 0.1f) {
    // Use Y axis if direction is close to Z axis
    arbitraryVector = Vec3(0.0f, 1.0f, 0.0f);
  } else {
    arbitraryVector = Vec3(0.0f, 0.0f, 1.0f);
  }

  Vec3 perpendicular = direction.cross(arbitraryVector).normalized();
  Vec3 offset = perpendicular * halfStrokeWeight;

  return {
    start - offset,
    start + offset,
    end + offset,
    end - offset
  };
}


json Line::toJSON() const
{
  return json{
    {JsonKeys::VERTICES,
      {{JsonKeys::X, start.x}, {JsonKeys::Y, start.y}, {JsonKeys::Z, start.z},},
      {{JsonKeys::X, end.x}, {JsonKeys::Y, end.y}, {JsonKeys::Z, end.z},},
    },
    {JsonKeys::STROKE_WEIGHT, strokeWeight},
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
  strokeWeight = j[JsonKeys::STROKE_WEIGHT];
  setColor(Color::fromJSON(j[JsonKeys::COLOR]));
}