#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <vector>
#include "object.hpp"
#include "vec3.hpp"

class Renderer; // Forward declaration
class RenderOptions; // Forward declaration

class Polygon : public Object {
  public:
    Polygon(const std::vector<Vec3>& points = {});
    ~Polygon() override = default; // Default destructor

    const std::vector<Vec3>& getPoints() const { return points; }
    void setPoints(const std::vector<Vec3>& points) { this->points = points; }

    Vec3 getMin() const
    {
      Vec3 min = points[0];
      for (const auto& point : points)
      {
        if (point.x < min.x) min.x = point.x;
        if (point.y < min.y) min.y = point.y;
        if (point.z < min.z) min.z = point.z;
      }

      return min;
    }

    Vec3 getMax() const
    {
      Vec3 max = points[0];
      for (const auto& point : points)
      {
        if (point.x > max.x) max.x = point.x;
        if (point.y > max.y) max.y = point.y;
        if (point.z > max.z) max.z = point.z;
      }
      return max;
    }

    json toJSON() const override;
    void fromJSON(const json& j) override;

    void render(const Renderer& renderer, const RenderOptions& options) override;

  private:
    std::vector<Vec3> points;
    // TODO: remove?
    int pointCount;
};

#endif