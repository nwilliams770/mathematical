#include "json.hpp"
#include "vec3.hpp"
#include "polygon.hpp"
#include "renderer.hpp"
#include "render_options.hpp"

Polygon::Polygon(const std::vector<Vec3>& points): points(points), pointCount(points.size()) {};

const std::vector<Vec3>& Polygon::getPoints() const { return points; }
void Polygon::setPoints(const std::vector<Vec3>& newPoints) { points = newPoints; }

Vec3 Polygon::getMin() const
{
  Vec3 min = points[0];
  for (const auto& point : points)
  {
   if (point.x < min.x) min.x = point.x;
   if (point.y < min.y) min.y = point.y;
   if (point.z < min.z) min.z = point.z;
  }

  return min;
}

Vec3 Polygon::getMax() const
{
  Vec3 max = points[0];
  for (const auto& point : points)
  {
   if (point.x > max.x) max.x = point.x;
   if (point.y > max.y) max.y = point.y;
   if (point.z > max.z) max.z = point.z;
  }

  return max;
}

json Polygon::toJSON() const
{
  json j;
  j[JsonKeys::COLOR] = color.toJSON();

  json vertices = json::array();
  for (const auto& point : points)
  {
    vertices.push_back({{JsonKeys::X, point.x}, {JsonKeys::Y, point.y}, {JsonKeys::Z, point.z}});
  }
  j[JsonKeys::VERTICES] = vertices;

  return j;
}

void Polygon::fromJSON(const json& j)
{
  setColor(Color::fromJSON(j[JsonKeys::COLOR]));
  points.clear();
  for (const auto& vertex : j[JsonKeys::VERTICES]) {
      points.emplace_back(Vec3(vertex[JsonKeys::X], vertex[JsonKeys::Y], vertex[JsonKeys::Z]));
      pointCount++;
  }
}

void Polygon::render(const Renderer& renderer, const RenderOptions& options) {
  renderer.setColor(color);
  renderer.renderPolygon(points);
  renderBoundingBox(renderer, options);
};