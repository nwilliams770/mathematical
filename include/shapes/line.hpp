#ifndef LINE_HPP
#define LINE_HPP

#include "object.hpp"
#include "point.hpp"

class Renderer; // Forward declaration of Renderer

class Line : public Object {
  public:
    Line(Point start = Point(), Point end = Point());
    ~Line() override = default; // Default destructor

    const Point getStart() const;
    const Point getEnd() const;

    void setStart(Point newStart);
    void setEnd(Point newEnd);

    json toJSON() const override;
    void fromJSON(const json& j) override;

    void render(const Renderer& renderer) override;

  private:
    Point start, end;
};

#endif