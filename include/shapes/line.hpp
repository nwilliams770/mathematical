#ifndef LINE_HPP
#define LINE_HPP

#include "object.hpp"
#include "point.hpp"

class Line : public Object {
  public:
    Line(Point start, Point end);

    const Point getStart() const;
    const Point getEnd() const;

    void setStart(Point newStart);
    void setEnd(Point newEnd);

    void render() override;

  private:
    Point start, end;
};

#endif