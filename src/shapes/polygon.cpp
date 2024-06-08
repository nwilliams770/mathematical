#include "json.hpp"
#include "point.hpp"
#include "polygon.hpp"
#include "renderer.hpp"

Polygon::Polygon(const std::vector<Point>& points): points(points), pointCount(points.size()) {};

const std::vector<Point>& Polygon::getPoints() const { return points; }
void Polygon::setPoints(const std::vector<Point>& newPoints) { points = newPoints; }

json Polygon::toJSON() const
{
  json j;
  j[JsonKeys::COLOR] = color.toJSON();

  json vertices = json::array();
  for (const auto& point : points)
  {
    vertices.push_back({{JsonKeys::X, point.getX()}, {JsonKeys::Y, point.getY()}});
  }
  j[JsonKeys::VERTICES] = vertices;

  return j;
}

void Polygon::fromJSON(const json& j)
{
  setColor(Color::fromJSON(j[JsonKeys::COLOR]));
  points.clear();
  for (const auto& vertex : j[JsonKeys::VERTICES]) {
      points.emplace_back(Point(vertex[JsonKeys::X], vertex[JsonKeys::Y], getColor()));
      pointCount++;
  }
}

void Polygon::render(const Renderer& renderer) {
  renderer.setColor(color);
  renderer.renderPolygon(points);
};