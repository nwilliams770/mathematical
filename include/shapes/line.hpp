#ifndef LINE_HPP
#define LINE_HPP

#include "object.hpp"
#include "vec3.hpp"
#include "render_options.hpp"
#include "json.hpp"

class Renderer; // Forward declaration
class RenderOptions; // Forward declaration

class Line : public Object {
  public:
    Line(Vec3 start = Vec3(), Vec3 end = Vec3());
    ~Line() override = default; // Default destructor

    const Vec3 getStart() const { return start; }
    const Vec3 getEnd() const { return end; }

    void setStart(Vec3 start) { this->start = start; }
    void setEnd(Vec3 end) { this->end = end; }

    Vec3 getMin() const override
    {
      return Vec3(
        std::min(start.x, end.x),
        std::min(start.y, end.y),
        std::min(start.z, end.z)
      );
    }

    Vec3 getMax() const override
    {
      return Vec3(
        std::max(start.x, end.x),
        std::max(start.y, end.y),
        std::max(start.z, end.z)
      );
    }

    json toJSON() const override;
    void fromJSON(const json& j) override;

    void render(const Renderer& renderer, const RenderOptions& options) override;

  private:
    Vec3 start, end;
};

#endif