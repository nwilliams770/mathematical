#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <vector>
#include "object.hpp"

class Point; // Forward declaration of Renderer
class Renderer; // Forward declaration of Renderer

class Polygon : public Object {
  public:
    Polygon(const std::vector<Point>& points = {});
    ~Polygon() override = default; // Default destructor

    const std::vector<Point>& getPoints() const;
    void setPoints(const std::vector<Point>& newPoints);

    json toJSON() const override;
    void fromJSON(const json& j) override;

    void render(const Renderer& renderer) override;

  private:
    std::vector<Point> points;
    // TODO: remove?
    int pointCount;
};

#endif