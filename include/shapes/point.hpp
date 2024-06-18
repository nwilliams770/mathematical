#ifndef POINT_HPP
#define POINT_HPP

#include "color.hpp"
#include "object.hpp" // because it inherits needs to know full definition
#include "json.hpp"
#include "vec3.hpp"

class Renderer; // Forward declaration
class RenderOptions; // Forward declaration

class Point : public Object {
  public:
    Point(float x = 0.0f, float y = 0.0f, float z = 0.0f, const Color& color = Color());
    ~Point() override = default; // Default destructor

    Vec3 getPosition() const { return position; }
    void setPosition(const Vec3& position) { this->position = position; }

    Vec3 getMin() const { return position; }
    Vec3 getMax() const { return position; }

    json toJSON() const override;
    void fromJSON(const json& j) override;

    void render(const Renderer& renderer, const RenderOptions& options) override;

  private:
    Vec3 position;
};

#endif