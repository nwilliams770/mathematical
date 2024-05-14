#include "line.hpp"

Line::Line(Point start, Point end) : start(start), end(end) {}

const Point Line::getStart() const { return start; }
const Point Line::getEnd() const { return end; }

void Line::setStart(Point newStart) { start = newStart; }
void Line::setEnd(Point newEnd) { end = newEnd; }