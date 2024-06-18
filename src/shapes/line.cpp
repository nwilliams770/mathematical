#include "line.hpp"
#include "renderer.hpp"
#include "vec3.hpp"

Line::Line(Vec3 start, Vec3 end) : start(start), end(end) {}

const Vec3 Line::getStart() const { return start; }
const Vec3 Line::getEnd() const { return end; }

void Line::setStart(Vec3 newStart) { start = newStart; }
void Line::setEnd(Vec3 newEnd) { end = newEnd; }

Vec3 Line::getMin() const
{
  return Vec3(
    std::min(start.x, end.x),
    std::min(start.y, end.y),
    std::min(start.z, end.z)
  );
}

Vec3 Line::getMax() const
{
  return Vec3(
    std::max(start.x, end.x),
    std::max(start.y, end.y),
    std::max(start.z, end.z)
  );
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


void Line::render(const Renderer& renderer, const RenderOptions& options) {
  renderer.setColor(color);
  renderer.renderLine(start, end);
  renderBoundingBox(renderer, options);
};