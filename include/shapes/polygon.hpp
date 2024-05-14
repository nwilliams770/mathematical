#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <vector>
#include "object.hpp"
#include "point.hpp"

class Polygon : public Object {
  public:
    Polygon(const std::vector<Point>& points);

    const std::vector<Point>& getPoints() const;
    void setPoints(const std::vector<Point>& newPoints);

    void render() override;

  private:
    std::vector<Point> points;
};

#endif