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

    const Vec3 getStart() const;
    const Vec3 getEnd() const;

    void setStart(Vec3 newStart);
    void setEnd(Vec3 newEnd);

    Vec3 getMin() const override;
    Vec3 getMax() const override;

    json toJSON() const override;
    void fromJSON(const json& j) override;

    void render(const Renderer& renderer, const RenderOptions& options) override;

  private:
    Vec3 start, end;
};

#endif