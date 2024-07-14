#include "json.hpp"
#include "vec3.hpp"
#include "polygon.hpp"
#include "renderer.hpp"
#include "render_options.hpp"

Polygon::Polygon(const std::vector<Vec3>& points, const Color& color)
  : Object(color), points(points), pointCount(points.size()) {};

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

float Polygon::calculateDistance(const Camera& camera) const
{
  Vec3 centroid;
  for (const auto& point : points)
  {
    centroid = centroid + point;
  }
  centroid = centroid / static_cast<float>(points.size());

  return (centroid - camera.getPosition()).magnitude();
}


void Polygon::render(const Renderer& renderer, const Camera& camera, const RenderOptions& options) {
    float distance = calculateDistance(camera);
  int distanceOpacity = Renderer::calculateOpacity(distance, camera.getFrustum());
  int renderOpacity = (color.getOpacity() * distanceOpacity) / 255; // TODO const

  Color renderColor = color;
  renderColor.setOpacity(renderOpacity);

  renderer.setColor(renderColor);
  renderer.renderPolygon(points);

  renderBoundingBox(renderer, options);
}