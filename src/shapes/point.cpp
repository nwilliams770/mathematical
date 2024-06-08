#include "object.hpp"
#include "point.hpp"
#include "renderer.hpp"
#include "logging.hpp"

Point::Point(double x, double y, const Color& color) : Object(color), x(x), y(y) {}

const double Point::getX() const { return x; }
const double Point::getY() const { return y; }

void Point::setX(double newX) { x = newX; }
void Point::setY(double newY) { y = newY; }

json Point::toJSON() const
{
  return json{
    {JsonKeys::VERTICES, {{JsonKeys::X, x}, {JsonKeys::Y, y}}},
    {JsonKeys::COLOR, color.toJSON()},
  };
}

void Point::fromJSON(const json& j)
{
  x = j[JsonKeys::VERTICES][0][JsonKeys::X];
  y = j[JsonKeys::VERTICES][0][JsonKeys::Y];
  setColor(Color::fromJSON(j[JsonKeys::COLOR]));
}

void Point::render(const Renderer& renderer) {
  renderer.setColor(color);
  renderer.renderPoint(x, y);
};