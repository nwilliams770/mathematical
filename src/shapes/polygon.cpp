#include "polygon.hpp"

Polygon::Polygon(const std::vector<Point>& points): points(points) {};

const std::vector<Point>& Polygon::getPoints() const { return points; }
void Polygon::setPoints(const std::vector<Point>& newPoints) { points = newPoints; }
