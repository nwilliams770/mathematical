#include "point.hpp"

Point::Point(double x, double y) : x(x), y(y) {}

const double Point::getX() const { return x; }
const double Point::getY() const { return y; }

void Point::setX(double newX) { x = newX; }
void Point::setY(double newY) { y = newY; }