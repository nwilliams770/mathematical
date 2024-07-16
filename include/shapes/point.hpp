#ifndef POINT_HPP
#define POINT_HPP

#include "color.hpp"
#include "object.hpp" // because it inherits needs to know full definition
#include "json.hpp"
#include "vec3.hpp"
#include "camera.hpp"

class Renderer; // Forward declaration
class RenderOptions; // Forward declaration

const float DEFAULT_POINT_SIZE = 1.0f;

class Point : public Object {
  public:
    Point(float x = 0.0f, float y = 0.0f, float z = 0.0f, const Color& color = Color(), float size = DEFAULT_POINT_SIZE);
    ~Point() override = default; // Default destructor

    Vec3 getPosition() const { return position; }
    void setPosition(const Vec3& position) { this->position = position; }

    Vec3 getMin() const override { return position; }
    Vec3 getMax() const override { return position; }

    float calculateDistance(const Camera& camera) const override;

    std::vector<Vec3> toPolygon() const override;

    json toJSON() const override;
    void fromJSON(const json& j) override;

    void render(const Renderer& renderer, const Camera& camera,const RenderOptions& options) override;

  private:
    Vec3 position;
    float size;
};

#endif