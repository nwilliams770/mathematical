#include "line.hpp"
#include "point.hpp"
#include "renderer.hpp"

Line::Line(Point start, Point end) : start(start), end(end) {}

const Point Line::getStart() const { return start; }
const Point Line::getEnd() const { return end; }

void Line::setStart(Point newStart) { start = newStart; }
void Line::setEnd(Point newEnd) { end = newEnd; }

json Line::toJSON() const
{
  return json{
    {JsonKeys::VERTICES,
      {{JsonKeys::X, start.getX()}, {JsonKeys::Y, start.getY()}},
      {{JsonKeys::X, end.getX()}, {JsonKeys::Y, end.getY()}},
    },
    {JsonKeys::COLOR, color.toJSON()},
  };
}

void Line::fromJSON(const json& j)
{
  start = Point(
    j[JsonKeys::VERTICES][0][JsonKeys::X], j[JsonKeys::VERTICES][0][JsonKeys::Y]
  );
  end = Point(
    j[JsonKeys::VERTICES][1][JsonKeys::X], j[JsonKeys::VERTICES][1][JsonKeys::Y]
  );
  setColor(Color::fromJSON(j[JsonKeys::COLOR]));
}


void Line::render(const Renderer& renderer) {
  renderer.setColor(color);
  renderer.renderLine(start.getX(), start.getY(), end.getX(), end.getY());
};