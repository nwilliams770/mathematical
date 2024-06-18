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

    const std::vector<Vec3>& getPoints() const;
    void setPoints(const std::vector<Vec3>& newPoints);

    Vec3 getMin() const override;
    Vec3 getMax() const override;

    json toJSON() const override;
    void fromJSON(const json& j) override;

    void render(const Renderer& renderer, const RenderOptions& options) override;

  private:
    std::vector<Vec3> points;
    // TODO: remove?
    int pointCount;
};

#endif