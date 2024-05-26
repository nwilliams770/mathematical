#include "point.hpp"
#include "polygon.hpp"
#include "renderer.hpp"

Polygon::Polygon(const std::vector<Point>& points): points(points) {};
Polygon::~Polygon() {};

const std::vector<Point>& Polygon::getPoints() const { return points; }
void Polygon::setPoints(const std::vector<Point>& newPoints) { points = newPoints; }
void Polygon::render(const Renderer& renderer) {};