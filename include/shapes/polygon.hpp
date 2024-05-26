#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <vector>
#include "object.hpp"

class Point; // Forward declaration of Renderer
class Renderer; // Forward declaration of Renderer

class Polygon : public Object {
  public:
    Polygon(const std::vector<Point>& points);
    ~Polygon() override;

    const std::vector<Point>& getPoints() const;
    void setPoints(const std::vector<Point>& newPoints);

    void render(const Renderer& renderer) override;

  private:
    std::vector<Point> points;
};

#endif