#include "json.hpp"
#include "vec3.hpp"
#include "polygon.hpp"
#include "renderer.hpp"
#include "render_options.hpp"

Polygon::Polygon(const std::vector<Vec3>& points): points(points), pointCount(points.size()) {};

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
}